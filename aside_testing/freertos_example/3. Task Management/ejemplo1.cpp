//Ejemplo 1 de FreeRTOS, parámetros y crear tareas

void vTask1(void *pvParameters){
  const char *pcTaskName = "Tarea 1 se está ejecutando\r\n";
  volatile uint32_t ul; //volátil para asegurar que ul no es optimizado
  //  xTaskCreate(vTask2, "Tarea 2", 1000, NULL, 1, NULL); //se puede crear la tarea dentro de otra
  for(;;){ //la mayoría de tareas tiene un for infinito
    vPrintString(pcTaskName);

    for (ul=0; ul<mainDELAY_LOOP_COUNT; ul++); //delay, implementado como for (en ejemplos posteriores se mejora)
  }
  //vTaskDelete(NULL); //en el caso que se salga del for anterior, hay que borrar la tarea
}

void vTask2(void *pvParameters){ //igual que la vTask1
  const char *pcTaskName = "Tarea 2 se está ejecutando\r\n";
  volatile uint32_t ul;
  for(;;){
    vPrintString(pcTaskName);

    for (ul=0; ul<mainDELAY_LOOP_COUNT; ul++);
  }
}

int main(void){
  xTaskCreate(vTask1, //puntero a la función
              "Tarea 1", //nombre descriptivo (usado en debug)
              1000, //stack depth (no tiene que ser exacto, pero si mayor de la cantidad de palabras que se van a usar)
              NULL, //parámetros
              1, //prioridad (entre 0 y la máxima establecida)
              NULL); //handler
  xTaskCreate(vTask2, "Tarea 2", 1000, NULL, 1, NULL);
  vTaskStartScheduler(); //comienzan a funcionar las tareas (solo 1 a la vez, se van turnando, ambas tienen misma prioridad)

  for(;;); //si las tareas funcionan bien, nunca se llega aquí. Si se llega aquí, es por un error de heap memory disponible

}