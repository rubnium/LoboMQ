#include <Arduino.h>
#include <esp_now.h>
#include <ESP32Time.h> //Installed library
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_now.h>
#include <WiFi.h>

#include "struct_message.h" //Created message structure

static QueueHandle_t readingsQueue = NULL;

//Callback when data is received, is 
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  struct_message receivedMessage;
  memcpy(&receivedMessage, incomingData, sizeof(receivedMessage));
  //TODO: añadir el mensaje a la cola
}

//Reads from the queue
void ReadQueueTask(void *parameter) {
  int *taskId = (int *)parameter;
  struct_message queuedMessage;

  for (;;) {
    BaseType_t xStatus = xQueueReceive(readingsQueue,&queuedMessage, pdMS_TO_TICKS(2000));
    if (xStatus == pdPASS) {
      printf("[ReceiveTask%d] RECEIVED MESSAGE: %s (%lu)\n", taskId, receivedMessage.msg, receivedMessage.xTimeStamp);
      printf("\tHumidity: %f\n", receivedMessage.humidity);
      printf("\tTemperature: %fºC\n", (float)receivedMessage.temperature);
    }
  }
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  esp_now_register_recv_cb(OnDataRecv);

  printf("RECEIVER BOARD\n",NULL);
  printf("MAC Addr: %s\n", WiFi.macAddress());

  readingsQueue = xQueueCreate(10, sizeof(struct_message));

  if (readingsQueue != NULL) {
    xTaskCreate(ReceiveTask, "ReceiveTask", 10000, (void *)1, 1, NULL);
  } else {
    printf("[SETUP] ERROR, Couldn't create the queue\n");  
    exit(1);  
  }
}

void loop() {
}
