#include <Arduino.h>
#include <DHT.h> //installed library
#include <ESP32Time.h> //installed library
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "struct_message.h" //created message structure

#define DHTPIN 2 //DHT sensor pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

static QueueHandle_t readingsQueue = NULL;

//reads temperature and humidity and sends them to the queue
void SendTask(void *parameter){
  int *taskId = (int *)parameter;
  float actualHumidity; float actualTemperature;
  int nMessage = 0;

  for(;;){
    actualHumidity = roundf(dht.readHumidity()*100)/100; //humidity read and rounded up to 2 decimals
    actualTemperature = roundf(dht.readTemperature(false)*100)/100; //temperature read in ºC and rounded up to 2 decimals
  
    //if none of the values is nan
    if(!isnan(actualHumidity) && !isnan(actualTemperature)){
      //creates the message, fills it and sends it
      struct_message message_to_send;
      sprintf(message_to_send.msg, "Message #%d", nMessage);
      message_to_send.humidity = actualHumidity;
      message_to_send.temperature = actualTemperature;
      message_to_send.xTimeStamp = xTaskGetTickCount();

      //sends the message (waits until there's space in the queue for 1 sec max)
      BaseType_t xStatus = xQueueSend(readingsQueue, &message_to_send, pdMS_TO_TICKS(1000));

      if(xStatus != pdPASS)
        printf("[SendTask%d]: LOST MESSAGE, Couldn't send the message to the queue\n", taskId);
      
      nMessage++;
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  readingsQueue = xQueueCreate(10, sizeof(struct_message));

  if(readingsQueue != NULL){
    xTaskCreate(SendTask, "SendTask", 10000, (void *)1, 1, NULL);  }else{
    printf("[SETUP] ERROR, Couldn't create the queue\n");  
    exit(1);  
  }
}

void loop() {

}
