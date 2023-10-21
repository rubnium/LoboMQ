//Ejemplo 7 de FreeRTOS, definir task hook
//configUSE_IDLE_HOOK debe estar a 1 en FreeRTOSConfig.h para llamar a la función idle hook

volatile uint32_t ulIdleCycleCount = 0UL; //variable incrementada por la función hook

//funciones idle hook siempre se llamrán así, no toman parámetros y son de tipo void
//se llaman cuando no está ejecutando ninguna tarea
void vApplicationIdleHook(void){
    ulIdleCycleCount++; //solo incrementará el contador
}

void vTaskFunction(void *pvParameters){
  volatile uint32_t ul;
  char *pcTaskName = (char *)pvParameters;
  for(;;){ //for infinito
    vPrintStringAndNumber(pcTaskName, ulIdleCycleCount);

    vTaskDelay(pdMS_TO_TICKS(250)); //delay 250ms
  }
}

static const char *pcTextForT1 = "Tarea 1 se está ejecutando\r\n";
static const char *pcTextForT2 = "Tarea 2 se está ejecutando\r\n";

int main(void){
    xTaskCreate(vTaskFunction, "Tarea 1", 1000, (void*)pcTextForT1, 1, NULL);
    xTaskCreate(vTaskFunction, "Tarea 2", 1000, (void*)pcTextForT1, 2, NULL);
    vTaskStartScheduler(); 

    return 0; //no llega aquí
}