//Ejemplo 12 de FreeRTOS, usar un Queue Set
//configUSE_QUEUE_SETS e INCLUDE_vTaskSuspend debe estar a 1 en FreeRTOSConfig.h
/*Funcionamiento:
 - Se crean dos colas vacías y se añaden al set de colas
 - Se inicializan las colas para tener solo 1 ítem
 - Dos tareas envían mensajes en colas separadas
 - Una tarea recibe el mensaje del set de colas
Es un ejemplo simple, ya que no usa semáforos y las colas contienen el mismo tipo de datos
*/


//Variables de colas y set de colas
static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;
static QueueSetHandle_t xQueueSet = NULL;

void vSenderTask1(void *pvParameters) {
    const TickType_t xBlockTime = pdMS_TO_TICKS(100);
    const char * const pcMessage = "Message from vSenderTask1\r\n";
    for(;;) {
        vTaskDelay(xBlockTime);
        
        //Envía el string a la cola
        //La cola solo admite 1 ítem, pero no se usa un block time. La tarea receptora tiene prioridad, entonces siempre va a leer antes de que se escriba
        xQueueSend(xQueue1, &pcMessage, 0);
    }
}

void vSenderTask2(void *pvParameters) {
    const TickType_t xBlockTime = pdMS_TO_TICKS(200);
    const char * const pcMessage = "Message from vSenderTask2\r\n";
    for(;;) {
        vTaskDelay(xBlockTime);
        
        //Envía el string a la cola
        //La cola solo admite 1 ítem, pero no se usa un block time. La tarea receptora tiene prioridad, entonces siempre va a leer antes de que se escriba
        xQueueSend(xQueue2, &pcMessage, 0);
    }
}

void vReceiverTask(void *pvParameters) {
    QueueHandle_t xQueueThatContainsData;
    char *pcReceivedString;
    for(;;) {
        //Retorna el manejador de la cola que haya recibido un mensaje
            //Espera indefinidamente a recibir un mensaje con portMAX_DELAY
            //Si retorna NULL es que no se pudo leer un manejador
        xQueueThatContainsData = (QueueHandle_t) xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
        
        //Lee de la cola. No usa un block time porque se sabe que esa cola tiene datos (por la línea de código anterior)
        xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0);
        vPrintString(pcReceivedString);
    }
}


int main(void){
    //Inicializa las colas, que solo pueden tener 1 item
    xQueue1 = xQueueCreate(1, sizeof(char *));
    xQueue2 = xQueueCreate(1, sizeof(char *));

    //Crea set de colas
        //uxEventQueueLength = 1*2. Es el número máximo de manejadores de cola
            //Crea 2 colas de 1 item cada uno
    xQueueSet = xQueueCreateSet(1 * 2);

    //Añade colas al set (se puede añadir un semáforo en vez de una cola)
        //Solo se pueden añadir estando vacías
        //Devuelve pdPASS si se añadió bien
        //o pdFAIL si o se pudo añadir
    xQueueAddToSet(xQueue1, xQueueSet);
    xQueueAddToSet(xQueue2, xQueueSet);

    //Crea tareas emisoras
    xTaskCreate(vSenderTask1, "Sender1", 1000, NULL, 1, NULL);
    xTaskCreate(vSenderTask2, "Sender2", 1000, NULL, 1, NULL);
    
    //Crea tarea receptora (con mayor prioridad, para vaciar las colas antes de escribirlas)
    xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 2, NULL);

    vTaskStartScheduler();

    for(;;); 
    return 0; //no llega aquí
}