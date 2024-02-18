//Ejemplo 6 de FreeRTOS, combinando tareas blocantes con no-blocantes

void vContinuosProcessingTask(void *pvParameters){
  char *pcTaskName = (char *)pvParameters;
  for(;;){ //for infinito
    vPrintString(pcTaskName); //infinitamente imprime el nombre de la tarea, sin bloqueos ni delays
  }
}

void vPeriodicTask(void *pvParameters){
  char *pcTaskName = (char *)pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for(;;){ //for infinito
    vPrintString(pcTaskName);

    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(3)); //ejecuta la tarea exactamente cada 3ms
  }
}

static const char *pcTextForCPT1 = "Tarea continua 1 se está ejecutando\r\n";
static const char *pcTextForCPT2 = "Tarea continua 2 se está ejecutando\r\n";
static const char *pcTextForPT = "Tarea periódica se está ejecutando\r\n";


int main(void){
    //2 tareas en prioridad=1: solo hacen print, y estarán o en Ready o en Running
    xTaskCreate(vContinuosProcessingTask, "Tarea continua 1", 1000, (void*)pcTextForCPT1, 1, NULL);
    xTaskCreate(vContinuosProcessingTask, "Tarea continua 2", 1000, (void*)pcTextForCPT2, 1, NULL);
    //1 tarea en prioridad=2: hace print, usa el delay until para colocarse a si mismo en Bloqueado entre cada print
    xTaskCreate(vPeriodicTask, "Tarea periódica", 1000, (void*)pcTextForPT, 2, NULL);
    vTaskStartScheduler(); 

    return 0; //no llega aquí
}