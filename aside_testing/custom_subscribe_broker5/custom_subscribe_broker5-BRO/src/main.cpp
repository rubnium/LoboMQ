#include <Arduino.h>
#include <esp_now.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>
#include "BrokerTopic.h"

#define SUBSCRIBETASKS 2
#define UNSUBSCRIBETASKS 2
#define PUBLISHTASKS 1

typedef struct {
  int number;
} PayloadStruct;

typedef struct {
  SubscribeAnnouncement *subAnnounce;
  const uint8_t *mac;
} SubscribeTaskParams;

typedef struct {
  UnsubscribeAnnouncement *unsubAnnounce;
  const uint8_t *mac;
} UnsubscribeTaskParams;

typedef struct {
  PublishContent *pubContent;
  const uint8_t *mac;
} PublishTaskParams;

std::vector<BrokerTopic> topicsVector; //each topic has messages and subscribers

//Message queues
QueueHandle_t subMsgQueue;
QueueHandle_t unsubMsgQueue;
QueueHandle_t pubMsgQueue;

bool hasWildcard(const char topic[]) {
  for (int i = 0; i < strlen(topic); i++) {
    if (topic[i] == '+' || topic[i] == '#')
      return true;
  }
  return false;
}

void SubscribeTask(void *parameter) {
  for (;;) {
    SubscribeTaskParams *params;
    if (xQueueReceive(subMsgQueue, &params, portMAX_DELAY) == pdPASS) { //gets the message from the queue
      SubscribeAnnouncement *subAnnounce = params->subAnnounce;
      const uint8_t *mac = params->mac;

      printf("Subscribing to %s by %02X:%02X:%02X:%02X:%02X:%02X\n",
        subAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      
      bool subscribed = false;
      for (const auto& topicObject : topicsVector) { //checks every topicObject to subscribe to the proper ones
        if (strcmp(subAnnounce->topic, topicObject.getTopic()) == 0) { //if the topic in message is the same as the topicObject
          if (!topicObject.isSubscribed(mac)) {
            topicObject.subscribe(mac);
          } else {
            printf("Already subscribed to %s\n", topicObject.getTopic());
          }
          subscribed = true; //if the topic was found in the vector
          break; //exit loop, no need to keep searching topics
        }
      }

      if (!subscribed) { //if it's a topic not existing in the vector
        printf("Topic %s not found, creating a new topic\n", subAnnounce->topic);

        BrokerTopic newTopic(subAnnounce->topic, hasWildcard(subAnnounce->topic));
        newTopic.subscribe(mac);
        topicsVector.push_back(newTopic);
      }
      free(params);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void UnsubscribeTask(void *parameter) {
  UnsubscribeTaskParams *params;

  for (;;) {
    if (xQueueReceive(unsubMsgQueue, &params, portMAX_DELAY) == pdPASS) { //gets the message from the queue
      UnsubscribeAnnouncement *unsubAnnounce = params->unsubAnnounce;
      const uint8_t *mac = params->mac;

      printf("Unsubscribed from %s by %02X:%02X:%02X:%02X:%02X:%02X\n",
        unsubAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      
      bool unsubscribed = false;
      for (auto it = topicsVector.begin(); it != topicsVector.end(); ++it) { //checks every topicObject
        if (strcmp(unsubAnnounce->topic, it->getTopic()) == 0) { //if the topic in message is the same as the topicObject
          if (it->isSubscribed(mac)) {
            it->unsubscribe(mac);
            if (it->getSubscribersAmount() == 0) { //if topicObject has no subscribers, 
              printf("Topic %s has no subscribers, is being deleted\n", it->getTopic());
              topicsVector.erase(it); //delete topicObject from topicsVector
            }
            unsubscribed = true;
            break; //exit loop, no need to keep searching topics
          }
        }
      }

      if (!unsubscribed) { //if it's a topic not existing in the vector
        printf("Topic %s not found, it was not subscribed\n", unsubAnnounce->topic);
      }
      free(params);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

void PublishTask(void *parameter) {
  PublishTaskParams *params;
  for (;;) {
    if (xQueueReceive(pubMsgQueue, &params, portMAX_DELAY) == pdPASS) { //gets the message from the queue

      PublishContent *pubContent = params->pubContent;
      const uint8_t *mac = params->mac;
      bool sent = false;
      std::vector<std::array<uint8_t, 6>> alreadySentMacs;
      for (const auto& topicObject : topicsVector) { //checks every topicObject to send the message to the proper ones
        if (topicObject.isPublishable(pubContent->topic)) { //if the topic in message is compatible with the topicObject
          topicObject.publish(*pubContent, alreadySentMacs);
          sent = true; //the topic was found in the vector
        }
      }

      printf("Received message by %02X:%02X:%02X:%02X:%02X:%02X:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      printf("\t- Topic: %s\n", pubContent->topic);
      if (!sent) { //if it's a topic not existing in the vector
        printf("\t- Topic %s not found (has no subscribers, so it isn't published)\n", pubContent->topic);
      } else {
        printf("\t- Sent to %d subscribers\n", alreadySentMacs.size());
      }
      free(params);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void ProduceMessagesTask(void *parameter) {
  char *topic = (char *)parameter;

  for (;;) {
    PayloadStruct payload;
    payload.number = random(101);

    PublishContent sendMessage;
    sendMessage.type = MSGTYPE_PUBLISH;

    strcpy(sendMessage.topic, topic);

    sendMessage.contentSize = sizeof(payload);
    memcpy(&sendMessage.content, &payload, sizeof(payload));

    PublishTaskParams pubTaskParams;
    pubTaskParams.pubContent = &sendMessage;
    uint8_t mac[6];
    WiFi.macAddress(mac);  
    pubTaskParams.mac = mac;
    
    if (xQueueSend(pubMsgQueue, &pubTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
      Serial.println("[OnDataRecv] ERROR, Couldn't create the publish task");
      return;
    }  
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  MessageType msgType = ((MessageBase*)incomingData)->type;
  switch (msgType) {
    case MSGTYPE_SUBSCRIBE: {
      //Initialize subTaskParams with the subscribe message
      SubscribeTaskParams *subTaskParams = (SubscribeTaskParams*)malloc(sizeof(SubscribeTaskParams));
      if (subTaskParams == NULL) {
        Serial.println("[OnDataRecv] ERROR, Couldn't allocate memory for subscribe task params");
        return;
      }
      subTaskParams->subAnnounce = (SubscribeAnnouncement*)malloc(sizeof(SubscribeAnnouncement));
      if (subTaskParams->subAnnounce == NULL) {
        Serial.println("[OnDataRecv] ERROR, Couldn't allocate memory for subscribe announcement");
        free(subTaskParams);
        return;
      }
      memcpy(subTaskParams->subAnnounce, (SubscribeAnnouncement*)incomingData, sizeof(SubscribeAnnouncement));
      subTaskParams->mac = mac;

      if (xQueueSend(subMsgQueue, &subTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        Serial.println("[OnDataRecv] ERROR, Couldn't send the subscribe message to the queue");
        free(subTaskParams->subAnnounce);
        free(subTaskParams);
        return;
      }
    } break;
    case MSGTYPE_UNSUBSCRIBE: {
      //Initialize unsubTaskParams with the unsubscribe message
      UnsubscribeTaskParams *unsubTaskParams = (UnsubscribeTaskParams*)malloc(sizeof(UnsubscribeTaskParams));
      if (unsubTaskParams == NULL) {
        Serial.println("[OnDataRecv] ERROR, Couldn't allocate memory for unsubscribe task params");
        return;
      }
      unsubTaskParams->unsubAnnounce = (UnsubscribeAnnouncement*)malloc(sizeof(UnsubscribeAnnouncement));
      if (unsubTaskParams->unsubAnnounce == NULL) {
        Serial.println("[OnDataRecv] ERROR, Couldn't allocate memory for unsubscribe announcement");
        free(unsubTaskParams);
        return;
      }
      memcpy(unsubTaskParams->unsubAnnounce, (UnsubscribeAnnouncement*)incomingData, sizeof(UnsubscribeAnnouncement));
      unsubTaskParams->mac = mac;
      
      if (xQueueSend(unsubMsgQueue, &unsubTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        Serial.println("[OnDataRecv] ERROR, Couldn't send the unsubscribe message to the queue");
        return;
      }
    } break;
    case MSGTYPE_PUBLISH: {
      //Initialize publishTaskParams with the publish message
      PublishTaskParams *pubTaskParams = (PublishTaskParams*)malloc(sizeof(PublishTaskParams));
      if (pubTaskParams == NULL) {
        Serial.println("[OnDataRecv] ERROR, Couldn't allocate memory for publish task params");
        return;
      }
      pubTaskParams->pubContent = (PublishContent*)malloc(sizeof(PublishContent));
      if (pubTaskParams->pubContent == NULL) {
        Serial.println("[OnDataRecv] ERROR, Couldn't allocate memory for publish content");
        free(pubTaskParams);
        return;
      }
      memcpy(pubTaskParams->pubContent, (PublishContent*)incomingData, sizeof(PublishContent));
      pubTaskParams->mac = mac;
      if (xQueueSend(pubMsgQueue, &pubTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        Serial.println("[OnDataRecv] ERROR, Couldn't send the publish message to the queue");
        return;
      }
    } break;
    
    default: {
      Serial.println("Invalid message type received!");
    } break;
  }
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  WiFi.mode(WIFI_STA);
  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) { 
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }

  printf("\nBROKER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  subMsgQueue = xQueueCreate(10, sizeof(SubscribeTaskParams));
  if (subMsgQueue == NULL) {
    Serial.println("[SETUP] ERROR, Couldn't create the subscribe message queue");
    exit(1);
  }

  unsubMsgQueue = xQueueCreate(10, sizeof(UnsubscribeTaskParams));
  if (unsubMsgQueue == NULL) {
    Serial.println("[SETUP] ERROR, Couldn't create the unsubscribe message queue");
    exit(1);
  }

  pubMsgQueue = xQueueCreate(10, sizeof(PublishTaskParams));
  if (pubMsgQueue == NULL) {
    Serial.println("[SETUP] ERROR, Couldn't create the publish message queue");
    exit(1);
  }
  /*
  char *produceTopic = "s/mock";
  BaseType_t producerTaskStatus = xTaskCreate(ProduceMessagesTask, "ProduceMessagesTask", 10000, produceTopic, 2, NULL);
  if (producerTaskStatus != pdPASS) {
    Serial.println("[SETUP] ERROR, Couldn't create the tasks");
    exit(1);
  }
  printf("[SETUP] Message producer started correctly, will be sending to the topic \"\%s\"\n", produceTopic);*/


  char taskName[20];
  
  for (int i = 0; i < SUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "SubscribeTask%d", 0+1);
    if (xTaskCreate(SubscribeTask, taskName, 7500, (void *) i, 2, NULL) != pdPASS) {
      Serial.println("[SETUP] ERROR, Couldn't create the subscribe task");
      exit(1);
    }
  }

  for (int i = 0; i < UNSUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "UnsubscribeTask%d", i+1);
    if (xTaskCreate(UnsubscribeTask, taskName, 7500, (void *) i, 1, NULL) != pdPASS) {
      Serial.println("[SETUP] ERROR, Couldn't create the unsubscribe task");
      exit(1);
    }
  }

  for (int i = 0; i < PUBLISHTASKS; i++) {
    snprintf(taskName, sizeof(taskName), "PublishTask%d", i+1);    
    if (xTaskCreate(PublishTask, taskName, 10000, (void *) i, 1, NULL) != pdPASS) {
      Serial.println("[SETUP] ERROR, Couldn't create the publish task");
      exit(1);
    }
  }

  vTaskStartScheduler();
}

void loop() { }
