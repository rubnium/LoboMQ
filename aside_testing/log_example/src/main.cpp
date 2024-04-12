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
#include "esp_log.h"
#include <SD.h>

#define LOG_TO_SD false
#define SDPIN 5

static const char *TAG = "MyProgram";
const String filepath = "/log.txt";

//Function to store the logs at SD card file
int logToSD(const char *format, va_list args) {
  char buf[256];
  int len = vsnprintf(buf, sizeof(buf), format, args);
  File logFile = SD.open(filepath, FILE_WRITE);
  if (logFile) {
    logFile.println(buf);
    logFile.close();
  } else {
		Serial.println("Failed to open file for writing");
  	return len;
	}
  Serial.print(buf);
  return len;
}

void setup() {
	esp_log_level_set("*", ESP_LOG_VERBOSE);
  Serial.begin(9600);

  if (LOG_TO_SD) {
  	if (!SD.begin(SDPIN)) {
      Serial.println("Error initializing SD card");
      return;
    }
    Serial.printf("Logs will be saved to the SD card file %s\n", filepath.c_str());
    esp_log_set_vprintf(logToSD);
  }
}

void loop() {
	for (int i=0; i<10; i++) {
		//Different types of log messages
		ESP_LOGE(TAG, "Error: critical error that the module cannot recover by itself.");
		ESP_LOGW(TAG, "Warning: error condition in which recovery measures have been taken.");
		ESP_LOGI(TAG, "Information: message that describe normal flow of events");
		ESP_LOGD(TAG, "Debug: debug message.");
		ESP_LOGV(TAG, "Verbose: detailed message.");
		Serial.println();
		delay(1000);
	}
}
