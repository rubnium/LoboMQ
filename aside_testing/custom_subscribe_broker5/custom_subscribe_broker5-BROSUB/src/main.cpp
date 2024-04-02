#include <Arduino.h>
#include <esp_now.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>

#define SUBSCRIBETASKS 1

typedef struct {
  int number;
} PayloadStruct;

typedef struct {
  SubscribeAnnouncement *subAnnounce;
  const uint8_t *mac;
} SubscribeTaskParams;

//Message queues
QueueHandle_t subMsgQueue;

void SubscribeTask(void *parameter) {
  SubscribeTaskParams *params;
  for (;;) {
    if (xQueueReceive(subMsgQueue, &params, portMAX_DELAY) == pdPASS) { //gets the message from the queue
      SubscribeAnnouncement *subAnnounce = params->subAnnounce;
      const uint8_t *mac = params->mac;

      printf("Subscribing to %s by %02X:%02X:%02X:%02X:%02X:%02X\n",
				subAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      
      //here goes subscribe logic

      free(params); //free the memory after using it
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  MessageType msgType = ((MessageBase*)incomingData)->type;
  switch (msgType) {
    case MSGTYPE_SUBSCRIBE: {
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

      printf("[OnDataRecv] RECEIVED SUBSCRIBE MESSAGE, with topic %s\n", subTaskParams->subAnnounce->topic);

      if (xQueueSend(subMsgQueue, &subTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        Serial.println("[OnDataRecv] ERROR, Couldn't send the subscribe message to the queue");
        free(subTaskParams->subAnnounce);
        free(subTaskParams);
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

  char taskName[20];
  
  for (int i = 0; i < SUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "SubscribeTask%d", i+1);
    if (xTaskCreate(SubscribeTask, taskName, 7500, (void *) i, 2, NULL) != pdPASS) {
      Serial.println("[SETUP] ERROR, Couldn't create the subscribe task");
      exit(1);
    }
  }

  vTaskStartScheduler();
}

void loop() { }
