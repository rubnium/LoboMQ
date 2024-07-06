/**
 * @file Logger.h
 * @author Rubén Gómez Villegas
 * 
 * This file contains the necessary definitions and declarations to easily
 * create an Elog logger object for LoboMQ.
 */

#ifndef LOGGER_H

#define LOGGER_H

#include <iostream>
#include <SD.h>
#include <SPI.h>

#include <Elog.h>

#define DEFAULT_LOG_LEVEL Loglevel::INFO

/**
 * @brief Enumerates every log class that represents the part of the library 
 * which is being logged.
 */
enum LoggerClass {
	/** Broker log class. */
	BROKER = 0,
	/** Publisher log class. */
	PUBLISHER,
	/** Subscriber log class. */
	SUBSCRIBER,
	/** Log class unknown or generic. */
	UNKNOWN
};

/**
 * @brief Creates a logger that prints messages to the serial monitor.
 * 
 * This function creates a logger used by the broker or client which prints 
 * messages to the serial monitor as most critical as the indicated.
 * @param className The log class.
 * @param level The most critical level of registration in which there is 
 * interest.
 * @return A pointer to an Elog instance set up to log through the serial 
 * monitor.
 */ 
Elog *initializeSerialLogger(LoggerClass className, Loglevel level = DEFAULT_LOG_LEVEL);

/**
 * @brief Creates a logger that prints messages to a file inside a SD card.
 * 
 * This function creates a logger used by the broker or client which prints 
 * messages to a file in the SD card as most critical as the indicated. 
 * @param className The log class.
 * @param cs The Chip Select pin of the SD card module.
 * @param sck The Serial Clock pin of the SD card module.
 * @param miso The Master In Slave Out pin of the SD card module.
 * @param mosi The Master Out Slave In pin of the SD card module.
 * @param level The most critical level of registration in which there is 
 * interest.
 * @return A pointer to an Elog instance set up to log to the SD card.
 */
Elog *initializeSDLogger(LoggerClass className, int cs, int sck, int miso, int mosi,
	Loglevel level = DEFAULT_LOG_LEVEL);

/**
 * @brief Creates a logger without the ability to print messages.
 * 
 * This function creates a logger used by the broker or client which will not 
 * print any message produced by the library. 
 * @return A pointer to an Elog instance set up to not log messages.
 */
Elog *disableLogger();

#endif
