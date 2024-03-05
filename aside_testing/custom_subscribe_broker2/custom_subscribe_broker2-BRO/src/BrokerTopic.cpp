#include "BrokerTopic.h"
#include <Arduino.h>

BrokerTopic::BrokerTopic(const std::string& topic) : topic(topic) {}

const std::string& BrokerTopic::getTopic() const {
    return topic;
}

int BrokerTopic::getSubscribersAmount() const {
    return subscribers.size();
}

const std::vector<std::array<uint8_t, 6>>& BrokerTopic::getSubscribers() const {
    return subscribers;
}

bool BrokerTopic::subscribe(const uint8_t *mac) {
    if (!isSubscribed(mac))
        subscribers.push_back(*reinterpret_cast<const std::array<uint8_t, 6>*>(mac));
    return true;
}   

bool BrokerTopic::unsubscribe(const uint8_t *mac) {
    //TODO: not implemented yet!
    return false;
}

bool BrokerTopic::isSubscribed(const uint8_t *mac) const {
    for (const auto& subscriber : subscribers) {
        if (std::equal(mac, mac + 6, subscriber))
            return true; //already subscribed
    }
    return false; //not subscribed
}

std::string BrokerTopic::getSubscribersString() const {
    std::string result = "";
    for (const auto& mac : subscribers)
        result += std::to_string(mac[0]) + ":" + std::to_string(mac[1]) + ":" + std::to_string(mac[2]) + ":" + std::to_string(mac[3]) + ":" + std::to_string(mac[4]) + ":" + std::to_string(mac[5]) + "\n";
    return result;
}

std::string BrokerTopic::toString() const {
    std::string result = "Topic: " + topic + "\n";
    result += "Subscribers:\n";
    result += getSubscribersString();
    return result;
}   
