#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_POSIX_SIGNALS
#include "doctest.h"
#include "LoboMQ/PubSub.cpp"

//Every topic case
char *startingTrailingSlashTopic = "/aaa/";
char *onlyTopic = "aaa";
char *trailingPlusTopic = "aaa/+";
char *middlePlusTopic = "aaa/+/aaa";
char *startingPlusTopic = "+/aaa";
char *onlyPlusTopic = "+";
char *trailingHashTopic = "aaa/#";
char *middleHashTopic = "aaa/#/aaa";
char *startingHashTopic = "#/aaa";
char *onlyHashTopic = "#";
char *onlySlashTopic = "/";
char *emptyTopic = "";
char *nullTopic;
char *nonASCIITopic = "ááá";
char *bigTopic = "aaaaaaaaaaaaaaaaaaaaaaaaaa";

//Payload structure
typedef struct {
  int number;
} CustomPayloadStruct;

TEST_CASE("Create Message And Check And Get Content") {
  int number = 666;

	//Create and fill publish message
  CustomPayloadStruct payloadSend;
  payloadSend.number = number;
  PublishContent pubMsg;
  pubMsg.type = MSGTYPE_PUBLISH;
  strcpy(pubMsg.topic, "test");
  pubMsg.contentSize = sizeof(payloadSend);
  memcpy(&pubMsg.content, &payloadSend, sizeof(payloadSend));

  //Transform to bytes
  const uint8_t *data = (const uint8_t *) &pubMsg;

  CHECK(isLMQMessage(data) == true);

  //Extract payload from bytes
  PayloadContent contentRecv = getLMQPayload(data);
  CustomPayloadStruct payloadRecv;
  memcpy(&payloadRecv, &contentRecv.content, contentRecv.contentSize);

  CHECK(payloadRecv.number == number);
}

TEST_CASE("Publish Topic Checks") {
  CHECK(pubTopicCheck(startingTrailingSlashTopic) == LMQ_ERR_SUCCESS);
  CHECK(pubTopicCheck(onlyTopic) == LMQ_ERR_SUCCESS);
  CHECK(pubTopicCheck(trailingPlusTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(middlePlusTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(startingPlusTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(onlyPlusTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(trailingHashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(middleHashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(startingHashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(onlyHashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(onlySlashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(emptyTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(nullTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(nonASCIITopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(pubTopicCheck(bigTopic) == LMQ_ERR_INVAL_TOPIC);
}

TEST_CASE("Subscribe Topic Checks") {
  CHECK(subTopicCheck(startingTrailingSlashTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(onlyTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(trailingPlusTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(middlePlusTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(startingPlusTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(onlyPlusTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(trailingHashTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(middleHashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(subTopicCheck(startingHashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(subTopicCheck(onlyHashTopic) == LMQ_ERR_SUCCESS);
  CHECK(subTopicCheck(onlySlashTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(subTopicCheck(emptyTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(subTopicCheck(nullTopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(subTopicCheck(nonASCIITopic) == LMQ_ERR_INVAL_TOPIC);
  CHECK(subTopicCheck(bigTopic) == LMQ_ERR_INVAL_TOPIC);
}

void setup() {
	Serial.begin(9600);
  Serial.println("Setup complete. Starting tests...");
}

void loop() {}
