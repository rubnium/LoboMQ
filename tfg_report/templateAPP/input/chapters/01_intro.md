# Introducción 

En este primer capítulo se presenta el problema que se pretende resolver mediante el desarrollo del Trabajo de Fin de Grado ([TFG](#TFG)), explicando el alcance de la librería y el protocolo desarrollados, junto con la motivación y a los desafíos que han dado lugar.

A lo largo de este Trabajo de Fin de Grado se detalla el proceso de desarrollo de LoboMQ, un protocolo que se fija en [MQTT](#MQTT) para tomar las bases de la comunicación a través de colas de mensajes y adaptarlas a un entorno de trabajo con dispositivos del Internet de las Cosas. Este protocolo aprovecha las capacidades de ESP-NOW para ofrecer una comunicación sin cables ni Internet y a larga distancia, y es implementado en forma de una librería C++ para placas ESP32, la cual está disponible en el registro de PlatformIO. La librería LoboMQ ofrece al usuario las funciones necesarias para, con facilidad, desplegar un broker, publicar mensajes a un tema, y suscribirse y desuscribirse de los mismos.

## Motivación

Esta sección aborda la motivación del trabajo. Se trata de señalar la necesidad que lo origina, su actualidad y pertinencia. Puede incluir también un estado de la cuestión (o estado del arte) en la que se revisen estudios o desarrollos previos y en qué medida sirven de base al trabajo que se presenta.

En este capítulo debería introducirse el contexto disciplinar y tecnológico en el que se desarrolla el trabajo de modo que pueda entenderse con facilidad el ámbito y alcance del TFG. Puesto que un TFG no tiene que ser necesariamente un trabajo con aportes novedosos u originales, solo es necesario la inclusión de estado del arte cuando este contribuya a aclarar aspectos clave del TFG o se desee justificar la originalidad del trabajo realizado. Si la sección estado del arte es muy extensa, considera la opción de introducirla como un capítulo independiente.



Popular iot @IoTConexiones_Statista @IoTGasto_Statista
Popular esp32
Popular MQTT
Habitual despliegue en zonas sin comunicación, o puede que no haga falta
No hay protocolos de comunicación que usen ESP-NOw, es tarea del desarrollador preparar la comunicacion entre los nodos (tarea compleja)
Usar característica integrada en ESP32



{
	La proliferación del Internet de las Cosas (IoT) se evidencia en aplicaciones que abarcan desde elementos de uso diario hasta iniciativas de gran alcance. Esto demanda que los profesionales en el desarrollo soluciones IoT se enfrenten y adapten a distintas restricciones, ya sean ambientales o propias del dispositivo. Un desafío recurrente es la gestión de energía en las placas, ya que muchos dispositivos exigen un consumo reducido. Esta exigencia se magnifica cuando se requiere la transmisión de información entre diferentes placas con conexiones intermitentes, complicando considerablemente la labor del desarrollador.
Este proyecto tiene como objetivo el diseño e implementación de un protocolo de mensajería para redes ESP-NOW, inspirado en características fundamentales de MQTT, como su modelo de publicación y suscripción y su aptitud para manejar conexiones intermitentes. El resultado combinará la eficiencia en latencia y consumo energético de ESP-NOW con la flexibilidad de MQTT. Además, se desarrollarán bibliotecas de software para facilitar la integración de este protocolo en aplicaciones IoT. Esta propuesta no solo sería una valiosa contribución a la comunidad de IoT, combinando lo mejor de dos protocolos existentes, sino también un desafío ingenieril significativo.

}

## Desafíos durante la realización

El desarrollo de la solución implica abordar una serie de desafíos, descritos a continuación.

El uso de placas ESP32 requiere de conocimientos específicos para maximizar el rendimiento y la eficiencia durante la ejecución. FreeRTOS es fundamental en este contexto, ya que comprender su uso y los conceptos que lo sustentan permiten una correcta ejecución paralela de múltiples tareas en esta placa, limitada por su capacidad de procesamiento. A su vez, requiere conocimientos del lenguaje C++ y de las herramientas para desarrollar código capaz de usar y liberar adecuadamente la memoria durante la ejecución. Por otro lado, la tecnología de comunicación utilizada, ESP-NOW, presenta sus propias limitaciones, como la cantidad de pares conectados simultáneamente y el tamaño máximo de los mensajes, las cuales deben ser consideradas al utilizarla.

Este nuevo protocolo, al basarse en el ya existente [MQTT](#MQTT), requiere un conocimiento profundo de su funcionamiento. Esto incluye el formato y los tipos de mensajes, las comprobaciones que se realizan al enviar mensajes, y el orden de ejecución y procesamiento, entre otros aspectos. Sin embargo, esto no limita la herramienta a ser una réplica fiel, ya que se deben diseñar componentes y funcionalidades del protocolo con suficiente libertad creativa, pero manteniendo una operación similar a [MQTT](#MQTT).

PlatformIO, a parte de permitir el desarrollo en las mencionadas placas, ofrece una serie de plantillas y comandos esenciales para desarrollar una librería. Esto implica realizar una lectura exhaustiva de la documentación de esta plataforma, junto con diversas pruebas, para disponer de una librería funcional.

## Estructura del Documento

/*TODO: redactar*/

## Objetivos

/*TODO: redactar*/
Para hacer un planteamiento apropiado de los objetivos se recomienda utilizar la Guía para la elaboración de propuestas de TFG en la que se explica cómo definir correctamente los objetivos de un TFG.

### Objetivo General

/*TODO: redactar*/

Introduce y motiva la problemática (i.e ¿cuál es el problema que se plantea y por qué es interesante su resolución?).

Debe concretar y exponer detalladamente el problema a resolver, el entorno de trabajo, la situación y qué se pretende obtener. También puede contemplar las limitaciones y condicionantes a considerar para la resolución del problema (lenguaje de construcción, equipo físico, equipo lógico de base o de apoyo, etc.). Si se considera necesario, esta sección puede titularse Objetivos del TFG e hipótesis de trabajo. En este caso, se añadirán las hipótesis de trabajo que el/la estudiante pretende demostrar con su TFG.

Una de las tareas más complicadas al proponer un TFG es plantear su Objetivo. La dificultad deriva de la falta de consenso respecto de lo que se entiende por objetivo en un trabajo de esta naturaleza.

En primer lugar, se debe distinguir entre dos tipos de objetivo:

- La finalidad específica del TFG que se plantea para resolver una problemática concreta aplicando los métodos y herramientas adquiridos durante la formación académica. Por ejemplo, Desarrollo de una aplicación software para gestionar reservas hoteleras on-line.

- El propósito académico que la realización de un TFG tiene en la formación de un graduado. Por ejemplo, la adquisición de competencias específicas de la intensificación cursada.

En el ámbito de la memoria del TFG se tiene que definir el primer tipo de objetivo, mientras que el segundo tipo es el que se añade en el Capítulo de Conclusiones y que justifica las competencias específicas de la intensificación alcanzadas y/o reforzadas con la realización del trabajo.

La categoría del objetivo planteado justifica modificaciones en la organización genérica de la memoria del trabajo. Así en el caso de estudios y validación de hipótesis el apartado de resultados y conclusiones debería incluir los resultados de experimentación y los comentarios de cómo dichos resultados validan o refutan la hipótesis planteada.

{
	Diseñar e implementar en forma de librerías un protocolo de mensajería publicador-subscriptor confiable, inspirado en MQTT, mediante el uso del protocolo de comunicación inalámbrica ESP-NOW.
}

### Objetivos Específicos

/*TODO: redactar*/

Generalmente, el objetivo general puede ser descompuesto en varios objetivos más específicos que se pretenden alcanzar. En esta sección se enumeran y describen cada uno de ellos.

Junto con la definición de estos objetivos se puede especificar los requisitos que debe satisfacer la solución aportada. Estos requisitos especifican características que debe poseer la solución y restricciones que acotan su alcance. En el caso de un trabajo cuyo objetivo es el desarrollo de un artefacto los requisitos pueden ser funcionales y no funcionales.

Al redactar el objetivo de un TFG se debe evitar confundir los medios con el fin. Así es habitual encontrarse con objetivos definidos en términos de las acciones (verbos) o tareas que será preciso realizar para llegar al verdadero objetivo. Sin embargo, a la hora de planificar el desarrollo del trabajo si es apropiado descomponer todo el trabajo en hitos y estos en tareas para facilitar dicha planificación.

La categoría del objetivo planteado justifica modificaciones en la organización genérica de la memoria del trabajo. Así en el caso de estudios y validación de hipótesis el apartado de resultados y conclusiones debería incluir los resultados de experimentación y los comentarios de cómo dichos resultados validan o refutan la hipótesis planteada.

{
	1.	Diseñar un protocolo de mensajería para redes ESP-NOW que incorpore características de publicación y suscripción similares a MQTT.
2.	Implementar librerías software que permitan a los desarrolladores integrar fácilmente el protocolo propuesto en sus aplicaciones de IoT.
3.	Presentar demostraciones o casos de uso que ilustren la utilidad y aplicabilidad del protocolo en contextos reales de IoT.
4.	Comparar el rendimiento y eficiencia del protocolo propuesto con otros protocolos existentes en términos de latencia, consumo energético y confiabilidad.
}
