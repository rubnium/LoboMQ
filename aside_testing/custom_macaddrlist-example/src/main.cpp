#include <unnamedMQ/MACAddrList.h>

void setup() {
	Serial.begin(9600);
	MACAddrList whitelist;
	whitelist.addToList("00:00:00:00:00:00");
	whitelist.addToList({0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF});
  whitelist.addArrayToList((std::vector<String>){
		"00:00:00:00:00:01", 
		"00:00:00:00:00:02"
		});
	whitelist.addArrayToList({
		{0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
		{0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC}});
	printf("\nAddresses:\n%s", whitelist.getAddressListAsString().c_str());
}

void loop() { }
