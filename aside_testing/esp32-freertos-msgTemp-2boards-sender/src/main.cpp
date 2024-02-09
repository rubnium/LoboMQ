#include <Arduino.h>
#include <DHT.h> //Installed library
#include <esp_now.h>
#include <ESP32Time.h> //Installed library
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFi.h>

#include "struct_message.h" //Created message structure

#define DHTPIN 2 //DHT sensor pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCB, 0x99, 0x10}; //MAC destination address

bool ReadSensor(float lastHumidity, float lastTemperature, float *actualHumidity, float *actualTemperature) {
  *actualHumidity = roundf(dht.readHumidity()*100)/100; //Humidity read and rounded up to 2 decimals
  *actualTemperature = roundf(dht.readTemperature()*100)/100; //Temperature read in ºC and rounded up to 2 decimals
  //If some value is nan, it means the sensor didn't read correctly
  if (isnan(*actualHumidity) || isnan(*actualTemperature)) {
    printf("Failed to read from DHT sensor\n");
    return false;
  }
  //If the humidity/temperature have changed, triggers a new message to be sent
  if (*actualHumidity != lastHumidity || *actualTemperature != lastTemperature) {
    printf("[ReadSensor] Humidity: %.2f %%, Temperature: %.2f °C\n", *actualHumidity, *actualTemperature);
    return true;
  } else {
    return false;
  }
}

//Reads temperature and humidity, and sends them to the destination board
void SendDataTask(void *parameter){
  int *taskId = (int *)parameter;
  float lastHumidity = 0.0; float lastTemperature = 0.0;
  float actualHumidity = 0.0; float actualTemperature = 0.0;
  int nMessage = 0;

  for(;;){
    //Reads sensors. If true, the value was correct and different from the previous. The actual values are written
    if (ReadSensor(lastHumidity, lastTemperature, &actualHumidity, &actualTemperature)) {
      //Creates the message, fills it and sends it
      struct_message message_to_send;
      sprintf(message_to_send.msg, "Message #%d", nMessage);
      message_to_send.humidity = actualHumidity;
      message_to_send.temperature = actualTemperature;
      message_to_send.xTimeStamp = xTaskGetTickCount();
      esp_err_t result = esp_now_send(destBoardAddr, (uint8_t *) &message_to_send, sizeof(message_to_send));
      if (result == ESP_OK) {
        printf("[SendTask%d] Message sent successfully\n", taskId);
        nMessage += 1;
        //Stores the sent values as previous
        lastHumidity = actualHumidity;
        lastTemperature = actualTemperature;
      } else {
        printf("[SendTask%d] LOST MESSAGE, Couldn't send the message\n", taskId);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  printf("SENDER BOARD\n",NULL);
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  //Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, destBoardAddr, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  //Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("[SETUP] Error adding peer");
    exit(1);
  }

  xTaskCreate(SendDataTask, "SendDataTask", 10000, (void *)1, 1, NULL);
}

void loop() {
}
