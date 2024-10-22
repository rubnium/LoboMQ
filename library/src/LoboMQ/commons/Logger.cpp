/**
 * @file Logger.cpp
 * @author Rubén Gómez Villegas
 * 
 * This file contains the necessary logic to easily create an Elog logger object
 * for LoboMQ.
 */

#include "Logger.h"

SPIClass spi_logger = SPIClass(VSPI);

Elog *initializeSerialLogger(LoggerClass className, Loglevel level) {
  Elog *logger = new Elog();
	const char *serviceName;
	switch (className) {
		case BROKER:
			serviceName = "BROKER";
			break;
		case PUBLISHER:
			serviceName = "PUBLISHER";
			break;
		case SUBSCRIBER:
			serviceName = "SUBSCRIBER";
			break;
		default:
			serviceName = "UNKNOWN";
			break;
	}
  logger->addSerialLogging(Serial, serviceName, level);
  return logger;
}

Elog *initializeSDLogger(LoggerClass className, int cs, int sck, int miso, int mosi, Loglevel level) {
  Elog *logger = new Elog();
	const char *filepath = "LMQ.log";
	pinMode(cs, OUTPUT);
	spi_logger.begin(sck, miso, mosi, cs);

	if (!SD.begin(cs)) {
		delete logger;
		logger = initializeSerialLogger(className, level);
		logger->log(WARNING,
			"Could not start SD logging, check the SD card pins and the card itself. Logs will be printed to Serial.");
	} else {
		logger->configureSd(spi_logger, cs, 2000000);
		logger->addSdLogging(filepath, level);
	}
  return logger;
}

Elog *disableLogger() {
	//Workaround to disable logging, making it only log the lowest level
	return initializeSerialLogger(UNKNOWN, EMERGENCY);
}
