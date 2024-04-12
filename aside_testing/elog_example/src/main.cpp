/* PINOUT:
CD/Chip Detect - 22 (not used)
DO/MISO - 19
SCK/CLK - 18
DI/MOSI - 23
CS - 5
VCC - 3.3V
GND - GND
*/

#include <Arduino.h>
#include <ELog.h>
#include <SD.h>
#include <SPI.h>

#define LOG_TO_SD true

#define CS 5
#define SCK 18
#define MISO 19
#define MOSI 23

SPIClass spi = SPIClass(VSPI);
char *filepath = "/logs.txt";

char *serviceName = "MyProgram";

Elog myLog;

void setup() {
	Serial.begin(9600);
	Loglevel loglevel = INFO;
	//Log level: EMERGENCY, ALERT, CRITICAL, ERROR, WARNING, NOTICE, INFO, DEBUG

	if (LOG_TO_SD) {
		spi.begin(SCK, MISO, MOSI, CS);
		pinMode(CS, OUTPUT);
		if (!SD.begin(CS)) {
			Serial.println("Error initializing SD card");
			return;
		}
		
		Elog::configureSd(spi, CS, 2000000); //speed=2MHz
		myLog.addSdLogging(filepath, loglevel);
    printf("Logs will be saved to the SD card file %s\n", filepath);
	} else {
		myLog.addSerialLogging(Serial, serviceName, loglevel);
		printf("Logs will be displayed in Serial Monitor\n");
	}
	
	delay(500);
}

void loop() {
	for (int i=0; i<10; i++) {
		myLog.log(INFO, "INFO log example\n");
		myLog.log(DEBUG, "DEBUG log example\n");
		myLog.log(NOTICE, "NOTICE log example\n");
		myLog.log(WARNING, "WARNING log example\n");
		myLog.log(ERROR, "ERROR log example\n");
		myLog.log(CRITICAL, "CRITICAL log example\n");
		myLog.log(ALERT, "ALERT log example\n");
		delay(1000);
	}
}
