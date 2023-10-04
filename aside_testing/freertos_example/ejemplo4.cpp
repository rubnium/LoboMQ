//Ejemplo 4 de FreeRTOS, delays con estado Blocked
//esto va a evitar que el ejemplo3 se quede T1 sin ejecutar al tener T2 mayor prioridad

void vTaskFunction(void *pvParameters){
  volatile uint32_t ul;
  char *pcTaskName = (char *)pvParameters;
  for(;;){ //for infinito
    vPrintString(pcTaskName);

    vTaskDelay(pdMS_TO_TICKS(250)); //delay nuevo, de 250ms, pasa a Blocked la tarea
  }
}

static const char *pcTextForT1 = "Tarea 1 se está ejecutando\r\n";
static const char *pcTextForT2 = "Tarea 2 se está ejecutando\r\n";

int main(void){
    xTaskCreate(vTaskFunction, "Tarea 1", 1000, (void*)pcTextForT1, 1, NULL);
    xTaskCreate(vTaskFunction, "Tarea 2", 1000, (void*)pcTextForT1, 2, NULL);
    //Tarea 2 tiene mayor prioridad que Tarea 1
    vTaskStartScheduler(); 

    return 0; //no llega aquí
}