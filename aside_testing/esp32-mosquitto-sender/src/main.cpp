#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> //installed library

//WiFi credentials
const char* ssid = "rubnium Mi A2";
const char* password = "rubniumHD13";	

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
}
