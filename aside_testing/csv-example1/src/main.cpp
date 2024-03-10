#include <Arduino.h>
#include <CSV_Parser.h>

void setup() {
  Serial.begin(9600);

  char *csv_str =
    "my_strings,my_numbers\n"
    "hello,5\n"
    "world,10\n";
                 
  CSV_Parser cp(csv_str, /*format*/ "sL");

  Serial.println("Accessing values by column name:");
  char **strings = (char**)cp["my_strings"];
  int32_t *numbers = (int32_t*)cp["my_numbers"];
  for (int row = 0; row < cp.getRowsCount(); row++)
    printf("%d. str=%s num=%ld\n", row, strings[row], numbers[row]);

  Serial.println();
  
  Serial.println("Accessing values by column number:");
  strings = (char**)cp[0];
  numbers = (int32_t*)cp[1];
  for (int row = 0; row < cp.getRowsCount(); row++)
    printf("%d. str=%s num=%ld\n", row, strings[row], numbers[row]);
}

void loop() { }

//based on https://github.com/michalmonday/CSV-Parser-for-Arduino/blob/master/examples/basic_usage/basic_usage.ino