# Conclusiones

En este capítulo final se presentan las conclusiones respecto a cómo se ha abordado el problema principal, analizando los objetivos cumplidos y el coste total del proyecto, y revisando las competencias de la formación académica adquiridas. Finalmente, se realiza una autocrítica del proyecto, señalando las posibles mejoras que se podrían implementar en el futuro.

## Revisión de los objetivos

En esta sección se analiza la consecución del objetivo principal del proyecto, el diseño y la implementación de un protocolo de mensajería publicador-subscriptor inspirado en [MQTT](#MQTT) y que haga uso del protocolo de comunicación inalámbrica ESP-NOW. Este objetivo se alcanzó a través de los siguientes objetivos específicos:

a. **Diseñar un protocolo de mensajería para redes ESP-NOW que incorpore características de publicación y suscripción similares a MQTT.** El diseño se ha alcanzado observando el funcionamiento y las características de MQTT y los límites de ESP-NOW. En base a esto, se definieron los tipos de mensaje intercambiados, los roles y las acciones realizables.

b. **Implementar librerías de software que permitan a los desarrolladores integrar fácilmente el protocolo propuesto en sus aplicaciones del Internet de las Cosas.** Este objetivo ha sido cumplido al crear una librería basada en la especificación anterior del protocolo que contiene las funciones necesarias para desplegar el broker, publicar, suscribirse o desuscribirse, y otras adicionales que complementan el uso del protocolo. Estas funciones fueron creadas con empatía hacia el usuario novato, quitándole en la mayor cantidad posible la responsabilidad de manejar la comunicación del protocolo mediante funciones que abstraen la creación de tareas y colas, la conexión con los nodos y la creación de los mensajes, y cuyos parámetros contienen lo justo y necesario. El código fuente ha sido desarrollado siguiendo criterios de calidad (listados en el Apartado [3.2.6](#criterios-de-calidad-y-estilo-del-codigo)), permitiendo al usuario comprender la ejecución de las funciones y el motivo de la existencia de las variables y estructuras. A esta característica se le suma el estar disponible la librería de manera pública en GitHub, posibilitando a que otros desarrolladores tomen la librería y creen su propia versión o aporten a la ya existente con funcionalidades nuevas.

c. **Presentar demostraciones o casos de uso que ilustren la utilidad y aplicabilidad del protocolo en contextos reales del Internet de las Cosas**. El desarrollo del manual de uso y los ejemplos mostrados en el Anexo [C](#manual-de-uso-y-ejemplo-simple) permitieron cumplir este objetivo, listando y demostrando el uso de las diferentes funcionalidades integradas en LoboMQ.

Adicionalmente, la lista de objetivos se ha desviado desde la original según se han progresado y descubierto nuevas oportunidades para mejorar el proyecto. Estas desviaciones se listan a continuación:

- **Proteger el uso de la solución mediante control de acceso.** Se ha logrado añadir una medida de seguridad a través de una lista blanca que lista los remitentes aceptados por el broker, evitando un posible robo de información o manipulación de mensajes.

- **Crear un mecanismo de recuperación de información tras un reinicio en el broker.** Los suscriptores y los temas se almacenan como objetos en la memoria de la placa, y además se ha añadido la posibilidad de almacenarse en la tarjeta micro SD en formato [JSON](#JSON). Cuando ocurre un reinicio en la placa, la información almacenada en la RAM es eliminada, pero con la persistencia es posible recuperar los suscriptores y temas que estaban en uso.

- **Permitir al usuario adaptar el protocolo a sus necesidades.** Se han parametrizado las funciones, más en concreto la de levantar el broker, para no forzar al usuario a utilizar todas las funcionalidades o utilizar únicamente las esenciales. Estos parámetros dan al usuario la capacidad de elección si su sistema necesita persistencia y control de acceso. Por otro lado, el usuario también puede decidir sobre el uso del logger o gestor de mensajes de registro y los tipo de mensajes que imprime y donde los imprime.

- **Mantener al usuario desarrollador informado y ofrecer la capacidad de adaptarse al estado de ejecución.** El ya mencionado logger es una funcionalidad importante en este caso, ya que establecerlo al nivel `DEBUG` permite observar los tamaños de mensajes intercambiados, en el caso de los nodos cliente, y la gestión de temas y mensajes en el caso de los nodos broker. Por otro lado, la implementación de códigos de error permite al desarrollador utilizar una función y controlar el resultado de esta para, por ejemplo, realizar determinadas acciones en caso de error.

- **Facilitar el acceso a la documentación de la librería.** El uso de Doxygen y GitHub Pages permite al usuario acceder a la documentación de la librería desde cualquier dispositivo, sin necesidad de utilizar el IDE ni revisar ficheros de código fuente manualmente.

## Presupuesto

Los costes del proyecto son estimados y listados en la Tabla \ref{conclusiones:presupuesto}, resultando en un total de 15.599,54 €. Es importante destacar que este total no refleja costes adicionales como la electricidad y el Internet. Por otro lado, la licencia de Visual Paradigm utilizada es de un mes, ya que esta herramienta se empleó en las fases finales del proyecto y no a lo largo del mismo. El salario del desarrollador se calcula en base al salario medio de un ingeniero de software en España, pero aplicado a tiempo parcial, debido a que no hubo un horario fijo para la realización del proyecto, variando entre 1 y 8 horas diarias.

| Concepto                               | Precio/unidad                      | Cantidad | Precio total    |
| -------------------------------------- | ---------------------------------: | :------: | --------------: |
| Ordenador Lenovo Ideapad 3 15ALC6      | 699,00 € @PcCompsLenovo            | 1        | 699,00 €        |
| Placa ESP32 DEVKIT V1                  | 8,00 € @ESP32_Precio               | 2        | 16,00 €         |
| Placa ESP32-2432S028R                  | 11,51 € @ESP32CYDAliexpress        | 1        | 11,51 €         |
| Placa de pruebas                       | 1,79 € @Protoboard_Precio          | 2        | 3,58 €          |
| 20 cables puente                       | 0,90 € @Cables_Precio              | 1        | 0,90 €          |
| Sensor DHT11                           | 1,99 € @DHT11_Precio               | 1        | 1,99 €          |
| Potenciómetro BQ Zum Kit               | 3,55 € @Pot_TiendaBQ               | 1        | 3,55€           |
| Módulo lector de tarjeta microSD       | 6,21 € @LectorSD_Precio            | 1        | 6,21 €          |
| Tarjeta microSD                        | 5,50 € @AmazonMicroSd              | 1        | 5,50 €          | 
| Licencia Windows 10                    | 145,00 € @LicenciaWindows          | 1        | 145,00 €        |
| Licencia Microsoft 365, 10 meses       | 7,00 €/mes @LicenciaM365           | 1        | 70,00 €         |
| Licencia Visual Paradigm, 1 mes        | 6,00 $/mes @LicenciaVisualParadigm | 1        | 5,50 €          |
| Licencia Smart Fields, 10 meses        | 4,99 $/mes @SmartFields_TrelloPU   | 1        | 45,80 €         |
| Salario desarrollador, 10 meses        | 1.458,50 € / mes @SueldoIso        | 1        | 14.585,00 €     |
| -------------------------------------- | ---------------------------------- | -------- | ----------------|
| **TOTAL**                              |                                    |          | **15.599,54 €** |

: Estimación de costes del proyecto\label{conclusiones:presupuesto}

## Competencias específicas de intensificación adquiridas y/o reforzadas

El desarrollo de este [TFG](#TFG) ha permitido adquirir, junto al resto de competencias del Grado en Ingeniería Informática, las competencias específicas de intensificación en Sistemas de Información, listadas y justificadas a continuación.

- **[SI1] Capacidad de integrar soluciones de Tecnologías de la Información y las Comunicaciones y procesos empresariales para satisfacer las necesidades de información de las organizaciones, permitiéndoles alcanzar sus objetivos de forma efectiva y eficiente, dándoles así ventajas competitivas.** El protocolo LoboMQ ofrece un método de comunicación indirecta entre microcontroladores comúnmente utilizados en IoT, posibilitando su uso en el ámbito empresarial para desarrollar soluciones que aprovechen el valor y las ventajas del IoT.
- **[SI2] Capacidad para determinar los requisitos de los sistemas de información y comunicación de una organización atendiendo a aspectos de seguridad y cumplimiento de la normativa y la legislación vigente.** El alumno y los tutores realizaron una recogida de requisitos para planificar la implementación de LoboMQ, incluyendo roles, mensajes y acciones a realizar en el proceso de comunicación. Durante esta recogida, se mencionó la conveniencia de implementar un mecanismo de seguridad mediante usuario y contraseña, encriptación y verificación de mensajes y control de acceso, ya que una vulnerabilidad podría resultar en la pérdida de información, manipulación de mensajes y caídas en el sistema. Debido al limitado tiempo de desarrollo, únicamente se implementó un control de acceso mediante whitelist.
- **[SI3] Capacidad para participar activamente en la especificación, diseño, implementación y mantenimiento de los sistemas de información y comunicación.** El proyecto ha implicado la ejecución de las fases comunes del desarrollo de software por parte del autor, distribuidas en varias etapas iterativas y cuyo éxito se refleja en el cumplimiento de los objetivos establecidos.
- **[SI4] Capacidad para comprender y aplicar los principios y prácticas de las organizaciones, de forma que puedan ejercer como enlace entre las comunidades técnica y de gestión de una organización y participar activamente en la formación de los usuarios.** Un principio muy activo durante el desarrollo de LoboMQ ha sido la comprensión del código de la librería, el cual abarca los comentarios, la documentación, la organización del código fuente y los ejemplos. Esto permite entender sus capacidades, limitaciones y funcionamiento, pudiendo así comprobar si es adecuado para implementarlo en un proyecto de una organización y formar a desarrolladores que conozcan la manera de implementarlo y adaptarlo a situaciones específicas.
- **[SI5] Capacidad para comprender y aplicar los principios de la evaluación de riesgos y aplicarlos correctamente en la elaboración y ejecución de planes de actuación.** En cuanto al desarrollo, la elección de Scrum como metodología de gestión de proyectos se justifica, entre otros motivos, por su capacidad de adaptación a requisitos cambiantes, como los que pueden surgir al encontrar fallos. Esto abre la posibilidad de crear parches rápidos o hotfixes en casos de errores críticos, o tareas para futuras iteraciones. En cambio, en LoboMQ se evaluó el riesgo de posibles reinicios de una placa broker durante su ejecución (debido a cortes de energía) y la pérdida de temas y suscriptores, que justificó la creación de un mecanismo de persistencia para almacenar y recuperar los temas y suscriptores en una tarjeta micro SD.
- **[SI6] Capacidad para comprender y aplicar los principios y las técnicas de gestión de la calidad y de la innovación tecnológica en las organizaciones.** El proyecto se ha realizado siguiendo buenas prácticas y estándares, como el uso de metodologías ágiles que permiten mantener una constante comunicación entre los miembros del equipo. Por otro lado, el código resultante ha experimentado un constante incremento de calidad siguiendo unos criterios establecidos para mejorar su uso y comprensión.

## Propuestas de trabajo a futuro

LoboMQ se encuentra en una versión base, pero con una amplia posibilidad de mejorar la comunicación, explotar las capacidades de las placas y, en general, potenciar las prestaciones del protocolo a través de un desarrollo más extenso. Algunas de estas posibilidades se presentan a continuación en forma de propuestas de mejora.

En primer lugar, debido a las tecnologías utilizadas por las placas ESP32 para este protocolo, existe la posibilidad de ampliar la compatibilidad con varios tipos de placas con similares características, como las ESP8266. Aunque estas placas disponen de un único núcleo y son relativamente antiguas, podría ser interesante implementar una versión de la librería para permitir la interoperabilidad entre distintos tipos de placas.

Un aspecto muy importante en la comunicación es la fiabilidad de la entrega, la cual puede ser mejorada implementando la calidad de servicio o [QoS](#QoS), una característica relevante de [MQTT](#MQTT). A su vez, el procesamiento de los mensajes podría mejorarse añadiendo una opción de persistencia de los mismos, permitiendo así reiniciar el broker sin perder ningún mensaje y entregarlos a las nuevas placas conectadas.

Otra mejora tomada de [MQTT](#MQTT) es la adición del mecanismo *Keep Alive*, que puede permitir tanto al broker como a los suscriptores comprobar la existencia de ambos cada cierto tiempo. Con este mecanismo, el broker puede beneficiarse en cuanto a rendimiento, ya que, si detecta que un suscriptor está desconectado, puede desuscribirlo, evitando así enviar mensajes que nunca llegarán.

El uso de una whitelist de direcciones [MAC](#MAC) que identifican un único dispositivo puede no resultar óptimo en redes con cambios frecuentes en su configuración. Por ello, se propone mejorar este aspecto mediante un mecanismo de autenticación con usuario y contraseña, permitiendo utilizar ambos para controlar el acceso. Asimismo, encriptar la comunicación puede asegurar los datos, y su implementación es posible utilizando las capacidades integradas en ESP-NOW o desarrollando un mecanismo propio de LoboMQ.

La capacidad de procesamiento de las placas ESP32 puede ser insuficiente en contextos donde la comunicación es constante y se realiza entre una gran cantidad de dispositivos. Añadir la posibilidad de distribuir un sistema que haga uso de LoboMQ puede beneficiar estos contextos, ya que al agregar el uso de varias placas broker se pueden distribuir las tareas (por ejemplo, una placa se encarga de la autenticación y la publicación, mientras que otra realiza las suscripciones) y los suscriptores, posibilitando superar la limitación de 20 dispositivos en redes ESP-NOW. Además, se podría designar un broker de respaldo o backup, manteniendo el sistema en continua operación incluso si un broker se detiene.

Finalmente, no se puede obviar la mejora de rendimiento. Todo software es susceptible de mejoras y este protocolo no es la excepción, especialmente cuando se utilizan placas de baja potencia. La implementación de funciones más eficientes y una adecuada gestión de la memoria son tareas esenciales para esta mejora.
