/**
 * @file BrokerTopic.h
 * @author Rubén Gómez Villegas
 * 
 * This library is used to create a MQTT Broker using ESP32 and ESP-NOW protocol.
 */

#ifndef BROKERTOPIC_H

#define BROKERTOPIC_H

#include <Arduino.h>
#include <esp_now.h>
#include <string>
#include <vector>
#include <array>

#include "PubSub.h"

class BrokerTopic {
  private:
    char topic[MAXTOPICLENGTH];
    std::vector<std::array<uint8_t, 6>> subscribers;
		char filename[MAXTOPICLENGTH*2]; //double the topic size, if it has to store special chars
    QueueHandle_t messagesQueue;
    bool hasWildcards;
		Elog *logger;

  public:
    BrokerTopic();
    BrokerTopic(Elog *_logger, const char topic[]);

    const char* getTopic() const;
    int getSubscribersAmount() const;
    const std::vector<std::array<uint8_t, 6>>& getSubscribers() const;
		const char* getFilename() const;
		void setFilename(const char* filename);
    bool subscribe(const uint8_t *mac) const;
		bool subscribe(const std::array<uint8_t, 6> &mac) const;
    bool unsubscribe(const uint8_t *mac);
    bool isSubscribed(const uint8_t *mac) const;
    std::string getSubscribersString() const;
    bool sendToQueue(const PublishContent *pubContent) const;
    void dispatchMessages() const;
    void publish(PublishContent pubContent, std::vector<std::array<uint8_t, 6>>& alreadySentMacs) const;
    bool isPublishable(const char *publishTopic) const;

    std::string toString() const;
};

#endif
