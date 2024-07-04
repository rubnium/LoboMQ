#include "LoboMQ/PubSub.h"

Elog *logger;

bool configureESPNOW(uint8_t *mac) {
	logger->log(DEBUG, "Setting up ESP-NOW and connection with broker at %02X:%02X:%02X:%02X:%02X:%02X.",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //initialize ESP-NOW
    logger->log(ERROR, "Couldn't initialize ESP-NOW");
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
			logger->log(ERROR, "Couldn't register peer: %d.", result);
			return false;
		}
		return true;
	}
}

int fixTopicAndCheckLength(char *topic) {
  if (topic == NULL) //if no topic was given
    return LMQ_ERR_INVAL_TOPIC;

  size_t len = strlen(topic);
  if (len == 0 || len > MAXTOPICLENGTH) //if empty or has many characters
    return LMQ_ERR_INVAL_TOPIC;

  if (topic[0] == '/') { //if leading '/', remove
    memmove(topic, topic + 1, len); //move characters one position to the left
    len--;
    if (len == 0)
      return LMQ_ERR_INVAL_TOPIC;
  }

  if (topic[len-1] == '/') { //if trailing '/'
    topic[len-1] = '\0'; //null-terminate the string to remove the trailing '/'
    len--;
    if (len == 0)
      return LMQ_ERR_INVAL_TOPIC;
  }

  return LMQ_ERR_SUCCESS;
}

bool isASCII(char c) {
  return c >= 0 && c <= 127;
}

int pubTopicCheck(char *topic) {
  if (fixTopicAndCheckLength(topic) == LMQ_ERR_INVAL_TOPIC) //removes initial or final '/' and checks its length
    return LMQ_ERR_INVAL_TOPIC;

  for (size_t i = 0; i < strlen(topic); i++) { 
    if (topic[i] == '+' || topic[i] == '#' || !isASCII(topic[i])) //if there's '+', '#' or a non-ASCII character
      return LMQ_ERR_INVAL_TOPIC;
  }
  return LMQ_ERR_VALID_TOPIC;
}

int subTopicCheck(char *topic) {
  if (fixTopicAndCheckLength(topic) == LMQ_ERR_INVAL_TOPIC) //removes initial or final '/' and checks its length
    return LMQ_ERR_INVAL_TOPIC;

  char prev = '\0';
  for (int i = 0; i < strlen(topic); i++) { //runs through every character
    char c = topic[i];
    if (!isASCII(c))
      return LMQ_ERR_INVAL_TOPIC;

    if (c == '+') { //if '+' was found
      if ((prev != '\0' && prev != '/') || (topic[i+1] != '\0' && topic[i+1] != '/'))
			//(not first char && not after '/') || (not last char && not followed by '/')
        return LMQ_ERR_INVAL_TOPIC;
    } else if (c == '#') { //if '#' was found
      if ((prev != '\0' && prev != '/') || topic[i+1] != '\0')
			//(not first char && not after '/') || not last char
        return LMQ_ERR_INVAL_TOPIC;
    }
    prev = c;
  }
  return LMQ_ERR_VALID_TOPIC;
}

LMQErrType publish(uint8_t *mac, char *topic, void *payload, Elog *_logger) {
	logger = _logger;
	if (!configureESPNOW(mac)) {
		return LMQ_ERR_BAD_ESP_CONFIG;
	}
	if (pubTopicCheck(topic) == LMQ_ERR_INVAL_TOPIC) {
		logger->log(ERROR, "Invalid topic: '%s'", topic);
		return LMQ_ERR_INVAL_TOPIC;
  }

	//Create and fill publish message
	PublishContent pubMsg;
	pubMsg.type = MSGTYPE_PUBLISH;
	strcpy(pubMsg.topic, topic);
	pubMsg.contentSize = sizeof(payload);
	memcpy(&pubMsg.content, payload, sizeof(payload));

	//Send message
	esp_err_t result = esp_now_send(mac, (uint8_t *) &pubMsg, sizeof(pubMsg));
	if (result != ESP_OK) {
		logger->log(ERROR, "Error sending message: %d.", result);
		return LMQ_ERR_ESP_SEND_FAIL;
  }
	logger->log(INFO, "Message of %dB published successfully to '%s'.", sizeof(payload), topic);

	return LMQ_ERR_SUCCESS;
}

LMQErrType subscribe(uint8_t *mac, char *topic, Elog *_logger) {
	logger = _logger;
	if (!configureESPNOW(mac)) {
		return LMQ_ERR_BAD_ESP_CONFIG;
	}
  if (subTopicCheck(topic) == LMQ_ERR_INVAL_TOPIC) {
		logger->log(ERROR, "Invalid topic: '%s'.", topic);
		return LMQ_ERR_INVAL_TOPIC;
  }

	//Create subscribe message
	SubscribeAnnouncement subMsg;
	subMsg.type = MSGTYPE_SUBSCRIBE;
  strcpy(subMsg.topic, topic);

	//Send message
	esp_err_t result = esp_now_send(mac, (uint8_t *) &subMsg, sizeof(subMsg));
	if (result != ESP_OK) {
		logger->log(ERROR, "Error sending message: %d.", result);
		return LMQ_ERR_ESP_SEND_FAIL;
  }
  logger->log(INFO, "Subscribed to '%s'.", subMsg.topic);
	
	return LMQ_ERR_SUCCESS;
}

LMQErrType unsubscribe(uint8_t *mac, char *topic, Elog *_logger) {
	logger = _logger;
	if (!configureESPNOW(mac)) {
		return LMQ_ERR_BAD_ESP_CONFIG;
	}
  if (subTopicCheck(topic) == LMQ_ERR_INVAL_TOPIC) {
		logger->log(ERROR, "Invalid topic: '%s'.", topic);
		return LMQ_ERR_INVAL_TOPIC;
  }

	//Create subscribe message
	UnsubscribeAnnouncement unsubMsg;
	unsubMsg.type = MSGTYPE_UNSUBSCRIBE;
  strcpy(unsubMsg.topic, topic);

	//Send message
	esp_err_t result = esp_now_send(mac, (uint8_t *) &unsubMsg, sizeof(unsubMsg));
	if (result != ESP_OK) {
		logger->log(ERROR, "Error sending message: %d.", result);
		return LMQ_ERR_ESP_SEND_FAIL;
  }
  logger->log(INFO, "Unsubscribed from '%s'.", unsubMsg.topic);
	return LMQ_ERR_SUCCESS;

	return LMQ_ERR_SUCCESS;
}

bool isLMQMessage(const uint8_t *incomingData) {
	MessageType msgType = ((MessageBase*)incomingData)->type;
	return msgType == MSGTYPE_PUBLISH;
}

PayloadContent getLMQPayload(const uint8_t *incomingData) {
	PublishContent *pubMsg;
	memcpy(&pubMsg, &incomingData, sizeof(pubMsg));
	PayloadContent content;
	content.contentSize = pubMsg->contentSize;
	memcpy(content.content, &pubMsg->content, content.contentSize);
	return content;
}
