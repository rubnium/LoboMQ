#include <unnamedMQ/PubSub.h>

typedef struct {
  int number;
} CustomPayloadStruct;

uint8_t brokerAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

Elog *_logger;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  if (isMQMessage(incomingData)) {
    PayloadContent content = getMQPayload(incomingData);
    CustomPayloadStruct customPayloadStruct;
    memcpy(&customPayloadStruct, &content.content, content.contentSize);
		_logger->log(INFO, "Received MQ message of %dB", content.contentSize);
    printf("\t- Number: %d\n", customPayloadStruct.number);
  } else {
    _logger->log(ERROR, "Invalid message type received");
  }
}

void setup() {
  Serial.begin(9600);
	_logger = initializeSerialLogger(SUBSCRIBER, INFO);

  WiFi.mode(WIFI_STA);

  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    _logger->log(ERROR, "Couldn't initialize ESP-NOW");
    exit(1);
  }

  printf("\nSUBSCRIBER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  subscribe(brokerAddr, "#", _logger);
  subscribe(brokerAddr, "s/+", _logger);
  subscribe(brokerAddr, "s/mock", _logger);

  sleep(20);

  unsubscribe(brokerAddr, "#", _logger);
  unsubscribe(brokerAddr, "s/+", _logger);
}

void loop() { }
