#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>

typedef struct {
  int number;
} PayloadStruct;

uint8_t brokerAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  if (isMQTTMessage(incomingData)) {
    ContentProperties content = getMQTTContent(incomingData);
    PayloadStruct payloadContent;
    memcpy(&payloadContent, &content.content, content.contentSize);
    printf("\t- Number: %d\n", payloadContent.number);
  } else {
    Serial.println("Invalid message type received!");
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
  printf("\nSUBSCRIBER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  subscribe(brokerAddr, "mock");
}

void loop() { }
