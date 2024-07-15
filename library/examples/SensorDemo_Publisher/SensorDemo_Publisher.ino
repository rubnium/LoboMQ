/**
 * LoboMQ Sensor Demo - Publisher
 * This publisher example reads temperature, humidity, and potentiometer values
 * every second. If any of these values change from the previous reading, the
 * new values are packaged and published to the broker under their respective
 * topics.
 * 
 * Pins:
 * - DHT11: 32
 * - Potentiometer: 34
 * 
 * https://github.com/rubnium/LoboMQ
 */

#include <LoboMQ/PubSub.h>
#include <DHT.h>

//Sensors configuration

#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define POT 34

//Structs of the different payloads in the messages
//Must be the same on the subscriber

typedef struct {
	int temperature100;
	int humidity100;
} DHTValues;

typedef struct {
	int potValue;
} PotValue;

uint8_t brokerAddr[] = {0x24, 0xDC, 0xC3, 0x9C, 0x7E, 0x40}; //Broker MAC destination
char *topicDht = "sensor/dht"; //Topic of temperature and humidity
char *topicPot = "sensor/pot"; //Topic of potentiometer

Elog *_logger;
int lastTemp100; //Last stored temperature value
int lastHum100;  //Last stored humidity value
int lastPotVal; //Last stored potentiometer value

void setup() {
	Serial.begin(9600);
	_logger = initializeSerialLogger(PUBLISHER, INFO);

	//Initialize sensors
	dht.begin();

	//Initialize last values
	lastTemp100 = -1;
	lastHum100 = -1;
	lastPotVal = -1;
	
	WiFi.mode(WIFI_STA);
	//Initialize ESP-NOW
	if (esp_now_init() != ESP_OK) {
		_logger->log(ERROR, "Couldn't initialize ESP-NOW");
		exit(1);
	}

	_logger->log(INFO, "Started sensor publisher on %s!", WiFi.macAddress().c_str());
}

void loop() {
	//Read DHT value
	float temperature = dht.readTemperature(); //reads temperature in Celsius
	float humidity = dht.readHumidity();

	//If the values aren't correct, DHT sensor isn't working
	if (isnan(temperature) || isnan(humidity)) {
		_logger->log(ERROR, "Failed to read from DHT sensor");
	} else {
		//Round the values to 2 decimals and multiply by 100 to store as integers
		int temperature100 = round(temperature * 100);
		int humidity100 = round(humidity * 100);
		bool dhtChanged = false;
		//If the temperature is different than the previous, it is processed
		if (fabs(temperature100 - lastTemp100) >= 10) {
			_logger->log(INFO, "Temperature: %.2fºC", (temperature100/100.0));
			lastTemp100 = temperature100; //Stores the new temperature
			dhtChanged = true;
		}
		//If the humidity is different than the previous, it is processed
		if (fabs(humidity100 - lastHum100) >= 10) {
			_logger->log(INFO, "Humidity: %.2f%%", (humidity100/100.0));
			lastHum100 = humidity100; //Stores the new humidity
			dhtChanged = true;
		}
		//If some of the values changed, they are published
		if (dhtChanged) {
			DHTValues dhtValues;
			dhtValues.temperature100 = temperature100;
			dhtValues.humidity100 = humidity100;
			if (publish(brokerAddr, topicDht, &dhtValues, sizeof(dhtValues), _logger) != LMQ_ERR_SUCCESS)
				_logger->log(ERROR, "Failed to publish DHT values");
			
			Serial.println(sizeof(dhtValues));
		}
	}

	int potVal = analogRead(POT); //Read potentiometer value in range [0, 4095]
	potVal = map(potVal, 0, 4095, 0, 100); //Transforms to range [0,100]
	//If the value is different than the previous, it is processed
	if (fabs(potVal - lastPotVal) >= 2) { 
		lastPotVal = potVal;
		_logger->log(INFO, "Value: %d%%", potVal);
		PotValue potValue;
		potValue.potValue = potVal;
		if (publish(brokerAddr, topicPot, &potValue, sizeof(potValue), _logger) != LMQ_ERR_SUCCESS)
			_logger->log(ERROR, "Failed to publish potentiometer value");
	}

	delay(1000);
}
