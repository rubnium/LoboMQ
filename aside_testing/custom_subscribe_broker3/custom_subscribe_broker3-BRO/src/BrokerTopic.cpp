#include "BrokerTopic.h"
#include <Arduino.h>

BrokerTopic::BrokerTopic(): topic(""), hasWildcards(false) {}

BrokerTopic::BrokerTopic(const char topic[], const bool hasWildcards) {
  //inserts topic to the attribute
  strncpy(this->topic, topic, sizeof(this->topic) - 1);
  this->topic[sizeof(this->topic) - 1] = '\0';

  this->hasWildcards = hasWildcards;

  //initializes the queue
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

bool addPeer(const uint8_t *mac) {
  //TODO: add return false if error
  if(!esp_now_is_peer_exist(mac)) { //if peer not registered
    //Register peer
    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);
  }
  return true;
}

bool removePeer(const uint8_t *mac) {
  //Check if peer exists
  if (esp_now_is_peer_exist(mac)) {
    if (esp_now_del_peer(mac) != ESP_OK)
      return false;
    
    return true;
  } else {
    return false;
  }
}

bool BrokerTopic::subscribe(const uint8_t *mac) const {
  if (!isSubscribed(mac)) {
    const_cast<BrokerTopic*>(this)->subscribers.push_back(*reinterpret_cast<const std::array<uint8_t, 6>*>(mac));
  }
  return true;
}   

bool BrokerTopic::unsubscribe(const uint8_t *mac) {
  //TODO: not implemented yet!
  //Remove from subscribers

  //esp_now_del_peer(mac);
  return true;
}

bool BrokerTopic::isSubscribed(const uint8_t *mac) const {
  for (const auto& subscriber : subscribers) { //checks every subscriber
    if (memcmp(mac, subscriber.data(), 6) == 0) //if the mac was found
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
  if (xQueueSend(messagesQueue, pubContent, pdMS_TO_TICKS(1000)) == pdTRUE)
    return true;
  else
    return false;
}

void BrokerTopic::dispatchMessages() const {
  PublishContent message;
  if (xQueueReceive(messagesQueue, &message, pdMS_TO_TICKS(1000)) == pdPASS) { //gets the message from the queue
    for (const auto& subscriber : subscribers) { //goes through every subscriber
      addPeer(subscriber.data());
      esp_now_send(subscriber.data(), (uint8_t *)&message, sizeof(message));
    }
    printf("[DISPATCHER] Sent %s topic messages to %d subscribers\n", topic, subscribers.size());
  }
}

void BrokerTopic::publish(PublishContent pubContent) const {
  //TODO: duplicate pubContent and make pubContent.topic = topic
  for (const auto& subscriber : subscribers) { //goes through every subscriber
    addPeer(subscriber.data());
    esp_now_send(subscriber.data(), (uint8_t *)&pubContent, sizeof(PublishContent));
  }
  printf("[PUBLISHER] Sent %s topic messages to %d subscribers\n", topic, subscribers.size());
}

bool BrokerTopic::isPublishable(const char *publishTopic) const {
  //compares publishTopic with topic
  if (strcmp(publishTopic, topic) == 0) //if both topics are the same
    return true;
  else if (!hasWildcards)
    return false;
  else {
    int publishLen = strlen(publishTopic);
    int subscribeLen = strlen(topic);

    int i = 0, j = 0;

    while (i < publishLen && j < subscribeLen) { //runs through every character in the topics
      char pubChar = publishTopic[i];
      char subChar = topic[j];
      //if current chars are different and not wildcards, incompatibles
      if (pubChar != subChar && subChar != '+' && subChar != '#')  
        return false;
      if (subChar == '+') { //'+' only accepts 1 level, goes to the next topic separator '/'
        while (publishTopic[i] != '/' && i < publishLen)
          i++;
        j++;
      } else if (subChar == '#') { //'#' will accept any topic level, compatibles
        return true;
      } else {
        i++; j++;
      }
    }
    //if only one of the topics has been traversed, incompatibles
    if (i < publishLen || j < subscribeLen)
      return false;
    else 
      return true;
  }
}


std::string BrokerTopic::toString() const {
  std::string result = "Topic: " + std::string(topic) + "\n";
  result += "Subscribers:\n";
  result += getSubscribersString();
  return result;
}   
