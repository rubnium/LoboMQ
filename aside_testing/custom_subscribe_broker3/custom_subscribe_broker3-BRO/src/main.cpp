#include <Arduino.h>
#include <esp_now.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>
#include "BrokerTopic.h"

typedef struct {
  int number;
} PayloadStruct;

typedef struct {
  SubscribeAnnouncement *subAnnounce;
  const uint8_t *mac;
} SubscribeTaskParams;

typedef struct {
  PublishContent *pubContent;
  const uint8_t *mac;
} PublishTaskParams;

std::vector<BrokerTopic> topicsVector; //each topic has messages and subscribers

void SubscribeTask(void *parameter) {
  SubscribeTaskParams *params = (SubscribeTaskParams *)parameter;
  SubscribeAnnouncement *subAnnounce = params->subAnnounce;
  const uint8_t *mac = params->mac;

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
    }
  }

  if (!subscribed) { //if it's a topic not existing in the vector
    printf("Topic %s not found, creating a new topic\n", subAnnounce->topic);
    BrokerTopic newTopic(subAnnounce->topic);
    newTopic.subscribe(mac);
    topicsVector.push_back(newTopic);
  }

  vTaskDelete(NULL);
}

void UnsubscribeTask(void *parameter) {
  //TODO: implement
  vTaskDelete(NULL);
}

void PublishTask(void *parameter) {
  PublishTaskParams *params = (PublishTaskParams *)parameter;
  PublishContent *pubContent = params->pubContent;
  const uint8_t *mac = params->mac;
  bool sent = false;
  for (const auto& topicObject : topicsVector) { //checks every topicObject to send the message to the proper ones
    if (strcmp(pubContent->topic, topicObject.getTopic()) == 0) { //if the topic in message is the same as the topicObject
      topicObject.publish(*pubContent);
      sent = true; //the topic was found in the vector
    }
  }

  if (!sent) { //if it's a topic not existing in the vector
    printf("Topic %s not found, creating a new topic\n", pubContent->topic);
    BrokerTopic newTopic(pubContent->topic);
    newTopic.publish(*pubContent);
    topicsVector.push_back(newTopic);
  }

  printf("Received message by %02X:%02X:%02X:%02X:%02X:%02X:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  printf("\t- Topic: %s\n", pubContent->topic);

  vTaskDelete(NULL);
}

void ProduceMessagesTask(void *parameter) {
  for (;;) {
    PayloadStruct payload;
    payload.number = random(101);

    PublishContent sendMessage;
    sendMessage.type = MSGTYPE_PUBLISH;

    strcpy(sendMessage.topic, "mock");

    sendMessage.contentSize = sizeof(payload);
    memcpy(&sendMessage.content, &payload, sizeof(payload));

    PublishTaskParams pubTaskParams;
    pubTaskParams.pubContent = &sendMessage;
    uint8_t mac[6];
    WiFi.macAddress(mac);  
    pubTaskParams.mac = mac;
    if (xTaskCreate(PublishTask, "PublishTask", 10000, &pubTaskParams, 1, NULL) != pdPASS) { //TODO: review this id
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
      if (xTaskCreate(SubscribeTask, "SubscribeTask", 10000, &subTaskParams, 1, NULL) != pdPASS) { //TODO: review this id
        Serial.println("[OnDataRecv] ERROR, Couldn't create the subscribe task");
        return;
      }
    } break;
    case MSGTYPE_PUBLISH: {
      PublishTaskParams pubTaskParams;
      pubTaskParams.pubContent = (PublishContent*)incomingData;
      pubTaskParams.mac = mac;
      if (xTaskCreate(PublishTask, "PublishTask", 10000, &pubTaskParams, 1, NULL) != pdPASS) { //TODO: review this id
        Serial.println("[OnDataRecv] ERROR, Couldn't create the publish task");
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
  
  BaseType_t producerTaskStatus = xTaskCreate(ProduceMessagesTask, "ProduceMessagesTask", 10000, (void *)1, 2, NULL);
  if (producerTaskStatus != pdPASS) {
    Serial.println("[SETUP] ERROR, Couldn't create the tasks");
    exit(1);
  }
}

void loop() { }
