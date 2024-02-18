//Ejemplo 8 de FreeRTOS, borrar tareas
//INCLUDE_vTaskDelete debe estar a 1 en FreeRTOSConfig.h
/*Funcionamiento:
- T1 se crea con prioridad 1
- Se ejecuta T1, que crea T2 con prioridad 2, espera en el delay termina de ejecutarse
- Se ejecuta T2 (pq tiene más prioridad), se borra a si misma, termina de ejecutarse
    (COMENTARIO: mientras T1 está en delay (estado blocked), Idle task libera la memoria que T2 ocupó)
- Vuelve a ejecutarse T1 (y vuelta a empezar)*/

TaskHandle_t xTask2Handle = NULL; //handler de la tarea 2 (usado luego para borrar T2)

void vTask2(void *pvParameters){
    vPrintString("Tarea 2 se está ejecutando, se va a borrar a sí misma\r\n");
    vTaskDelete(xTask2Handle); //se borra a sí misma
    //NOTA: para este ejemplo, como la tarea se borra a sí misma, se pudo haber hecho:
    //vTaskDelete(NULL);
}

void vTask1(void *pvParameters){
    for(;;){
        vPrintString("Tarea 1 se está ejecutando\r\n");
        xTaskCreate(vTask2, "Tarea 2", 1000, NULL, 2, &xTask2Handle); //crea T2 con la prioridad más alta
        vTaskDelay(pdMS_TO_TICKS(100UL)); //delay de 100ms
    }
}

int main(void){
    //Se crea T1 con prioridad baja
    xTaskCreate(vTask1, "Tarea 1", 1000, NULL, 1, NULL);
    vTaskStartScheduler(); 

    for(;;); 
    return 0; //no llega aquí
}