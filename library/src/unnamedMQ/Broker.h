/**
 * @file Broker.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef BROKER_H

#define BROKER_H

#include "unnamedMQ/PubSub.h"
#include "unnamedMQ/MACAddrList.h"
#include "unnamedMQ/commons/Includes.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>

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

IMQErrType initBroker(MACAddrList *whitelist = NULL, Elog *_logger = initializeSerialLogger(BROKER),
	bool persistence = false, int csSdPin = -1);

#endif
