#include <Arduino.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);

  JsonDocument doc;

  doc["sensor"] = "gps";
  doc["time"] = 1351824120;

  JsonArray data = doc["data"].to<JsonArray>();
  data.add(48.756080);
  data.add(2.302038);

  //Generate the minified JSON and send it to the Serial port

  serializeJson(doc, Serial);
  //Prints: {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}

  Serial.println();

  serializeJsonPretty(doc, Serial);
  /*Prints:
  {
    "sensor": "gps",
    "time": 1351824120,
    "data": [
      48.756080,
      2.302038
    ]
  }*/
}

void loop() { }

//based on https://arduinojson.org/v7/example/generator/