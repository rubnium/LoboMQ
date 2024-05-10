/**
 * @file PubSub.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef PUBSUB_H

#define PUBSUB_H

#include "unnamedMQ/commons/Includes.h"
#include <stdint.h>

#define MAXTOPICLENGTH 10

typedef enum __attribute__((packed)) {
	MSGTYPE_SUBSCRIBE = (uint8_t)0x00,
	MSGTYPE_UNSUBSCRIBE,
	MSGTYPE_PUBLISH
} MessageType;

typedef struct {
	MessageType type;
} MessageBase;

typedef struct : public MessageBase {
	char topic[MAXTOPICLENGTH];
} SubscribeAnnouncement;

typedef struct : public MessageBase{
	char topic[MAXTOPICLENGTH];
} UnsubscribeAnnouncement;

typedef struct : public MessageBase {
	char topic[MAXTOPICLENGTH];
	size_t contentSize;
	void* content[16]; //stores any type of content
} PublishContent;


/**
 * @brief Publishes a message to the broker.
 * This function takes the payload and builds a message that will be published
 * to the specified topic on the broker.
 * @param mac The broker MAC address.
 * @param topic The MQTT topic to publish the message to. It can't contain
 * wildcard characters (`+`, `#`) nor non-UTF-8 characters. Invalid example: 
 * `+/café`. Valid example: `kitchen/coffee`.
 * @param payload Pointer to the message payload.
 * @retval `true` if the message is successfully published.  
 * @retval `false` if an error occurs during publishing.
 */
IMQErrType publish(uint8_t *mac, char *topic, void *payload, Elog *_logger = disableLogger());

/**
 * @brief Subscribes to a topic on the broker.
 * This function sends a message to the broker announcing that the calling board
 * is interested in receiving all the messages compatible with the specified
 * topic.
 * @param mac The broker MAC address.
 * @param topic The MQTT topic the board subscribes to. Is compatible with
 * wildcard characters (`+`, `#`) when used properly, and can't contain
 * non-UTF-8 characters. Invalid example: `résumé/+/#/garden`. Valid example:
 * `+/+/out/#`.
 * @retval `true` if it's successfully subscribed.  
 * @retval `false` if an error occurs during subscription.
 */
IMQErrType subscribe(uint8_t *mac, char *topic, Elog *_logger = disableLogger());

/**
 * @brief Unsubscribes from a topic on the broker.
 * This function sends a message to the broker announcing that the calling board
 * is no longer interested in receiving all the messages compatible with the
 * specified topic.
 * @param mac The broker MAC address.
 * @param topic The MQ topic the board unsubscribes from. Is compatible with
 * wildcard characters (`+`, `#`) when used properly, and can't contain
 * non-UTF-8 characters. Invalid example: `résumé/+/#/garden`. Valid example:
 * `+/+/out/#`.
 * @retval `true` if it's successfully unsubscribed.  
 * @retval `false` if an error occurs during unsubscription.
 */
IMQErrType unsubscribe(uint8_t *mac, char *topic, Elog *_logger = disableLogger());

/**
 * @brief Checks if the data received is a MQ message.
 * This function checks if the received bytes represent a MQ message from this
 * library.
 * @param incomingData The data received.
 * @retval true if the data is a MQ message.  
 * @retval false if the data is not a MQ message.  
 * @note This function is recommended to be used at the subscriber side in the
 * data receive callback alongside getMQContent(). Pseudocode example:  
 * ```
 * 	OnReceiveCallback(incomingData) {  
 * 		if isMQMessage(incomingData)  
 * 			payload = getMQContent(incomingData)  
 * 	} 
 * ```
 */
bool isMQMessage(const uint8_t *incomingData);

/**
 * @brief Structure representing the content of a payload
 * This structure holds properties of the content received inside a publication
 * message.
 */
typedef struct {
	void* content[16]; /**< Array to hold content. */
	size_t contentSize; /**< Size of the content. */
} PayloadContent;

/**
 * @brief Gets the payload content inside a published message
 * This function extracts the payload from the bytes of a received publication 
 * message.
 * @param incomingData The data received.
 * @return A PayloadContent structure containing the extracted payload content.
 * @note This function is recommended to be used at the subscriber side in the
 * data receive callback alongside isMQMessage(). Pseudocode example:  
 * ```
 * 	OnReceiveCallback(incomingData) {  
 * 		if isMQMessage(incomingData)  
 * 			payload = getMQContent(incomingData)  
 * 	} 
 * ```
 */
PayloadContent getMQPayload(const uint8_t *incomingData);

#endif
