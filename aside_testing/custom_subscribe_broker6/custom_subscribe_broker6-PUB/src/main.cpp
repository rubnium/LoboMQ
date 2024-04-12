#include <Arduino.h>

#include <unnamedMQ/PubSub.h>

typedef struct {
  int number;
} CustomPayloadStruct;

uint8_t brokerAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  printf("\nPUBLISHER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());
}

void loop() {
  CustomPayloadStruct payload;
  payload.number = random(101);

  publish(brokerAddr, "topic1", &payload);

  sleep(5);
}
