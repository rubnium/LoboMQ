/**
 * LoboMQ Publisher Example
 * This publisher example publishes a random number every 2 seconds.
 * 
 * https://github.com/rubnium/LoboMQ
 */

#include <LoboMQ/PubSub.h>

uint8_t brokerAddr[] = {0x24, 0xDC, 0xC3, 0x9C, 0x7E, 0x40}; //Broker MAC destination

Elog *_logger;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

	//Choose logger:
	_logger = initializeSerialLogger(PUBLISHER, DEBUG);
	//_logger = initializeSDLogger(...);
	//_logger = disableLogger();

  _logger->log(INFO, "Started publisher board on %s!", WiFi.macAddress().c_str());
}

void loop() {
  int numberExample = random(101); //generates random number
  publish(brokerAddr, "topic1", &numberExample, sizeof(numberExample), _logger);
  sleep(2);
}
