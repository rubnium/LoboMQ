#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED 2

void BlinkTask(void *parameter) {
  char *taskName = (char *)parameter;
  bool isOn = false;
  int counter = 0;
  for(;;) {
    Serial.printf("%s LED (%s %d)\n", isOn ? "Encender" : "Apagar", taskName, counter + 1);
    digitalWrite(LED, isOn ? HIGH : LOW);
    isOn = !isOn;
    counter++;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  xTaskCreate(BlinkTask, "BlinkTask", 10000, (void *)"Blink", 1, NULL);
}

void loop() {

}
