/**
 * @file PubSub.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef PUBSUB_H

#define PUBSUB_H

#include <stdint.h>

#include "commons/Includes.h"

#define MAXTOPICLENGTH 10

/**
 * @enum MessageType
 * @brief Enumerates every type of message sent between the broker and the 
 * clients.
 */
typedef enum __attribute__((packed)) {
	MSGTYPE_SUBSCRIBE = (uint8_t)0x00,	/**< Subscribe message, sent from subscriber to broker. */
	MSGTYPE_UNSUBSCRIBE,								/**< Unsubscribe message, sent from subscriber to broker. */
	MSGTYPE_PUBLISH											/**< Publish message, sent from publisher to broker or from broker to subscriber. */
} MessageType;

/**
 * @struct MessageBase
 * @brief Structure that contains the fields used by every message.
 */
typedef struct {
	MessageType type;
} MessageBase;

/**
 * @struct SubscribeAnnouncement
 * @brief Structure that contains the fields used by a subscribe message, apart 
 * from those inherited from the MessageBase.
 */
typedef struct : public MessageBase {
	char topic[MAXTOPICLENGTH]; /**< Topic that the subscriber shows interest in. */
} SubscribeAnnouncement;

/**
 * @struct UnsubscribeAnnouncement
 * @brief Structure that contains the fields used by a unsubscribe message, 
 * apart from those inherited from the MessageBase.
 */
typedef struct : public MessageBase{
	char topic[MAXTOPICLENGTH]; /**< Topic that the subscriber no longer shows interest in. */
} UnsubscribeAnnouncement;

/**
 * @struct PublishContent
 * @brief Structure that contains the fields used by a publish message, apart 
 * from those inherited from the MessageBase.
 */
typedef struct : public MessageBase {
	char topic[MAXTOPICLENGTH];	/**< Topic where the message is published to. */
	size_t contentSize;					/**< Size of the content. */
	void* content[16];					/**< Any content stored as bytes. */
} PublishContent;


/**
 * @brief Publishes a message to the broker.
 * This function takes the payload and builds a message that will be published
 * to the specified topic on the broker.
 * @param mac The broker MAC address.
 * @param topic The topic to publish the message to. It can't contain wildcard 
 * characters (`+`, `#`) nor non-UTF-8 characters. Invalid example: `+/café`. 
 * Valid example: `kitchen/coffee`.
 * @param payload Pointer to the message payload.
 * @param _logger Pointer to the logger object.
 * @retval `LMQ_ERR_SUCCESS` if the message is successfully published.  
 * @retval `LMQ_ERR_BAD_ESP_CONFIG` if ESP-NOW couldn't be initialized.
 * @retval `LMQ_ERR_INVAL_TOPIC` if the given topic is invalid.
 * @retval `LMQ_ERR_ESP_SEND_FAIL` if the message couldn't be sent.
 */
LMQErrType publish(uint8_t *mac, char *topic, void *payload, Elog *_logger = disableLogger());

/**
 * @brief Subscribes to a topic on the broker.
 * This function sends a message to the broker announcing that the calling board
 * is interested in receiving all the messages compatible with the specified
 * topic.
 * @param mac The broker MAC address.
 * @param topic The topic the board subscribes to. Is compatible with wildcard 
 * characters (`+`, `#`) when used properly, and can't contain non-UTF-8 
 * characters. Invalid example: `résumé/+/#/garden`. Valid example: `+/+/out/#`.
 * @param _logger Pointer to the logger object.
 * @retval `LMQ_ERR_SUCCESS` if the message is successfully published.  
 * @retval `LMQ_ERR_BAD_ESP_CONFIG` if ESP-NOW couldn't be initialized.
 * @retval `LMQ_ERR_INVAL_TOPIC` if the given topic is invalid.
 * @retval `LMQ_ERR_ESP_SEND_FAIL` if the message couldn't be sent.
 */
LMQErrType subscribe(uint8_t *mac, char *topic, Elog *_logger = disableLogger());

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
 * @param _logger Pointer to the logger object.
 * @retval `LMQ_ERR_SUCCESS` if the message is successfully published.  
 * @retval `LMQ_ERR_BAD_ESP_CONFIG` if ESP-NOW couldn't be initialized.
 * @retval `LMQ_ERR_INVAL_TOPIC` if the given topic is invalid.
 * @retval `LMQ_ERR_ESP_SEND_FAIL` if the message couldn't be sent.
 */
LMQErrType unsubscribe(uint8_t *mac, char *topic, Elog *_logger = disableLogger());

/**
 * @brief Checks if the data received is a MQ message.
 * This function checks if the received bytes represent a MQ message from this
 * library.
 * @param incomingData The data received.
 * @retval `true` if the data is a MQ message.  
 * @retval `false` otherwise.  
 * @note This function is recommended to be used at the subscriber side in the
 * data receive callback alongside getLMQPayload(). Pseudocode example:  
 * ```
 * 	OnReceiveCallback(incomingData) {  
 * 		if isLMQMessage(incomingData)  
 * 			payload = getLMQPayload(incomingData)  
 * 	} 
 * ```
 */
bool isLMQMessage(const uint8_t *incomingData);

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
 * data receive callback alongside isLMQMessage(). Pseudocode example:  
 * ```
 * 	OnReceiveCallback(incomingData) {  
 * 		if isLMQMessage(incomingData)  
 * 			payload = getLMQPayload(incomingData)  
 * 	} 
 * ```
 */
PayloadContent getLMQPayload(const uint8_t *incomingData);

#endif
