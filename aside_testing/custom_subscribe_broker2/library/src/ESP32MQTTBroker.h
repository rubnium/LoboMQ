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
	
void HelloWorld();

#endif