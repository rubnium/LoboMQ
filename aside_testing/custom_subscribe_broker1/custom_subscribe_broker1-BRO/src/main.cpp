#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <ESP32MQTTBroker.h>

typedef struct {
  int number;
} PayloadStruct;

std::vector<uint8_t*> subscribers; //stores each mac
static QueueHandle_t messagesQueue = NULL;

void printSubscribers() {
  for (const auto& mac : subscribers)
    printf("%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println();
}

bool isSubscribed(const uint8_t *mac) {
  for (const auto& subscriber : subscribers) {
    if (memcmp(mac, subscriber, 6) == 0)
      return true; //already subscribed
  }
  return false; //not subscribed
}

void handleSubscribeMsg(const SubscribeAnnouncement subAnnounce, const uint8_t *mac){
  printf("Subscribed to %s by %02X:%02X:%02X:%02X:%02X:%02X\n", subAnnounce.topic, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  if (!isSubscribed(mac))
    subscribers.push_back((uint8_t*)mac);
  else
    printf("Already subscribed\n");
  
  printf("Actual subscribers:\n");
  printSubscribers();
}

void handlePublishMsg(const Message message, const uint8_t *mac){
  PublishContent pubContent = message.payload.publish;
  PayloadStruct payloadContent;
  memcpy(&pubContent.content, &payloadContent, pubContent.contentSize);

  printf("Received message by %02X:%02X:%02X:%02X:%02X:%02X:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  printf("\t- Topic: %s\n", pubContent.topic);
  printf("\t- Number: %d\n", payloadContent.number);

  xQueueSend(messagesQueue, &message, pdMS_TO_TICKS(1000));
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  Message recvMessage;
  memcpy(&recvMessage, incomingData, sizeof(recvMessage));
  if (recvMessage.msgType == MSGTYPE_SUBSCRIBE)
    handleSubscribeMsg(recvMessage.payload.subscribeAnnouncement, mac);
  else if (recvMessage.msgType == MSGTYPE_PUBLISH)
    handlePublishMsg(recvMessage, mac);
}

void ProduceMessagesTask(void *parameter) {
  for (;;) {
    PayloadStruct payload;
    payload.number = random(101);

    Message sendMessage;
    sendMessage.msgType = MSGTYPE_PUBLISH;
    strcpy(sendMessage.payload.publish.topic, "mock");

    sendMessage.payload.publish.contentSize = sizeof(payload);
    memcpy(&sendMessage.payload.publish.content, &payload, sizeof(payload));

    xQueueSend(messagesQueue, &sendMessage, pdMS_TO_TICKS(1000)); //sends the message to the queue
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void DispatchMessagesTask(void *parameter) {
  int *taskId = (int *)parameter;
  Message message;
  for (;;) {
    BaseType_t xStatus = xQueueReceive(messagesQueue, &message, pdMS_TO_TICKS(portMAX_DELAY));
    if (xStatus == pdPASS && subscribers.size() > 0) {
      for (const auto& subscriber : subscribers) {
        //Register peer
        esp_now_peer_info_t peerInfo;
        memset(&peerInfo, 0, sizeof(peerInfo));
        memcpy(peerInfo.peer_addr, subscriber, 6);
        peerInfo.channel = 0;  
        peerInfo.encrypt = false;
        esp_now_add_peer(&peerInfo);
          
        bool sent = false;
        //while (!sent) { //tries indefinitely to send the message to the subscriber
          esp_err_t sendResult = esp_now_send(subscriber, (uint8_t *)&message, sizeof(message));
          if (sendResult == ESP_OK) //if sent correctly, stops trying. TODO: replace with checking ACK
            sent=true;
        //}      
      
      }
      printf("[DISPATCHER] Sent message to %d subscribers\n", subscribers.size());
    }
  }

  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  esp_now_register_recv_cb(OnDataRecv);

  printf("\nBROKER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  messagesQueue = xQueueCreate(10, sizeof(Message));
  if (messagesQueue == NULL) {
    Serial.println("[SETUP] ERROR, Couldn't create the queue\n");
    exit(1);
  }

  BaseType_t dispatcherTaskStatus = xTaskCreate(DispatchMessagesTask, "DispatchMessagesTask", 10000, (void *)1, 1, NULL);
  BaseType_t producerTaskStatus = xTaskCreate(ProduceMessagesTask, "ProduceMessagesTask", 10000, (void *)1, 2, NULL);
  if (dispatcherTaskStatus != pdPASS || producerTaskStatus != pdPASS) {
    Serial.println("[SETUP] ERROR, Couldn't create the tasks");
    exit(1);
  }
}

void loop() { }
