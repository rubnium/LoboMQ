#include "unnamedMQ/MACAddrUtils.h"

bool MACAddrList::isInList(const uint8_t *mac) {
	//Find the address in the vector
	auto it = std::find_if(this->begin(), this->end(), [&](const MACAddress& address) {
		return memcmp(address, mac, 6) == 0;
	});

	return it != this->end(); // if found, true; otherwise, false
}

void MACAddrList::addToList(const uint8_t *mac) {
	MACAddress newAddress;
	memcpy(newAddress, mac, 6);
	if (!isInList(newAddress))
		this->push_back(newAddress);
}

void MACAddrList::addToList(const String &macStr) {
	MACAddress newAddress;
	sscanf(macStr.c_str(), "%02X:%02X:%02X:%02X:%02X:%02X",
		&newAddress[0], &newAddress[1], &newAddress[2], &newAddress[3], &newAddress[4], &newAddress[5]);
	if (!isInList(newAddress))
		this->push_back(newAddress);
}

void MACAddrList::addArrayToList(const std::vector<String>& macArray) { //receives ["AA:BB:CC:DD:EE:FF", "AA:BB:CC:DD:EE:FF"]
	for (const auto& macStr : macArray)
		addToList(macStr);
}

void MACAddrList::addArrayToList(const std::vector<MACAddress>& macArray) {
	for (const auto& mac : macArray)
		addToList(mac);
}

bool MACAddrList::removeFromList(const uint8_t *mac) {
	//Find the address in the vector
	auto it = std::find_if(this->begin(), this->end(), [&](const MACAddress& address) {
		return memcmp(address, mac, 6) == 0;
	});

	if (it != this->end()) { //if found
		this->erase(it);
		return true;
	}

	return false; //Address not found
}

void MACAddrList::clearList() {
	this->clear();
}

String MACAddrList::getAddressListAsString() {
	String result = "";
	for (const auto& mac : *this) {
		char macChar[18];
		snprintf(macChar, sizeof(macChar), "%02X:%02X:%02X:%02X:%02X:%02X\n",
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		result += macChar;
	}
	return result;
}
