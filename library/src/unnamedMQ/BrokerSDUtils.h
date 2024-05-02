#ifndef BROKERSDUTILS_H

#define BROKERSDUTILS_H

#include <array>
#include <FS.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <ArduinoJson.h>

#include "unnamedMQ/commons/Includes.h"
#include "unnamedMQ/BrokerTopic.h"

#define FILE_PATH "/unnamedMQ/topics" //must not end with "/"
#define FILE_FORMAT ".json"

String replaceChars(const char *str);
bool initializeSDCard(int csPin, Elog *logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);
void restoreBTs(std::vector<BrokerTopic> *topicsVector, int csPin, Elog *logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);
void writeBTToFile(BrokerTopic* brokerTopic, Elog* logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);
void deleteBTFile(const char* filename, Elog* logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);

#endif
