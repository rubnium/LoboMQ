/**
 * @file Broker.h
 * @author Rubén Gómez Villegas
 * 
 * This file contains the necessary definitions and declarations to deploy a
 * LoboMQ broker.
 */

#ifndef BROKER_H

#define BROKER_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>

#include "commons/Includes.h"
#include "PubSub.h"
#include "MACAddrList.h"

typedef struct {
  SubscribeAnnouncement *subAnnounce;
  const uint8_t *mac;
} SubscribeTaskParams;

typedef struct {
  UnsubscribeAnnouncement *unsubAnnounce;
  const uint8_t *mac;
} UnsubscribeTaskParams;

typedef struct {
  PublishContent *pubContent;
  const uint8_t *mac;
} PublishTaskParams;

#define BRO_DEFAULT_WHITELIST nullptr
#define BRO_DEFAULT_LOGGER initializeSerialLogger(BROKER)
#define BRO_DEFAULT_PERSISTENCE false
#define BRO_DEFAULT_CS_SD_PIN -1

/**
 * @brief Initializes the broker.
 * This function sets up the proper tasks and queues to handle received message
 * and gives a node the role of broker. This broker redirects published messages
 * to the subscribers. If persistence is enabled, topics will be restored on
 * boot and stored in the SD card.
 * @param whitelist List with the allowed MAC addresses. If is
 * `BRO_DEFAULT_WHITELIST`, all MAC addresses are allowed.
 * @param _logger Pointer to the logger object.
 * @param persistence If is `true`, the broker will save the topics in a SD
 * card.
 * @param csSdPin The Chip Select pin of the SD card module.
 * @retval `LMQ_ERR_SUCCESS` if the broker is successfully deployed.  
 * @retval `LMQ_ERR_BAD_ESP_CONFIG` if ESP-NOW couldn't be initialized.
 * @retval `LMQ_ERR_XQUEUECREATE_FAIL` if the message queues for the tasks
 * couldn't be created.
 * @retval `LMQ_ERR_XTASKCREATE_FAIL` if the tasks to process the messages
 * couldn't be created.
 */
LMQErrType initBroker(MACAddrList *whitelist = BRO_DEFAULT_WHITELIST, Elog *_logger = BRO_DEFAULT_LOGGER,
	bool persistence = BRO_DEFAULT_PERSISTENCE, int csSdPin = BRO_DEFAULT_CS_SD_PIN);

#endif
