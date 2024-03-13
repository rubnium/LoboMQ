#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SD.h>

#define CSPIN 5 //Chip select SD card reader pin

bool writeCreateFile(const char* filepath) {
  Serial.printf("Writing file: %s ... ", filepath);
  File file = SD.open(filepath, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return false;
  }

  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();
  
  JsonObject obj1 = array.createNestedObject();
  obj1["id"] = "1";
  obj1["name"] = "John Doe";
  obj1["year"] = 2024;

  JsonObject obj2 = array.createNestedObject();
  obj2["id"] = "2";
  obj2["name"] = "Jane Doe";
  obj2["year"] = 2020;

  serializeJsonPretty(doc, file);
  Serial.println("Wrote to file successfully");
  file.close();
  return true;
}

bool readFile(const char* filepath) {
  Serial.printf("Reading file: %s ... ", filepath);
  File file = SD.open(filepath, FILE_READ);
  if (!file) {
    Serial.printf("Failed to open %s for reading\n", filepath);
    return false;
  }
  String fileContent = "";
  while (file.available()) {
    fileContent += (char)file.read();
  }

  file.close();

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, fileContent);
  if (error) {
    Serial.printf("Error parsing JSON file %s\n", filepath);
    return false;
  }

  JsonArray array = doc.as<JsonArray>();

  Serial.println();
  for (JsonObject obj: array) {
    String id = obj["id"];
    String name = obj["name"];
    int year = obj["year"];
    printf("ID: %s   Name: %s   Year: %d\n", id.c_str(), name.c_str(), year);
  }

  return true;
}

void setup() {
  Serial.begin(9600);
  Serial.println();

  if (!SD.begin(CSPIN)) {
    Serial.println("Error initializing SD card");
    return;
  }

  const char *filepath = "/data.json";

  if (!readFile(filepath)) { //If file exists: read and print
    writeCreateFile(filepath); //If not: create and write
  }
}

void loop() { }

//based on https://arduinojson.org/v7/example/generator/