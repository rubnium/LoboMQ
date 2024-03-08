#ifndef ESP32MQTTBroker_h

#define ESP32MQTTBroker_h
#include <Arduino.h>
#include <stdint.h>

typedef enum {
	MSGTYPE_SUBSCRIBE = 0x00,
	MSGTYPE_UNSUBSCRIBE,
	MSGTYPE_PUBLISH
} MessageType;

typedef struct {
	char topic[10];
} SubscribeAnnouncement;

typedef struct {
	char topic[10];
} UnsubscribeAnnouncement;

typedef struct {
	char topic[10];
	size_t contentSize;
	void* content[16]; //stores any type of content
} PublishContent;

typedef union {
	SubscribeAnnouncement subscribeAnnouncement;
	UnsubscribeAnnouncement unsubscribeAnnouncement;
	PublishContent publish;
} PayloadUnion;

typedef struct {
	uint8_t msgType;
	PayloadUnion payload;
} Message;
	
#endif