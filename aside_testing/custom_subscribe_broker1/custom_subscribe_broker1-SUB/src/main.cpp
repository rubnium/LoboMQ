#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "struct_message.h"

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

void subscribe(const char* topic){
  Message subMsg;
  subMsg.msgType = MSGTYPE_SUBSCRIBE;
  strncpy(subMsg.payload.subscribeAnnouncement.topic, topic, sizeof(subMsg.payload.subscribeAnnouncement.topic)-1);
  esp_err_t result = esp_now_send(destBoardAddr, (uint8_t *) &subMsg, sizeof(subMsg));
  if (result == ESP_OK) {
    printf("Message sent successfully\n");
    printf("Subscribed to: %s\n",subMsg.payload.subscribeAnnouncement.topic);
  }
}

void setup() {
  Serial.begin(9600);

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
}

void loop() {
  subscribe("topic1");
  sleep(2);
}
