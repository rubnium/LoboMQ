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
#include <WiFi.h>

#define MAXTOPICLENGTH 10

typedef enum {
	MSGTYPE_SUBSCRIBE = 0x00,
	MSGTYPE_UNSUBSCRIBE,
	MSGTYPE_PUBLISH
} MessageType;

typedef struct {
	MessageType type;
} MessageBase;

typedef struct : public MessageBase {
	char topic[MAXTOPICLENGTH];
} SubscribeAnnouncement;

typedef enum {
	MQTT_ERR_SUCCESS = 0x00,
	MQTT_ERR_INVAL_TOPIC
} ErrorType;

#endif