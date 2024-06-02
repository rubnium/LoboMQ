#include <Arduino.h>
#include <LoboMQ/Broker.h>


void setup() {
	Serial.begin(9600);

	MACAddrList *whitelist = new MACAddrList();

	whitelist->addArrayToList((std::vector<String>){
		"00:00:00:00:00:00", 
		//"C0:49:EF:CB:99:10"
	});

	whitelist->addToList({0xC0, 0x49, 0xEF, 0xCB, 0x99, 0x10});
	
	Elog *logger = initializeSerialLogger(BROKER, DEBUG);

	initBroker(whitelist, logger, true, 5);
	//initBroker(BRO_DEFAULT_WHITELIST, BRO_DEFAULT_LOGGER, BRO_DEFAULT_PERSISTENCE, BRO_DEFAULT_CS_SD_PIN);
}

void loop() { }
