/* PINOUT:
CD/Chip Detect - 22 (not used)
DO/MISO - 19
SCK/CLK - 18
DI/MOSI - 23
CS - 5
VCC - 3.3V
GND - GND
*/

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include "CustomObject.h"

#define SDPIN 5

void listDir(fs::FS &fs, const char * dirname, uint8_t levels, String prefix="", String ogPrefix="\t") {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.printf("%sDIR : %s\n", prefix, file.name());
      if (levels) {
        char dirFileName[strlen(dirname) + strlen(file.name()) + 2];
        snprintf(dirFileName, sizeof(dirFileName), "%s/%s", dirname, file.name());
        listDir(fs, dirFileName, levels -1, ogPrefix+prefix, ogPrefix);
      }
    } else {
      Serial.printf("%sFILE: %s  SIZE: %d\n", prefix, file.name(), file.size());
    }
    file = root.openNextFile();
  }
}

bool readFile(fs::FS &fs, const char * path) {
  File file = fs.open(path, FILE_READ);
  if (!file) {
    Serial.printf("Failed to open %s for reading\n", path);
    return false;
  }

  Serial.printf("Read from %s:\n", path);
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  return true;
}

bool writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s ... ", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return false;
  }
  bool returnVal = true;
  if (file.print(message)) {
    Serial.println("Written");
  } else {
    Serial.println("Failed");
    returnVal = false;
  }
  file.close();
  return returnVal;
}

bool appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return false;
  }
  bool returnVal = true;
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
    returnVal = false;
  }
  file.close();
  return returnVal;
}

/* Available functions:
- listDir(SD, "/", 2); Prints directories and files from / and 2 levels deep
- SD.mkdir("/newDir");
- SD.rmdir("/remDir");
- SD.rename("/old.txt", "/new.txt");
- readFile(SD, "/hello.txt");
- writeFile(SD, "/hello.txt", "Hello World!")
- appendFile(SD, "/hello.txt", "Hello again!")
*/

void setup() {
  Serial.begin(9600);

  if (!SD.begin(SDPIN)) {
    Serial.println("Card Mount Failed!");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  CustomObject myObject;

  char* filepath = "/myObject.txt";
  if (!readFile(SD, filepath)) {
    myObject = CustomObject(1, "HelloWorld!");
    writeFile(SD, filepath, myObject.serialize().c_str());
  } else {
    Serial.println("Reading file content");
    String fileContent;
    File file = SD.open(filepath);
    if (file) {
      while (file.available()) {
        fileContent += (char)file.read();
      }
      file.close();

      // Deserialize the object using the file content
      myObject.deserialize(fileContent.c_str());
    } else {
      Serial.println("Error opening file for reading");
    }
  }
}

void loop() { }
