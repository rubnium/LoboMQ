# Introducción 

En este primer capítulo se presenta el problema que se pretende resolver mediante el desarrollo del Trabajo de Fin de Grado ([TFG](#TFG)), explicando el alcance de la solución, junto con la motivación y a los desafíos que han dado lugar.

A lo largo de este Trabajo de Fin de Grado se detalla el proceso de desarrollo de LoboMQ, un protocolo que se inspira en [MQTT](#MQTT) para tomar las bases de la comunicación publicador-suscriptor a través de colas de mensajes y adaptarlas a un entorno de trabajo con dispositivos del Internet de las Cosas. Este protocolo aprovecha las capacidades de ESP-NOW para ofrecer una comunicación sin cables ni Internet y a larga distancia, y es implementado en forma de una librería C++ para placas ESP32, la cual se encuentra disponible en el registro de PlatformIO. La librería LoboMQ ofrece al usuario las funciones necesarias para, con facilidad, desplegar un broker, publicar mensajes a un tema, y suscribirse y desuscribirse de los mismos.

## Motivación

El crecimiento en la popularidad del Internet de las Cosas es un hecho @IoTConexiones_Statista @IoTGasto_Statista, observable tanto en la aparición de productos cotidianos como en las iniciativas de gran alcance emprendidas por organizaciones. Esta situación implica el desarrollo cada vez más frecuente de soluciones que se enfrenten y adapten a distintas restricciones, tanto del dispositivo conectado como del entorno en el que se conecta.

Uno de los dispositivos más populares en el ámbito del [IoT](#IoT) son los microcontroladores ESP32, dispositivos con alta disponibilidad en el mercado, relativamente asequibles y con bastante apoyo y recursos en la comunidad de desarrolladores, siendo posible encontrar una gran cantidad de guías, ejemplos y tutoriales que permiten alcanzar las soluciones deseadas. Bajo la popularidad del [IoT](#IoT) también se frecuentan protocolos de mensajería publicador-suscriptor basados en colas de mensajes, como [MQTT](#MQTT), los cuales ofrecen la capacidad de comunicar bidireccionalmente muchos dispositivos entre sí. Existen una gran variedad de librerías que permiten implementar estos protocolos en microcontroladores @MqttLib1 @MqttLib2 @MqttLib3, pero dependen de una conexión a Internet para comunicarse con el dispositivo encargado de gestionar las colas de mensajes. En algunos contextos con poco o ningún alcance de red, situaciones que son comunes en este ámbito, esta dependencia puede ser un problema que implique encarecer el uso de soluciones [IoT](#IoT), provocando la pérdida de interés en los usuarios y desarrolladores.

Las placas de Espressif integran, junto con Wi-Fi, un protocolo de comunicación inalámbrica denominado ESP-NOW cuyo uso no requiere redes de Internet. Hasta donde alcanza el conocimiento del autor y los tutores de este [TFG](#TFG), el uso de ESP-NOW se ha limitado a que el desarrollador diseñe una manera propia de transmitir datos para cada proyecto, y no existe de forma pública ninguna solución que permita implementar un sistema publicación-suscripción aprovechando esta forma de comunicación. Esta es la oportunidad que el proyecto pretende explotar. Se busca aportar a la comunidad del Internet de las Cosas un protocolo utilizable en entornos restringidos por la red y el consumo energético, que combine tanto los beneficios de [MQTT](#MQTT) como los de ESP-NOW en placas ESP32.

## Desafíos durante la Realización

El desarrollo de la solución implica abordar una serie de desafíos, descritos a continuación.

En primer lugar, el uso de placas ESP32 requiere de conocimientos específicos para maximizar el rendimiento y la eficiencia durante la ejecución. FreeRTOS es fundamental en este contexto, ya que comprender su uso y los conceptos que lo sustentan permiten una correcta ejecución paralela de múltiples tareas en este microcontrolador, limitado por su capacidad de procesamiento. A su vez, requiere conocimientos del lenguaje C++ y de las herramientas para desarrollar código capaz de usar y liberar adecuadamente la memoria durante la ejecución. Por otro lado, el protocolo de comunicación utilizado, ESP-NOW, presenta sus propias limitaciones, como la cantidad de pares conectados simultáneamente y el tamaño máximo de los mensajes, las cuales deben ser consideradas al utilizarla.

Por otro lado, este nuevo protocolo, al basarse en el ya existente [MQTT](#MQTT), requiere un conocimiento profundo de su funcionamiento. Esto incluye el formato y los tipos de mensajes, las comprobaciones que se realizan al enviar mensajes, y el orden de ejecución y procesamiento, entre otros aspectos. Sin embargo, esto no limita la herramienta a ser una réplica fiel, ya que se deben diseñar componentes y funcionalidades del protocolo con suficiente libertad creativa, pero manteniendo una operación similar a [MQTT](#MQTT).

Finalmente, PlatformIO, a parte de permitir el desarrollo en las mencionadas placas, ofrece una serie de plantillas y comandos esenciales para desarrollar una librería. Esto implica realizar una lectura exhaustiva de la documentación de esta plataforma, junto con diversas pruebas, para disponer de una librería funcional.

## Objetivos

En este apartado se detallan el objetivo general y los subobjetivos específicos del proyecto, utilizados para guiar su desarrollo y evaluar la adecuación de los resultados obtenidos.

### Objetivo General

El objetivo general del proyecto es el diseño y la implementación en forma de librerías de un protocolo de mensajería publicador-subscriptor inspirado en [MQTT](#MQTT) y que haga uso del protocolo de comunicación inalámbrica ESP-NOW.

### Objetivos Específicos

La consecución del objetivo general se descompone en una serie de objetivos específicos esenciales descritos a continuación.

a. **Diseñar un protocolo de mensajería para redes ESP-NOW que incorpore características de publicación y suscripción similares a [MQTT](#MQTT).** Este objetivo inicial es fundamental para los siguientes, ya que pretende definir las características necesarias del protocolo conteniendo las bases de la mensajería a través de colas y temas. Esto incluye la definición de roles de los nodos (cliente y broker), las acciones que pueden realizar (publicar, suscribrse y desuscribirse), los tipos y formatos de los mensajes intercambiados, así como la secuencia de procesamiento de los mismos.

b. **Implementar librerías de software que permitan a los desarrolladores integrar fácilmente el protocolo propuesto en sus aplicaciones del Internet de las Cosas.** Una vez diseñado el protocolo, se debe proceder a su implementación práctica. Esto implica la creación de una librería pública que cumpla con las especificaciones de dicho protocolo, proporcionando funciones sencillas de utilizar y bien documentadas, facilitando su integración por parte de los desarrolladores.

c. **Presentar demostraciones o casos de uso que ilustren la utilidad y aplicabilidad del protocolo en contextos reales del Internet de las Cosas**. Como parte final del proyecto, demostrar su funcionamiento y relevancia a través de ejemplos prácticos y proveer instrucciones detalladas para utilizar la librería resultante es esencial.

## Estructura del Documento

El resto del contenido de esta memoria se estructura de la siguiente manera:

- Capítulo 2: se contextualiza el desarrollo de la solución, presentando conceptos como el Internet de las Cosas, varios protocolos de mensajería y las placas ESP32.
- Capítulo 3: se exponen las herramientas y metodologías utilizadas para el desarrollo de la solución, incluyendo el software y hardware requeridos, así como las distintas fases del desarrollo.
- Capítulo 4: se presenta el resultado de aplicar la metodología a lo largo de múltiples iteraciones, concluyendo con un apartado donde se detalla el protocolo final.
- Capítulo 5: se desarrollan las conclusiones del proyecto, repasando los objetivos alcanzados y reflexionando sobre el posible trabajo futuro, entre otros aspectos.
