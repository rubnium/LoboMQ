#include "ESP32MQTTBroker.h"

bool configureESPNOW(uint8_t *mac) {
  //Setup ESPNOW and peer
	//TODO: check if peer was already registered
	esp_now_peer_info_t peerInfo;
	memset(&peerInfo, 0, sizeof(peerInfo));
	memcpy(peerInfo.peer_addr, mac, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;

  esp_err_t result = esp_now_add_peer(&peerInfo);
  if (result != ESP_OK) {
    printf("Error registering peer: %d\n", result);
    return false;
  }
  return true;
} 

bool publish(uint8_t *mac, char *topic, void *payload) {
	configureESPNOW(mac);

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
	configureESPNOW(mac);

	//Create subscribe message
	SubscribeAnnouncement subMsg;
	subMsg.type = MSGTYPE_SUBSCRIBE;
  strcpy(subMsg.topic, topic);

	//Send message
	//TODO: try sending message without registering peer
	esp_err_t result = esp_now_send(mac, (uint8_t *) &subMsg, sizeof(subMsg));
	if (result == ESP_OK) {
    printf("Message sent successfully\n");
    printf("Subscribed to: %s\n",subMsg.topic);
		return true;
  } else {
    printf("Error sending message: %d\n", result);
		return false;
  }

	//TODO: implement ack
}

bool isMQTTMessage(const uint8_t *incomingData) {
	MessageType msgType = ((MessageBase*)incomingData)->type;
	return msgType == MSGTYPE_PUBLISH;
}

ContentProperties getMQTTContent(const uint8_t *incomingData) {
	PublishContent *pubMsg;
	memcpy(&pubMsg, &incomingData, sizeof(pubMsg));
	ContentProperties content;
	content.contentSize = pubMsg->contentSize;
	memcpy(content.content, &pubMsg->content, content.contentSize);
	return content;
}
