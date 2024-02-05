#ifndef STRUCT_MESSAGE_H
#define STRUCT_MESSAGE_H

#include <stdint.h>
#include <freertos/FreeRTOS.h>

typedef struct struct_message {
    TickType_t xTimeStamp;
    char msg[50];
    float humidity;
    float temperature;
} struct_message;

#endif //STRUCT_MESSAGE_H