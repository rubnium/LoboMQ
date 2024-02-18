//Ejemplo 2 de FreeRTOS, usando parámetros de tareas

void vTaskFunction(void *pvParameters){
  volatile uint32_t ul;

  char *pcTaskName = (char *)pvParameters; //recibe el nombre de la tarea por los parámetros

  for(;;){ //for infinito
    vPrintString(pcTaskName);

    for (ul=0; ul<mainDELAY_LOOP_COUNT; ul++); //delay
  }
}

static const char *pcTextForT1 = "Tarea 1 se está ejecutando\r\n";
static const char *pcTextForT2 = "Tarea 2 se está ejecutando\r\n";

int main(void){
  xTaskCreate(vTaskFunction, "Tarea 1", 1000, (void*)pcTextForT1, 1, NULL); //se le pasa el parámetro que imprimirá
  xTaskCreate(vTaskFunction, "Tarea 2", 1000, (void*)pcTextForT1, 1, NULL);
  vTaskStartScheduler();

  for(;;); //si las tareas funcionan bien, nunca se llega aquí
}