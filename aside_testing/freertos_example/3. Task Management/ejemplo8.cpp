//Ejemplo 8 de FreeRTOS, set y get de prioridades
//INCLUDE_vTaskPrioritySet y INCLUDE_vTaskPriorityGet debe estar a 1 en FreeRTOSConfig.h para que las funciones funcionen
/*Funcionamiento:
- T1 se crea con mayor prioridad que T2 (entonces T1 se ejecuta la primera)
- Se ejecuta T1, imprime, aumenta la prioridad de T2 (ahora T2 es la que más prioridad tiene), y termina de ejecutar
- Ahora se ejecuta la tarea con más prioridad, que es T2. T2 imprime, reduce su prioridad, y termina de ejecutar
- Se ejecuta la tarea con más prioridad, que vuelve a ser T1 (y vuelta a empezar)*/

TaskHandle_t xTask2Handle = NULL; //handler de la tarea 2 (usado luego jugar con la prioridad de la T2)

void vTask1(void *pvParameters){
    UBaseType_t uxPriority = uTaskPriorityGet(NULL); //obtiene la prioridad de la tarea actual

    for(;;){
        vPrintString("Tarea 1 se está ejecutando\r\n");
        vPrintString("Ahora se aumenta la prioridad de la Tarea 2\r\n");
        //Parámetros: handler de tarea, prioridad
        vTaskPrioritySet(xTask2Handle, (uxPriority+1)); //hace que la tarea 2 sea la que más prioridad tenga
    }
}

void vTask2(void *pvParameters){
    UBaseType_t uxPriority = uTaskPriorityGet(NULL); //obtiene la prioridad de la tarea actual

    for(;;){
        vPrintString("Tarea 2 se está ejecutando\r\n");
        vPrintString("Ahora se reduce la prioridad de la Tarea 2\r\n");
        //NULL = tarea actual
        vTaskPrioritySet(NULL, (uxPriority-2)); //hace que la tarea 2 sea la que menos prioridad tenga
    }
}



int main(void){
    //Prioridad de T1 es más alta que la de T2
    xTaskCreate(vTask1, "Tarea 1", 1000, NULL, 2, NULL);
    xTaskCreate(vTask2, "Tarea 2", 1000, NULL, 1, &xTask2Handler); //se le asigna el handler
    vTaskStartScheduler(); 

    for(;;); 
    return 0; //no llega aquí
}