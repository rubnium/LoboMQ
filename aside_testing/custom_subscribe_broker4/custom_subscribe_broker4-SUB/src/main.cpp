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
  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  
  printf("\nSUBSCRIBER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  subscribe(brokerAddr, "#");
  //sleep(2);
  subscribe(brokerAddr, "s/+");
  //sleep(2);
  subscribe(brokerAddr, "s/mock");

  sleep(20);

  unsubscribe(brokerAddr, "#");
  unsubscribe(brokerAddr, "s/+");
}

void loop() { }
