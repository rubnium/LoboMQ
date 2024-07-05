#ifndef BROKERSDUTILS_H

#define BROKERSDUTILS_H

#include <array>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <FS.h>
#include <vector>

#include <ArduinoJson.h>

#include "commons/Includes.h"
#include "BrokerTopic.h"

#define FILE_PATH "/LoboMQ/topics" //must not end with "/"
#define FILE_FORMAT ".json"

String replaceChars(const char *str);
bool initializeSDCard(int csPin, Elog *logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);
void restoreBTs(std::vector<BrokerTopic> *topicsVector, Elog *logger, SemaphoreHandle_t *mutex, 
	TickType_t delay = portMAX_DELAY);
void writeBTToFile(BrokerTopic* brokerTopic, Elog* logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);
void deleteBTFile(const char* filename, Elog* logger, SemaphoreHandle_t *mutex, TickType_t delay = portMAX_DELAY);

#endif
