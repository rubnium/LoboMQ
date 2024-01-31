#include <Arduino.h>
#include <DHT.h> //installed library
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define DHTPIN 2 //sensor DHT pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

static QueueHandle_t readingsQueue = NULL;

typedef struct struct_message {
    TickType_t xTimeStamp;
    char msg[50];
    float humidity;
    float temperature;
} struct_message;

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

//reads from the queue
void ReceiveTask(void *parameter) {
  int *taskId = (int *)parameter;
  float lastHumidity = 0; float lastTemperature = 0;
  struct_message received_message;

  for(;;){
    BaseType_t xStatus = xQueueReceive(readingsQueue,&received_message, pdMS_TO_TICKS(5000));
    if(xStatus != pdPASS){
        printf("[ReceiveTask%d]: CAN'T READ, Couldn't read a message from the queue\n", taskId);
    }else{
      //if humidity and temperature readings are different from the previous, they are processed
      if(received_message.humidity != lastHumidity || received_message.temperature != lastTemperature){
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

void setup() {
  Serial.begin(9600);
  dht.begin();

  readingsQueue = xQueueCreate(10, sizeof(struct_message));

  if(readingsQueue != NULL){
    xTaskCreate(SendTask, "SendTask", 10000, (void *)1, 1, NULL);
    xTaskCreate(ReceiveTask, "ReceiveTask", 10000, (void *)1, 1, NULL);
  }else{
    printf("[SETUP] ERROR, Couldn't create the queue\n");  
    exit(1);  
  }
}

void loop() {

}
