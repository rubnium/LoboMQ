/* PINOUT:
CD/Chip Detect - 22 (not used)
DO/MISO - 19
SCK/CLK - 18
DI/MOSI - 23
CS - 5
VCC - 3.3V
GND - GND
*/

#include <unnamedMQ/commons/Includes.h>
#include <unnamedMQ/commons/Logger.h>

Elog *logger;

void setup() {
  Serial.begin(9600);
  //logger = initializeSerialLogger(BROKER, INFO);
	logger = initializeSDLogger(BROKER, 5, 18, 19, 23, DEBUG);
}

void loop() {
	for (int i=0; i<10; i++) {
		logger->log(INFO, "Hello world!");
		logger->log(INFO, "Hello again!");
		logger->log(INFO, "Goodbye!");
		delay(1000);
	}
	logger = disableLogger();
	logger->log(INFO, "You shouldn't see this");

  delete logger;
}
