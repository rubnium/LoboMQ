/**
 * @file MACAddrList.cpp
 * @author Rubén Gómez Villegas
 * 
 * This file contains the necessary logic to easily manage a vector with MAC
 * addresses.
 */

#include "LoboMQ/MACAddrList.h"

bool MACAddrList::isInList(const uint8_t *mac) const {
	//Find the address in the vector
	auto it = std::find_if(this->begin(), this->end(), [&](const MACAddress& address) {
		return address == *reinterpret_cast<const MACAddress*>(mac);
	});

	return it != this->end(); //if found, true; otherwise, false
}

bool MACAddrList::isInList(const MACAddress &mac) const {
	//Find the address in the vector
	auto it = std::find_if(this->begin(), this->end(), [&](const MACAddress& address) {
		return address == mac;
	});

	return it != this->end(); //if found, true; otherwise, false
}

void MACAddrList::addToList(const uint8_t *mac) {
	if (!isInList(mac))
		this->push_back(*reinterpret_cast<const MACAddress*>(mac));
}

void MACAddrList::addToList(const MACAddress &mac) {
	if (!isInList(mac))
		this->push_back(mac);
}

void MACAddrList::addToList(const String &macStr) {
	MACAddress newAddress;
  if (sscanf(macStr.c_str(), "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX",
  	&newAddress[0], &newAddress[1], &newAddress[2], &newAddress[3], &newAddress[4], &newAddress[5]) == 6) {
    addToList(newAddress.data());
  }
}

void MACAddrList::addArrayToList(const std::vector<String>& macArray) { //receives ["AA:BB:CC:DD:EE:FF", "AA:BB:CC:DD:EE:FF"]
	for (const auto& macStr : macArray)
		addToList(macStr);
}

void MACAddrList::addArrayToList(const std::vector<MACAddress>& macArray) {
	for (const auto& mac : macArray)
		addToList(mac.data());
}

bool MACAddrList::removeFromList(const uint8_t *mac) {
	//Find the address in the vector
	auto it = std::find_if(this->begin(), this->end(), [&](const MACAddress& address) {
    return address == *reinterpret_cast<const MACAddress*>(mac);
  });

	if (it != this->end()) { //if found
		this->erase(it);
		return true;
	}

	return false; //Address not found
}

bool MACAddrList::removeFromList(const MACAddress &mac) {
	//Find the address in the vector
	auto it = std::find_if(this->begin(), this->end(), [&](const MACAddress& address) {
    return address == mac;
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

String MACAddrList::getAddressListAsString() const {
	String result = "";
	for (const auto& mac : *this) {
		char macChar[18];
		snprintf(macChar, sizeof(macChar), "%02X:%02X:%02X:%02X:%02X:%02X",
      mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		result = result + macChar + "\n";
	}
	return result;
}
