# Resultados

En este capítulo se describe el avance del desarrollo del proyecto a través de iteraciones o sprints, mencionando los logros y problemas identificados en cada uno. Además, se muestra, mediante diagramas y listados, el funcionamiento de la herramienta desarrollada en su última versión a fecha de redacción de esta memoria. Este proyecto se puede encontrar en el repositorio /*TODO: insertar repo*/

## Iteración 0

Periodo: 28/09/2023 - 18/02/2024 (20,43 semanas). Peso total: 143.

El objetivo principal de este sprint fue la preparación previa al desarrollo y la obtención de conocimientos necesarios.

Tareas:

- Preparar el entorno de desarrollo (peso: 3). Consiste en la instalación de las herramientas y la creación del repositorio.
- Familiarizarse con ESP32 y PlatformIO (peso: 3). Aprender a utilizar PlatformIO para desarrollar programas y subirlos a la placa de desarrollo.
- Escribir el anteproyecto del [TFG](#TFG) (peso: 5).
- Comunicar placas ESP32 a través de ESP-NOW (peso: 2). Aprender a enlazar las placas a través de sus direcciones [MAC](#MAC) y comprender el uso de las funciones para formar y emitir un mensaje (procurando no sobrepasar el tamaño máximo del payload) y para extraer los datos al recibirlo.
- Entender y realizar ejemplos de FreeRTOS (peso: 100). Leer la documentación de FreeRTOS y comprender los distintos conceptos que abarca, como las tareas (con sus estados y prioridades), las colas y los semáforos.
- Realizar ejemplos emisor-receptor con ESP-NOW y FreeRTOS (peso: 5). Aplicar el conocimiento de ambos aspectos para crear tareas que envíen y reciban datos aprovechando los hilos de ejecución disponibles.
- Realizar ejemplos publicador-suscriptor con [MQTT](#MQTT) (peso: 5). Desplegar un broker Mosquitto en Docker y crear un código para que la placa ESP32 publique mensajes, mientras que otro permite obtenerlos. Esto permite conocer los tipos y parámetros al trabajar con mensajes y otras capacidades en [MQTT](#MQTT).
- Preparar tablero Kanban (peso: 20). Crear el tablero, las columnas y las plantillas, junto a la configuración necesaria para la gestión del proyecto a lo largo de todo el desarrollo.

## Iteración 1

Periodo: 19/02/2024 - 25/02/2024 (1 semana). Peso total: 26.

El objetivo principal de este sprint fue realizar una primera versión funcional centrada en los roles de broker y suscriptor, sin tener en cuenta los topics.

Tareas:

- Crear el esqueleto de la librería (peso: 5). Preparar los ficheros necesarios para definir una librería en PlatformIO. En esta iteración, la librería contenía el fichero de configuración y el de código para definir un broker vacío.
- Definir la estructura de los mensajes (peso: 8). La primera definición de los mensajes se realizó fuera de la librería, en ficheros `.h` que formaban parte de un ejemplo. En esta definición se distinguen tres tipos de mensajes: suscripción, desuscripción y publicación, que eran contenidos en un mensaje genérico con un campo de byte `msgType` para identificar el tipo de mensaje. Tanto los mensajes de suscripción como los de publicación contenían únicamente un campo `topic`, definido con capacidad para 10 caracteres, y los de publicación además contenían un campo `content` con capacidad para 20 bytes. El código de la definición se muestra en el Listado \ref{resultados:defMensajes1}.

```{.cpp #resultados:defMensajes1 .numberLines caption="Primera definición de los mensajes" frame=single}
#define MSGTYPE_SUBSCRIBE 1
#define MSGTYPE_UNSUBSCRIBE 2
#define MSGTYPE_PUBLISH 3

typedef struct {
	char topic[10];
} SubscribeAnnouncement;

typedef struct {
	char topic[10];
} UnsubscribeAnnouncement;

typedef struct {
	char topic[10];
	uint8_t content[20];
} PublishContent;

typedef union {
	SubscribeAnnouncement subscribeAnnouncement;
	UnsubscribeAnnouncement unsubscribeAnnouncement;
	PublishContent publish;
} PayloadUnion;

typedef struct {
	uint8_t msgType;
	PayloadUnion payload;
} Message;
```

- Crear un ejemplo de suscriptor (peso: 13). Sin utilizar la librería, se crearon dos códigos de ejemplo para los roles broker y suscriptor a partir de la definición de mensajes anterior. El broker utilizaba FreeRTOS para crear dos tareas que se ejecutan en paralelo: la primera generadora de mensajes de prueba en una cola de mensajes, y la otra para enviarlos a las placas que se hayan suscrito al broker (sin tener en cuenta los topics en esta iteración). Esta suscripción es controlada al añadir las direcciones de los suscriptores a un vector, y por cada nuevo suscriptor se comprueba si ya existía. El suscriptor, por su parte, crea mensajes de suscripción y se los envía al broker cada 2 segundos, además de controlar los mensajes de suscripción recibidos. El pseudocódigo de estos ejemplos se muestra en los Listados \ref{resultados:broker1} y \ref{resultados:subscriber1}.

```{.md #resultados:broker1 .numberLines caption="Pseudocódigo de la primera definición del broker" frame=single}
struct PayloadStruct: //Estructura de mensajes enviados
	int number

vector<uint8_t> subscribers //Contiene las direcciones MAC de las placas suscriptoras
QueueHandle_t messagesQueue //Cola de mensajes para enviar

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message recvMessage = Copia de los datos recibidos
	Si recvMessage.msgType es un mensaje de suscripción:
		Si mac no estaba en subscribers: //Si es un suscriptor nuevo
			Imprimir mensaje de aviso de suscripción con topic
			Agregar mac a subscribers

//Tarea encargada de gestionar la cola de mensajes
Función DispatchMessagesTask():
	Message message
	Por siempre:
		Recibir de la cola de mensajes y copiar en message
		Por cada subscriber en subscribers:
			Registrar el subscriber como par
			Enviar message a subscriber

//Tarea encargada de crear mensajes de prueba en la cola de mensajes
Función ProduceMessageTask():
	Por siempre:
		PayloadStruct payload
		payload.number = Número aleatorio
		Message sendMessage //Nuevo mensaje
		sendMessage.msgType = Definir mensaje como publicación
		sendMessage.payload.subscribeAnnouncement.topic = "mock" //Asignar topic al payload SubscribeAnnouncement
		sendMessage.payload.content = payload
		Enviar sendMessage a la cola messagesQueue
		Esperar 1 segundo

Función setup():
	Inicializar ESP-NOW
	Registrar la función OnDataRecv como callback al recibir un mensaje
	Inicializar la cola messagesQueue
	Crear tarea DispatchMessagesTask
	Crear tarea ProduceMessageTask
```

```{.md #resultados:subscriber1 .numberLines caption="Pseudocódigo de la primera definición del suscriptor" frame=single}
struct PayloadStruct: //Estructura de mensajes recibidos
	int number

uint8_t destBoardAddr[] //Contiene la dirección MAC de la placa broker

//Cada vez que se reciba un mensaje del broker, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message recvMessage = Copia de los datos recibidos
	PayloadStruct messagePayload = recvMessage.payload.publish.content //Contenido recibido
	Imprimir messagePayload.number

Función subscribe(char* topic):
	Message subMsg //Nuevo mensaje
	subMsg.msgType = Definir mensaje como suscripción
	subMsg.payload.subscribeAnnouncement.topic = topic //Asignar topic al payload SubscribeAnnouncement
	Enviar subMsg al broker

Función setup():
	Inicializar ESP-NOW
	Registrar la función OnDataRecv como callback al recibir un mensaje
	Registrar el broker como par

Función loop():
	subscribe("topic1")
	Esperar 2 segundos
```

/*TODO: preguntar si mencionar los ejemplos que utilicé*/

## Iteración 2

Periodo: 26/02/2024 - 08/03/2024 (1,71 semanas). Peso total: 49.

El objetivo principal de este sprint fue el soporte agregado a la publicación de mensajes y al uso de los temas.

Tareas:

- Probar la subida de la librería a PlatformIO (peso: 5).
- Crear ejemplo publicador (peso: 8). En adición al ejemplo del suscriptor realizado en la [iteración 1](#iteración-1), teniendo en común la desatención del topic y el desarrollo fuera de la librería, el publicador crea mensajes que publica en el broker. El Listado \ref{resultados:publisher1} muestra el pseudocódigo de este ejemplo. Asimismo, se añadió al broker la capacidad de gestionar estos mensajes, modificando la función `OnRecv` como se observa en el Listado \ref{resultados:modBroker1}.

```{.md #resultados:publisher1 .numberLines caption="Pseudocódigo de la primera definición del publicador" frame=single}
struct PayloadStruct: //Estructura de mensajes enviados
	int number

uint8_t destBoardAddr[] //Contiene la dirección MAC de la placa broker

Función generateAndPublish(char* topic):
	PayloadStruct payload
	payload.number = Número aleatorio
	Message sendMessage //Nuevo mensaje
	sendMessage.msgType = Definir mensaje como publicación
	sendMessage.payload.publish.topic = topic //Asignar topic al payload PublishContent
	sendMessage.payload.content = payload
	Enviar sendMessage al broker

Función setup():
	Inicializar ESP-NOW
	Registrar el broker como par

Función loop():
	generateAndPublish("topic1")
	Esperar 5 segundos
```

```{.md #resultados:modBroker1 .numberLines caption="Pseudocódigo de la modificación del broker del Listado \ref{resultados:broker1} para admitir publicaciones" frame=single}
//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message recvMessage = Copia de los datos recibidos
	Si recvMessage.msgType es un mensaje de suscripción:
		Si mac no estaba en subscribers: //Si es un suscriptor nuevo
			Imprimir mensaje de aviso de suscripción con topic
			Agregar mac a subscribers
	Sino si recvMessage.msgType es un mensaje de publicación:
		PublishContent pubMsg = recvMessage.payload.publish
		PayloadStruct pubContentPayload = pubMsg.content
		Imprimir pubContentPayload
		Enviar recvMessage a la cola messagesQueue
```

- Mejorar la estructura de los mensajes (peso: 8). La estructura original de la [iteración 1](#iteración-1) tenía un problema, y es que al utilizar un `typedef union` (utilizado para crear un mensaje genérico), todos los mensajes tenían el mismo tamaño, independientemente de su contenido, provocando un consumo de memoria innecesario. Para solucionarlo, se cambió la estructura de los mensajes, utilizando el primer byte para identificar el tipo de mensaje, y dependiendo del tipo se conoce la cantidad de bytes que habrá que leer del mensaje recibido. Este cambio se puede ver en el Listado \ref{resultados:defMensajes2}. A su vez, se realizaron ligeros cambios en el publicador, suscriptor y broker para gestionar los mensajes, añadiendo el mencionado método para identificarlos.

```{.cpp #resultados:defMensajes2 .numberLines caption="Segunda definición de los mensajes" frame=single}
typedef enum {
	MSGTYPE_SUBSCRIBE = 0x00,
	MSGTYPE_UNSUBSCRIBE,
	MSGTYPE_PUBLISH
} MessageType;

typedef struct {
	MessageType type;
} MessageBase;

typedef struct : public MessageBase {
	char topic[10];
} SubscribeAnnouncement;

typedef struct : public MessageBase {
	char topic[10];
} UnsubscribeAnnouncement;

typedef struct : public MessageBase {
	char topic[10];
	uint8_t content[20];
} PublishContent;
```

- Hacer ejemplos con tarjeta SD (peso: 8). Primer acercamiento a este tipo de memoria externa para aprender a trabajar con ficheros y carpetas.
- Implementar el uso de más topics (peso: 20). Para añadir esta posibilidad, se decidió crear una clase `BrokerTopic`, siendo cada una un topic o tema con un listado de suscriptores y una cola de mensajes, y las funciones apropiadas para gestionar la lista y la cola. Se crea una clase `BrokerTopic` por cada mensaje (de publicación o suscripción) recibido con un nuevo topic en el broker, añadiendo soporte a temas. El Listado \ref{resultados:brokerTopic1} muestra el pseudocódigo de la primera versión de esta clase, y \ref{resultados:broker2} muestra la implementación de `BrokerTopic`.

```{.md #resultados:brokerTopic1 .numberLines caption="Pseudocódigo de la primera definición de la clase BrokerTopic" frame=single}
Clase BrokerTopic:
Privado:
	char topic[10]
	vector<uint8_t[6]> subscribers //Direcciones MAC de los suscriptores
	QueueHandle_t messagesQueue //Cola que almacena mensajes para enviar

Público:
	Función constructora
	Función getTopic()
	Función getSubscribersAmount() //Cuenta la cantidad de suscriptores
	Función getSubscribers()
	Función subscribe(uint8_t *mac):
		Si no isSubscribed(mac):
			Registrar mac como par
			Agregar mac a subscribers
	Función isSubscribed(uint8_t *mac): //Comprueba si la dirección MAC ya estaba suscrita
		Por cada subscriber en subscribers:
			Si mac es igual que subscriber:
				Retornar true //Está suscrito
		Retornar false //No está suscrito
	Función sendToQueue(PublishContent *pubContent) //Enviar mensaje a la cola messagesQueue
	Función dispatchMessages(): //Enviar todos los mensajes de la cola messagesQueue a los suscriptores
		PublishContent message = Recibir una copia del primer mensaje de messagesQueue
		Por cada subscriber en subscribers:
			Registrar subscriber como par
			Enviar message a subscriber
```

```{.md #resultados:broker2 .numberLines caption="Pseudocódigo de la segunda definición del broker" frame=single}
struct PayloadStruct: //Estructura de mensajes enviados
	int number

vector<BrokerTopic> topicsVector //Contiene los topics

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message msgType = Primer byte de incomingData
	Según msgType:
		Si es un mensaje de suscripción:
			SubscribeAnnouncement *subAnnounce = Copia de los datos recibidos
			bool subscribed = false //Si la dirección MAC se suscribió en un topic existente
			Por cada topicObject en topicsVector:
				Si el topic de subAnnounce es el mismo que el de topicObject:
					Si mac no está suscrita en el topicObject:
						topicObject.subscribe(mac)
					subscribed = true

			Si subscribed es false:
				BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
				newTopic.subscribe(mac)
				Agregar newTopic a topicsVector

		Si es un mensaje de publicación:
			PublishContent *pubContent = Copia de los datos recibidos
			bool sent = false //Si la publicación se envió en un topic existente
			Por cada topicObject en topicsVector:
				Si el topic de pubContent es el mismo que el de topicObject:
					topicObject.sendToQueue(pubContent)
					sent = true

			Si sent es false:
				BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
				topicObject.sendToQueue(pubContent)
				Agregar newTopic a topicsVector

//Tarea encargada de enviar cada mensaje almacenado en los topics
Función DispatchMessagesTask():
	Por siempre:
		Por cada topicObject en topicsVector:
			topicObject.dispatchMessage()
		Esperar 1 segundo

//Tarea encargada de crear mensajes de prueba
Función ProduceMessageTask():
	Por siempre:
		PayloadStruct payload
		payload.number = Número aleatorio
		Message sendMessage //Nuevo mensaje
		sendMessage.msgType = Definir mensaje como publicación
		sendMessage.payload.subscribeAnnouncement.topic = "mock" //Asignar topic al payload SubscribeAnnouncement
		sendMessage.payload.content = payload

		bool queued = false //Si se pudo encolar el mensaje en un topic existente
		Por cada topicObject en topicsVector:
			Si el topic de sendMessage es el mismo que el de topicObject
				Enviar sendMessage a la cola de topicObject
				queued = true

		Si queued es false:
			BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de sendMessage
			Enviar sendMessage a la cola de topicObject
			Agregar newTopic a topicsVector

		Esperar 1 segundo

Función setup():
	Inicializar ESP-NOW
	Registrar la función OnDataRecv como callback al recibir un mensaje
	Inicializar la cola messagesQueue
	Crear tarea DispatchMessagesTask
	Crear tarea ProduceMessageTask
```

## Iteración 3

Periodo: 09/03/2024 - 15/03/2024 (1 semana). Peso total: 57.

El objetivo principal de este sprint fue la implementación de paralelismo al procesar los tipos de mensajes y la compatibilidad con caracteres comodín en los topics.

Tareas:

- Mover funciones de publicar/suscribir de los ejemplos al código de la librería (peso: 8). Las funciones desarrolladas como ejemplos en las iteraciones [1](#iteración-1) y [2](#iteración-2) fueron movidas tras considerarse versiones funcionales adecuadas, quedando declaradas como en el Listado \ref{resultados:libraryPubSub1}. Los códigos anteriores fueron modificados para hacer llamadas a la librería.

```{.md #resultados:libraryPubSub1 .numberLines caption="Pseudocódigo de la primera versión de los parámetros de funciones de publicar y suscribir definidos en la librería" frame=single}
Función publish(uint8_t *mac, char *topic, void *payload)
Función subscribe(uint8_t *mac, char *topic)
```

- Modificar callback del broker para crear tareas (peso: 20). Para aprovechar la capacidad del paralelismo, se implementaron tareas capaces de gestionar los mensajes de suscripción y publicación, que recorren los objetos `BrokerTopic` para determinar en cuál es más adecuado publicar o suscribir. En este primer acercamiento, cada vez que el broker recibe uno de estos mensajes, se crea una tarea. La modificación se llevó a cabo como se muestra en el Listado \ref{resultados:modBroker2}. Junto a esto, se eliminó la tarea `DispatchMessagesTask` del broker y se creó la función `publish(PublishContent pubContent)` en `BrokerTopic`, que envía directamente el mensaje de publicación a todos los suscriptores del objeto. Esto se debe a la nueva solución, en la que la carga del procesamiento de los suscriptores se realiza en cada tarea `PublishTask` creada.

```{.md #resultados:modBroker2 .numberLines caption="Pseudocódigo de la modificación del broker para crear tareas según el mensaje recibido" frame=single}
struct SubscribeTaskParams: //Estructura para los parámetros de la tarea de suscripción
	SubscribeAnnouncement *subAnnounce
	uint8_t *mac

struct PublishTaskParams: //Estructura para los parámetros de la tarea de publicación
	PublishContent *pubContent
	uint8_t *mac

Función SubscribeTask(void *parameter):
	SubscribeTaskParams params = parameter //Extraer los parámetros
	SubscribeAnnouncement subAnnounce = params.subAnnounce
	uint8_t mac = params.mac;

	bool subscribed = false //Si la dirección MAC se suscribió en un topic existente
	Por cada topicObject en topicsVector:
		Si el topic de subAnnounce es el mismo que el de topicObject:
			Si mac no está suscrita en el topicObject:
				topicObject.subscribe(mac)
			subscribed = true
	
	Si subscribed es false:
		BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
		newTopic.subscribe(mac)
		Agregar newTopic a topicsVector

Función PublishTask(void *parameter):
	PublishTaskParams params = parameter //Extraer los parámetros
	PublishContent pubContent = params.pubContent
	uint8_t mac = params.mac;

	bool sent = false //Si la publicación se envió en un topic existente
	Por cada topicObject en topicsVector:
		Si el topic de pubContent es el mismo que el de topicObject:
			topicObject.sendToQueue(pubContent)
			sent = true

	Si sent es false:
		BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
		topicObject.sendToQueue(pubContent)
		Agregar newTopic a topicsVector

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message msgType = Primer byte de incomingData
	Según msgType:
		Si es un mensaje de suscripción:
			SubscribeTaskParams subTaskParams
			subTaskParams.subAnnounce = Copia de los datos recibidos
			subTaskParams.mac = mac
			Crear tarea SubscribeTask con parámetro subTaskParams
		Si es un mensaje de publicación:
			PublishTaskParams pubTaskParams
			pubTaskParams.pubContent = Copia de los datos recibidos
			pubTaskParams.mac = mac
			Crear tarea PublishTask con parámetro pubTaskParams
```

- Añadir comprobador, agregador y eliminador de pares (peso: 13). ESP-NOW tiene un límite de pares que se pueden agregar, por lo que es necesario implementar un comprobador de pares para no agregar pares repetidos. Con este objetivo, se creó la función `addPeer(uint8_t *mac)` en `BrokerTopic`, que es llamada antes de enviar un mensaje a los suscriptores. Además, se creó la función `removePeer(uint8_t *mac)` para eliminar un par registrado en la futura implementación de la desuscripción.
- Hacer ejemplos con formatos CSV y [JSON](#JSON) en tarjeta SD (peso: 8). Crear ejemplos para serializar y deserializar objetos en ficheros contenidos en una tarjeta SD con el fin de aprender las capacidades de las librerías que lo permiten para implementar la persistencia de topics en futuras iteraciones.
- Añadir soporte a jerarquía de topics y caracteres comodín (peso: 8). La librería que se desarrolla en este proyecto se basa en [MQTT](#MQTT), y está influenciada por sus capacidades, como la jerarquía y los caracteres comodín o wildcards `+` y `#`. Esto implica tener en cuenta el topic que inserta el usuario al publicar o suscribirse mediante dos funciones creadas en la librería. Definidas en el Listado \ref{resultados:topicCheck}, `pubTopicCheck` y `subTopicCheck` ambas arreglan el mal uso de los caracteres `/`, comprueban que el tamaño del topic no sea mayor del permitido y recorren todos los caracteres comprobando que sean ASCII y estén bien utilizados, como por ejemplo, la prohibición del publicador para usar wildcards. Son funciones llamadas antes del envío de los mensajes, es decir, desde los roles publicador y suscriptor/desuscriptor.

	En cuanto a la jerarquía de suscripción, se refiere a la suscripción a un tema como `cocina/+`, que significa la suscripción a publicaciones con temas como `cocina/nevera` o `cocina/grifo`. Esto se ha resuelto implementando una nueva estrategia para crear `BrokerTopic`s. Primero, se sigue creando un `BrokerTopic` por cada suscripción, incluso si el topic tiene un wildcard. Para cada publicación, en cambio, se elimina esta capacidad, evitando un consumo de memoria por publicaciones sin receptores, que en este caso se descartarán. Una publicación a un topic pasa por la comprobación del topic con los `BrokerTopic`s ya creados, y si es compatible o "publicable", envía mensajes a los suscriptores. Por ejemplo, una publicación con topic `cocina/grifo` es "publicable" para los suscriptores de `cocina/+`, pero, por el contrario, una publicación `baño/grifo` no lo es, y si no existen `BrokerTopic`s compatibles se descarta el mensaje. La implementación se ha llevado a cabo agregando la función para comprobar si es "publicable" junto a un atributo que facilita dicha comprobación, como se muestra en el Listado \ref{resultados:brokerTopicWildcard}.

```{.md #resultados:topicCheck .numberLines caption="Pseudocódigo de las funciones añadidas para comprobar los topics" frame=single}
#define MAXTOPICLENGTH 10 //Declarada la longitud máxima del topic

Función fixTopicAndCheckLength(char *topic):
  Si topic es null:
  	Retornar error
  Elimina caracteres / añadidos al principio o al final
  Si topic es demasiado grande:
    Retornar error
	Retornar éxito

Función pubTopicCheck(char *topic):
  Si fixTopicAndCheckLength(topic) retorna error:
  	Retornar error
    
  Por cada caracter en topic:
    Si caracter es '+' o es '#' o no es ASCII:
    	Retornar error
    
  Retornar éxito

Función subTopicCheck(char *topic):
  Si fixTopicAndCheckLength(topic) retorna error:
    Retornar error
    
  Por cada caracter en topic:
  	Si no es ASCII:
    	Retornar error

    Si es '+' o es '#':
      Si está en una posición incorrecta:
        Retornar error

  Retornar éxito
```

```{.md #resultados:brokerTopicWildcard .numberLines caption="Pseudocódigo de la comprobación de compatibilidad en BrokerTopic" frame=single}
Clase BrokerTopic:
Privado:
	bool hasWildcards //Si el topic contiene wildcards
	char topic[MAXTOPICLENGTH]
	...

Público:
	Función constructora
	...
	Función publish(PublishContent pubContent)
    Función isPublishable(char *publishTopic):
		Si publishTopic es igual a topic:
			Retornar true
		Sino si hasWildcards es false:
			Retornar false
		Sino:
			Recorre publishTopic y topic comprobando que los wildcards en topic sean compatibles con los niveles de publishTopic
			Retornar true si son compatibles, false si no
```

## Iteración 4

Periodo: 16/03/2024 - 21/03/2024 (1 semana). Peso total: 39.

El objetivo principal de este sprint fue añadir soporte para la desuscripción y arreglar varios errores y vulnerabilidades.

Tareas:

- Probar publicador/suscriptor [MQTT](#MQTT) con Python (peso: 5). Al igual que en la [iteración 0](#iteración-0), pero esta vez con Python, trata de desarrollar un código para explorar las capacidades de [MQTT](#MQTT). En concreto, en esta iteración se comprobó que si un usuario se suscribe a dos temas como `cocina/nevera` y `cocina/+`, y se publica un mensaje en `cocina/nevera`, cuántas veces recibe el mensaje el suscriptor. El resultado fue 1.
- Realizar pruebas de estrés o bullying a la solución actual (peso: 5). La solución desarrollada en la [iteración 3](#iteración-3) presentó una vulnerabilidad revisada al final del sprint anterior. Anteriormente, se creaban tareas cada vez que se recibía un mensaje, lo que significaba que un nodo malicioso que publicara o se suscribiera constantemente al broker podría realizar ataques de denegación de servicio, provocando sobrecargas en la memoria o tareas mal ejecutadas. La tarea consistió en desarrollar un publicador malicioso que enviara mensajes constantemente a un broker desplegado y modificado para que las tareas demoren más tiempo, generando tres tipos de errores:

	- El broker no podía crear tareas, posiblemente debido a que la memoria de la placa estaba saturada con demasiadas tareas encoladas.
	- Error de "núcleo entró en pánico" y "carga prohibida".
	- Los mensajes no se trataban correctamente, el contenido era interpretado con caracteres erróneos.

- Arreglar vulnerabilidad DDOS (peso: 8). A partir de la prueba anterior, se vio necesario idear una nueva solución para gestionar los mensajes. En esta, el broker ejecuta constantemente una tarea por cada tipo de mensaje: una para publicar, otra para suscribir y otra para desuscribir. Estas tareas leen constantemente de una cola de mensajes, en las cuales los mensajes se insertan tras su recepción, como se muestra en el Listado \ref{resultados:modBroker3}.

```{.md #resultados:modBroker3 .numberLines caption="Pseudocódigo de la modificación del broker para insertar mensajes recibidos en colas" frame=single}
//Cantidad de tareas ejecutadas por tipo de mensaje
#define SUBSCRIBETASKS 1
#define UNSUBSCRIBETASKS 1
#define PUBLISHTASKS 1

struct SubscribeTaskParams: //Estructura para los parámetros de la tarea de suscripción
	SubscribeAnnouncement *subAnnounce
	uint8_t *mac

struct PublishTaskParams: //Estructura para los parámetros de la tarea de publicación
	PublishContent *pubContent
	uint8_t *mac

vector<BrokerTopic> topicsVector //Contiene los topics

//Colas de mensajes
QueueHandle_t subMsgQueue;
QueueHandle_t unsubMsgQueue;
QueueHandle_t pubMsgQueue;

//Tarea encargada de procesar mensajes de suscripción
Función SubscribeTask(void *parameter):
	SubscribeTaskParams params
	Por siempre:
		Recibir de la cola subMsgQueue y copiar en params
		//Extraer los parámetros
		SubscribeAnnouncement subAnnounce = params.subAnnounce
		uint8_t mac = params.mac;

		bool subscribed = false //Si la dirección MAC se suscribió en un topic existente
		Por cada topicObject en topicsVector:
			Si el topic de subAnnounce es el mismo que el de topicObject:
				Si mac no está suscrita en el topicObject:
					topicObject.subscribe(mac)
				subscribed = true
				Salir del bucle
		
		Si subscribed es false:
			BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
			newTopic.subscribe(mac)
			Agregar newTopic a topicsVector

		Esperar 1 segundo

//Tarea encargada de procesar mensajes de publicación
Función PublishTask(void *parameter):
	PublishTaskParams params = parameter
	Por siempre:
		Recibir de la cola pubMsgQueue y copiar en params
		//Extraer los parámetros
		PublishContent pubContent = params.pubContent
		uint8_t mac = params.mac;

		Por cada topicObject en topicsVector:
			Si topicObject.isPublishable(pubContent.topic): //Si el topic de la publicación es compatible con el del BrokerTopic
				topicObject.publish(pubContent)

		Esperar 1 segundo

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message msgType = Primer byte de incomingData
	Según msgType:
		Si es un mensaje de suscripción:
			SubscribeTaskParams subTaskParams
			subTaskParams.subAnnounce = Copia de los datos recibidos
			subTaskParams.mac = mac
			Enviar subTaskParams a la cola subMsgQueue
		Si es un mensaje de publicación:
			PublishTaskParams pubTaskParams
			pubTaskParams.pubContent = Copia de los datos recibidos
			pubTaskParams.mac = mac
			Enviar pubTaskParams a la cola pubMsgQueue

Función setup():
	Inicializar ESP-NOW
	Registrar la función OnDataRecv como callback al recibir un mensaje
	Inicializar la cola subMsgQueue
	Inicializar la cola unsubMsgQueue
	Inicializar la cola pubMsgQueue
	Crear tareas SubscribeTask según SUBSCRIBETASKS
	Crear tareas PublishTask según PUBLISHTASKS
```

- Implementar la desuscripción (peso: 13). Crear las funciones de desuscripción en la librería y en `BrokerTopic`, y la tarea y cola necesarias en el broker para gestionar este tipo de mensajes recibidos. La desuscripción elimina la dirección [MAC](#MAC) de la lista de suscriptores de un topic, en este caso se realiza aprovechando las funciones integradas en C++ para buscar en un vector y eliminar el elemento, junto con la función `removePeer` creada anteriormente. En adición a eliminar de la lista de suscriptores, para evitar malgasto de memoria, si al desuscribir el `BrokerTopic` se queda sin suscriptores, se elimina. La implementación se muestra en los Listados \ref{resultados:libraryPubSub2}, \ref{resultados:modBroker4} y \ref{resultados:brokerTopicUnsub}.

```{.md #resultados:libraryPubSub2 .numberLines caption="Pseudocódigo de la función de desuscribir definida en la librería" frame=single}
Función unsubscribe(uint8_t *mac, char *topic):
  Inicializar ESP-NOW
  Registrar el broker como par
  Si subTopicCheck(topic) retorna error:
    Retornar error
    
  UnsubscribeAnnouncement unsubMsg //Nuevo mensaje
  unsubMsg.type = Definir mensaje como desuscripción
  unsubMsg.topic = topic
  Enviar unsubMsg al broker
```

```{.md #resultados:modBroker4 .numberLines caption="Pseudocódigo de la adición de la desuscripción al broker" frame=single}
//Cantidad de tareas ejecutadas por tipo de mensaje
#define SUBSCRIBETASKS 1
#define UNSUBSCRIBETASKS 1
#define PUBLISHTASKS 1

struct UnsubscribeTaskParams: //Estructura para los parámetros de la tarea de desuscripción
	UnsubscribeAnnouncement *unsubAnnounce
	uint8_t *mac

vector<BrokerTopic> topicsVector //Contiene los topics

//Colas de mensajes
QueueHandle_t unsubMsgQueue;

//Tarea encargada de procesar mensajes de desuscripción
Función UnsubscribeTask(void *parameter):
	UnsubscribeTaskParams params
	Por siempre:
		Recibir de la cola unsubMsgQueue y copiar en params
		//Extraer los parámetros
		UnsubscribeAnnouncement unsubAnnounce = params.subAnnounce
		uint8_t mac = params.mac;

		Por cada it en topicsVector:
			Si el topic de unsubAnnounce es el mismo que el de it:
				Si mac está suscrita en el it:
					it.unsubscribe(mac)
					Si it tiene 0 suscriptores:
						Eliminar it de topicsVector
				Salir del bucle

		Esperar 1 segundo

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message msgType = Primer byte de incomingData
	Según msgType:
		...
		Si es un mensaje de desuscripción:
			UnsubscribeTaskParams unsubTaskParams
			unsubTaskParams.unsubAnnounce = Copia de los datos recibidos
			unsubTaskParams.mac = mac
			Enviar unsubTaskParams a la cola unsubMsgQueue

Función setup():
	Inicializar ESP-NOW
	Registrar la función OnDataRecv como callback al recibir un mensaje
	Inicializar la cola subMsgQueue
	Inicializar la cola unsubMsgQueue
	Inicializar la cola pubMsgQueue
	Crear tareas SubscribeTask según SUBSCRIBETASKS
	Crear tareas UnsubscribeTask según UNSUBSCRIBETASKS
	Crear tareas PublishTask según PUBLISHTASKS
```

```{.md #resultados:brokerTopicUnsub .numberLines caption="Pseudocódigo de la adición de la desuscripción a BrokerTopic" frame=single}
Clase BrokerTopic:
Privado:
    ...
	char topic[MAXTOPICLENGTH]
  vector<uint8_t[6]> subscribers //Direcciones MAC de los suscriptores

Público:
	Función constructora
	...
  Función removePeer(uint8_t *mac)
  Función isSubscribed(uint8_t *mac)
  Función unsubscribe(uint8_t *mac):
    Recorrer subscribers con un valor igual a mac
    Si lo encuentra:
      Borrar de subscribers
      removePeer(mac)
      Retornar true
    Retornar false //Si no se encontró
```

- Arreglar el envío de mensajes duplicados al suscribirse múltiples veces al mismo topic (peso: 8). Añadir un comprobador de los destinatarios a quienes ya se les envió el mensaje. Esto se realizó creando, al recibir un mensaje de publicación, un vector en el broker, `alreadySentMacs`, el cual es compartido por todos los `BrokerTopic`s compatibles. Este contiene todos los destinatarios. Primero se comprueba si un suscriptor ya está en esta lista y, si no es el caso, se le envía el mensaje y se añade a la lista. El uso de este vector desde `BrokerTopic` se observa en el Listado \ref{resultados:brokerTopicAlreadySent}.

```{.md #resultados:brokerTopicAlreadySent .numberLines caption="Pseudocódigo de la nueva comprobación para evitar envíos duplicados en BrokerTopic" frame=single}
Clase BrokerTopic:
Privado:
  ...
  vector<uint8_t[6]> subscribers //Direcciones MAC de los suscriptores

Público:
	Función constructora
	...
  Función addPeer(uint8_t *mac)
  Función publish(PublishContent pubContent, vector<uint8_t[6]> alreadySentMacs):
    Por cada subscriber en subscribers:
      bool alreadySent = false //Si ya se envió el mensaje
      Por cada sentMac en alreadySentMacs:
        Si sentMac es igual a subscriber: //Comprueba si está en la lista de "ya enviados"
          alreadySent = true
          Salir del bucle
        
      Si alreadySent es false:
        addPeer(subscriber)
        Enviar pubContent a subscriber
        Agregar subscriber a alreadySentMacs
```

## Iteración 5

Periodo: 16/03/2024 - 21/03/2024 (1 semana). Peso total: 57.

El objetivo principal de este sprint fue la mejora de la calidad del código, la corrección de errores y el primer paso para redactar la memoria.

Tareas:

- Encontrar (peso: 8) y arreglar (peso: 20) la recepción de mensajes corruptos o duplicados. Tras la revisión del sprint anterior, se encontró el fallo de que los mensajes de suscripción y desuscripción se duplicaban en las colas. El primer paso para resolverlo fue aislar el error, creando un broker dedicado únicamente a atender peticiones de suscripción. Luego de realizar pruebas modificando este código, se descubrió que el fallo se encontraba en la mala gestión de la memoria con las variables que almacenan los parámetros de los mensajes y se insertan en las colas, por lo que se solucionó haciendo un mejor uso de los punteros y de las liberaciones de memoria.
- Clonar la plantilla de la memoria del [TFG](#TFG) (peso: 5).
- Renombrar variables, añadir comentarios y arreglar el formato del código (peso: 8). Junto con eliminar código sin usar, comentarios innecesarios e implementar EditorConfig[^it5:editorConfig] y cumplir con los criterios de calidad, con el fin de mejorar la calidad del código.
- Crear ideas para nombrar la herramienta (peso: 8). En gran parte del desarrollo, la librería no ha tenido un nombre definido, siendo este paso es esencial para poder publicarla y darle una identidad.
- Probar y familiarizarse con la plantilla de la memoria (peso: 8). Aprender a utilizar la plantilla para empezar a redactar en posteriores iteraciones.

[^it5:editorConfig]: <https://editorconfig.org/>

## Resultados del TFG

Este apartado debe explicar cómo el empleo de la metodología permite satisfacer tanto el objetivo principal como los específicos planteados en el TFG así como los requisitos exigidos (según exposición en capítulo Objetivos).
