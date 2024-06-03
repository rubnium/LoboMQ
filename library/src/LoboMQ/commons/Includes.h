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

/**
 * @enum LMQErrType
 * @brief Enumerates every error code that can be returned by the library
 * functions.
 */
typedef enum {
	/** ! @brief No error, operation successful. */
	LMQ_ERR_SUCCESS = 0,

	/** ! @brief No error, valid topic. */
	LMQ_ERR_VALID_TOPIC,
	/** ! @brief Invalid topic (no topic, too big, contains wildcard characters 
	 * in wrong positions, or contains non-UTF-8 characters). */
	LMQ_ERR_INVAL_TOPIC,

	/** ! @brief Couldn't initialize ESP-NOW. */
	LMQ_ERR_BAD_ESP_CONFIG,

	/** ! @brief Couldn't send the message. */
	LMQ_ERR_ESP_SEND_FAIL,
	
	/** ! @brief Couldn't create the broker queue. */
	LMQ_ERR_XQUEUECREATE_FAIL,
	/** ! @brief Couldn't create the broker task. */
	LMQ_ERR_XTASKCREATE_FAIL
} LMQErrType;

#endif
