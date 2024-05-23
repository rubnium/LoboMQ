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
	MQ_ERR_SUCCESS = 0,

	MQ_ERR_VALID_TOPIC,
	MQ_ERR_INVAL_TOPIC,

	MQ_ERR_BAD_ESP_CONFIG,

	MQ_ERR_ESP_SEND_FAIL,

	MQ_ERR_XQUEUECREATE_FAIL,
	MQ_ERR_XTASKCREATE_FAIL
} IMQErrType;

#endif
