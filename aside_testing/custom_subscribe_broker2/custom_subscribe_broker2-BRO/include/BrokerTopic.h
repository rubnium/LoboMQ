#ifndef BROKERTOPIC_H

#define BROKERTOPIC_H

#include <string>
#include <vector>
#include <array>

class BrokerTopic {
    private:
        std::string topic;
        std::vector<std::array<uint8_t, 6>> subscribers;

    public:
        BrokerTopic(const std::string& topic);

        const std::string& getTopic() const;
        int getSubscribersAmount() const;
        const std::vector<std::array<uint8_t, 6>>& getSubscribers() const;
        bool subscribe(const uint8_t *mac);
        bool unsubscribe(const uint8_t *mac);
        bool isSubscribed(const uint8_t *mac) const;
        std::string getSubscribersString() const;

        std::string toString() const;
};

#endif