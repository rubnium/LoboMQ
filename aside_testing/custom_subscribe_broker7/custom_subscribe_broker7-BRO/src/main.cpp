#include <Arduino.h>
#include <unnamedMQ/Broker.h>

void setup() {
	Serial.begin(9600);
	Elog *logger = initializeSerialLogger(BROKER, DEBUG);
	setupBroker(logger);
}

void loop() { }