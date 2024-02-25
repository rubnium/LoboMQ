#include <Arduino.h>
#include <stdint.h>
#include <esp_now.h>
#include <WiFi.h>

typedef struct {
  int id;
  size_t payloadSize;
  void *payload[16]; //could I not define this?
} GenericMessage;

typedef struct {
  int number;
  char text[10];
} PayloadMessage;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  //Copies received data into message
  GenericMessage message;
  memcpy(&message, incomingData, sizeof(message));

  //Extracts the payload (convert bytes to PayloadMessage)
  PayloadMessage payloadMessage;
  memcpy(&payloadMessage, &message.payload, message.payloadSize);

  printf("Message received:(%d bytes)\n", sizeof(message));
  printf("\t- id: %d (%d bytes)\n", message.id, sizeof(message.id));
  printf("\t- payloadSize: %d (%d bytes)\n", message.payloadSize, sizeof(message.payloadSize));
  printf("\t- Payload content: (%d bytes in message, %d bytes in struct)\n", sizeof(message.payload), sizeof(payloadMessage));
  printf("\t\t- number: %d (%d bytes)\n", payloadMessage.number, sizeof(payloadMessage.number));
  printf("\t\t- text: %s (%d bytes)\n", payloadMessage.text, sizeof(payloadMessage.text));
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }

  esp_now_register_recv_cb(OnDataRecv);

  printf("RECEIVER BOARD\n",NULL);
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());
}

void loop() { }
