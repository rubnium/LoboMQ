#include "BrokerTopic.h"
#include <Arduino.h>

BrokerTopic::BrokerTopic(): topic(""){}

BrokerTopic::BrokerTopic(const char topic[]) {
  strncpy(this->topic, topic, sizeof(this->topic) - 1);
  this->topic[sizeof(this->topic) - 1] = '\0';
  messagesQueue = xQueueCreate(10, sizeof(PublishContent));
  if (messagesQueue == NULL) {
    Serial.println("[BROKER TOPIC] ERROR, Couldn't create the queue");
    return;
  }
}

const char* BrokerTopic::getTopic() const {
  return topic;
}

int BrokerTopic::getSubscribersAmount() const {
  return subscribers.size();
}

const std::vector<std::array<uint8_t, 6>>& BrokerTopic::getSubscribers() const {
  return subscribers;
}

bool BrokerTopic::subscribe(const uint8_t *mac) const {
  if (!isSubscribed(mac))
     const_cast<BrokerTopic*>(this)->subscribers.push_back(*reinterpret_cast<const std::array<uint8_t, 6>*>(mac));
  return true;
}   

bool BrokerTopic::unsubscribe(const uint8_t *mac) {
  //TODO: not implemented yet!
  return false;
}

bool BrokerTopic::isSubscribed(const uint8_t *mac) const {
  for (const auto& subscriber : subscribers) {
    if (memcmp(mac, subscriber.data(), 6) == 0)
      return true; //already subscribed
  }
  return false; //not subscribed
}

std::string BrokerTopic::getSubscribersString() const {
  std::string result = "";
  for (const auto& mac : subscribers) {
    char macChar[18];
    snprintf(macChar, sizeof(macChar), "%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    result += macChar;
  }
  return result;
}

bool BrokerTopic::sendToQueue(const PublishContent *pubContent) const {
  //TODO: duplicate pubContent and make pubContent.topic = topic
  if (xQueueSend(messagesQueue, &pubContent, pdMS_TO_TICKS(1000)) == pdTRUE)
    return true;
  else
    return false;
}

void BrokerTopic::dispatchMessages(esp_now_peer_info_t peerInfo) const {
  PublishContent message;
  if (xQueueReceive(messagesQueue, &message, pdMS_TO_TICKS(1000)) == pdPASS) {
    for (const auto& subscriber : subscribers) {
      //Register peer
      memset(&peerInfo, 0, sizeof(&peerInfo));
      memcpy(peerInfo.peer_addr, subscriber.data(), 6);
      peerInfo.channel = 0;  
      peerInfo.encrypt = false;
      esp_now_add_peer(&peerInfo);

      printf("Tamaño mensaje: %d\n", sizeof(message));
      esp_now_send(subscriber.data(), (uint8_t *)&message, sizeof(message));
    }

    printf("[DISPATCHER] Sent %s topic messages to %d subscribers\n", topic, subscribers.size());
  }
}

std::string BrokerTopic::toString() const {
  std::string result = "Topic: " + std::string(topic) + "\n";
  result += "Subscribers:\n";
  result += getSubscribersString();
  return result;
}   
