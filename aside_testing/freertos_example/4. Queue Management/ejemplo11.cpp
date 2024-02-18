//Ejemplo 11 de FreeRTOS, bloqueo al enviar a la cola
//Funcionamiento:
//- Hay 2 tareas que crean datos en la cola, y 1 que recibe. La que crea tiene más prioridad
//- Tareas emisoras se ejecutan, hasta llenar la cola
//- Cuando vuelven a intentar ejecutarse, ambas se quedan bloqueadas, porque la cola está llena y no pueden escribir
//- Mientras, se ejecuta la tarea receptora, que obtiene un dato de la cola, y lo imprime identificando cuál tarea lo creó
//- Cuando lo ha obtenido, se desbloquea una emisora, escribe datos (llena la cola), y vuelta a empezar


typedef enum{ //enumeración para identificar la fuente de los datos enviados
    eSender1,
    eSender2
} DataSource_t;

typedef struct{ //tipo de objeto que se le pasa a la cola
    uint8_t ucValue;
    DataSource_t eDataSource;
} Data_t;

//Se declaran los objetos que se pasarán a la cola (uno por task), usado luego en el main
static const Data_t xStructsToSend[2] = {
    {100, eSender1},
    {200, eSender2}
};

static void vSenderTask(void *pvParameters){
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100); //declara ticks a esperar, 100ms, usado luego
    for(;;){
        //Envía datos a la cola
        BaseType_t xStatus = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);
        if(xStatus != pdPASS){
            vPrintString("No se pudo enviar a la cola\r\n");
        }
    }
}

static void vReceiverTask(void *pvParameters){
    Data_t xReceivedStructure; //donde se va a guardar el dato que recibe
    for(;;){
        //Comprueba el nº de items que hay en la cola
        if(uxQueueMessagesWaiting(xQueue) != 3){
            vPrintString("¡La cola debería estar llena!\r\n");
        }
        //Recibe datos de la cola
        BaseType_t xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);
        if(xStatus == pdPASS){
            if(xReceivedStructure.eDataSource == eSender1){ //if para comprobar el emisor que envió el dato
                vPrintStringAndNumber("Recibido del emisor 1 = ", xReceivedStructure.ucValue);
            }else{
                vPrintStringAndNumber("Recibido del emisor 2 = ", xReceivedStructure.ucValue);
            }
        }else{
            vPrintString("No se pudo recibir de la cola\r\n");
        }
    }
}

int main(void){
    //Crea una cola para almacenar 3 Data_t
    xQueue = xQueueCreate(3, sizeof(Data_t));                   
    if(xQueue != NULL){
        //2 tareas que envían datos a la cola, con la mayor prioridad. Cada tarea envía un objeto distinto a la misma cola
        xTaskCreate(vSenderTask, "Emisor1", 1000, &(xStructsToSend[0]), 2, NULL);
        xTaskCreate(vSenderTask, "Emisor2", 1000, &(xStructsToSend[1]), 2, NULL);

        //Tarea que recibe datos de la cola, tiene menor prioridad
        xTaskCreate(vReceiverTask, "Receptor", 1000, NULL, 1, NULL);

        vTaskStartScheduler();
    } else {
        //La cola no se pudo crear
    }

    for(;;); 
    return 0; //no llega aquí
}