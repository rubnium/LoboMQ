#include <Arduino.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);

  JsonDocument doc;

  //JSON input string
  char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return; 
  }

  //Fetch values
  const char* sensor = doc["sensor"];
  long time = doc["time"]; //also can do doc["time"].as<long>();
  double latitude = doc["data"][0];
  double longitude = doc["data"][1];

  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);
}

void loop() { }

//based on https://arduinojson.org/v7/example/parser/