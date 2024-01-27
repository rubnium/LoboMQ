//Ejemplo customizado de FreeRTOS, usar un queue como Mailbox
//Un Mailbox es una cola de un solo item que se va sobreescribiendo

//Estructura del mensaje del mailbox
typedef struct xExampleStructure {
    TickType_t xTimeStamp;
    uint32_t ulValue;
} Example_t;

//Cola
static QueueHandle_t xMailbox;

void vUpdateMailbox(uint32_t ulNewValue) {
    Example_t xData;
    //Rellena el nuevo objeto a escribir
    xData.xTimeStamp = xTaskGetTickCount();
    xData.ulValue = ulNewValue;

    //Escribe el nuevo objeto en la cola, reemplazando cualquiera que haya en la cola
        //Solo retorna pdPASS, porque escribe en la cola aunque esté llena
    xQueueOverwrite(xMailbox, &xData);

}

BaseType_t vReadMailbox(Example_t *pxData) {
    TickType_t xPreviousTimeStamp;
    BaseType_t xDataUpdated;

    //Almacena el timestamp que está en el objeto
    xPreviousTimeStamp = pxData->xTimeStamp;

    //Reemplaza el objeto al que apunta lo anterior con el de la cola
    //Solo lee de la cola, no saca el objeto de la misma
        //El tiempo de block está puesto por si la cola está vacía
        //Se desbloquea cuando haya datos disponibles
    xQueuePeek(xMailbox, pxData, portMAX_DELAY);

    //Devuelve pdTRUE si se actualizó el valor. Sino, pdFALSE
    if(pxData->xTimeStamp > xPreviousTimeStamp) {
        xDataUpdated = pdTRUE;
    } else {
        xDataUpdated = pdFALSE;
    }
    return xDataUpdated;
}

void vTask1(void *pvParameters) {
    //Para hacer una tarea que lea y actualice la cola
    for(;;) {
    }
}


int main(void){
    //Inicializa el mailbox (con solo 1 ítem)
    xMailbox = QueueCreate(1, sizeof(Example_t));

    //Crea tareas que trabajan con el mailbox
    xTaskCreate(vTask1, "Task1 1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask1, "Task1 2", 1000, NULL, 1, NULL);

    vTaskStartScheduler();

    for(;;); 
    return 0; //no llega aquí
}