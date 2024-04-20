//https://registry.platformio.org/libraries/hideakitai/DebugLog
/* PINOUT:
CD/Chip Detect - 22 (not used)
DO/MISO - 19
SCK/CLK - 18
DI/MOSI - 23
CS - 5
VCC - 3.3V
GND - GND
*/

//#define DEBUGLOG_DISABLE_LOG //uncommenting DEBUGLOG_DISABLE_LOG disables ASSERT and all log (Release Mode)

//You can also set default log level by defining macro (default: INFO)
//#define DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE

//If going to use SD card
#include <SD.h>
#define fs SD
#define CS 5

//If going to use SPIFFS
/*#include <SPIFFS.h>
#define fs SPIFFS*/

#define DEBUGLOG_ENABLE_FILE_LOGGER

#include <DebugLog.h>

#define LOG_TO_SD true
const String filepath = "/log.txt";

void setup() {
	Serial.begin(9600);

	LOG_SET_LEVEL(DebugLogLevel::LVL_TRACE);
	//0: NONE, 1: ERROR, 2: WARN, 3: INFO, 4: DEBUG, 5: TRACE

	if (LOG_TO_SD) {
		if (!fs.begin(CS)) {
			Serial.println("Error initializing SD card");
      return;
		}
		LOG_ATTACH_FS_AUTO(fs, filepath, FILE_APPEND);
		Serial.printf("Logs will be saved to the SD card file %s\n", filepath.c_str());
	} else {
		LOG_ATTACH_SERIAL(Serial);
	}
	
	printf("Current log level: %d\n", (int)LOG_GET_LEVEL());

  delay(1000);
}

void loop() {
	for (int i=0; i<10; i++) {
		LOG_ERROR("Error log");
		LOG_WARN("Warn log");
		LOG_INFO("Info log");
		LOG_DEBUG("Debug log");
		LOG_TRACE("Trace log");
		delay(2000);
	}
}
