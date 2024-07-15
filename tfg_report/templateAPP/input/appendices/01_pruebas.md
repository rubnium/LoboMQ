# Pruebas

Se han desarrollado pruebas para comprobar la correcta ejecución del código en la librería. Debido a que PlatformIO no proporciona una manera sencilla de verificar la correcta comunicación entre dos placas, en este capítulo solo se abordan pruebas que evalúan funciones de la librería que no están relacionadas directamente con el envío de datos.

En el caso de los ficheros `PubSub`, estas pruebas unitarias de caja negra tienen como objetivo probar la correcta identificación de los mensajes y los temas restringidos para publicar o suscribirse.

La primera prueba consiste en crear un mensaje con un número y almacenarlo como bytes, tal como lo haría un publicador. Luego, se llama a la función `isLMQMessage()` para comprobar que se trata de un mensaje compatible con LoboMQ, y posteriormente se extraen los datos creando los correspondientes objetos, llamando a la función `getLMQPayload()` para obtener el contenido de los bytes, al igual que lo haría un suscriptor. Finalmente, se verifica si el número empaquetado sigue siendo el mismo. Este código se detalla en el Listado \ref{anexoPruebas:testCreateGetMessage}

```{.cpp #anexoPruebas:testCreateGetMessage .numberLines caption="Código para probar la creación de mensajes y la obtención de su contenido" frame=single}
//Payload structure
typedef struct { 
  int number;
} CustomPayloadStruct;

TEST_CASE("Create Message And Check And Get Content") {
  int number = 666;

  //Create and fill publish message
  CustomPayloadStruct payloadSend;
  payloadSend.number = number;
  PublishContent pubMsg;
  pubMsg.type = MSGTYPE_PUBLISH;
  strcpy(pubMsg.topic, "test");
  pubMsg.contentSize = sizeof(payloadSend);
  memcpy(&pubMsg.content, &payloadSend, sizeof(payloadSend));

  //Transform to bytes
  const uint8_t *data = (const uint8_t *) &pubMsg;

  CHECK(isLMQMessage(data) == true);

  //Extract payload from bytes
  PayloadContent contentRecv = getLMQPayload(data);
  CustomPayloadStruct payloadRecv;
  memcpy(&payloadRecv, &contentRecv.content, contentRecv.contentSize);

  CHECK(payloadRecv.number == number);
}
```

El resto de los tests de estos ficheros prueban la compatibilidad de los temas con la publicación y la suscripción. A partir de las verificaciones que se realizan al publicar o suscribirse, se han identificado una serie de casos de prueba, mostrados en la Tabla \ref{anexoPruebas:casosTopics} junto al parámetro que recibe la función y el resultado esperado. Estos buscan cubrir todas las condiciones y decisiones posibles. Se prueba la comprobación de temas nulos o vacíos, la presencia de caracteres ASCII, el tamaño excesivo de los temas y el uso de caracteres comodín en posiciones prohibidas.

| Función         | Parámetros                             | Resultado             |
| --------------- | -------------------------------------- | --------------------- |
| `pubTopicCheck` | `topic = "/aaa/"`                      | `LMQ_ERR_SUCCESS`     |
| `pubTopicCheck` | `topic = "aaa"`                        | `LMQ_ERR_SUCCESS`     |
| `pubTopicCheck` | `topic = "aaa/+`                       | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "aaa/+/aaa"`                  | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "+/aaa"`                      | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "+"`                          | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "aaa/#"`                      | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "aaa/#/aaa"`                  | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "#/aaa"`                      | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "#"`                          | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "/"`                          | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = ""`                           | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = null`                         | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "ááá"`                        | `LMQ_ERR_INVAL_TOPIC` |
| `pubTopicCheck` | `topic = "aaaaaaaaaaaaaaaaaaaaaaaaaa"` | `LMQ_ERR_INVAL_TOPIC` |
| --------------- | -------------------------------------- | --------------------- |
| `subTopicCheck` | `topic = "/aaa/"`                      | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "aaa"`                        | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "aaa/+`                       | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "aaa/+/aaa"`                  | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "+/aaa"`                      | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "+"`                          | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "aaa/#"`                      | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "aaa/#/aaa"`                  | `LMQ_ERR_INVAL_TOPIC` |
| `subTopicCheck` | `topic = "#/aaa"`                      | `LMQ_ERR_INVAL_TOPIC` |
| `subTopicCheck` | `topic = "#"`                          | `LMQ_ERR_SUCCESS`     |
| `subTopicCheck` | `topic = "/"`                          | `LMQ_ERR_INVAL_TOPIC` |
| `subTopicCheck` | `topic = ""`                           | `LMQ_ERR_INVAL_TOPIC` |
| `subTopicCheck` | `topic = null`                         | `LMQ_ERR_INVAL_TOPIC` |
| `subTopicCheck` | `topic = "ááá"`                        | `LMQ_ERR_INVAL_TOPIC` |
| `subTopicCheck` | `topic = "aaaaaaaaaaaaaaaaaaaaaaaaaa"` | `LMQ_ERR_INVAL_TOPIC` |

: Casos de prueba en la comprobación de topics\label{anexoPruebas:casosTopics}

Estas pruebas se encuentran en la carpeta `test` de la librería. Han sido desarrolladas con el framework de pruebas Doctest[^anexoPruebas:doctest], y para su ejecución se requiere de placas compatibles con el modo de depuración y pruebas, conectadas al ordenador encargado de compilar y subir el código del test desde PlatformIO.

[^anexoPruebas:doctest]: <https://docs.platformio.org/en/latest/advanced/unit-testing/frameworks/doctest.html>
