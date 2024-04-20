/**
 * @file Logger.h
 * @author Rubén Gómez Villegas
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef LOGGER_H

#define LOGGER_H

#include <iostream>
#include <SD.h>
#include <SPI.h>

//Installed libraries:
#include <Elog.h>

#define DEFAULT_LOG_LEVEL Loglevel::INFO

enum LoggerClass {
	BROKER = 0,
	PUBLISHER,
	SUBSCRIBER,
	UNKNOWN
};

Elog *initializeSerialLogger(LoggerClass className, Loglevel level = DEFAULT_LOG_LEVEL);
Elog *initializeSDLogger(LoggerClass className, int cs, int sck, int miso, int mosi, Loglevel level = DEFAULT_LOG_LEVEL);
Elog *disableLogger();

#endif
