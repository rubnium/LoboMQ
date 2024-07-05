#include "LoboMQ/BrokerSDUtils.h"

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

bool initializeSDCard(int csPin, Elog *logger, SemaphoreHandle_t *mutex, TickType_t delay) {
	if (!SD.begin(csPin)) {
    logger->log(ERROR, "[BT SD] Couldn't initialize SD card for persistence.");
    return false;
  }

	if (!xSemaphoreTake(*mutex, delay)) {
		logger->log(ERROR, "[BT SD] Couldn't take mutex for initialization.");
		return false;
	}

	//Creates all folders in path
  int index = 0;
  while (index != -1) {
    index = String(FILE_PATH).indexOf("/", index+1); //Finds "/" position
    if (index>0) {
      String subpath = String(FILE_PATH).substring(0, index); //Gets subpath until next "/"
      if (!SD.exists(subpath) and !SD.mkdir(subpath)) { //If subpath does not exist, creates it
			  logger->log(ERROR, "[BT SD] Couldn't create folder (%s).", subpath.c_str());
				xSemaphoreGive(*mutex); //release mutex because of error
        return false;
      }
    }
  }

  //Creates deepest folder
  if (!SD.exists(FILE_PATH) and !SD.mkdir(FILE_PATH)) {
		logger->log(ERROR, "[BT SD] Couldn't create folder (%s).", String(FILE_PATH).c_str());
		xSemaphoreGive(*mutex); //release mutex because of error
    return false;
  }
	xSemaphoreGive(*mutex); //release mutex, success
	return true;
}

void restoreBTs(std::vector<BrokerTopic> *topicsVector, Elog *logger, SemaphoreHandle_t *mutex,
	TickType_t delay) {
	if (!xSemaphoreTake(*mutex, delay)) {
		logger->log(ERROR, "[BT SD] Couldn't take mutex for BTs restoration.");
		return;
	}

	File dir = SD.open(FILE_PATH);
	//go through every file at folder FILE_PATH
	if (!dir) {
    logger->log(ERROR, "[BT SD] Couldn't open main directory %s.", FILE_PATH);
  } else {
		while (File file = dir.openNextFile()) {
			String filename = file.name();
			if (!file.isDirectory() && filename.endsWith(FILE_FORMAT)) {
				const char *topic;
				//std::vector<std::array<uint8_t, 6>> subscribers;

				JsonDocument doc;
				DeserializationError error = deserializeJson(doc, file);
				if (error) {
					logger->log(ERROR, "[BT SD] Error parsing JSON file %s.", file.name());
					continue;
				}

				topic = doc["topic"];
				JsonArray subscribersArray = doc["subscribers"];

				if (subscribersArray.size() == 0) {
					logger->log(WARNING, "[BT SD] No subscribers found in topic '%s' of the SD card, skipped.", topic);
					continue;
				}

				BrokerTopic newTopic(logger, topic);

				for (const auto &mac : subscribersArray) {
					std::array<uint8_t, 6> macArray;
					sscanf(mac, "%02X:%02X:%02X:%02X:%02X:%02X\n",
						&macArray[0], &macArray[1], &macArray[2], &macArray[3], &macArray[4], &macArray[5]);
					//subscribers.push_back(macArray);
					newTopic.subscribe(macArray);
				}
				String filename = file.name();
				filename.replace(FILE_FORMAT, "");
				newTopic.setFilename(filename.c_str());
				topicsVector->push_back(newTopic);
				logger->log(INFO, "[BT SD] Created topic '%s' found on SD card.", topic);
			}
			file.close();
		}
		dir.close();
	}
	xSemaphoreGive(*mutex);
}

void writeBTToFile(BrokerTopic* brokerTopic, Elog* logger, SemaphoreHandle_t *mutex, TickType_t delay) {
	JsonDocument doc;
	doc["topic"] = brokerTopic->getTopic();
	JsonArray subscribersArray = doc["subscribers"].to<JsonArray>();
	for (const auto& mac : brokerTopic->getSubscribers()) {
		char macChar[18];
		snprintf(macChar, sizeof(macChar), "%02X:%02X:%02X:%02X:%02X:%02X\n",
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		subscribersArray.add(macChar);
	}

	String fullFilepath = (String(FILE_PATH)+"/"+brokerTopic->getFilename()+String(FILE_FORMAT));
	
	if (!xSemaphoreTake(*mutex, delay)) {
		logger->log(ERROR, "[BT SD] Couldn't take mutex for BT file write.");
		return;
	}

	File file = SD.open(fullFilepath, FILE_WRITE);
	if (!file) {
		logger->log(ERROR, "[BT SD] Couldn't open file for writing (%s).", fullFilepath.c_str());
	} else {
		serializeJsonPretty(doc, file);
		logger->log(DEBUG, "[BT SD] Wrote topic '%s' to file '%s' successfully.", brokerTopic->getTopic(),
			(brokerTopic->getFilename()+String(FILE_FORMAT)));
		file.close();
	}
	xSemaphoreGive(*mutex);
}

void deleteBTFile(const char* filename, Elog* logger, SemaphoreHandle_t *mutex, TickType_t delay) {
	if (!xSemaphoreTake(*mutex, delay)) {
		logger->log(ERROR, "[BT SD] Couldn't take mutex for BT file deletion.");
		return;
	}

	String fullFilepath = (String(FILE_PATH)+"/"+filename+String(FILE_FORMAT));
	File file = SD.open(fullFilepath, FILE_WRITE);
	if (!file) {
		logger->log(ERROR, "[BT SD] Couldn't open file for deletion (%s).", fullFilepath.c_str());
  } else {
		if (!SD.remove(file.path())) {
			logger->log(ERROR, "[BT SD] Couldn't delete file (%s).", fullFilepath.c_str());
		} else {
			logger->log(DEBUG, "[BT SD] Deleted file %s successfully.", file.name());
		}
		file.close();
	}
	xSemaphoreGive(*mutex);
}
