//Ejemplo 10 de FreeRTOS, bloqueo al recibir de la cola
//Funcionamiento:
//- Hay 2 tareas que crean datos en la cola, y 1 que recibe. La que recibe tiene más prioridad
//- Tarea Receptora se ejecuta, intenta recibir datos, como no hay se bloquea 100ms
//- Mientras, se ejecuta una tarea emisora, escribe datos a la cola
//- Cuando ha escrito, se desbloquea la receptora, recibe los datos (vacía la cola), y vuelta a empezar

QueueHandle_t xQueue; //handler para acceder a la cola (para guardar y leer)

static void vSenderTask(void *pvParameters){
    int32_t lValueToSend = (int32_t)pvParameters; //el valor a enviar lo toma de los parámetros 
    for(;;){
        //Envía datos al final de la cola (no a la cabeza)
        BaseType_t xStatus = xQueueSendToBack(xQueue, //handler de la cola
                                            &lValueToSend, //puntero hacia los datos a copiar en la cola
                                            0); //máximo nº de ticks que se va a bloquear hasta que haya espacio en la cola
        //Devuelve:
        //- pdPass = se envió correctamente
        //- errQUEUE_FULL = no se pudo escribir datos en la cola, está llena
        if(xStatus != pdPASS){
            vPrintString("No se pudo enviar a la cola\r\n");
        }
    }
}

static void vReceiverTask(void *pvParameters){
    int32_t lReceivedValue; //donde se va a guardar el dato que recibe
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100); //declara ticks a esperar, 100ms, usado luego

    for(;;){
        //Comprueba el nº de items que hay en la cola (si devuelve 0, está vacía)
        if(uxQueueMessagesWaiting(xQueue) != 0){
            vPrintString("¡La cola debería estar vacía!\r\n");
        }
        //Recibe datos de la cola
        BaseType_t xStatus = xQueueReceive(xQueue, //handler de la cola
                                        &lReceivedValue, //puntero hacia la memoria donde se van a copiar los datos, debe ser lo suficientemente grande para almacenar los datos
                                        xTicksToWait); //máximo nº de ticks que se va a bloquear hasta que haya datos para recibir en la cola
        //Devuelve:
        //- pdPass = se recibió correctamente
        //- errQUEUE_EMPTY = no se pudo recibir datos de la cola, está vacía
        if(xStatus == pdPASS){
            vPrintStringAndNumber("Recibido = ", lReceivedValue);
        }else{
            vPrintString("No se pudo recibir de la cola\r\n");
        }
    }
}

int main(void){
    xQueue = xQueueCreate(5, //max nº de items que puede mantener la cola
                        sizeof(int32_t)); //tamaño en bytes de cada item
    //xQueue devuelve:
    //- NULL si no se pudo crear por falta de memoria
    //- o el valor que se necesita para el handler                    
    if(xQueue != NULL){
        //2 tareas que envían datos a la cola, con prioridad 1. Una tarea envía "100", y la otra "200"
        xTaskCreate(vSenderTask, "Emisor1", 1000, (void *)100, 1, NULL);
        xTaskCreate(vSenderTask, "Emisor2", 1000, (void *)200, 1, NULL);

        //Tarea que recibe datos de la cola, tiene mayor prioridad
        xTaskCreate(vReceiverTask, "Receptor", 1000, NULL, 2, NULL);

        vTaskStartScheduler();
    } else {
        //La cola no se pudo crear
    }

    for(;;); 
    return 0; //no llega aquí
}