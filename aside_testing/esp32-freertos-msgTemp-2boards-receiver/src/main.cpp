#include <Arduino.h>
#include <ESP32Time.h> //installed library
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_now.h>
#include <WiFi.h>

#include "struct_message.h" //created message structure

static QueueHandle_t readingsQueue = NULL;

//recieves data using ESPNOW
void ReceiveDataTask(void *parameter) {
  int *taskId = (int *)parameter;
  float lastHumidity = 0; float lastTemperature = 0;
  struct_message received_message;

  for (;;) {
    BaseType_t xStatus = xQueueReceive(readingsQueue,&received_message, pdMS_TO_TICKS(5000));
    if (xStatus != pdPASS) {
        printf("[ReceiveTask%d]: CAN'T READ, Couldn't read a message from the queue\n", taskId);
    } else {
      //if humidity and temperature readings are different from the previous, they are processed
      if (received_message.humidity != lastHumidity || received_message.temperature != lastTemperature) {
        printf("[ReceiveTask%d] RECEIVED MESSAGE: %s (%lu)\n", taskId, received_message.msg, received_message.xTimeStamp);
        printf("\tHumidity: %f\n", received_message.humidity);
        printf("\tTemperature: %fºC\n", (float)received_message.temperature);
        //new values stored
        lastHumidity = received_message.humidity;
        lastTemperature = received_message.temperature;
      }
    }
    
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

//reads from the queue
void ReadQueueTask(void *parameter) {

}

void setup() {
  Serial.begin(9600);

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
