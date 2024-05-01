#ifndef BROKERSDUTILS_H

#define BROKERSDUTILS_H

#include <array>
#include <FS.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <ArduinoJson.h>

#include "unnamedMQ/commons/Includes.h"

#define FILE_PATH "/unnamedMQ/topics" //must not end with "/"
#define FILE_FORMAT ".json"

bool initializeSDCard(int csPin, Elog *logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);

#endif
