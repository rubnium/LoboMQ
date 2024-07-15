# Manual de uso y ejemplo simple

Este anexo demuestra el correcto uso de la librería LoboMQ por parte del usuario final, explicando sus componentes y proporcionando ejemplos.

Tras la correcta instalación de la dependencia de la librería, la cual está fuera del alcance de este anexo, es posible comenzar a integrar la librería en el código de cualquier proyecto. Dependiendo de las funciones a utilizar, será necesario incluir los ficheros de cabecera correspondientes, listados a continuación.

- `#include <LoboMQ/Broker.h>`:
	- Función `initBroker`: configurar las tareas y colas adecuadas para gestionar los mensajes recibidos y otorgar a la placa/nodo el rol de broker.
		- Parámetro `whitelist`: lista con las direcciones MAC permitidas.
		- Parámetro `logger`: objeto de tipo `Elog` para la salida de mensajes de registro.
		- Parámetro `persistence`: indica si se desea activar la persistencia.
		- Parámetro `csSdPin`: pin *Chip Select* del lector de tarjeta SD.
		- Retorna un código de error.
	- Clase `MACAddrList`: lista de direcciones MAC. Hereda de `std::vector`, añadiendo nuevas funciones:
		- `isInList`: comprobar si una dirección MAC se encuentra en la lista.
			- Parámetro `mac`: dirección MAC a comprobar.
			- Retorna `true` o `false`.
		- `addToList`: añadir una dirección MAC a la lista. No inserta duplicados.
			- Parámetro `mac`: dirección MAC a añadir.
		- `addArrayToList`: añadir múltiples direcciones MAC de un array a la lista. No inserta duplicados.
			- Parámetro `macArray`: array de direcciones MAC.
		- `removeFromList`: eliminar una dirección MAC de la lista.
			- Parámetro `mac`: dirección MAC a eliminar.
			- Retorna `true` si se eliminó correctamente, o `false`.
		- `clearList`: vaciar la lista.
		- `getAddressListAsString`: obtener un string con todas las direcciones MAC de la lista.
		 
- `#include <LoboMQ/PubSub.h>`. Funciones incluidas:
	- `publish`: tomar el payload, construir un mensaje y publicarlo en el tema especificado en el broker.
		- Parámetro `mac`: dirección MAC del broker.
		- Parámetro `topic`: tema al que se publicará el mensaje.
		- Parámetro `payload`: contenido del mensaje.
		- Parámetro `payloadSize`: tamaño del payload en bytes.
		- Parámetro `logger`: objeto de tipo `Elog` para la salida de mensajes de registro.
		- Retorna un código de error.
	- `subscribe`: enviar un mensaje al broker anunciando interés en recibir todos los mensajes compatibles con el tema especificado.
		- Parámetro `mac`: dirección MAC del broker.
		- Parámetro `topic`: tema al que se suscribe el emisor.
		- Parámetro `logger`: objeto de tipo `Elog` para la salida de mensajes de registro.
		- Retorna un código de error.
	- `unsubscribe`: enviar un mensaje al broker anunciando desinterés en recibir todos los mensajes compatibles con el tema especificado.
		- Parámetro `mac`: dirección MAC del broker.
		- Parámetro `topic`: tema del cual se desuscribe el emisor.
		- Parámetro `logger`: objeto de tipo `Elog` para la salida de mensajes de registro.
		- Retorna un código de error.
	- `isLMQMessage`: comprobar si los bytes representan un mensaje de publicación LoboMQ.
		- Parámetro `incomingData`: bytes a comprobar.
		- Retorna `true` o `false`.
	- `getLMQPayload`: extraer el payload de los bytes de un mensaje de publicación LoboMQ.
		- Parámetro `incomingData`: bytes del mensaje.
		- Retorna un objeto `PayloadContent`.
- `#include <LoboMQ.h>`. Incluye todas las funciones mencionadas anteriormente.

Estas cabeceras comparten el objeto `Elog logger`, el cual hereda características relevantes, como la función `log` para mostrar mensajes de registro y el listado de niveles de registro: `ALERT`, `CRITICAL`, `ERROR`, `WARNING`, `NOTICE`, `INFO` y `DEBUG`. Esta librería incluye funciones para crear este objeto fácilmente:

- `initializeSerialLogger`: crear un objeto `Elog` que imprime mensajes en el monitor serial.
	- Parámetro `className`: clase de registro.
	- Parámetro `level`: nivel más crítico de registro interesado.
	- Retorna un objeto `Elog`.
- `initializeSDLogger`: crear un objeto `Elog` que imprime mensajes en la tarjeta SD.
	- Parámetro `className`: clase de registro.
	- Parámetros `cs`, `sck`, `miso` y `mosi`: pines del módulo lector de la tarjeta SD.
	- Parámetro `level`: nivel más crítico de registro interesado.
	- Retorna un objeto `Elog`.
- `disableLogger`: crear un objeto `Elog` sin la habilidad para mostrar mensajes de registro.
	- Retorna un objeto `Elog`.

El valor de `className` debe ser `BROKER`, `PUBLISHER`, `SUBSCRIBER` o `UNKNOWN`, dependiendo del rol del nodo que cree el objeto. Esto es importante, ya que al ver el registro, permite conocer quién lo está emitiendo.

Cabe aclarar que cada vez que se mencionan los códigos de error en las funciones principales de LoboMQ, se refiere a los mostrados en la Sección [4.10](#iteracion-9). Por otro lado, el uso de temas o topics está restringido de la siguiente manera:

- Existe un límite de 24 caracteres.
- Solo se admiten caracteres ASCII.
- El uso de caracteres comodín es similar al del protocolo MQTT, explicado en la Subsección [2.2.1](##message-queue-telemetry-transport-mqtt).
- No se puede publicar en temas con caracteres comodín.
- No se puede utilizar el carácter comodín `#` en un nivel intermedio. Por ejemplo, `sensor/#/temp`.

Además, resulta ideal conocer las estructuras de los mensajes de publicación, ya que de esta manera el desarrollador puede extraer otros campos que esta librería no aporta con facilidad. Los mensajes publicados y los que reciben los suscriptores utilizan la estructura `PublishContent`, formada por el topic, el contenido en bytes y el tamaño del contenido. Por otro lado, este mensaje es filtrado y extraído en una estructura `PayloadContent` al utilizar la función `getLMQPayload`. Ambas estructuras mencionadas se muestran en el Listado \ref{anexoManual:structs}.

```{.cpp #anexoManual:structs .numberLines caption="Estructuras de PublishContent y PayloadContent" frame=single}
typedef struct : public MessageBase {
	char topic[MAXTOPICLENGTH];
	size_t contentSize;
	void* content[MAXCONTENTSIZE];
} PublishContent;

typedef struct {
	size_t contentSize;
	void* content[MAXCONTENTSIZE];
} PayloadContent;
```

Una vez puesta a disposición del usuario final la funcionalidad de la librería, se procede a ver cómo se utiliza para los distintos tipos de nodos: broker y cliente, teniendo este último la capacidad de publicar y suscribirse o desuscribirse.

## Broker

El despliegue de este nodo es el más sencillo, ya que `initBroker` es la única función que se necesita llamar para realizarlo. Si es necesario aprovechar las funcionalidades disponibles, se debe seguir la siguiente secuencia de ejecución:

1. Crear la whitelist de direcciones MAC. Si no es necesario, se debe utilizar su valor por defecto, el cual indica que no se usa este método de control de acceso.
2. Crear el logger. Su valor por defecto imprime los mensajes por el monitor serial.
3. Llamar a la función `initBroker`. Si es necesario, se debe indicar la persistencia.

El siguiente ejemplo muestra un broker con persistencia y control de acceso activado. Para ello, primero se han realizado las conexiones adecuadas entre la placa ESP32 y el lector de tarjetas SD, como se muestra en la Figura \ref{anexoManual:broker}. Luego, se presenta el desarrollo del código de este ejemplo, representado en el Listado \ref{anexoManual:brokerCode}.

![Diagrama de conexión del broker\label{anexoManual:broker}](broker_ej1.png){width=80%}

```{.cpp #anexoManual:brokerCode .numberLines caption="Código del broker de ejemplo" frame=single}
#include <LoboMQ/Broker.h>

void setup() {
  Serial.begin(9600);
  MACAddrList *whitelist = new MACAddrList();
  whitelist->addArrayToList((std::vector<String>){
    "08:B6:1F:BA:04:F8", 
    "C0:49:EF:CB:99:10"
  });
	
  //Choose logger
  Elog *logger = initializeSDLogger(BROKER, 5, 18, 19, 23, DEBUG);

  //Initialize broker
  initBroker(whitelist, logger, true, 5);
}

void loop() { }
```

Este ejemplo se encuentra en la carpeta `examples` de la librería.

## Publicador

En el caso de un nodo que publique contenido, la secuencia de ejecución es la siguiente:

1. Crear el logger. Su valor por defecto imprime los mensajes por el monitor serial.
2. Crear la estructura del contenido a publicar. Debe ser la misma estructura en el suscriptor.
3. Crear el contenido a publicar.
4. Llamar a la función `publish`. Uno de los parámetros es la dirección del broker, que debe de obtenerse previamente. Una manera de hacerlo es revisando los logs al iniciar el broker.

El siguiente código de ejemplo, mostrado en el Listado \ref{anexoManual:pubCode}, contiene un publicador que genera un número aleatorio y lo publica cada dos segundos en el tema "topic1".

```{.cpp #anexoManual:pubCode .numberLines caption="Código del publicador de ejemplo" frame=single}
#include <LoboMQ/PubSub.h>

uint8_t brokerAddr[] = {0x24, 0xDC, 0xC3, 0x9C, 0x7E, 0x40}; //Broker MAC destination

Elog *_logger;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); //to generate random numbers

  //Choose logger:
  _logger = initializeSerialLogger(PUBLISHER, DEBUG);

  _logger->log(INFO, "Started publisher board on %s!", WiFi.macAddress().c_str());
}

void loop() {
  int numberExample = random(101); //generates random number
  publish(brokerAddr, "topic1", &numberExample, sizeof(numberExample), _logger);
  sleep(2);
}
```

Este ejemplo se encuentra en la carpeta `examples` de la librería.

## Suscriptor y desuscriptor

A diferencia de los ejemplos previos, el suscriptor requiere aplicar más lógica, ya que estos nodos procesan los mensajes recibidos. La secuencia de ejecución es la siguiente:

1. Crear el logger. Su valor por defecto imprime los mensajes por el monitor serial.
2. Crear la estructura del contenido a publicar. Debe ser la misma estructura en el publicador.
3. Configurar ESP-NOW junto a la función que procesa los mensajes.
4. Llamar a la función `subscribe`. Uno de los parámetros es la dirección del broker, que debe de obtenerse previamente. Una manera de hacerlo es revisando los logs al iniciar el broker.

Junto a esta secuencia, en la función utilizada para procesar los mensajes, resulta esencial llamar a las funciones de LoboMQ `isLMQMessage` y `getLMQPayload` para comprobar que el mensaje recibido forma parte de LoboMQ y obtener sus bytes de contenido. Estos bytes luego pueden ser copiados a un objeto de la estructura definida en el paso 2.

En cambio, la secuencia de ejecución de la desuscripción es más simple:

1. Crear el logger. Su valor por defecto imprime los mensajes por el monitor serial.
2. Configurar ESP-NOW.
3. Llamar a la función `unsubscribe`. Uno de los parámetros es la dirección del broker, que debe de obtenerse previamente. Una manera de hacerlo es revisando los logs al iniciar el broker.

El siguiente código de ejemplo muestra el uso de estas características, suscribiéndose a cualquier tema y, 20 segundos más tarde, desuscribiéndose. Además, muestra una forma de procesar los mensajes recibidos, en este caso un entero. Todo ello es observable en el Listado \ref{anexoManual:subCode}.

```{.cpp #anexoManual:subCode .numberLines caption="Código del suscriptor y desuscriptor de ejemplo" frame=single}
#include <LoboMQ/PubSub.h>

uint8_t brokerAddr[] = {0x24, 0xDC, 0xC3, 0x9C, 0x7E, 0x40}; //Broker MAC destination

Elog *_logger;

//Function called on every ESP-NOW message reception
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (isLMQMessage(incomingData)) {
    PayloadContent content = getLMQPayload(incomingData);

    int numberExample;
    memcpy(&numberExample, &content.content, content.contentSize);

    _logger->log(INFO, "Received LMQ message of %dB", content.contentSize);
    _logger->log(INFO, "Number: %d", numberExample);
  } else {
    _logger->log(ERROR, "Invalid message type received");
  }
}

void setup() {
  Serial.begin(9600);

  //Choose logger:
  _logger = initializeSerialLogger(SUBSCRIBER, DEBUG);

  WiFi.mode(WIFI_STA);

  //Initialize ESP-NOW and set up receive callback
  if (esp_now_init() != ESP_OK || esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    _logger->log(ERROR, "Couldn't initialize ESP-NOW");
    exit(1);
  }

  _logger->log(INFO, "Started subscriber board on %s!", WiFi.macAddress().c_str());
  subscribe(brokerAddr, "#", _logger);
  sleep(20);
  unsubscribe(brokerAddr, "#", _logger);
}

void loop() { }
```

Este ejemplo se encuentra en la carpeta `examples` de la librería.
