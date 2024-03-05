#include "CustomObject.h"
#include <Arduino.h>

CustomObject::CustomObject() : id(0), topic("") {}
CustomObject::CustomObject(int id, std::string topic) : id(id), topic(topic) {}

int CustomObject::getID() const {
    return id;
}

std::string CustomObject::getTopic() const {
    return topic;
}

std::string CustomObject::serialize() const {
    std::ostringstream oss;
    oss << id << " ";
    oss << topic << " ";

    return oss.str();
}

void CustomObject::deserialize(const std::string& data) {
    std::istringstream iss(data);
    iss >> id;
    iss >> topic;
}
