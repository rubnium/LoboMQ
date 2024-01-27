//Modificación del ejemplo 12 de FreeRTOS, usar un Queue  (parte receptora real)
//configUSE_QUEUE_SETS e INCLUDE_vTaskSuspend debe estar a 1 en FreeRTOSConfig.h
/*Funcionamiento:
 - Se crean dos colas vacías y se añaden al set de colas
 - Se inicializan las colas para tener solo 1 ítem
 - Dos tareas envían mensajes en colas separadas
 - Una tarea recibe el mensaje del set de colas
Es un ejemplo más realista, pero solo la parte receptora*/


//Variables de colas y set de colas
QueueHandle_t xCharPointerQueue; //cola de punteros char
QueueHandle_t xUint32tQueue; //cola de uint32
SemaphoreHandle_t xBinarySemaphore; //semáforo binario
QueueSetHandle_t xQueueSet;

void vAMoreRealisticReceiverTask(void *pvParameters) {
    QueueSetMemberHandle_t xHandle;
    char *pcReceivedString;
    uint32_t ulRecievedValue;
    for(;;) {
        //Retorna el manejador de la cola que haya recibido un mensaje en un máximo de 100ms
        xHandle = xQueueSelectFromSet(xQueueSet, pdMS_TO_TICKS(100));

        if(xHandle == NULL) {
            //Si devolvió NULL, ocurrió un timeout al no haber colas con datos
        } else if(xHandle == (QueueSetMemberHandle_t) xCharPointerQueue) {
            //Si devolvió el manejador de punteros char
            xQueueReceive(xCharPointerQueue, &pcReceivedString, 0);
            //Manejar el puntero char
        } else if(xHandle == (QueueSetMemberHandle_t) xUint32tQueue) {
            //Si devolvió el manejador de uint32
            xQueueReceive(xUint32tQueue, &ulRecievedValue, 0 );
            //Manejar el valor
        } else if(xHandle == (QueueSetMemberHandle_t) xBinarySemaphore) {
            //Si devolvió el semáforo
            xSemaphoreTake(xBinarySemaphore, 0);
            //Procesar el semáforo
        }
    }
}