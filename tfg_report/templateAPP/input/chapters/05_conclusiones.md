# Conclusiones

En este capítulo se debe incluir el juicio crítico y discusión sobre los resultados obtenidos. Si es pertinente deberá incluir información sobre trabajos derivados como publicaciones o ponencias, así como trabajos futuros, solo si estos están planificados en el momento en que se redacta el texto. Incluirá obligatoriamente la justificación de las competencias de la tecnología específica cursada por el estudiante que se han adquirido durante el desarrollo del TFG

## Revisión de los Objetivos

En esta sección se deberá revisar en qué grado se han completado los objetivos fijados al principio del proyecto. Se deberá también indicar las posibles desviaciones de los objetivos fijados, así como de la planificación, y tratar de justificar tales desviaciones.

## Presupuesto

Si el TFG consiste en el desarrollo e implementación de un prototipo, la memoria debe incluir el coste del prototipo considerando tanto el hardware como los recursos humanos necesarios para su desarrollo.

Cuando se tiene en cuenta la puesta en marcha de un proyecto de ingeniería, la planificación y presupuesto que se realizan de modo previo a su ejecución son críticos para gestionar los recursos que permitan alcanzar los objetivos de calidad, temporales y económicos previstos para el proyecto. Es muy importante que todas las justificaciones aportadas se sustenten no solo en juicios de valor sino en evidencias tangibles como: historiales de actividad, repositorios de código y documentación, porciones de código, trazas de ejecución, capturas de pantalla, demos, etc.

## Competencias Específicas de Intensificación Adquiridas y/o Reforzadas

Se deberán listar aquellas competencias de la intensificación que hayan sido adquiridas y/o reforzadas con el desarrollo de este TFG, incluyendo su justificación.

## Propuestas de trabajo a futuro

LoboMQ se encuentra en una versión base, pero con una amplia posibilidad de mejorar la comunicación, explotar las capacidades de las placas y, en general, potenciar las prestaciones del protocolo a través de un desarrollo más extenso. Algunas de estas posibilidades se presentan a continuación en forma de propuestas de mejora.

En primer lugar, debido a las tecnologías utilizadas por las placas ESP32 para este protocolo, existe la posibilidad de ampliar la compatibilidad con varios tipos de placas con similares características, como las ESP8266. Aunque estas placas disponen de un único núcleo y son relativamente antiguas, podría ser interesante implementar una versión de la librería para permitir la interoperabilidad entre distintos tipos de placas.

Un aspecto muy importante en la comunicación es la fiabilidad de la entrega, la cual puede ser mejorada implementando la calidad de servicio o [QoS](#QoS), una característica relevante de [MQTT](#MQTT). A su vez, el procesamiento de los mensajes podría mejorarse añadiendo una opción de persistencia de los mismos, permitiendo así reiniciar el broker sin perder ningún mensaje y entregarlos a las nuevas placas conectadas.

Otra mejora tomada de [MQTT](#MQTT) es la adición del mecanismo *Keep Alive*, que puede permitir tanto al broker como a los suscriptores comprobar la existencia de ambos cada cierto tiempo. Con este mecanismo, el broker puede beneficiarse en cuanto a rendimiento, ya que, si detecta que un suscriptor está desconectado, puede desuscribirlo, evitando así enviar mensajes que nunca llegarán.

El uso de una whitelist de direcciones [MAC](#MAC) que identifican un único dispositivo puede no resultar óptimo en redes con cambios frecuentes en su configuración. Por ello, se propone mejorar este aspecto mediante un mecanismo de autenticación con usuario y contraseña, permitiendo utilizar ambos para controlar el acceso. Asimismo, encriptar la comunicación puede asegurar los datos, y su implementación es posible utilizando las capacidades integradas en ESP-NOW o desarrollando un mecanismo propio de LoboMQ.

La capacidad de procesamiento de las placas ESP32 puede ser insuficiente en contextos donde la comunicación es constante y se realiza entre una gran cantidad de dispositivos. Añadir la posibilidad de distribuir un sistema que haga uso de LoboMQ puede beneficiar estos contextos, ya que al agregar el uso de varias placas broker se pueden distribuir las tareas (por ejemplo, una placa se encarga de la autenticación y la publicación, mientras que otra realiza las suscripciones) y los suscriptores, posibilitando superar la limitación de 20 dispositivos en redes ESP-NOW. Además, se podría designar un broker de respaldo o backup, manteniendo el sistema en continua operación incluso si un broker se detiene.

Finalmente, no se puede obviar la mejora de rendimiento. Todo software es susceptible de mejoras y este protocolo no es la excepción, especialmente cuando se utilizan placas de baja potencia. La implementación de funciones más eficientes y una adecuada gestión de la memoria son tareas esenciales para esta mejora.
