#include "unnamedMQ/Broker.h"
#include "unnamedMQ/BrokerTopic.h"
#include "unnamedMQ/BrokerSDUtils.h"

#define SUBSCRIBETASKS 1
#define UNSUBSCRIBETASKS 1
#define PUBLISHTASKS 1


std::vector<BrokerTopic> topicsVector; //each topic has messages and subscribers

//Message queues
QueueHandle_t subMsgQueue;
QueueHandle_t unsubMsgQueue;
QueueHandle_t pubMsgQueue;

Elog *logger;
bool gPersistence;
int gCsSdPin;
//Mutex semaphore
SemaphoreHandle_t mutex;

bool hasWildcard(const char topic[]) {
  for (int i = 0; i < strlen(topic); i++) {
    if (topic[i] == '+' || topic[i] == '#')
      return true;
  }
  return false;
}

void SubscribeTask(void *parameter) {
  for (;;) {
    SubscribeTaskParams *subParams;
    if (xQueueReceive(subMsgQueue, &subParams, portMAX_DELAY) == pdPASS) { //gets the message from the queue
			//Extracts fields from the subscription parameters
      SubscribeAnnouncement *subAnnounce = subParams->subAnnounce;
      const uint8_t *mac = subParams->mac;

      logger->log(INFO, "Subscribing to '%s' by %02X:%02X:%02X:%02X:%02X:%02X",
        subAnnounce->topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

      bool subscribed = false;
      for (const auto& topicObject : topicsVector) { //checks every topicObject to subscribe to the proper ones
        if (strcmp(subAnnounce->topic, topicObject.getTopic()) == 0) { //if the topic in message is the same as the topicObject
          if (!topicObject.isSubscribed(mac)) {
            topicObject.subscribe(mac);
          } else {
            logger->log(INFO, "\tAlready subscribed to '%s'", topicObject.getTopic());
          }
          subscribed = true; //if the topic was found in the vector
          break; //exit loop, no need to keep searching topics
        }
      }

      if (!subscribed) { //if it's a topic not existing in the vector
        logger->log(INFO, "Topic '%s' not found, creating a new topic", subAnnounce->topic);

        BrokerTopic newTopic(logger, subAnnounce->topic, hasWildcard(subAnnounce->topic));
        newTopic.subscribe(mac);
        topicsVector.push_back(newTopic);
      }
      free(subParams->subAnnounce);
      free(subParams);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void UnsubscribeTask(void *parameter) {
  UnsubscribeTaskParams *unsubParams;

  for (;;) {
    if (xQueueReceive(unsubMsgQueue, &unsubParams, portMAX_DELAY) == pdPASS) { //gets the message from the queue
      //Extracts fields from the unsubscription parameters
			UnsubscribeAnnouncement *unsubAnnounce = unsubParams->unsubAnnounce;
      const uint8_t *mac = unsubParams->mac;

      logger->log(INFO, "Unsubscribing %02X:%02X:%02X:%02X:%02X:%02X from '%s'",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], unsubAnnounce->topic);

      bool unsubscribed = false;
      for (auto it = topicsVector.begin(); it != topicsVector.end(); ++it) { //checks every topicObject
        if (strcmp(unsubAnnounce->topic, it->getTopic()) == 0) { //if the topic in message is the same as the topicObject
          if (it->isSubscribed(mac)) {
            it->unsubscribe(mac);
            if (it->getSubscribersAmount() == 0) { //if topicObject has no subscribers,
              logger->log(INFO, "Topic '%s' has no subscribers, is being deleted", it->getTopic());
              topicsVector.erase(it); //delete topicObject from topicsVector
            }
            unsubscribed = true;
            break; //exit loop, no need to keep searching topics
          }
        }
      }

      if (!unsubscribed) { //if it's a topic not existing in the vector
        logger->log(INFO, "\tTopic '%s' not found, it was not subscribed", unsubAnnounce->topic);
      }
      free(unsubParams->unsubAnnounce);
      free(unsubParams);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

void PublishTask(void *parameter) {
  PublishTaskParams *pubParams;
  for (;;) {
    if (xQueueReceive(pubMsgQueue, &pubParams, portMAX_DELAY) == pdPASS) { //gets the message from the queue
			//Extracts fields from the publication parameters
      PublishContent *pubContent = pubParams->pubContent;
      const uint8_t *mac = pubParams->mac;

      bool sent = false;
      std::vector<std::array<uint8_t, 6>> alreadySentMacs;
      for (const auto& topicObject : topicsVector) { //checks every topicObject to send the message to the proper ones
        if (topicObject.isPublishable(pubContent->topic)) { //if the topic in message is compatible with the topicObject
          topicObject.publish(*pubContent, alreadySentMacs);
          sent = true; //the topic was found in the vector
        }
      }

    	logger->log(INFO, "Received a %dB message by %02X:%02X:%02X:%02X:%02X:%02X with topic '%s':", pubContent->contentSize, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], pubContent->topic);
      if (!sent) { //if it's a topic not existing in the vector
        logger->log(INFO, "\tTopic '%s' not found (has no subscribers, so it isn't published)", pubContent->topic);
      } else {
        logger->log(INFO, "\tSent to %d subscribers", alreadySentMacs.size());
      }
			free(pubParams->pubContent);
      free(pubParams);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  MessageType msgType = ((MessageBase*)incomingData)->type;
  switch (msgType) {
    case MSGTYPE_SUBSCRIBE: {
			logger->log(DEBUG, "Received a subscribe message from %02X:%02X:%02X:%02X:%02X:%02X, adding it to the queue",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      //Initialize subTaskParams with the subscribe message
      SubscribeTaskParams *subTaskParams = (SubscribeTaskParams*)malloc(sizeof(SubscribeTaskParams));
      if (subTaskParams == NULL) {
				logger->log(ERROR, "Couldn't allocate memory for subscribe task params");
        return;
      }
      subTaskParams->subAnnounce = (SubscribeAnnouncement*)malloc(sizeof(SubscribeAnnouncement));
      if (subTaskParams->subAnnounce == NULL) {
				logger->log(ERROR, "Couldn't allocate memory for subscribe announcement");
        free(subTaskParams);
        return;
      }
      memcpy(subTaskParams->subAnnounce, (SubscribeAnnouncement*)incomingData, sizeof(SubscribeAnnouncement));
      subTaskParams->mac = mac;

      if (xQueueSend(subMsgQueue, &subTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
				logger->log(ERROR, "Couldn't send the subscribe message to the queue");
        free(subTaskParams->subAnnounce);
        free(subTaskParams);
        return;
      }
    } break;
    case MSGTYPE_UNSUBSCRIBE: {
			logger->log(DEBUG, "Received an unsubscribe message from %02X:%02X:%02X:%02X:%02X:%02X, adding it to the queue",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      //Initialize unsubTaskParams with the unsubscribe message
      UnsubscribeTaskParams *unsubTaskParams = (UnsubscribeTaskParams*)malloc(sizeof(UnsubscribeTaskParams));
      if (unsubTaskParams == NULL) {
        logger->log(ERROR, "Couldn't allocate memory for unsubscribe task params");
        return;
      }
      unsubTaskParams->unsubAnnounce = (UnsubscribeAnnouncement*)malloc(sizeof(UnsubscribeAnnouncement));
      if (unsubTaskParams->unsubAnnounce == NULL) {
        logger->log(ERROR, "Couldn't allocate memory for unsubscribe announcement");
        free(unsubTaskParams);
        return;
      }
      memcpy(unsubTaskParams->unsubAnnounce, (UnsubscribeAnnouncement*)incomingData, sizeof(UnsubscribeAnnouncement));
      unsubTaskParams->mac = mac;

      if (xQueueSend(unsubMsgQueue, &unsubTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        logger->log(ERROR, "Couldn't send the unsubscribe message to the queue");
        return;
      }
    } break;
    case MSGTYPE_PUBLISH: {
			logger->log(DEBUG, "Received a publish message from %02X:%02X:%02X:%02X:%02X:%02X, adding it to the queue",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			//Initialize publishTaskParams with the publish message
      PublishTaskParams *pubTaskParams = (PublishTaskParams*)malloc(sizeof(PublishTaskParams));
      if (pubTaskParams == NULL) {
        logger->log(ERROR, "Couldn't allocate memory for publish task params");
        return;
      }
      pubTaskParams->pubContent = (PublishContent*)malloc(sizeof(PublishContent));
      if (pubTaskParams->pubContent == NULL) {
        logger->log(ERROR, "Couldn't allocate memory for publish content");
        free(pubTaskParams);
        return;
      }
      memcpy(pubTaskParams->pubContent, (PublishContent*)incomingData, sizeof(PublishContent));
      pubTaskParams->mac = mac;
      if (xQueueSend(pubMsgQueue, &pubTaskParams, pdMS_TO_TICKS(1000)) != pdTRUE) {
        logger->log(ERROR, "Couldn't send the publish message to the queue");
        return;
      }
    } break;

    default: {
			//Log with "invalid message" and the sender's mac
			logger->log(INFO, "Invalid message type received from %02X:%02X:%02X:%02X:%02X:%02X\n",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    } break;
  }
}

void setupBroker(Elog *_logger, bool persistence, int csSdPin) {
	logger = _logger;
  randomSeed(analogRead(0)); //to generate random numbers
	logger->log(DEBUG, "Initializing broker...");

	//Retrieve topics from SD card (if persistence is enabled)
	gCsSdPin = csSdPin;
	gPersistence = persistence;
	if (gPersistence) {
		mutex = xSemaphoreCreateBinary();
		if(mutex == NULL) {
			logger->log(ERROR, "Failed to create mutex, trying to continue without persistence");
			gPersistence = false;
		} else {
			xSemaphoreGive(mutex);
			if (!initializeSDCard(gCsSdPin, logger, &mutex, portMAX_DELAY)) {
				logger->log(WARNING, "Couldn't initialize SD card for persistence, continuing without it");
				gPersistence = false;
			} else {
				logger->log(INFO, "SD card initialized for persistence");
			}
		}
	}

  WiFi.mode(WIFI_STA);
  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    logger->log(CRITICAL, "Couldn't initialize ESP-NOW, aborting!");
    exit(1);
  }

  subMsgQueue = xQueueCreate(10, sizeof(SubscribeTaskParams));
  if (subMsgQueue == NULL) {
    logger->log(CRITICAL, "Couldn't create the subscribe message queue, aborting!");
    exit(1);
  }

  unsubMsgQueue = xQueueCreate(10, sizeof(UnsubscribeTaskParams));
  if (unsubMsgQueue == NULL) {
    logger->log(CRITICAL, "Couldn't create the unsubscribe message queue, aborting!");
    exit(1);
  }

  pubMsgQueue = xQueueCreate(10, sizeof(PublishTaskParams));
  if (pubMsgQueue == NULL) {
    logger->log(CRITICAL, "Couldn't create the publish message queue");
    exit(1);
  }


  char taskName[20];

  for (int i = 0; i < SUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "SubscribeTask%d", 0+1);
    if (xTaskCreate(SubscribeTask, taskName, 10000, (void *) i, 1, NULL) != pdPASS) {
      logger->log(CRITICAL, "Couldn't create the subscribe task");
      exit(1);
    }
  }

  for (int i = 0; i < UNSUBSCRIBETASKS; i++) {
    snprintf(taskName, sizeof(taskName), "UnsubscribeTask%d", i+1);
    if (xTaskCreate(UnsubscribeTask, taskName, 10000, (void *) i, 1, NULL) != pdPASS) {
      logger->log(CRITICAL, "Couldn't create the unsubscribe task");
      exit(1);
    }
  }

  for (int i = 0; i < PUBLISHTASKS; i++) {
    snprintf(taskName, sizeof(taskName), "PublishTask%d", i+1);
    if (xTaskCreate(PublishTask, taskName, 10000, (void *) i, 1, NULL) != pdPASS) {
      logger->log(CRITICAL, "Couldn't create the publish task");
      exit(1);
    }
  }
	logger->log(INFO, "Broker is running at %s!", WiFi.macAddress().c_str());
}
