//Ejemplo 3 de FreeRTOS, prioridades

void vTaskFunction(void *pvParameters){
  volatile uint32_t ul;
  char *pcTaskName = (char *)pvParameters;
  for(;;){ //for infinito
    vPrintString(pcTaskName);
    for (ul=0; ul<mainDELAY_LOOP_COUNT; ul++); //delay
  }
}

static const char *pcTextForT1 = "Tarea 1 se está ejecutando\r\n";
static const char *pcTextForT2 = "Tarea 2 se está ejecutando\r\n";

int main(void){
    xTaskCreate(vTaskFunction, "Tarea 1", 1000, (void*)pcTextForT1, 1, NULL);
    xTaskCreate(vTaskFunction, "Tarea 2", 1000, (void*)pcTextForT1, 2, NULL);
    //Tarea 2 tiene mayor prioridad que Tarea 1
    vTaskStartScheduler(); //siempre se ejecutará Tarea 2, ya que no tiene que esperar
    //(se ejecuta Tarea 2 el primero, y cuando se termina de ejecutar, el kernel comprueba cual de las tareas ejecutar de las que estén en Non Running (T1 o T2), y escoge el de mayor prioridad)

    return 0; //no llega aquí
}