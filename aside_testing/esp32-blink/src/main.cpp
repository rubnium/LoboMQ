#include <Arduino.h>
#define LED 2

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(500);
  digitalWrite(LED, HIGH);
  Serial.print("\nLED encendido");
  delay(500);
  digitalWrite(LED, LOW);
  Serial.print("\nLED apagado");
}