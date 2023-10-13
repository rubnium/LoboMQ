//Ejemplo 5 de FreeRTOS, delays con until
//para las tareas garantiza una frecuencia fija de ejecución

void vTaskFunction(void *pvParameters){
  volatile uint32_t ul;
  char *pcTaskName = (char *)pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount(); //inicializa la variable, se irá actualizando sola
  for(;;){ //for infinito
    vPrintString(pcTaskName);

    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(250)); //ejecuta la tarea exactamente cada 250ms
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