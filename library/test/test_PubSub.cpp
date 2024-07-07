#include "LoboMQ/PubSub.cpp"
#include <unity.h>

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

typedef struct {
  int number;
} CustomPayloadStruct;

void createMessageAndCheckAndGetContent() {
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

	TEST_ASSERT_EQUAL(isLMQMessage(data), true);

	//Extract payload from bytes
	PayloadContent contentRecv = getLMQPayload(data);
  CustomPayloadStruct payloadRecv;
  memcpy(&payloadRecv, &contentRecv.content, contentRecv.contentSize);

  TEST_ASSERT_EQUAL(payloadRecv.number, number);
}


void pubCheckStartingTrailingSlashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, pubTopicCheck(startingTrailingSlashTopic));
}

void pubCheckOnlyTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, pubTopicCheck(onlyTopic));
}

void pubCheckTrailingPlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(trailingPlusTopic));
}

void pubCheckMiddlePlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(middlePlusTopic));
}

void pubCheckStartingPlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(startingPlusTopic));
}

void pubCheckOnlyPlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(onlyPlusTopic));
}

void pubCheckTrailingHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(trailingHashTopic));
}

void pubCheckMiddleHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(middleHashTopic));
}

void pubCheckStartingHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(startingHashTopic));
}

void pubCheckOnlyHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(onlyHashTopic));
}

void pubCheckOnlySlashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(onlySlashTopic));
}

void pubCheckEmptyTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(emptyTopic));
}

void pubCheckNullTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(nullTopic));
}

void pubCheckNonASCIITopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(nonASCIITopic));
}

void pubCheckBigTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, pubTopicCheck(bigTopic));
}

void subCheckStartingTrailingSlashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(startingTrailingSlashTopic));
}

void subCheckOnlyTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(onlyTopic));
}

void subCheckTrailingPlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(trailingPlusTopic));
}

void subCheckMiddlePlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(middlePlusTopic));
}

void subCheckStartingPlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(startingPlusTopic));
}

void subCheckOnlyPlusTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(onlyPlusTopic));
}

void subCheckTrailingHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(trailingHashTopic));
}

void subCheckMiddleHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(middleHashTopic));
}

void subCheckStartingHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(startingHashTopic));
}

void subCheckOnlyHashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_SUCCESS, subTopicCheck(onlyHashTopic));
}

void subCheckOnlySlashTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(onlySlashTopic));
}

void subCheckEmptyTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(emptyTopic));
}

void subCheckNullTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(nullTopic));
}

void subCheckNonASCIITopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(nonASCIITopic));
}

void subCheckBigTopic() {
	TEST_ASSERT_EQUAL(LMQ_ERR_INVAL_TOPIC, subTopicCheck(bigTopic));
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(createMessageAndCheckAndGetContent);
	RUN_TEST(pubCheckStartingTrailingSlashTopic);
	RUN_TEST(pubCheckOnlyTopic);
	RUN_TEST(pubCheckTrailingPlusTopic);
	RUN_TEST(pubCheckMiddlePlusTopic);
	RUN_TEST(pubCheckStartingPlusTopic);
	RUN_TEST(pubCheckOnlyPlusTopic);
	RUN_TEST(pubCheckTrailingHashTopic);
	RUN_TEST(pubCheckMiddleHashTopic);
	RUN_TEST(pubCheckStartingHashTopic);
	RUN_TEST(pubCheckOnlyHashTopic);
	RUN_TEST(pubCheckOnlySlashTopic);
	RUN_TEST(pubCheckEmptyTopic);
	RUN_TEST(pubCheckNullTopic);
	RUN_TEST(pubCheckNonASCIITopic);
	RUN_TEST(pubCheckBigTopic);
	RUN_TEST(subCheckStartingTrailingSlashTopic);
	RUN_TEST(subCheckOnlyTopic);
	RUN_TEST(subCheckTrailingPlusTopic);
	RUN_TEST(subCheckMiddlePlusTopic);
	RUN_TEST(subCheckStartingPlusTopic);
	RUN_TEST(subCheckOnlyPlusTopic);
	RUN_TEST(subCheckTrailingHashTopic);	
	RUN_TEST(subCheckMiddleHashTopic);
	RUN_TEST(subCheckStartingHashTopic);
	RUN_TEST(subCheckOnlyHashTopic);
	RUN_TEST(subCheckOnlySlashTopic);
	RUN_TEST(subCheckEmptyTopic);
	RUN_TEST(subCheckNullTopic);
	RUN_TEST(subCheckNonASCIITopic);
	RUN_TEST(subCheckBigTopic);
	UNITY_END();
}

void loop() {}
