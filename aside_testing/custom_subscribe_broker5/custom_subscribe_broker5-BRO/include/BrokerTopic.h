#ifndef BROKERTOPIC_H

#define BROKERTOPIC_H

#include <esp_now.h>
#include <string>
#include <vector>
#include <array>

#include <ESP32MQTTBroker.h>

class BrokerTopic {
  private:
    char topic[10];
    std::vector<std::array<uint8_t, 6>> subscribers;
    QueueHandle_t messagesQueue;
    bool hasWildcards;

  public:
    BrokerTopic();
    BrokerTopic(const char topic[], const bool hasWildcards);

    const char* getTopic() const;
    int getSubscribersAmount() const;
    const std::vector<std::array<uint8_t, 6>>& getSubscribers() const;
    bool subscribe(const uint8_t *mac) const;
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
