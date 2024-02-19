#ifndef STRUCT_MESSAGE_H
    #define STRUCT_MESSAGE_H
    #include <stdint.h>

    #define MSGTYPE_SUBSCRIBE 1
    #define MSGTYPE_UNSUBSCRIBE 2
    #define MSGTYPE_PUBLISH 3

    typedef struct {
        char topic[10];
    } SubscribeAnnouncement;

    typedef struct {
        char topic[10];
    } UnsubscribeAnnouncement;

    typedef struct {
        char topic[10];
        uint8_t content[20];
    } PublishContent;

    typedef union {
        SubscribeAnnouncement subscribeAnnouncement;
        UnsubscribeAnnouncement unsubscribeAnnouncement;
        PublishContent publish;
    } PayloadUnion;

    typedef struct {
        uint8_t msgType;
        PayloadUnion payload;
    } Message;

#endif 

