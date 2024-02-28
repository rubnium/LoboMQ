#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>

typedef struct {
  int number;
} PayloadStruct;

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

void generateAndPublish(const char* topic) {
  PayloadStruct payload;
  payload.number = random(101);

  Message sendMessage;
  sendMessage.msgType = MSGTYPE_PUBLISH;
  strcpy(sendMessage.payload.publish.topic, "mock");

  sendMessage.payload.publish.contentSize = sizeof(payload);
  memcpy(&sendMessage.payload.publish.content, &payload, sizeof(payload));

  esp_err_t sendResult = esp_now_send(destBoardAddr, (uint8_t *)&sendMessage, sizeof(sendMessage));
  if (sendResult == ESP_OK)
    printf("[DISPATCHER] Sent message with number: %d\n", payload.number);
}

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

  //Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, destBoardAddr, 6);

  //Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("[SETUP] Error adding peer");
    exit(1);
  }
}

void loop() {
  generateAndPublish("topic1");
  sleep(5);
}
