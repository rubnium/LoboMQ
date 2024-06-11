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

/**
 * @typedef MACAddress
 * @brief Represents a MAC address as an array of 6 bytes.
 */
using MACAddress = std::array<uint8_t, 6>;

/**
 * @class MACAddrList
 * @brief A class for managing a list of MAC addresses.
 */
class MACAddrList : public std::vector<MACAddress> {
	public:

		/**
     * @brief Checks if a MAC address is in the list.
		 * This function checks if the given MAC address is in the list.
     * @param mac Pointer to the MAC address to check.
     * @retval `true` if the MAC address is in the list.
		 * @retval `false` otherwise.
     */
		bool isInList(const uint8_t *mac) const;

		/**
     * @brief Checks if a MAC address is in the list.
		 * This function checks if the given MAC address is in the list.
     * @param mac Reference to the MAC address to check.
     * @retval `true` if the MAC address is in the list.
		 * @retval `false` otherwise.
     */
		bool isInList(const MACAddress &mac) const;

		/**
     * @brief Adds a MAC address to the list if it is not already present.
		 * This function adds a MAC address to the list after checking that it 
		 * isn't already present.
     * @param mac Pointer to the MAC address to add.
     */
		void addToList(const uint8_t *mac);

		/**
     * @brief Adds a MAC address to the list if it is not already present.
		 * This function adds a MAC address to the list after checking that it 
		 * isn't already present.
     * @param mac Reference to the MAC address to add (e.g., `{0xAA, 0xBB, 0xCC, 
		 * 0xDD, 0xEE, 0xFF}`).
     */
		void addToList(const MACAddress &mac);

		/**
     * @brief Adds a MAC address to the list if it is not already present.
		 * This function adds a MAC address to the list after checking that it 
		 * isn't already present.
     * @param macStr String representation of the MAC address (e.g., 
		 * `"AA:BB:CC:DD:EE:FF"`).
     */
		void addToList(const String &macStr);

		/**
     * @brief Adds multiple MAC addresses from an array to the list.
		 * This function runs through a given array of MAC addresses adding them if 
		 * they're not already present in the list.
     * @param macArray Vector of string representations of MAC addresses (e.g., 
		 * addresses like `"AA:BB:CC:DD:EE:FF"`).
     */
		void addArrayToList(const std::vector<String>& macArray);

		/**
     * @brief Adds multiple MAC addresses from an array to the list.
		 * This function runs through a given array of MAC addresses adding them if 
		 * they're not already present in the list.
     * @param macArray Vector of MACAddress objects (e.g., objects like `{0xAA, 
		 * 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}`).
     */
		void addArrayToList(const std::vector<MACAddress>& macArray);

		/**
     * @brief Removes a MAC address from the list.
		 * This function finds the given MAC address in the list, and then removes 
		 * it.
     * @param mac Pointer to the MAC address to remove.
     * @retval `true` if the MAC address was found and removed.
		 * @retval `false` otherwise.
     */
		bool removeFromList(const uint8_t *mac);

		/**
     * @brief Removes a MAC address from the list.
		 * This function finds the given MAC address in the list, and then removes
		 * it.
     * @param mac Reference to the MAC address to remove (e.g., `{0xAA, 0xBB,
		 * 0xCC, 0xDD, 0xEE, 0xFF}`).
     * @retval `true` if the MAC address was found and removed.
		 * @retval `false` otherwise.
     */
		bool removeFromList(const MACAddress &mac);

		/**
     * @brief Clears all the MAC addresses of the list.
		 * This function empties every position of the list, resulting in a list
		 * with no elements or MAC addresses.
     */
		void clearList();

		/**
     * @brief Returns a string representation of all MAC addresses in the list.
		 * This function runs through every position of the list, formats each MAC 
		 * address to human readable (e.g., "AA:BB:CC:DD:EE:FF") and concatenates it
		 * to a String.
     * @return String containing all MAC addresses, each separated by a newline.
     */
		String getAddressListAsString() const;
};

#endif
