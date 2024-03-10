/* The user must define the following 2 functions/callbacks:
- char feedRowParser()
- bool rowParserFinished()
That is because cp.parseRow() calls these functions continuously "under the hood". */

#include <Arduino.h>
#include <CSV_Parser.h>
#include <SD.h>
#include <SPI.h>

const char *f_name = "/customers.csv";
const int chipSelect = 5; //CS pin
File file;

char feedRowParser() {
  return file.read();
}

bool rowParserFinished() {
  return ((file.available()>0)?false:true);
}

void setup() {
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println(" card failed or not present");
    exit(1);
  }
  Serial.println(" card initialized.");

  if (!SD.exists(f_name)) {
    printf("ERROR: File %s does not exist.", String(f_name));  
    exit(1);
  }

  file = SD.open(f_name, FILE_READ);
  if (!file) {
    Serial.println("ERROR: File open failed");
    exit(1);
  }

  //Line below could fail because there isn't enough memory to store the header, and the whole single row.
  //"customers.csv" has rather large rows, too much for borads with 1KB SRAM.
  //CSV_Parser cp(/*format*/ "Lsssssssssss");

  CSV_Parser cp(/*format*/ "Ls-------s--"); //L=long, s=string, -=skip

  //parseRow calls feedRowParser() continuously until it reads a 
  //full row or until the rowParserFinished() returns true
  int row_index = 0;

  //WARNING: String indexing can't be used here because the header was not supplied to the cp object yet.
  //int32_t *ids = (int32_t*)cp["Index"];
  //char **customer_ids = (char**)cp["Customer Id"];
  //char **emails = (char**)cp["Email"];

  int32_t *ids = (int32_t*)cp[0];
  char **customer_ids = (char**)cp[1];
  char **emails = (char**)cp[9];

  while (cp.parseRow()) {
    //We could use string indexing, but it would be much slower.
    //char *email = ((char**)cp["Email"])[0];

    int32_t id = ids[0];
    char *customer_id = customer_ids[0];
    char *email = emails[0];

    printf("%d. customer_id=%s, id=%ld, email=%s\n", row_index+1, customer_id, id, email);

    row_index++;
  }
  //Serial.println();
  //cp.print();
}

void loop() { }

//based on https://github.com/michalmonday/CSV-Parser-for-Arduino/blob/master/examples/parsing_row_by_row_sd_card/parsing_row_by_row_sd_card.ino