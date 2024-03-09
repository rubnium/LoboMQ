#include "ESP32MQTTBroker.h"


bool publish(uint8_t *mac, char *topic, void *payload) {
	//Create and fill message
	PublishContent pubMsg;
	pubMsg.type = MSGTYPE_PUBLISH;
	strcpy(pubMsg.topic, topic);
	pubMsg.contentSize = sizeof(payload);
	memcpy(&pubMsg.content, payload, sizeof(payload));

	//Send message
	//TODO: try sending message without registering peer
	esp_err_t result = esp_now_send(mac, (uint8_t *) &pubMsg, sizeof(pubMsg));
	if (result == ESP_OK) {
    printf("Message published successfully\n");
  }

	//TODO: implement ack
	return true;
}


bool subscribe(uint8_t *mac, char *topic) {
	SubscribeAnnouncement subMsg;
	subMsg.type = MSGTYPE_SUBSCRIBE;
  strcpy(subMsg.topic, topic);

	//Send message
	//TODO: try sending message without registering peer
	esp_err_t result = esp_now_send(mac, (uint8_t *) &subMsg, sizeof(subMsg));
	if (result == ESP_OK) {
    printf("Message sent successfully\n");
    printf("Subscribed to: %s\n",subMsg.topic);
  }

	//TODO: implement ack
	return true;
}