/**
 * @file MACAddrList.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef MACADDRLIST_H

#define MACADDRLIST_H

#include <Arduino.h>
#include <cstdint>
#include <vector>

using MACAddress = std::array<uint8_t, 6>;

class MACAddrList : public std::vector<MACAddress> {
	public:
		bool isInList(const uint8_t *mac) const;
		bool isInList(const MACAddress &mac) const;
		void addToList(const uint8_t *mac);
		void addToList(const MACAddress &mac);
		void addToList(const String &macStr);
		void addArrayToList(const std::vector<String>& macArray);
		void addArrayToList(const std::vector<MACAddress>& macArray);
		bool removeFromList(const uint8_t *mac);
		bool removeFromList(const MACAddress &mac);
		void clearList();
		String getAddressListAsString() const;
};

#endif
