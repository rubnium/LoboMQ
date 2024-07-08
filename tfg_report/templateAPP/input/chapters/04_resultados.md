# Resultados

En este capítulo se describe el avance del desarrollo del proyecto a través de iteraciones o sprints, mencionando los logros y problemas identificados en cada uno. Además, se muestra, mediante diagramas y listados, el funcionamiento de la herramienta desarrollada en su última versión a fecha de redacción de esta memoria. Este proyecto se puede encontrar en el repositorio /*TODO: insertar repo*/

Las iteraciones se comenzaron el 28 de septiembre de 2023, luego de evaluar la viabilidad del proyecto y de recopilar los requisitos y objetivos del mismo entre los tutores y el alumno, así como de establecer las metodologías y herramientas a utilizar. Estas iteraciones se desarrollaron en orden y se representan en la Figura \ref{resultados:gantt}, mostrada de manera optimizada a partir de febrero de 2024.

```{.plantuml #resultados:gantt caption="Diagrama de Gantt del proyecto desde febrero de 2024" frame=single}
@startgantt
printscale weekly
Project starts 2024-02-01
[Sprint 0] starts 2024-02-01 and ends 2024-02-18
[Sprint 1] starts at [Sprint 0]'s end and ends 2024-02-25
[Sprint 2] starts at [Sprint 1]'s end and ends 2024-03-08
[Sprint 3] starts at [Sprint 2]'s end and ends 2024-03-15
[Sprint 4] starts at [Sprint 3]'s end and ends 2024-03-21
[Sprint 5] starts at [Sprint 4]'s end and ends 2024-04-05
[Sprint 6] starts at [Sprint 5]'s end and ends 2024-04-12
[Sprint 7] starts at [Sprint 6]'s end and ends 2024-04-19
[Sprint 8] starts at [Sprint 7]'s end and ends 2024-04-26
[Sprint 9] starts at [Sprint 8]'s end and ends 2024-05-10
[Sprint 10] starts at [Sprint 9]'s end and ends 2024-05-23
[Sprint 11] starts at [Sprint 10]'s end and ends 2024-06-07
[Sprint 12] starts at [Sprint 11]'s end and ends 2024-06-21
[Sprint 13] starts at [Sprint 12]'s end and ends 2024-07-05
[Sprint 14] starts at [Sprint 13]'s end and ends 2024-07-12
[Primer release] happens at [Sprint 14]'s end
@endgantt
```

## Iteración 0

Periodo: 28/09/2023 - 18/02/2024 (20,43 semanas). Peso total: 143.

El objetivo principal de este sprint fue la preparación previa al desarrollo y la obtención de conocimientos necesarios. Esta es la iteración más larga y con menor progreso por semana debido a la necesidad de compaginar las asignaturas del grado con este desarrollo y a la lenta pero eficaz captación de conocimientos por parte del alumno.

Tareas:

- Preparar el entorno de desarrollo (peso: 3). Instalar las herramientas y crear el repositorio.
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
#definir MSGTYPE_SUBSCRIBE = 1
#definir MSGTYPE_UNSUBSCRIBE = 2
#definir MSGTYPE_PUBLISH = 3

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

- Crear un ejemplo de suscriptor (peso: 13). Sin utilizar la librería, se crearon dos códigos de ejemplo para los roles broker y suscriptor a partir de la definición de mensajes anterior. El broker utilizaba FreeRTOS para crear dos tareas que se ejecutan en paralelo: la primera generadora de mensajes de prueba en una cola de mensajes, y la otra para enviarlos a las placas que se hayan suscrito al broker (sin tener en cuenta los topics en esta iteración). Esta suscripción es controlada al añadir las direcciones de los suscriptores a un vector, y por cada nuevo suscriptor se comprueba si ya existía. El suscriptor, por su parte, crea mensajes de suscripción y se los envía al broker cada 2 segundos, además de controlar los mensajes de publicación recibidos. El pseudocódigo de estos ejemplos se muestra en los Listados \ref{resultados:broker1} y \ref{resultados:subscriber1}.

```{.md #resultados:broker1 .numberLines caption="Pseudocódigo de la primera definición del broker" frame=single}
struct PayloadStruct: //Estructura de mensajes enviados
	int number

vector<uint8_t> subscribers //Direcciones MAC de las placas suscriptoras
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
		message = Recibir un mensaje de messagesQueue
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

uint8_t destBoardAddr[] //Dirección MAC de la placa broker

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

uint8_t destBoardAddr[] //Dirección MAC de la placa broker

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

```{.md #resultados:modBroker1 .numberLines caption="Pseudocódigo de la modificación del broker para admitir publicaciones" frame=single}
//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t *mac, uint8_t *incomingData):
	Message recvMessage = Copia de los datos recibidos
	Si recvMessage.msgType es un mensaje de suscripción:
		Si mac no estaba en subscribers: //Si es un suscriptor nuevo
			Agregar mac a subscribers
	Sino si recvMessage.msgType es un mensaje de publicación:
		PublishContent pubMsg = recvMessage.payload.publish
		PayloadStruct pubContentPayload = pubMsg.content
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
- Implementar el uso de más topics (peso: 20). Para añadir esta posibilidad, se decidió crear una clase `BrokerTopic`, siendo cada una un topic con un listado de suscriptores y una cola de mensajes, y las funciones apropiadas para gestionar la lista y la cola. Se crea una clase `BrokerTopic`  en el broker por cada mensaje (de publicación o suscripción) recibido con un nuevo topic. El Listado \ref{resultados:brokerTopic1} muestra el pseudocódigo de la primera versión de esta clase, y el \ref{resultados:broker2} muestra la implementación de `BrokerTopic`.

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
	Función subscribe(uint8_t mac):
		Si no isSubscribed(mac):
			Registrar mac como par
			Agregar mac a subscribers
	Función isSubscribed(uint8_t mac): //Comprueba si la MAC ya estaba suscrita
		Recorrer subscribers
			Si encuentra mac en subscribers, retornar true //Suscrita
			Sino, retornar false //No suscrita
	Función sendToQueue(PublishContent pubContent) //Enviar mensaje a la cola messagesQueue
	Función dispatchMessages(): //Enviar todos los mensajes de la cola messagesQueue a los suscriptores
		PublishContent message = Recibir un mensaje de messagesQueue
		Por cada subscriber en subscribers:
			Registrar subscriber como par
			Enviar message a subscriber
```

```{.md #resultados:broker2 .numberLines caption="Pseudocódigo de la segunda definición del broker" frame=single}
struct PayloadStruct: //Estructura de mensajes enviados
	int number

vector<BrokerTopic> topicsVector //Contiene los topics

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t mac, uint8_t incomingData):
	Message msgType = Primer byte de incomingData
	Según msgType:
		Si es un mensaje de suscripción:
			SubscribeAnnouncement subAnnounce = Copia de los datos recibidos
			Por cada topicObject de topicsVector con topicObject.topic igual al topic de subAnnounce:
				Si mac no está suscrita al topicObject:
					topicObject.subscribe(mac)
			Si no hubo ningún topicObject con el mismo topic:
				BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
				newTopic.subscribe(mac)
				Agregar newTopic a topicsVector

		Si es un mensaje de publicación:
			PublishContent pubContent = Copia de los datos recibidos
			Por cada topicObject de topicsVector con topicObject.topic igual al topic de pubContent:
				topicObject.sendToQueue(pubContent)
			Si no hubo ningún topicObject con el mismo topic:
				BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
				topicObject.sendToQueue(pubContent)
				Agregar newTopic a topicsVector

//Tarea encargada de enviar cada mensaje almacenado en los topics
Función DispatchMessagesTask():
	Por siempre, cada 1 segundo:
		Por cada topicObject en topicsVector:
			topicObject.dispatchMessage()

//Tarea encargada de crear mensajes de prueba
Función ProduceMessageTask():
	Por siempre, cada 1 segundo:
		PayloadStruct payload
		payload.number = Número aleatorio
		Message sendMessage //Nuevo mensaje
		sendMessage.msgType = Definir mensaje como publicación
		sendMessage.payload.subscribeAnnouncement.topic = "mock" //Asignar topic al payload SubscribeAnnouncement
		sendMessage.payload.content = payload
		Por cada topicObject de topicsVector con topicObject.topic igual al topic de sendMessage:
			topicObject.sendToQueue(sendMessage)
		Si no hubo ningún topicObject con el mismo topic:
			BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de sendMessage
			topicObject.sendToQueue(sendMessage)
			Agregar newTopic a topicsVector

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

```{.md #resultados:libraryPubSub1 .numberLines caption="Pseudocódigo de la primera versión de los parámetros de las funciones para publicar y suscribir definidos en la librería" frame=single}
Función publish(uint8_t mac, char topic, void payload)
Función subscribe(uint8_t mac, char topic)
```

- Modificar callback del broker para crear tareas (peso: 20). Para aprovechar la capacidad del paralelismo, se implementaron tareas capaces de gestionar los mensajes de suscripción y publicación, que recorren los objetos `BrokerTopic` para determinar en cuál es más adecuado publicar o suscribir. En este primer acercamiento, cada vez que el broker recibe uno de estos mensajes, se crea una tarea. La modificación se llevó a cabo como se muestra en el Listado \ref{resultados:modBroker2}. Junto a esto, se eliminó la tarea `DispatchMessagesTask` del broker y se creó la función `publish(PublishContent pubContent)` en `BrokerTopic`, que envía directamente el mensaje de publicación a todos los suscriptores del objeto. Esto se debe a la nueva solución, en la que la carga del procesamiento de los suscriptores se realiza en cada tarea `PublishTask` creada.

```{.md #resultados:modBroker2 .numberLines caption="Pseudocódigo de la modificación del broker para crear tareas según el mensaje recibido" frame=single}
struct SubscribeTaskParams: //Estructura de parámetros para suscripción
	SubscribeAnnouncement subAnnounce
	uint8_t mac

struct PublishTaskParams: //Estructura de parámetros para publicación
	PublishContent pubContent
	uint8_t mac

Función SubscribeTask(void parameter):
	SubscribeTaskParams params = parameter //Extraer los parámetros
	SubscribeAnnouncement subAnnounce = params.subAnnounce
	uint8_t mac = params.mac
	Por cada topicObject de topicsVector con topicObject.topic igual al topic de subAnnounce:
		Si mac no está suscrita al topicObject:
			topicObject.subscribe(mac)
	Si no hubo ningún topicObject con el mismo topic:
		BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
		newTopic.subscribe(mac)
		Agregar newTopic a topicsVector

Función PublishTask(void parameter):
	PublishTaskParams params = parameter //Extraer los parámetros
	PublishContent pubContent = params.pubContent
	uint8_t mac = params.mac
	Por cada topicObject de topicsVector con topicObject.topic igual a pubContent.topic:
		topicObject.sendToQueue(pubContent)
	Si no hubo ningún topicObject con el mismo topic:
		BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
		topicObject.sendToQueue(pubContent)
		Agregar newTopic a topicsVector


//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t mac, uint8_t incomingData):
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

	En cuanto a la jerarquía de suscripción, se refiere a la suscripción a un tema como `cocina/+`, que significa la suscripción a publicaciones con temas como `cocina/nevera` o `cocina/grifo`. Esto se ha resuelto implementando una nueva estrategia para crear `BrokerTopic`s. Primero, se sigue creando un `BrokerTopic` por cada suscripción, incluso si el topic tiene un wildcard. Para cada publicación, en cambio, se elimina esta capacidad, evitando un consumo de memoria por publicaciones sin receptores, que en este caso se descartarán. Una publicación a un topic pasa por la comprobación del topic con los `BrokerTopic`s ya creados, y si es compatible o "publicable", envía mensajes a los suscriptores. Por ejemplo, una publicación con topic `cocina/grifo` es "publicable" para los suscriptores de `cocina/+`, pero, por el contrario, una publicación `banio/grifo` no lo es, y si no existen `BrokerTopic`s compatibles se descarta el mensaje. La implementación se ha llevado a cabo agregando la función para comprobar si es "publicable" junto a un atributo que facilita dicha comprobación, como se muestra en el Listado \ref{resultados:brokerTopicWildcard}.

```{.md #resultados:topicCheck .numberLines caption="Pseudocódigo de las funciones añadidas para comprobar los topics" frame=single}
#definir MAXTOPICLENGTH = 10 //Longitud máxima del topic

Función fixTopicAndCheckLength(char topic):
  Si topic es null:
  	Retornar error
  Eliminar caracteres / añadidos al principio o al final de topic
  Si topic es demasiado grande:
    Retornar error
	Retornar éxito

Función pubTopicCheck(char topic):
  Si fixTopicAndCheckLength(topic) retorna error:
  	Retornar error
  Si existe algún carácter '+', '#' o no ASCII en topic:
    Retornar error
  Retornar éxito

Función subTopicCheck(char topic):
  Si fixTopicAndCheckLength(topic) retorna error:
    Retornar error
  Por cada caracter en topic:
  	Si no es ASCII:
    	Retornar error
    Si es '+' o es '#' en una posición incorrecta:
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
  Función isPublishable(char publishTopic):
		Si publishTopic es igual a topic:
			Retornar true
		Si hasWildcards es true y se recorrieron los wildcards de topic probando su compatibilidad con publishTopic:
			Retornar true
		Sino:
			Retornar false
```

## Iteración 4

Periodo: 16/03/2024 - 21/03/2024 (1 semana). Peso total: 39.

El objetivo principal de este sprint fue añadir soporte para la desuscripción y arreglar varios errores y vulnerabilidades.

Tareas:

- Probar publicador/suscriptor [MQTT](#MQTT) con Python (peso: 5). Parecido a la [iteración 0](#iteración-0), trata de desarrollar un código en Python para explorar las capacidades de [MQTT](#MQTT). En concreto, en esta iteración se comprobó que si un usuario se suscribe a dos temas como `cocina/nevera` y `cocina/+`, y se publica un mensaje en `cocina/nevera`, cuántas veces recibe el mensaje el suscriptor. El resultado fue 1.
- Realizar pruebas de estrés o bullying a la solución actual (peso: 5). La solución desarrollada en la [iteración 3](#iteración-3) presentó una vulnerabilidad revisada al final del sprint anterior. Anteriormente, se creaban tareas cada vez que se recibía un mensaje, lo que significaba que un nodo malicioso que publicara o se suscribiera constantemente al broker podría realizar ataques de denegación de servicio, provocando sobrecargas en la memoria o tareas mal ejecutadas. La tarea consistió en desarrollar un publicador malicioso que enviara mensajes constantemente a un broker desplegado y modificado para que las tareas demoren más tiempo, generando tres tipos de errores:

	- El broker no podía crear tareas, posiblemente debido a que la memoria de la placa estaba saturada con demasiadas tareas encoladas.
	- Error de "núcleo entró en pánico" y "carga prohibida".
	- Los mensajes no se trataban correctamente, el contenido era interpretado con caracteres erróneos.

- Arreglar vulnerabilidad DDOS (peso: 8). A partir de la prueba anterior, se vio necesario idear una nueva solución para gestionar los mensajes. En esta, el broker ejecuta constantemente una tarea por cada tipo de mensaje: una para publicar, otra para suscribir y otra para desuscribir. Estas tareas leen constantemente de una cola de mensajes, en las cuales los mensajes se insertan tras su recepción, como se muestra en el Listado \ref{resultados:modBroker3}.

```{.md #resultados:modBroker3 .numberLines caption="Pseudocódigo de la modificación del broker para insertar mensajes recibidos en colas" frame=single}
//Cantidad de tareas ejecutadas por tipo de mensaje
#definir SUBSCRIBETASKS = 1
#definir UNSUBSCRIBETASKS = 1
#definir PUBLISHTASKS = 1

struct SubscribeTaskParams: //Estructura de parámetros para suscripción
	SubscribeAnnouncement subAnnounce
	uint8_t mac

struct PublishTaskParams: //Estructura de parámetros para publicación
	PublishContent pubContent
	uint8_t mac

vector<BrokerTopic> topicsVector //Contiene los topics

//Colas de mensajes
QueueHandle_t subMsgQueue;
QueueHandle_t pubMsgQueue;

//Tarea encargada de procesar mensajes de suscripción
Función SubscribeTask(void parameter):
	SubscribeTaskParams params
	Por siempre, cada 1 segundo:
		Recibir de la cola subMsgQueue y copiar en params
		//Extraer los parámetros
		SubscribeAnnouncement subAnnounce = params.subAnnounce
		uint8_t mac = params.mac
		topicObject = Primer elemento de topicsVector con un topic igual al de subAnnounce
		Si topicObject existe:
			Si mac no está suscrita al topicObject:
				topicObject.subscribe(mac)
		Sino:
			BrokerTopic newTopic = Nuevo topic creado con el mismo topic que el de subAnnounce
			newTopic.subscribe(mac)
			Agregar newTopic a topicsVector

//Tarea encargada de procesar mensajes de publicación
Función PublishTask(void parameter):
	PublishTaskParams params = parameter
	Por siempre, cada 1 segundo:
		Recibir de la cola pubMsgQueue y copiar en params
		//Extraer los parámetros
		PublishContent pubContent = params.pubContent
		uint8_t mac = params.mac
		Por cada topicObject en topicsVector:
			Si topicObject.isPublishable(pubContent.topic): //Compatibilidad entre topic de la publicación y el del BrokerTopic
				topicObject.publish(pubContent)

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t mac, uint8_t incomingData):
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
#definir SUBSCRIBETASKS = 1
#definir UNSUBSCRIBETASKS = 1
#definir PUBLISHTASKS = 1

struct UnsubscribeTaskParams: //Estructura de parámetros para desuscripción
	UnsubscribeAnnouncement *unsubAnnounce
	uint8_t *mac

vector<BrokerTopic> topicsVector //Contiene los topics

//Colas de mensajes
QueueHandle_t unsubMsgQueue;

//Tarea encargada de procesar mensajes de desuscripción
Función UnsubscribeTask(void parameter):
	UnsubscribeTaskParams params
	Por siempre, cada 1 segundo:
		Recibir de la cola unsubMsgQueue y copiar en params
		//Extraer los parámetros
		UnsubscribeAnnouncement unsubAnnounce = params.subAnnounce
		uint8_t mac = params.mac
		it = Primer elemento de topicsVector con un topic igual al de unsubAnnounce
		Si it existe:
			Si mac está suscrita al it:
				it.unsubscribe(mac)
			Si it tiene 0 suscriptores:
				Eliminar it de topicsVector

//Cada vez que se reciba un mensaje, se llama a esta función
Función OnDataRecv(uint8_t mac, uint8_t incomingData):
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
	Función removePeer(uint8_t mac)
	Función isSubscribed(uint8_t mac)
	Función unsubscribe(uint8_t mac):
		Recorrer subscribers con un valor igual a mac
		Si lo encuentra:
			Borrar de subscribers
			removePeer(mac)
			Retornar true
		Retornar false //Si no se encontró
```

- Arreglar el envío de mensajes duplicados al suscribirse múltiples veces al mismo topic (peso: 8). Añadir un comprobador de los destinatarios a quienes ya se les envió el mensaje. Esto se realizó creando, al recibir un mensaje de publicación, un vector `alreadySentMacs` en el broker, el cual es compartido por todos los `BrokerTopic`s compatibles con el topic publicado y contiene todos los destinatarios a los que ya se le envió el mensaje. Un objeto `BrokerTopic` de los compatibles primero comprueba uno a uno si sus suscriptores ya están en esta lista y, si no es el caso, se le envía el mensaje y se le añade al vector, para que otros objetos `BrokerTopic` compatibles no le envíen el mensaje.

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

## Iteración 6

Periodo: 06/04/2024 - 12/04/2024 (1 semana). Peso total: 36.

El objetivo principal de este sprint fue la integración del broker en el código de la librería.

Tareas:

- Tomar inspiración de otras memorias de [TFG](#TFG) (peso: 5).
- Crear ejemplos con las funciones integradas de log y la librería Elog (peso: 13). Dos ejemplos sencillos probando el registro o log en diferentes niveles y en la tarjeta SD, con el fin de comparar las capacidades de cada uno y decidir cuál es considerado más adecuado para las necesidades del alumno. Se descubrió poca libertad de uso con las funciones integradas, ya que requieren una configuración del proyecto que vaya a utilizarlas, traduciéndose negativamente en trabajo adicional para el usuario final.
- Mover el código fuente del broker a la librería (peso: 13). Al igual que lo realizado previamente con las funciones de publicar, suscribir y desuscribir, tras haberse probado en profundidad el funcionamiento del código del broker, se movió al código final de la librería, resultando en la función `setupBroker()`.
- Probar librería refactorizada (peso: 5). El proyecto pasó por una refactorización, incluyendo una jerarquía de ficheros, variables y definiciones organizadas, y la modificación y creación de cabeceras apropiadas para los usuarios finales que únicamente requieran de las funciones de cliente, solo las del broker, o ambas simultáneamente. La prueba implementó la librería y confirmó su correcto funcionamiento.

## Iteración 7

Periodo: 13/04/2024 - 19/04/2024 (1 semana). Peso total: 42.

El objetivo principal de este sprint fue la implementación de logs en la librería.

Tareas:

- Crear ejemplos con las librerías ArduinoLog[^it7:arduinoLog] y DebugLog[^it7:debugLog] (peso: 13). Siguiendo con la iteración anterior, se crearon ejemplos para probar las librerías.
- Elegir un sistema de registro/log (peso: 8). Comparar las funciones integradas de log y las librerías Elog, ArduinoLog, DebugLog, en base a requisitos establecidos por el alumno:

	- Simple de implementar y modificar o personalizar.
	- Diferentes niveles de registro.
	- Mensajes mostrados junto a marcas de tiempo y el nivel de log.
	- Permite guardar registros en la tarjeta SD.

	La comparación resultó en la decisión de utilizar Elog para implementar los registros.

- Crear la primera versión de la estructura de la memoria del [TFG](#TFG) (peso: 8). Idear una estructura adecuada para debatirla con los tutores y empezar a redactar en siguientes iteraciones.
- Implementar mensajes de registro (peso: 13). La implementación de Elog se basó en ofrecer la facilidad al usuario final de decidir qué tipo de mensajes mostrar en pantalla (en base al nivel de log) o si prefiere guardarlos en una tarjeta SD. Para ello, se crearon los ficheros `Logger.h` y `Logger.c`, que definen las tres funciones mostradas en el Listado \ref{resultados:logger1}. La idea es que el usuario primero cree un objeto `Elog` configurado a su gusto y se lo pase como parámetro a las funciones principales de la librería. Además, se modificó el broker, cambiando la función principal a `setupBroker(Elog logger)` para tomar el objeto configurado y utilizarlo, y añadiendo logs en el código para imprimir mensajes en puntos clave.

[^it7:arduinoLog]: <https://registry.platformio.org/libraries/thijse/ArduinoLog>
[^it7:debugLog]: <https://registry.platformio.org/libraries/hideakitai/DebugLog>

```{.md #resultados:logger1 .numberLines caption="Pseudocódigo de las funciones de Logger" frame=single}
Enumeración LoggerClass:
	BROKER,	PUBLISHER,	SUBSCRIBER,	UNKNOWN

Función initializeSerialLogger(LoggerClass className, LogLevel level = INFO) //Muestra logs por terminal
	Retorna objeto Elog configurado
Función initializeSDLogger(LoggerClass className, int cs, int sck, int miso, int mosi, LogLevel level = INFO) //Guarda logs en la tarjeta SD
	Retorna objeto Elog configurado a los pines de la tarjeta SD
Función disableLogger(): //No muestra ni guarda logs
	Retorna objeto Elog configurado
```

## Iteración 8

Periodo: 20/04/2024 - 26/04/2024 (1 semana). Peso total: 41.

El objetivo principal de este sprint fue crear y probar una estructura de ficheros para persistir los temas y suscriptores del broker.

Tareas:

- Implementar logs en las funciones de publicador/suscriptor (peso: 13). Al igual que en la función del broker, añadir mensajes de log clave e incluir por parámetro el objeto `Elog`, quedando las funciones `publish(uint8_t mac, char topic, void payload, Elog logger = disableLogger())`, `subscribe(uint8_t mac, char topic, Elog logger = disableLogger())` y `unsubscribe(uint8_t mac, char topic, Elog logger = disableLogger())`.
- Idear una estructura de ficheros para persistir los topics y sus suscriptores (peso: 8). Se ideó un sistema de almacenamiento para los objetos `BrokerTopic`, guardándolos dentro del directorio `/LoboMQ/topics` en ficheros [JSON](#JSON) debido a la sencillez de manipulación. Su contenido, como se observa en el Listado \ref{resultados:jsonEjemplo}, tiene dos campos: el topic y la lista de suscriptores en un formato de dirección MAC legible para el usuario, útil en caso de necesitar editarlo manualmente. El nombre de los ficheros se basa en el nombre del topic, aunque de manera limitada, ya que existen caracteres que el sistema operativo no permite utilizar para nombrar ficheros. Debido a que los nombres de los topics son siempre caracteres ASCII, y para no sustituir los caracteres inválidos por letras y símbolos que el usuario pueda usar, se ha optado por utilizar el juego de caracteres ASCII extendido, compatibles con el nombrado de ficheros. Los caracteres inválidos son sustituidos por caracteres con cierta semejanza según decidió el alumno, mostrados en la Tabla \ref{it8:caracteres}. Esto resulta en, por ejemplo, que la lista de suscriptores del topic `cocina/+` se guarde en el fichero `cocina√+.json`.

```{.json #resultados:jsonEjemplo .numberLines caption="Ejemplo de fichero de persistencia" frame=single}
{
	"topic": "cocina/+",
	"subscribers": [
		"C0:49:EF:CB:99:10",
		"29:BB:91:73:38:44"
	]
}
```

| Carácter ASCII inválido | Reemplazo extended ASCII |
|:-----------------------:|:------------------------:|
| <                       | «                        |
| >                       | »                        |
| :                       | ÷                        |
| "                       | ª                        |
| /                       | √                        |
| \                       | ì                        |
| \|                      | │                        |
| ?                       | ¿                        |
| *                       | º                        |


: Lista de caracteres inválidos y su reemplazo para el nombrado de ficheros de persistencia\label{it8:caracteres}

- Crear y probar la lectura y escritura de ficheros que almacenan topics y suscriptores (peso: 20). A partir de lo anterior, crear un ejemplo capaz de crear y leer ficheros en la tarjeta SD, y realizar las conversiones adecuadas para las direcciones MAC y el nombre del fichero.

## Iteración 9

Periodo: 27/04/2024 - 10/05/2024 (2 semanas). Peso total: 65.

El objetivo principal de este sprint fue la adición de la persistencia y de códigos de error a la librería.

Tareas:

- Añadir persistencia al broker para los temas y suscriptores (peso: 20). La persistencia permite almacenar en la tarjeta SD los temas y suscriptores que se están utilizando al momento de la ejecución del broker, permitiendo que el sistema se pueda reiniciar y continuar funcionando sin perder información. A partir de la estructura y las pruebas de la [iteración 8](#iteración-8), se ha implementado en el código del broker, comenzando por ofrecer la opción al usuario mediante los parámetros de `setupBroker(Elog logger = initializeSerialLogger(BROKER), bool persistence = false, int csSdPin = -1)`. Si el usuario activa la persistencia, se almacena el pin CS de la tarjeta SD y se inicializa un semáforo mutex, que controla los accesos a la tarjeta. El broker lee los ficheros almacenados al iniciarse y escribe el fichero correspondiente al topic cada vez que ocurre una suscripción o desuscripción, gracias a las funciones probadas en la iteración, incluidas en los ficheros `BrokerSDUtils` y recopiladas en el Listado \ref{resultados:brokerSdUtils}. Para evitar la constante conversión del topic al nombre de fichero compatible, se ha creado un atributo `filename` en la clase `BrokerTopic`.
- Redactar Estado del arte (peso: 40). Primera redacción de la memoria.
- Implementar códigos de error en las funciones (peso: 5). Con la intención de ofrecer al usuario herramientas para conocer el estado de su código, se han modificado las funciones para que retornen información sobre la ejecución, ya sea que esta fue correcta o que ocurrió algún error, mediante los siguientes códigos definidos:

	- `LMQ_ERR_SUCCESS`: ejecución correcta, sin errores.
	- `LMQ_ERR_INVAL_TOPIC`: el tema utilizado para publicar, suscribirse o desuscribirse no cumple con los requisitos de formato.
	- `LMQ_ERR_BAD_ESP_CONFIG`: no se pudo inicializar ESP-NOW.
	- `LMQ_ERR_ESP_SEND_FAIL`: no se pudo enviar el mensaje de publicación, suscripción o desuscripción.
	- `LMQ_ERR_XQUEUECREATE_FAIL`: el broker no pudo crear las colas necesarias.
	- `LMQ_ERR_XTASKCREATE_FAIL`: el broker no pudo crear las tareas necesarias.

```{.md #resultados:brokerSdUtils .numberLines caption="Pseudocódigo de las funciones de BrokerSDUtils" frame=single}
#definir FILE_PATH = "/LoboMQ/topics" //Directorio de ficheros
#definir FILE_FORMAT = ".json" //Formato de ficheros

Función replaceChars(char str): //Utilizado para los nombres de ficheros
	Retorna un string con los caracteres inválidos reemplazados
Función initializeSDCard(int csPin, Elog logger, SemaphoreHandle_t mutex, TickType_t delay):
	Inicializar conexión con la tarjeta SD
		Si falla, retornar false
	Tomar el mutex con una espera máxima indicada en delay
		Si pasa el tiempo, retornar false
	Crear las estructura de carpetas FILE_PATH
		Si falla, devolver mutex y retornar false
	Devolver el mutex
	Retornar true

Función restoreBTs(vector<BrokerTopic> topicsVector, Elog logger, SemaphoreHande_t mutex, TickType_t delay):
	Tomar el mutex con una espera máxima indicada en delay
		Si falla, retornar
	Por cada file en los ficheros del directorio FILE_PATH:
		Si file no es una carpeta y termina en FILE_FORMAT:
			JsonDocument doc
			Deserializar file en doc
				Si falla, continuar bucle
			topic = doc["topic"]
			JsonArray subscribersArray = doc["subscribers"]
			Si subscribersArray tiene tamaño igual a 0: //Si no tiene suscriptores
				Continuar bucle
			
			BrokerTopic newTopic = Creado con topic asignado
			Suscribir cada suscriptor de subscribersArray a newTopic
			newTopic.setFileName(file) //Guardar el nombre del fichero
	Devolver el mutex

Función writeBTtoFile(BrokerTopic brokerTopic, Elog logger, SemaphoreHande_t mutex, TickType_t delay):
	JsonDocument doc
	doc["topic"] = brokerTopic.topic
	doc["subscribers"] = brokerTopic.subscribers
	fullFilepath = FILE_PATH + "/" + brokerTopic.filename + FILE_FORMAT
	Tomar el mutex con una espera máxima indicada en delay
		Si pasa el tiempo, retornar
	file = Abrir fichero fullFilepath en modo escritura
	Si file existe:
		Serializar doc en file
	Devolver el mutex

Función deleteBTFile(char filename, Elog logger, SemaphoreHande_t mutex, TickType_t delay):
	Tomar el mutex con una espera máxima indicada en delay
		Si pasa el tiempo, retornar
	fullFilepath = FILE_PATH + "/" + filename + FILE_FORMAT
	file = Abrir fichero fullFilepath en modo escritura
	Si file existe:
		Eliminar fichero
	Devolver el mutex
```

## Iteración 10

Periodo: 11/05/2024 - 23/05/2024 (2 semanas). Peso total: 106.

El objetivo principal de este sprint fue añadir una capa de seguridad adicional a través de un whitelist.

Tareas:

- Crear clase para almacenar una lista de direcciones MAC (peso: 20). La creación de la nueva clase `MACAddrList` facilita al usuario la creación de listas de direcciones MAC. Esta clase hereda de la clase `vector` y añade funciones para verificar si una dirección MAC ya está incluida, para añadir una o varias direcciones a la vez (pasándolas como un string o un `uint8_t[6]`), para eliminarlas y para limpiar la lista.
- Añadir autenticación mediante una whitelist de MACs (peso: 20). A partir de la clase `MACAddrList` creada recientemente , el usuario puede crear una lista de direcciones al iniciar el broker, la cuál que será utilizada para comprobar quién tiene acceso. Esta lista es pasada a la función principal del broker, mostrada en el Listado \ref{resultados:finalBrokerH}. Por defecto, la whitelist es un puntero nulo, utilizado para indicar que no se ha especificado ninguna. En caso de estar especificada la whitelist, el broker, al recibir mensajes, primero verifica si el emisor se encuentra en dicha lista, y si no es así no procesa el mensaje.

```{.md #resultados:finalBrokerH .numberLines caption="Versión final del pseudocódigo de la declaración de funciones del broker" frame=single}
#definir BRO_DEFAULT_WHITELIST = nullptr
#definir BRO_DEFAULT_LOGGER = initializeSerialLogger(BROKER)
#definir BRO_DEFAULT_PERSISTENCE = false
#definir BRO_DEFAULT_CS_SD_PIN = -1

Función initBroker(MACAddrList whitelist = BRO_DEFAULT_WHITELIST, Elog logger = BRO_DEFAULT_LOGGER, bool persistence = BRO_DEFAULT_PERSISTENCE, int csSdPin = BRO_DEFAULT_CS_SD_PIN):
	Levantar el broker o retornar un código de error
```

- Arreglar y probar error al crear logs en la tarjeta SD (peso: 13).
- Arreglar y probar bug de creación de ficheros erróneos para la persistencia (peso: 13).
- Redactar Estado del Arte (peso: 40).

## Iteración 11

Periodo: 24/05/2024 - 07/06/2024 (2 semanas). Peso total: 106.

El objetivo principal de este sprint fue redactar la memoria y preparar la documentación Doxygen.

Tareas:

- Redactar Estado del arte (peso: 40) y Herramientas y metodología (peso: 40).
- Añadir descripciones Doxygen y corregir las ya existentes (peso: 13). Mejorar la documentación de las funciones que el usuario puede utilizar con descripciones detalladas, que serán mostradas en la página Doxygen.
- Migrar la librería al nuevo nombre (peso: 8). Finalmente, se decidió por el nombre "LoboMQ", por lo que se reemplazaron todos los nombres provisionales de los ficheros, las variables y cualquier otra referencia a la herramienta.
- Configurar Doxygen y Doxygen Awesome (peso: 13). Establecer las propiedades necesarias en el fichero Doxyfile y descargar las hojas de estilo Doxygen Awesome para generar un HTML que muestre la documentación del proyecto.

## Iteración 12

Periodo: 08/06/2024 - 21/06/2024 (2 semanas). Peso total: 100.

El objetivo principal de este sprint fue redactar la memoria y arreglar Doxygen.

Tareas:

- Redactar Estado del arte (peso: 40) y Herramientas y metodología (peso: 40).
- Corregir los comentarios y la generación de Doxygen (peso: 20). Realizado con el fin de mostrar la documentación de forma correcta.

## Iteración 13

Periodo: 22/06/2024 - 05/07/2024 (2 semanas). Peso total: 116.

El objetivo principal de este sprint fue redactar la memoria, realizar pequeñas correcciones, personalizar la herramienta y crear un test para probar el funcionamiento de los clientes.

Tareas:

- Añadir comprobación ASCII del topic al publicar (peso: 5). Arreglar esta opción ya existente en el caso de la suscripción.
- Eliminar el parámetro `csPin` no utilizado al recuperar objetos `BrokerTopic` de la tarjeta SD (peso: 5). Mejorar el código evitando la asignación innecesaria de parámetros.
- Actualizar y probar la librería Elog (peso: 8). Hasta el momento, en el desarrollo se ha utilizado la versión 1.1.4. Para asegurar que el uso de la librería siga siendo correcto, se realizan pruebas con la reciente versión 1.1.6.
- Añadir readme y un logo (peso: 5). Mejorar la documentación del proyecto mediante un fichero que lo describa, y crear un logo que añada identidad a la herramienta.
- Mejorar la generación de la documentación Doxygen y añadir comentarios (peso: 8).
- Crear test de publicador y suscriptor (peso: 13). Asegurar que las funciones de crear mensaje, extraer contenido y comprobar el topic funcionan correctamente, siendo además útil para comprobar estas funciones luego de que surja alguna modificación.
- Redactar Resultados (peso: 40), Estado del arte y Herramientas y metodología (peso: 40).



## Diseño final del protocolo

Una vez finalizado el desarrollo, los artefactos del protocolo quedan definidos. En LoboMQ existen 2 tipos de nodos: el broker y los clientes. El broker gestiona las suscripciones y actúa como un centro de mensajería, ya que redirige las publicaciones a los suscriptores interesados en el mismo tema. Los clientes, por su parte, publican mensaje en temas y se suscriben o desuscriben de estos. Tanto la publicación como la suscripción o desuscripción se transmiten de forma asíncrona, permitiendo la ejecución de tareas sin  estar bloqueados esperando una respuesta.

Se identifican tres tipos de mensajes: SubscribeAnnouncement, UnsubscribeAnnouncement y PublishContent, cuyos campos se muestran en la Figura /*TODO: crear*/. Estos mensajes tienen en común el campo `MessageType`, que identifica el tipo de mensaje, y `topic`, el tema al cual se relaciona el mensaje. El topic, al igual que en [MQTT](#MQTT), admite el uso de wildcards, pero en este caso está limitado a /*TODO: mencionar caracteres*/. Además, los mensajes no pueden superar los 250 bytes debido a las limitaciones de ESP-NOW.

/*TODO: hacer figura campos del protocolo*/

La implementación de este protocolo se realiza mediante la creación de código en C++ que utilice la homónima librería LoboMQ, la cual está disponible tanto en el anteriormente mencionado repositorio como en el registro de PlatformIO /*TODO: insertar enlace*/. La documentación de esta librería también se encuentra disponible en la página /*TODO: insertar enlace*/
