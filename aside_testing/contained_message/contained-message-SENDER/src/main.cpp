#include <Arduino.h>
#include <stdint.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

typedef struct {
  int id;
  size_t payloadSize;
  void *payload[16]; //could I not define this?
} GenericMessage;

typedef struct {
  int number;
  char text[10];
} PayloadMessage;

GenericMessage createMessage() {
  GenericMessage message;
  message.id = 1;

  PayloadMessage payloadMessage;
  payloadMessage.number = random(100);
  //TODO: check that the text to insert doesn't overflow
  strcpy(payloadMessage.text, "test msg");
  message.payloadSize = sizeof(payloadMessage);
  memcpy(&message.payload, &payloadMessage, sizeof(payloadMessage));

  printf("Message created: (%d bytes)\n", sizeof(message));
  printf("\t- id: %d (%d bytes)\n", message.id, sizeof(message.id));
  printf("\t- payloadSize: %d (%d bytes)\n", message.payloadSize, sizeof(message.payloadSize));
  printf("\t- Payload content: (%d bytes in message, %d bytes in struct)\n", sizeof(message.payload), sizeof(payloadMessage));
  printf("\t\t- number: %d (%d bytes)\n", payloadMessage.number, sizeof(payloadMessage.number));
  printf("\t\t- text: %s (%d bytes)\n", payloadMessage.text, sizeof(payloadMessage.text));

  return message;
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }

  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, receiverAddr, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);

  printf("SENDER BOARD\n",NULL);
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());
}

void loop() {
  GenericMessage message = createMessage();
  esp_now_send(receiverAddr, (uint8_t *)&message, sizeof(message));
  sleep(5);
}
