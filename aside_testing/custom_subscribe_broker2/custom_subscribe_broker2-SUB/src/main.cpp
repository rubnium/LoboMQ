#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include <ESP32MQTTBroker.h>

typedef struct {
  int number;
} PayloadStruct;

uint8_t destBoardAddr[] = {0xC0, 0x49, 0xEF, 0xCA, 0x2B, 0x74}; //MAC destination address

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  MessageType msgType = ((MessageBase*)incomingData)->type;

  if (msgType == MSGTYPE_PUBLISH) {
    PublishContent *pubMsg;
    memcpy(&pubMsg, &incomingData, sizeof(pubMsg));

    printf("Received message from broker: (%d bytes)\n", sizeof(pubMsg));
    printf("\t- Topic: %s\n", pubMsg->topic);
    /*
    printf("\t- Content (in bytes): \n");
    for (int i = 0; i < sizeof(pubMsg.content); i++) {
      printf("%02X ", pubMsg.content+i);
    }
    printf("\n");*/

    PayloadStruct payloadContent;
    memcpy(&payloadContent, &pubMsg->content, pubMsg->contentSize);
    printf("\t- Number: %d\n", payloadContent.number);
  }
}

void subscribe(const char* topic){
  SubscribeAnnouncement subMsg;
  subMsg.type = MSGTYPE_SUBSCRIBE;
  strcpy(subMsg.topic, topic);
  esp_err_t result = esp_now_send(destBoardAddr, (uint8_t *) &subMsg, sizeof(subMsg));
  if (result == ESP_OK) {
    printf("Message sent successfully\n");
    printf("Subscribed to: %s\n",subMsg.topic);
  }
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) { //Initialize ESP-NOW
    Serial.println("[SETUP] Error initializing ESP-NOW");
    exit(1);
  }
  esp_now_register_recv_cb(OnDataRecv);
  printf("\nSUBSCRIBER BOARD\n");
  Serial.println((String)"MAC Addr: "+WiFi.macAddress());

  //Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, destBoardAddr, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  //Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("[SETUP] Error adding peer");
    exit(1);
  }

  subscribe("topic1");
}

void loop() {
  sleep(2);
}
