/**
 * LoboMQ Sensor Demo - Broker
 * This example broker has topic and subscriber persistence enabled and
 * whitelist access control disabled. The log messages are printed on the serial
 * monitor.
 * 
 * SD module pins:
 * - CD/Chip Detect: 22 (not used)
 * - DO/MISO: 19
 * - SCK/CLK: 18
 * - DI/MOSI: 23
 * - CS: 5
 * - VCC: 3.3V
 * - GND: GND
 * 
 * https://github.com/rubnium/LoboMQ
 */

#include <LoboMQ/Broker.h>

void setup() {
	Serial.begin(9600);
	Elog *logger = initializeSerialLogger(BROKER, DEBUG);

	initBroker(BRO_DEFAULT_WHITELIST, logger, true, 5);
}

void loop() { }
