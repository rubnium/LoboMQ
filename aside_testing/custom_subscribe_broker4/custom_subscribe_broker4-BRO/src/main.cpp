#include <Arduino.h>
#include <esp_now.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>
#include "BrokerTopic.h"

#define SUBSCRIBETASKS 1
#define UNSUBSCRIBETASKS 1
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
  SubscribeTaskParams params;

  for (;;) {
    if (xQueueReceive(subMsgQueue, &params, pdMS_TO_TICKS(1000)) == pdPASS) { //gets the message from the queue
      SubscribeAnnouncement *subAnnounce = params.subAnnounce;
      const uint8_t *mac = params.mac;

      Serial.println(subAnnounce->topic);
      printf("Subscribed to %s by %02X:%02X:%02X:%02X:%02X:%02X\n", subAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      
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
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void UnsubscribeTask(void *parameter) {
  UnsubscribeTaskParams params;

  for (;;) {
    if (xQueueReceive(unsubMsgQueue, &params, pdMS_TO_TICKS(1000)) == pdPASS) { //gets the message from the queue
      UnsubscribeAnnouncement *unsubAnnounce = params.unsubAnnounce;
      const uint8_t *mac = params.mac;

      Serial.println(unsubAnnounce->topic);
      printf("Unsubscribed from %s by %02X:%02X:%02X:%02X:%02X:%02X\n", unsubAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      
      bool unsubscribed = false;
      for (auto it = topicsVector.begin(); it != topicsVector.end(); ++it) { //checks every topicObject
        if (strcmp(unsubAnnounce->topic, it->getTopic()) == 0) { //if the topic in message is the same as the topicObject
          if (it->isSubscribed(mac)) {
            it->unsubscribe(mac);
            if (it->getSubscribersAmount() == 0) { //if topicObject has no subscribers, 
              printf("Topic %s has no subscribers, is being deleted\n", it->getTopic());
              topicsVector.erase(it); //delete topicObject from topicsVector
            }
            break; //exit loop, no need to keep searching topics
          }
        }
      }

      if (!unsubscribed) { //if it's a topic not existing in the vector
        printf("Topic %s not found, it was not subscribed\n", unsubAnnounce->topic);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

void PublishTask(void *parameter) {
  PublishTaskParams params;
  for (;;) {
    if (xQueueReceive(pubMsgQueue, &params, pdMS_TO_TICKS(1000)) == pdPASS) { //gets the message from the queue

      PublishContent *pubContent = params.pubContent;
      const uint8_t *mac = params.mac;
      bool sent = false;
      for (const auto& topicObject : topicsVector) { //checks every topicObject to send the message to the proper ones
        if (topicObject.isPublishable(pubContent->topic)) { //if the topic in message is compatible with the topicObject
          topicObject.publish(*pubContent);
          sent = true; //the topic was found in the vector
        }
      }

      if (!sent) { //if it's a topic not existing in the vector
        printf("Topic %s not found (has no subscribers, so it isn't published)\n", pubContent->topic);
      }

      printf("Received message by %02X:%02X:%02X:%02X:%02X:%02X:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      printf("\t- Topic: %s\n", pubContent->topic);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void ProduceMessagesTask(void *parameter) {
  for (;;) {
    PayloadStruct payload;
    payload.number = random(101);

    PublishContent sendMessage;
    sendMessage.type = MSGTYPE_PUBLISH;

    strcpy(sendMessage.topic, "s/mock");

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

    Serial.println("[PRODUCE MESSAGE] Message sent correctly");
  
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  MessageType msgType = ((MessageBase*)incomingData)->type;
  switch (msgType) {
    case MSGTYPE_SUBSCRIBE: {
      SubscribeTaskParams subTaskParams;
      subTaskParams.subAnnounce = (SubscribeAnnouncement*)incomingData;
      subTaskParams.mac = mac;
      if (xQueueSend(subMsgQueue, &subTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        Serial.println("[OnDataRecv] ERROR, Couldn't send the subscribe message to the queue");
        return;
      }
    } break;
    case MSGTYPE_UNSUBSCRIBE: {
      UnsubscribeTaskParams unsubTaskParams;
      unsubTaskParams.unsubAnnounce = (UnsubscribeAnnouncement*)incomingData;
      unsubTaskParams.mac = mac;
      if (xQueueSend(unsubMsgQueue, &unsubTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        Serial.println("[OnDataRecv] ERROR, Couldn't send the unsubscribe message to the queue");
        return;
      }
    } break;
    case MSGTYPE_PUBLISH: {
      PublishTaskParams pubTaskParams;
      pubTaskParams.pubContent = (PublishContent*)incomingData;
      pubTaskParams.mac = mac;
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
  }*/

  pubMsgQueue = xQueueCreate(10, sizeof(PublishTaskParams));
  if (pubMsgQueue == NULL) {
    Serial.println("[SETUP] ERROR, Couldn't create the publish message queue");
    exit(1);
  }
  
  BaseType_t producerTaskStatus = xTaskCreate(ProduceMessagesTask, "ProduceMessagesTask", 10000, (void *)1, 2, NULL);
  if (producerTaskStatus != pdPASS) {
    Serial.println("[SETUP] ERROR, Couldn't create the tasks");
    exit(1);
  }

  char taskName[20];
  
  for (int i = 0; i < SUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "SubscribeTask%d", 0+1);
    if (xTaskCreate(SubscribeTask, taskName, 10000, (void *) i, 2, NULL) != pdPASS) {
      Serial.println("[SETUP] ERROR, Couldn't create the subscribe task");
      exit(1);
    }
  }

  for (int i = 0; i < UNSUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "UnsubscribeTask%d", i+1);
    if (xTaskCreate(UnsubscribeTask, taskName, 10000, (void *) i, 1, NULL) != pdPASS) {
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
}

void loop() { }
