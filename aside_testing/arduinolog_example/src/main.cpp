/* PINOUT:
CD/Chip Detect - 22 (not used)
DO/MISO - 19
SCK/CLK - 18
DI/MOSI - 23
CS - 5
VCC - 3.3V
GND - GND
*/
#include <ArduinoLog.h>
#include <SD.h>
#include <SPI.h>

#define LOG_TO_SD true
#define CS 5
#define SCK 18
#define MISO 19
#define MOSI 23
const String filepath = "/log.txt";
File logSDFile;
// #define DISABLE_LOGGING  //uncomment to remove all logging code

void printTimestamp(Print* _logOutput) {
  //Division constants
  const unsigned long MSECS_PER_SEC = 1000;
  const unsigned long SECS_PER_MIN = 60;
  const unsigned long SECS_PER_HOUR = 3600;
  const unsigned long SECS_PER_DAY = 86400;

  //Total time
  const unsigned long msecs =  millis();
  const unsigned long secs =  msecs / MSECS_PER_SEC;

  //Time in components
  const unsigned long MilliSeconds =  msecs % MSECS_PER_SEC;
  const unsigned long Seconds =  secs  % SECS_PER_MIN ;
  const unsigned long Minutes = (secs  / SECS_PER_MIN) % SECS_PER_MIN;
  const unsigned long Hours = (secs  % SECS_PER_DAY) / SECS_PER_HOUR;

  //Time as string
  char timestamp[20];
  sprintf(timestamp, "%02d:%02d:%02d.%03d ", Hours, Minutes, Seconds, MilliSeconds);
  _logOutput->print(timestamp);
}

void printLogLevel(Print* _logOutput, int logLevel) {
  //Show log description based on log level
  switch (logLevel) {
    default:
    case 0:_logOutput->print("SILENT "); break;
    case 1:_logOutput->print("FATAL "); break;
    case 2:_logOutput->print("ERROR "); break;
    case 3:_logOutput->print("WARNING "); break;
    case 4:_logOutput->print("INFO "); break;
    case 5:_logOutput->print("TRACE "); break;
    case 6:_logOutput->print("VERBOSE "); break;
  }   
}

void printPrefix(Print* _logOutput, int logLevel) {
  printTimestamp(_logOutput);
  printLogLevel(_logOutput, logLevel);
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

	int logLevel = LOG_LEVEL_VERBOSE;
	//Levels: LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, LOG_LEVEL_INFO, LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE


	if (LOG_TO_SD) {
		SPI.begin(SCK, MISO, MOSI, CS);
		pinMode(CS, OUTPUT);
		if (!SD.begin(CS)) {
      Serial.println("Error initializing SD card");
      return;
    }
		logSDFile = SD.open(filepath, FILE_WRITE);
    if (!logSDFile) {
      Serial.println("Error opening SD log file");
      return;
    }
    Serial.printf("Logs will be saved to the SD card file %s\n", filepath.c_str());
		Log.begin(logLevel, &logSDFile);
	} else {
		Log.begin(logLevel, &Serial);
	}

	Log.setPrefix(printPrefix);
	Log.setShowLevel(false); //prefix printed by the prefix

  //Log.notice(F(CR "Example" CR)); //Info string with Newline
  //Log.notice("Example" CR); //Info string in flash memory
}

void loop() {
	for (int i=0; i<10; i++) {
		Log.fatal("Fatal log" CR);
		Log.error("Errors log" CR);
		Log.warning("Warning log" CR);
		Log.notice("Notice log" CR);
		Log.info("Info log" CR);
		Log.trace("Trace log" CR);
		Log.verbose("Verbose log" CR);
		Serial.println();
		delay(2000);
		logSDFile.flush();
	}
}
