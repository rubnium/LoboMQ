#include <LoboMQ/PubSub.h>

typedef struct {
  int number;
} CustomPayloadStruct;

uint8_t brokerAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

Elog *_logger;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers
	_logger = initializeSerialLogger(PUBLISHER, INFO);

  printf("\nPUBLISHER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());
}

void loop() {
  CustomPayloadStruct payload;
  payload.number = random(101);

  publish(brokerAddr, "topic1", &payload, _logger);

  sleep(5);
}
