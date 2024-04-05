#include "ESP32MQTTBroker.h"

bool configureESPNOW(uint8_t *mac) {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    return false;
  }

  //Setup ESPNOW and peer
	if(esp_now_is_peer_exist(mac)) {
    return true; //peer already registered
  } else {
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
}

int fixTopicAndCheckLength(char *topic) {
  if (topic == NULL) //if no topic was given
    return MQTT_ERR_INVAL_TOPIC;

  size_t len = strlen(topic);
  if (len == 0 || len > MAXTOPICLENGTH) //if empty or has many characters
    return MQTT_ERR_INVAL_TOPIC;

  if (topic[0] == '/') { //if leading '/', remove
    memmove(topic, topic + 1, len); //move characters one position to the left
    len--;
    if (len == 0)
      return MQTT_ERR_INVAL_TOPIC;
  }

  if (topic[len-1] == '/') { //if trailing '/'
    topic[len-1] = '\0'; //null-terminate the string to remove the trailing '/'
    len--;
    if (len == 0)
      return MQTT_ERR_INVAL_TOPIC;
  }

  return MQTT_ERR_SUCCESS;
}

bool isASCII(char c) {
  return c >= 0 && c <= 127;
}

int pubTopicCheck(char *topic) {
  if (fixTopicAndCheckLength(topic) == MQTT_ERR_INVAL_TOPIC) //removes initial or final '/' and checks its length
    return MQTT_ERR_INVAL_TOPIC;

  for (size_t i = 0; i < strlen(topic); i++) { 
    if (topic[i] == '+' || topic[i] == '#') //if there's '+' or '#' inside
      return MQTT_ERR_INVAL_TOPIC;
  }
  return MQTT_ERR_SUCCESS;
}

int subTopicCheck(char *topic) {
  if (fixTopicAndCheckLength(topic) == MQTT_ERR_INVAL_TOPIC) //removes initial or final '/' and checks its length
    return MQTT_ERR_INVAL_TOPIC;

  char prev = '\0';
  for (int i = 0; i < strlen(topic); i++) { //runs through every character
    char c = topic[i];
    if (!isASCII(c))
      return MQTT_ERR_INVAL_TOPIC;

    if (c == '+') { //if '+' was found
      if ((prev != '\0' && prev != '/') || (topic[i+1] != '\0' && topic[i+1] != '/'))
			//(not first char && not after '/') || (not last char && not followed by '/')
        return MQTT_ERR_INVAL_TOPIC;
    } else if (c == '#') { //if '#' was found
      if ((prev != '\0' && prev != '/') || topic[i+1] != '\0')
			//(not first char && not after '/') || not last char
        return MQTT_ERR_INVAL_TOPIC;
    }
    prev = c;
  }
  return MQTT_ERR_SUCCESS;
}

bool publish(uint8_t *mac, char *topic, void *payload) {
	configureESPNOW(mac);
	if (pubTopicCheck(topic) == MQTT_ERR_INVAL_TOPIC) {
		printf("Invalid topic\n");
		return false;
  }

	//Create and fill publish message
	PublishContent pubMsg;
	pubMsg.type = MSGTYPE_PUBLISH;
	strcpy(pubMsg.topic, topic);
	pubMsg.contentSize = sizeof(payload);
	memcpy(&pubMsg.content, payload, sizeof(payload));

	//Send message
	esp_err_t result = esp_now_send(mac, (uint8_t *) &pubMsg, sizeof(pubMsg));
	if (result == ESP_OK) {
    printf("Message published successfully\n");
  }

	//TODO: implement ack
	return true;
}

bool subscribe(uint8_t *mac, char *topic) {
	configureESPNOW(mac);
  if (subTopicCheck(topic) == MQTT_ERR_INVAL_TOPIC) {
		printf("Invalid topic\n");
		return false;
  }

	//Create subscribe message
	SubscribeAnnouncement subMsg;
	subMsg.type = MSGTYPE_SUBSCRIBE;
  strcpy(subMsg.topic, topic);

	//Send message
	esp_err_t result = esp_now_send(mac, (uint8_t *) &subMsg, sizeof(subMsg));
	if (result == ESP_OK) {
    printf("Message sent successfully\n");
    printf("Subscribed to: %s\n", subMsg.topic);
		return true;
  } else {
    printf("Error sending message: %d\n", result);
		return false;
  }

	//TODO: implement ack
}

bool unsubscribe(uint8_t *mac, char *topic) {
	configureESPNOW(mac);
  if (subTopicCheck(topic) == MQTT_ERR_INVAL_TOPIC) {
		printf("Invalid topic\n");
		return false;
  }

	//Create subscribe message
	UnsubscribeAnnouncement unsubMsg;
	unsubMsg.type = MSGTYPE_UNSUBSCRIBE;
  strcpy(unsubMsg.topic, topic);

	//Send message
	esp_err_t result = esp_now_send(mac, (uint8_t *) &unsubMsg, sizeof(unsubMsg));
	if (result == ESP_OK) {
    printf("Message sent successfully\n");
    printf("Unsubscribed from: %s\n", unsubMsg.topic);
		return true;
  } else {
    printf("Error sending message: %d\n", result);
		return false;
  }

	//TODO:  implement ack
}

bool isMQTTMessage(const uint8_t *incomingData) {
	MessageType msgType = ((MessageBase*)incomingData)->type;
	return msgType == MSGTYPE_PUBLISH;
}

PayloadContent getMQTTPayload(const uint8_t *incomingData) {
	PublishContent *pubMsg;
	memcpy(&pubMsg, &incomingData, sizeof(pubMsg));
	PayloadContent content;
	content.contentSize = pubMsg->contentSize;
	memcpy(content.content, &pubMsg->content, content.contentSize);
	return content;
}
