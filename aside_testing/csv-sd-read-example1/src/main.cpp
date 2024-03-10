/* This example is reading "file.csv" from sd card and prints the parsed values from it.
Example contents of the "file.csv" (used to test this example) were:
      
column_1,column_2\n
1,2\n
11,22\n
111,333\n */

#include <Arduino.h>
#include <CSV_Parser.h>
#include <SD.h>
#include <SPI.h>

const int chipSelect = 5; //CS pin

void setup() {
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println(" card failed or not present");
    exit(1);
  }
  Serial.println(" card initialized.");

  CSV_Parser cp(/*format*/ "dd", /*has_header*/ true, /*delimiter*/ ',');

  if (cp.readSDfile("/file.csv")) { //if false, the file doesn't exist
    int16_t *column_1 = (int16_t*)cp["column_1"];
    int16_t *column_2 = (int16_t*)cp["column_2"];

    if (column_1 && column_2) {
      for (int row = 0; row < cp.getRowsCount(); row++)
        printf("%d. column_1=%d  column_2=%d\n", row, column_1[row], column_1[row]);
    } else {
      Serial.println("ERROR: At least 1 of the columns was not found, something went wrong.");
    }

    //output parsed values (allows to check that the file was parsed correctly), "Serial.begin()" must be called before
    cp.print();
  } else {
    Serial.println("ERROR: File called '/file.csv' does not exist...");
  }
}

void loop() { }

//based on https://github.com/michalmonday/CSV-Parser-for-Arduino/blob/master/examples/reading_from_sd_card/reading_from_sd_card.ino