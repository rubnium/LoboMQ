/**
 * @file Broker.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
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

IMQErrType initBroker(MACAddrList *whitelist = BRO_DEFAULT_WHITELIST, Elog *_logger = BRO_DEFAULT_LOGGER,
	bool persistence = BRO_DEFAULT_PERSISTENCE, int csSdPin = BRO_DEFAULT_CS_SD_PIN);

#endif
