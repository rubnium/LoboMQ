#ifndef ESP32MQTTBroker_h

#define ESP32MQTTBroker_h
#include <Arduino.h>
#include <stdint.h>

#define MSGTYPE_SUBSCRIBE 1
#define MSGTYPE_UNSUBSCRIBE 2
#define MSGTYPE_PUBLISH 3

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
	
void HelloWorld();

#endif