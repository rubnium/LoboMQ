#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> //installed library

//WiFi credentials
const char* ssid = "MiFibra-8696_EXT";
const char* password = "7ahKvT57";	

//MQTT configuration
const char* mqttServer = "192.168.1.122";
const int mqttPort = 1883;
const char* mqttUser = "rubnium";
const char* mqttPassword = "root";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);

  //Connects to WiFi
	WiFi.mode(WIFI_STA);
	Serial.print("Connecting to WiFi");
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println(" CONNECTED");

  //Connects to MQTT server
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println(" CONNECTED");
    } else {
      Serial.print(" FAILED with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  client.loop(); //Keeps MQTT connection alive
  
  //Generates random number 
  char str[230];
  sprintf(str, "%u", random(100));

  //Publishes message to MQTT server
  //Returns true if was successfully published
  //Additional parameter: bool retained: MQTT will retain last published message that will be sent to any new subscriber
  if (client.publish("Fake/Random numbers", str)) {
    Serial.println(str);
  } else {
    Serial.print("ERROR, lost message, could not be published - ");
    Serial.println(str);
  }

  delay(1000);
}
