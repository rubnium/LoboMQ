#include <Arduino.h>
#include <array>
#include <FS.h>
#include <SD.h>
#include <vector>

#include <ArduinoJson.h>

#define CSPIN 5 //Chip select SD card reader pin

#define FILE_PATH "/unnamedMQ/topics"
#define FILE_FORMAT ".json"

String replaceChars(const char *str) {
  String result = "";
  while (*str) {
    switch (*str) {
			/* Converted special chars to escaped unicode chars, its the only way to
			properly use it for filenames
			https://www.utf8-chartable.de/unicode-utf8-table.pl?utf8=string-literal */
      case '<': result += "\xC2\xAB"; break; //«
      case '>': result += "\xC2\xBB"; break; //»
      case ':': result += "\xC3\xB7"; break; //÷
      case '"': result += "\xC2\xAA"; break; //ª
      case '/': result += "\xE2\x88\x9A"; break; //√
      case '\\': result += "\xC3\xAC"; break; //ì
      case '|': result += "\xE2\x94\x82"; break; //│
      case '?': result += "\xC2\xBF"; break; //¿
      case '*': result += "\xC2\xBA"; break; //º
      default: result += *str; break;
    }
    str++;
  }
  return result;
}

bool initializeSDCard() {
	if (!SD.begin(CSPIN)) {
    Serial.println("Error initializing SD card");
    return false;
  }

	//TODO: get mutex
	//Creates all folders in path
  int index = 0;
  while (index != -1) {
    index = String(FILE_PATH).indexOf("/", index+1); //Finds "/" position
    if (index>0) {
      String subpath = String(FILE_PATH).substring(0, index); //Gets subpath until next "/"
      if (!SD.exists(subpath) and !SD.mkdir(subpath)) { //If subpath does not exist,creates it
        Serial.println("Error creating folder: "+subpath);
				//TODO: release mutex
        return false;
      }
    }
  }

  //Creates deepest folder
  if (!SD.exists(FILE_PATH) and !SD.mkdir(FILE_PATH)) {
    Serial.println("Error creating folder: "+String(FILE_PATH));
		//TODO: release mutex
    return false;
  }
	//TODO: release mutex
	return true;
}

void writeFiles() {
	std::vector<const char *> topics = {"topic1/prueba", "topic*", "t>opic3", "topic:4", "topic\\5", "topic|6", "topic?7"};
	bool bolVal = false;
	std::vector<std::string> contents = {"a", "b", "c", "d", "e", "f"};
	std::vector<std::array<uint8_t, 6>> macsSubscribers = {
		{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC},
		{0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56},
		{0x00, 0x11, 0x22, 0x33, 0x44, 0x55}
	};

	for (const auto &topic : topics) {
		JsonDocument doc;
		doc["topic"] = topic;
		doc["bolVal"] = bolVal;

		JsonArray contentsArray = doc["contents"].to<JsonArray>();
		for (const auto &content : contents) {
			contentsArray.add(content);
		}

		JsonArray macsSubscribersArray = doc["macsSubscribers"].to<JsonArray>();
		for (const auto& mac : macsSubscribers) {
			char macChar[18];
			snprintf(macChar, sizeof(macChar), "%02X:%02X:%02X:%02X:%02X:%02X\n",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			macsSubscribersArray.add(macChar);
		}

		String filename = replaceChars(topic);
		String fullFilepath = (String(FILE_PATH) + "/" + filename + String(FILE_FORMAT));
		//TODO: get mutex
		File file = SD.open(fullFilepath, FILE_WRITE);
		if (!file) {
			Serial.println("Failed to open file for writing");
		} else {
			serializeJsonPretty(doc, file);
			Serial.println("Wrote to file successfully");
			file.close();
		}
		//TODO: release mutex
  }
}

void readFiles() {
	//TODO: get mutex
	File dir = SD.open(FILE_PATH);
	//go through every file at folder FILE_PATH
	if (!dir) {
    Serial.println("Error opening file path");
		//TODO: release mutex
    return;
  }

	while (File file = dir.openNextFile()) {
		String filename = file.name();
		if (!file.isDirectory() && filename.endsWith(FILE_FORMAT)) {
			const char *topic;
			bool boolVal;
			std::vector<std::string> contents;
			std::vector<std::array<uint8_t, 6>> macsSubscribers;

			JsonDocument doc;
			DeserializationError error = deserializeJson(doc, file);
			if (error) {
				Serial.printf("Error parsing JSON file %s\n", file.name());
				return;
			}

			topic = doc["topic"];
			boolVal = doc["boolVal"];
			JsonArray contentsArray = doc["contents"];
			for (const auto &content : contentsArray) {
				contents.push_back(content);
			}

			JsonArray macsSubscribersArray = doc["macsSubscribers"];
			for (const auto &mac : macsSubscribersArray) {
				std::array<uint8_t, 6> macArray;
				sscanf(mac, "%02X:%02X:%02X:%02X:%02X:%02X\n",
					&macArray[0], &macArray[1], &macArray[2], &macArray[3], &macArray[4], &macArray[5]);
				macsSubscribers.push_back(macArray);
			}

			printf("File: %s\n", filename.c_str());
			printf("\tTopic: %s\n", topic);
			printf("\tboolVal: %s\n", boolVal ? "true" : "false");
			printf("\tContents:\n");
			for (const auto &content : contents) {
				printf("\t\t%s\n", content.c_str());
			}
			printf("\tMacsSubscribers:\n");
			for (const auto &mac : macsSubscribers) {
				printf("\t\t%02X:%02X:%02X:%02X:%02X:%02X\n",
					mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			}
    }
    file.close();
	}
	dir.close();
	//TODO: release mutex
}

void deleteFiles() {
	//TODO: get mutex
	File dir = SD.open(FILE_PATH);
	//go through every file at folder FILE_PATH
	if (!dir) {
    Serial.println("Error opening file path");
		//TODO: release mutex
    return;
  }

	while (File file = dir.openNextFile()) {
		String filename = file.name();
		if (!file.isDirectory() && filename.endsWith(FILE_FORMAT)) {
			if (!SD.remove(file.path())) {
				Serial.printf("Error deleting file %s\n", file.name());
			} else {
				Serial.printf("Deleted file %s\n", file.name());
			}
		}
		file.close();
	}
	dir.close();
	//TODO: release mutex
}

void updateFiles() {
	//TODO: get mutex
	File dir = SD.open(FILE_PATH);
	//go through every file at folder FILE_PATH
	if (!dir) {
    Serial.println("Error opening file path");
		//TODO: release mutex
    return;
  }

	while (File file = dir.openNextFile()) {
		String fullFilePath = file.path();

		String filename = file.name();
		if (!file.isDirectory() && filename.endsWith(FILE_FORMAT)) {
			JsonDocument doc;
			DeserializationError error = deserializeJson(doc, file);
			if (error) {
				Serial.printf("Error parsing JSON file %s\n", file.name());
				continue;
			}
			file.close();

			file = SD.open(fullFilePath, FILE_WRITE);	
			if (!file) {
				Serial.printf("Error opening file %s for writing\n", file.name());
				continue;
			}		
			int newVal = doc["newVal"] | 0;
			doc["newVal"] = newVal+1;
			serializeJsonPretty(doc, file);
		}
		file.close();
	}
	dir.close();
	//TODO: release mutex
}
		

void setup() {
  Serial.begin(9600);
  Serial.println();

  if (!initializeSDCard())
		return;

	writeFiles();
	//readFiles();
	updateFiles();
	//deleteFiles();
}

void loop() { }
