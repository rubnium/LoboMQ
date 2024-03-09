#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <ESP32MQTTBroker.h>
#include "BrokerTopic.h"

typedef struct {
  int number;
} PayloadStruct;

std::vector<BrokerTopic> topicsVector; //each topic has messages and subscribers

void handleSubscribeMsg(const SubscribeAnnouncement *subAnnounce, const uint8_t *mac) {
  Serial.println(subAnnounce->topic);
  printf("Subscribed to %s by %02X:%02X:%02X:%02X:%02X:%02X\n", subAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  
  bool subscribed = false;
  for (const auto& topicObject : topicsVector) { //checks every topicObject to subscribe to the proper ones
    if (strcmp(subAnnounce->topic, topicObject.getTopic()) == 0) { //if the topic in message is the same as the topicObject
      if (!topicObject.isSubscribed(mac)) {
        topicObject.subscribe(mac);
        printf("Subscribed to %s\n", topicObject.getTopic());
      } else {
        printf("Already subscribed to %s\n", topicObject.getTopic());
      }
      subscribed = true; //if the topic was found in the vector
    }
  }

  if (!subscribed) { //if it's a topic not existing in the vector
    printf("Topic %s not found, creating a new topic\n");
    BrokerTopic newTopic(subAnnounce->topic);
    newTopic.subscribe(mac);
    topicsVector.push_back(newTopic);
  }
}

void handlePublishMsg(const PublishContent *pubContent, const uint8_t *mac) {
  PayloadStruct payloadContent;
  memcpy(&payloadContent, &pubContent->content, pubContent->contentSize);

  printf("Received message by %02X:%02X:%02X:%02X:%02X:%02X:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  printf("\t- Topic: %s\n", pubContent->topic);
  printf("\t- Number: %d\n", payloadContent.number);

  bool sent = false;
  for (const auto& topicObject : topicsVector) { //checks every topicObject to send the message to the proper ones
    if (strcmp(pubContent->topic, topicObject.getTopic()) == 0) { //if the topic in message is the same as the topicObject
      topicObject.sendToQueue(pubContent);
      sent = true; //the topic was found in the vector
    }
  }

  if (!sent) { //if it's a topic not existing in the vector
    printf("Topic %s not found, creating a new topic\n");
    BrokerTopic newTopic(pubContent->topic);
    newTopic.sendToQueue(pubContent);
    topicsVector.push_back(newTopic);
  }
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  MessageType msgType = ((MessageBase*)incomingData)->type;
  switch (msgType) {
    case MSGTYPE_SUBSCRIBE: {
      SubscribeAnnouncement* subAnnounce;
      memcpy(&subAnnounce, &incomingData, sizeof(subAnnounce));
      handleSubscribeMsg(subAnnounce, mac);
    } break;
    case MSGTYPE_PUBLISH: {
      PublishContent* pubContent;
      memcpy(&pubContent, &incomingData, sizeof(pubContent));
      handlePublishMsg(pubContent, mac);
    } break;
    
    default: {
      Serial.println("Invalid message type received!");
    } break;
  }
}

void ProduceMessagesTask(void *parameter) {
  for (;;) {
    PayloadStruct payload;
    payload.number = random(101);
    publish((uint8_t*)WiFi.macAddress().c_str(), "mock", &payload); //TODO: test this

    Serial.println("[PRODUCE MESSAGE] Message sent correctly");
  
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}


void DispatchMessagesTask(void *parameter) {
  int *taskId = (int *)parameter;

  for (;;) {
    for (const auto& topicObject : topicsVector) { //goes through every topic
      topicObject.dispatchMessages(); //and dispatches its messages
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  esp_now_register_recv_cb(OnDataRecv);

  printf("\nBROKER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());
  
  BaseType_t dispatcherTaskStatus = xTaskCreate(DispatchMessagesTask, "DispatchMessagesTask", 10000, (void *)1, 1, NULL);
  BaseType_t producerTaskStatus = xTaskCreate(ProduceMessagesTask, "ProduceMessagesTask", 10000, (void *)1, 2, NULL);
  if (dispatcherTaskStatus != pdPASS || producerTaskStatus != pdPASS) {
    Serial.println("[SETUP] ERROR, Couldn't create the tasks");
    exit(1);
  }
}

void loop() { }
