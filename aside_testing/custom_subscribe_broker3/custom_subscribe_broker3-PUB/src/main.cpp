#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>

typedef struct {
  int number;
} PayloadStruct;

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  printf("\nPUBLISHER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  /**
  //Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, destBoardAddr, 6);

  //Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("[SETUP] Error adding peer");
    exit(1);
  }
  **/
}

void loop() {
  PayloadStruct payload;
  payload.number = random(101);
  publish(destBoardAddr, "topic1", &payload);

  sleep(5);
}
