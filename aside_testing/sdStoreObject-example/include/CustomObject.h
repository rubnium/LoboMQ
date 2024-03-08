#ifndef CUSTOMOBJECT_H

#define CUSTOMOBJECT_H

#include <string>
#include <sstream>

class CustomObject {
    private:
        int id;
        std::string topic;

    public:
        CustomObject();
        CustomObject(int id, std::string topic);

        int getID() const;
        std::string getTopic() const;

        std::string serialize() const;
        void deserialize(const std::string& data);
};

#endif
