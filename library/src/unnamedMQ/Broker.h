#ifndef BROKER_H

#define BROKER_H

#include "unnamedMQ/PubSub.h"
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

void setupBroker(Elog *_logger = initializeSerialLogger(BROKER));

#endif
