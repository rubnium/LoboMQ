#ifndef MACADDRUTILS_H

#define MACADDRUTILS_H

#include <Arduino.h>
#include <cstdint>
#include <vector>

using MACAddress = uint8_t[6];

class MACAddrList : public std::vector<MACAddress> {
	public:
		bool isInList(const uint8_t *mac);
		void addToList(const uint8_t *mac);
		void addToList(const String &macStr);
		void addArrayToList(const std::vector<String>& macArray);
		void addArrayToList(const std::vector<MACAddress>& macArray);
		bool removeFromList(const uint8_t *mac);
		void clearList();
		String getAddressListAsString();
};

#endif
