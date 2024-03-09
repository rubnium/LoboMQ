/**
 * @file ESP32MQTTBroker.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef ESP32MQTTBroker_h

#define ESP32MQTTBroker_h
#include <Arduino.h>
#include <esp_now.h>
#include <stdint.h>

typedef enum {
	MSGTYPE_SUBSCRIBE = 0x00,
	MSGTYPE_UNSUBSCRIBE,
	MSGTYPE_PUBLISH
} MessageType;

typedef struct {
	MessageType type;
} MessageBase;

typedef struct : public MessageBase {
	char topic[10];
} SubscribeAnnouncement;

typedef struct : public MessageBase{
	char topic[10];
} UnsubscribeAnnouncement;

typedef struct : public MessageBase {
	char topic[10];
	size_t contentSize;
	void* content[16]; //stores any type of content
} PublishContent;

/**
 * @brief Publish brief description.
 * Publish full description
 * @param mac 
 * @param topic 
 * @param payload 
 * @return true if correctly
 * @return false if wrong
 */
bool publish(uint8_t *mac, char *topic, void *payload);


/**
 * @brief Subscribe brief description.
 * Subscribe full description
 * @param mac 
 * @param topic 
 * @return true if correctly
 * @return false if wrong
 */
bool subscribe(uint8_t *mac, char *topic);

#endif