/**
 * @file Includes.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef INCLUDES_H

#define INCLUDES_H

#include <Arduino.h>
#include <esp_now.h>
#include <SD.h>
#include <SPI.h>
#include <WiFi.h>

#include <Elog.h>

#include "Logger.h"

typedef enum {
	LMQ_ERR_SUCCESS = 0,

	LMQ_ERR_VALID_TOPIC,
	LMQ_ERR_INVAL_TOPIC,

	LMQ_ERR_BAD_ESP_CONFIG,

	LMQ_ERR_ESP_SEND_FAIL,

	LMQ_ERR_XQUEUECREATE_FAIL,
	LMQ_ERR_XTASKCREATE_FAIL
} LMQErrType;

#endif
