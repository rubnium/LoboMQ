/**
 * @file Includes.h
 * @author Rubén Gómez Villegas
 * 
 * This file contains the definitions and dependencies shared by every LoboMQ
 * library part.
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
	/** No error, operation successful. */
	LMQ_ERR_SUCCESS = 0,

	/** No error, valid topic. */
	LMQ_ERR_VALID_TOPIC,
	/** Invalid topic (no topic, too big, contains wildcard characters in wrong
	 * positions, or contains non-UTF-8 characters). */
	LMQ_ERR_INVAL_TOPIC,

	/** Couldn't initialize ESP-NOW. */
	LMQ_ERR_BAD_ESP_CONFIG,

	/** Couldn't send the message. */
	LMQ_ERR_ESP_SEND_FAIL,
	
	/** Couldn't create the broker queue. */
	LMQ_ERR_XQUEUECREATE_FAIL,
	/** Couldn't create the broker task. */
	LMQ_ERR_XTASKCREATE_FAIL
} LMQErrType;

#endif
