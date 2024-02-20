#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>

#include "struct_message.h"

std::vector<uint8_t*> subscribers; //stores each mac

void printSubscribers() {
  for (const auto& mac : subscribers) {
    printf("%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  }
  Serial.println();
}

bool isSubscribed(const uint8_t *mac) {
  for (const auto& subscriber : subscribers) {
    if (memcmp(mac, subscriber, 6) == 0) {
      return true; //already subscribed
    }
  }
  return false; //not subscribed
}

void handleSubscribeMsg(const SubscribeAnnouncement subAnnounce, const uint8_t *mac){
  printf("Subscribed to %s by %02X:%02X:%02X:%02X:%02X:%02X\n", subAnnounce.topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  if (!isSubscribed(mac)) {
    subscribers.push_back((uint8_t*)mac);
  } else {
    printf("Already subscribed\n");
  }
  printf("Actual subscribers:\n");
  printSubscribers();
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Message recvMessage;
  memcpy(&recvMessage, incomingData, sizeof(recvMessage));
  if (recvMessage.msgType == MSGTYPE_SUBSCRIBE) {
    handleSubscribeMsg(recvMessage.payload.subscribeAnnouncement, mac);
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

  printf("BROKER BOARD\n",NULL);
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());
}

void loop() {
}
