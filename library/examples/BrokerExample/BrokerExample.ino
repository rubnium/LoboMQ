/**
 * LoboMQ Broker Example
 * This broker example has both topic and subscriber persistence and
 * whitelist access control enabled. The log messages are stored on the SD card.
 * 
 * https://github.com/rubnium/LoboMQ
 */

#include <LoboMQ/Broker.h>

void setup() {
	Serial.begin(9600);

	//Create whitelist of the devices allowed to connect to the broker
	MACAddrList *whitelist = new MACAddrList();
	whitelist->addToList({0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}); //add 1 by 1
	whitelist->addArrayToList((std::vector<String>){ //or multiple at once
		"08:B6:1F:BA:04:F8", 
		"C0:49:EF:CB:99:10"
	});
	
	//Choose logger:
	//a. Serial monitor logger
	//Elog *logger = initializeSerialLogger(BROKER, DEBUG);
	//b. SD logger. In this case, pins are:
	// - CD/Chip Detect: 22 (not used)
	// - DO/MISO: 19
	// - SCK/CLK: 18
	// - DI/MOSI: 23
	// - CS: 5
	// - VCC: 3.3V
	// - GND: GND
	Elog *logger = initializeSDLogger(BROKER, 5, 18, 19, 23, DEBUG);
	//c. No logger
	//Elog *logger = disableLogger();

	//Initialize broker
	initBroker(whitelist, logger, true, 5);
	//Default values are available:
	//initBroker(BRO_DEFAULT_WHITELIST, BRO_DEFAULT_LOGGER, BRO_DEFAULT_PERSISTENCE, BRO_DEFAULT_CS_SD_PIN);
}

void loop() { }
