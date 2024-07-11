/**
 * LoboMQ Subscriber Example
 * This subscriber example subscribes to any topic to receive a random number.
 * After 20 seconds, unsubscribes.
 * 
 * https://github.com/rubnium/LoboMQ
 */

#include <LoboMQ/PubSub.h>

uint8_t brokerAddr[] = {0x24, 0xDC, 0xC3, 0x9C, 0x7E, 0x40}; //Broker MAC destination

Elog *_logger;

//Function called on every ESP-NOW message reception
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (isLMQMessage(incomingData)) {
    PayloadContent content = getLMQPayload(incomingData);

		int numberExample;
    memcpy(&numberExample, &content.content, content.contentSize);

		_logger->log(INFO, "Received LMQ message of %dB", content.contentSize);
		_logger->log(INFO, "Number: %d", numberExample);
  } else {
    _logger->log(ERROR, "Invalid message type received");
  }
}

void setup() {
  Serial.begin(9600);

	//Choose logger:
	_logger = initializeSerialLogger(SUBSCRIBER, DEBUG);
	//_logger = initializeSDLogger(...);
	//_logger = disableLogger();

  WiFi.mode(WIFI_STA);

  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    _logger->log(ERROR, "Couldn't initialize ESP-NOW");
    exit(1);
  }

  _logger->log(INFO, "Started subscriber board on %s!", WiFi.macAddress().c_str());

  subscribe(brokerAddr, "#", _logger);
  sleep(20);
  unsubscribe(brokerAddr, "#", _logger);
}

void loop() { }
