/**
 * LoboMQ Sensor Demo - Subscriber Cheap Yellow Display
 * This example subscribes to a topic to receive published values for
 * temperature, humidity, and potentiometer readings. Each received message is
 * processed to identify its type and store its value. The updated values are
 * shown on the screen along with the number of times they have been updated.
 * 
 * https://github.com/rubnium/LoboMQ
 */

#include <LoboMQ/PubSub.h>
#include <TFT_eSPI.h>

//RGB LED pins
#define CYD_LED_RED 4
#define CYD_LED_GREEN 16
#define CYD_LED_BLUE 17

TFT_eSPI tft = TFT_eSPI();

//Structs of the different payloads in the messages
//Must be the same on the publisher

typedef struct {
	int temperature100;
	int humidity100;
} DHTValues;

typedef struct {
	int potValue;
} PotValue;

uint8_t brokerAddr[] = {0x24, 0xDC, 0xC3, 0x9C, 0x7E, 0x40}; //Broker MAC destination
char *topic = "sensor/+";

Elog *_logger;
int gTemp100; //Temperature value
int gHum100; //Humidity value
int gPotValue; //Potentiometer value
int updCounterTemp = 0; //Times that the temperature has changed
int updCounterHum = 0; //Times that the humidity has changed
int updCounterPot = 0; //Times that the humidity has changed
int defaultValue = -1;
//Strings used in header of the screen
String subToString;
String brokerString;

//Screen values
int xRes = 320;
int yRes = 240;
int leftMargin = 5;
int upMargin = 5;
int fontNum = 2; 
int xCenter = xRes /2;
int yCenter = yRes /2;
int bottom = yRes - 20;

void drawHeader() {
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(2);
	tft.drawCentreString("[LoboMQ Sensor Demo]", xCenter, upMargin, fontNum);
	tft.setTextSize(1);
	tft.drawString(WiFi.macAddress(), leftMargin, upMargin+35, fontNum);
	tft.drawRightString(brokerString, xRes-leftMargin, upMargin+35, fontNum);
	tft.drawRightString(subToString, xRes-leftMargin, upMargin+50, fontNum);
}

void drawFooter() {
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(1);
	tft.drawCentreString("github.com/rubnium/LoboMQ", xCenter, bottom, fontNum);
}

//Redraw the screen with the stored values
void drawContent() {
	tft.fillScreen(TFT_BLACK);
	drawHeader();

	char valBuf[100];

	String tempString;
	if (gTemp100 == defaultValue) {
		tempString = " Temperature: - #0            ";
	} else {
		sprintf(valBuf, " Temperature: %.2fC #%d       ", (gTemp100/100.0), updCounterTemp);
		tempString = String(valBuf);
	}

	String humString;
	if (gHum100 == defaultValue) {
		humString = " Humidity: - #0               ";
	} else {
		sprintf(valBuf, " Humidity: %.2f%% #%d         ", (gHum100/100.0), updCounterHum);
		humString = String(valBuf);
	}

	String potString;
	if (gPotValue == defaultValue) {
		potString = " Value: - #0                  ";
	} else {
		sprintf(valBuf, " Value: %d%% #%d              ", gPotValue, updCounterPot);
		potString = String(valBuf);
	}

	tft.setTextSize(2);
	tft.setTextColor(TFT_BLACK, TFT_CYAN, true); //blue because is DHT message
	tft.drawString(tempString, -10, yCenter+7-30, fontNum);
	tft.drawString(humString, -10, yCenter+7, fontNum);
	tft.setTextColor(TFT_BLACK, TFT_GREEN, true); //green because is POT message
	tft.drawString(potString, -10, yCenter+7+30, fontNum);
	
	drawFooter();
}

//Function called on every ESP-NOW message reception
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (isLMQMessage(incomingData)) {
		PublishContent pubMsg;
		memcpy(&pubMsg, incomingData, sizeof(pubMsg));
    PayloadContent content = getLMQPayload(incomingData);
		_logger->log(INFO, "Received LMQ message of %dB", content.contentSize);

		//Process the content depending on the topic
		if (strcmp(pubMsg.topic, "sensor/dht") == 0) {
			digitalWrite(CYD_LED_BLUE, LOW); //Blue on
			DHTValues dhtValues;
			memcpy(&dhtValues, content.content, content.contentSize);
			if (dhtValues.temperature100 != gTemp100) {
				gTemp100 = dhtValues.temperature100;
				updCounterTemp++;
			}
			if (dhtValues.humidity100 != gHum100) {
				gHum100 = dhtValues.humidity100;
				updCounterHum++;
			}
		} else if (strcmp(pubMsg.topic, "sensor/pot") == 0) {
			digitalWrite(CYD_LED_GREEN, LOW); //Green on
			PotValue potVal;
			memcpy(&potVal, content.content, content.contentSize);
			if (potVal.potValue != gPotValue) {
				gPotValue = potVal.potValue;
				updCounterPot++;
			}
		}
		drawContent();
		//Turn LED off (they are active low, LOW==on, HIGH==off)
		digitalWrite(CYD_LED_RED, HIGH);
		digitalWrite(CYD_LED_GREEN, HIGH);
		digitalWrite(CYD_LED_BLUE, HIGH);
  } else {
    _logger->log(ERROR, "Invalid message type received");
  }
}

void setup() {
	_logger = initializeSerialLogger(SUBSCRIBER, INFO);
	Serial.begin(115200);
	
	//Initialize RGB LED
	pinMode(CYD_LED_RED, OUTPUT);
  pinMode(CYD_LED_GREEN, OUTPUT);
  pinMode(CYD_LED_BLUE, OUTPUT);
	digitalWrite(CYD_LED_RED, HIGH);
	digitalWrite(CYD_LED_GREEN, HIGH);
	digitalWrite(CYD_LED_BLUE, HIGH);

	//Initialize global values
	gTemp100 = defaultValue;
	gHum100 = defaultValue;
	gPotValue = defaultValue;

	//Initialize header strings
	char initialStrBuf[100];

	sprintf(initialStrBuf, "Subscribed to '%s'", topic);
	subToString = String(initialStrBuf);

	sprintf(initialStrBuf, "Broker: %02X:%02X:%02X:%02X:%02X:%02X",
  	brokerAddr[0], brokerAddr[1], brokerAddr[2],
  	brokerAddr[3], brokerAddr[4], brokerAddr[5]);
	brokerString = String(initialStrBuf);

	WiFi.mode(WIFI_STA);

  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    _logger->log(ERROR, "Couldn't initialize ESP-NOW");
    exit(1);
  }

	//Draw initial screen
  tft.init();
  tft.setRotation(1); //landscape
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
	drawHeader();
	tft.drawCentreString("Waiting for messages...", xCenter, yCenter, fontNum);
	drawFooter();

	if (subscribe(brokerAddr, topic, _logger) != LMQ_ERR_SUCCESS) {
		_logger->log(ERROR, "Couldn't subscribe to topic");
		exit(1);
	}

	_logger->log(INFO, "Waiting for messages...");
}

void loop() { }
