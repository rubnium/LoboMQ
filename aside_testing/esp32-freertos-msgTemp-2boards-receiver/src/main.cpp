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

//Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  //Receives message
  struct_message receivedMessage;
  memcpy(&receivedMessage, incomingData, sizeof(receivedMessage));
  //Adds it to the queue
  BaseType_t xStatus = xQueueSend(readingsQueue, &receivedMessage, pdMS_TO_TICKS(1000));
  if (xStatus != pdPASS)
    printf("[OnDataRecv] LOST MESSAGE, Couldn't add the message to the queue\n");
}

//Reads from the queue
void ReadQueueTask(void *parameter) {
  int *taskId = (int *)parameter;
  struct_message queuedMessage;

  for (;;) {
    BaseType_t xStatus = xQueueReceive(readingsQueue, &queuedMessage, pdMS_TO_TICKS(2000));
    if (xStatus == pdPASS) {
      printf("[ReadQueueTask%d] RECEIVED MESSAGE: %s (%lu)\n", taskId, queuedMessage.msg, queuedMessage.xTimeStamp);
      printf("\tHumidity: .2%f %%\n", queuedMessage.humidity);
      printf("\tTemperature: .2%f ºC\n", queuedMessage.temperature);
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
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  readingsQueue = xQueueCreate(10, sizeof(struct_message));

  if (readingsQueue != NULL) {
    xTaskCreate(ReadQueueTask, "ReadQueueTask", 10000, (void *)1, 1, NULL);
  } else {
    printf("[SETUP] ERROR, Couldn't create the queue\n");  
    exit(1);  
  }
}

void loop() {
}
