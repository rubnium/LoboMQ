# Estado del arte

En este capítulo se aborda el concepto de Internet de las Cosas, incluyendo su valor, los desafíos que presenta y los tipos de dispositivos que lo conforman. Sumado a esto, se comparan los distintos protocolos, middleware y tecnologías empleados en el transporte de datos en este ámbito, y se menciona la popular placa ESP32, ampliamente utilizada en el Internet de las Cosas.

## Internet de las Cosas

El siglo XX dio lugar al desarrollo de numerosos inventos que impulsaron una revolución y un avance ágil en la sociedad, que en la actualidad son frecuentemente usados y facilitan la vida humana. Este es el caso del Internet, que desde 1969 ha permitido la comunicación entre personas y el acceso a información. Hoy en día, también millones de objetos están conectados a la red, cuyas funcionalidades dependen de esta @Linkedin_OrigenIoT.

Internet de las Cosas o Internet of Things ([IoT](#IoT)) es un término utilizado por primera vez en un discurso realizado en septiembre de 1985 @IoT_Swifttalk, cuando Peter T. Lewis predijo que "no sólo los humanos, sino también las máquinas y otras cosas se comunicarán interactivamente a través de Internet"(@Podcast_Lewis); también empleado por Kevin Ashton en 1999 al realizar una presentación del uso de etiquetas de identificación por radiofrecuencia, o radio frequency identification ([RFID](#RFID)) en inglés, y otros sensores en los productos de la cadena de suministro @IoT_Ashton_Avast @IoT_Swifttalk @Linkedin_OrigenIoT @Itop_IoT @IoT_at3w @KevinAshton_Eexcellence @IoT_Wiki. Sin embargo, es esencial tener una clara comprensión del significado del [IoT](#IoT), en mayor parte por la confusión inherente al término en sí y por las aplicaciones cotidianas de esta tecnología.

A primera vista, "Internet de las Cosas" podría dar la impresión de ser un término moderno para referirse a "conectar a Internet algo para controlarlo", una definición bastante simple para alguien que por ejemplo controla las luces de su hogar desde su teléfono móvil. Es tanta la confusión que no existe una definición formal única, sino que se pueden encontrar una disparidad de definiciones que no todos los sistemas [IoT](#IoT) cumplen @IoTDefs_InfoMatters. En 2012, la Unión Internacional de Telecomunicaciones ([ITU](#ITU)) recomendó definir el [IoT](#IoT) como una infraestructura global que permite ofrecer servicios avanzados a todo tipo de aplicaciones conectando objetos entre sí e interoperando tecnologías de la información y comunicación, aprovechando capacidades de identificación, obtención de datos, procesamiento y comunicación y cumpliendo con requisitos de seguridad y privacidad @IoTDef_ITU. Sin embargo, por lo general, podemos entender que el [IoT](#IoT) trata de dotar de capacidades de comunicación además de procesamiento, captura y/o análisis de datos a distintos tipos de entes, como dispositivos físicos, objetos, edificaciones, terrenos, sistemas, hardware, software, e incluso contextos y situaciones, ya sea añadiéndoles dispositivos o integrando ciertas capacidades en los propios objetos. Estos entes pueden estar compuestos de sensores, que recopilan datos, o actuadores, que controlan otros objetos, y a través de redes, privadas o públicas, pueden intercambiar información con otros dispositivos, recopilar la información en un mismo dispositivo y transferir órdenes @IoTDef_Nougir @IoTDefs_InfoMatters @IoTDef_ITU @IoT_IHS @IoT_VideoClase @IoT_Rama @IoT_Bankinter @IoT_Swifttalk @Itop_IoT @IoT_at3w @IoT_RH @IoT_Wiki @IoT_Survey.

### Ventajas y usos

Hoy en día vivimos en un mundo conectado, en el cual estamos rodeados de numerosos dispositivos, gran parte de ellos interconectados como sistemas, ya que la información es crucial para la sociedad. Por ejemplo, a nivel empresarial es la que permite crear nuevas posibilidades, modelos, interacciones y soluciones únicas, entender y anticiparse a tendencias e identificar nuevas oportunidades. Esta información se obtiene a partir del procesamiento y análisis de colecciones de datos, recopilados de diversas fuentes potenciales, como es el caso de los sistemas [IoT](#IoT) @IoT_VentDesv_Tokio @IoT_VentDesv_Krypton @IoTDef_Nougir @IoT_Survey.

Gracias al [IoT](#IoT) es posible monitorear los procesos que ocurren en un negocio para controlar y optimizar los recursos utilizados, ya sean energéticos o de personal humano; además de encontrar tareas manuales o repetitivas que pueden ser automatizadas mediante el propio [IoT](#IoT), mejorando así la eficiencia, el tiempo y la productividad. Asimismo, permite la toma de decisiones informadas a partir de datos de negocio, tanto internos como externos, que permitan agregar valor al negocio de manera más rápida, y la mejora de experiencia y de calidad de vida de los usuarios o clientes basándose en los datos recibidos sobre estos @IoT_IBM @IoT_Wiki @IoT_CdU_Ubi @IoT_VentDesv_Tokio @IoT_VentDesv_Krypton @IoTDef_Nougir @IoT_Survey.

En adición, tiene la capacidad de implementarse de diferentes maneras en una gran variedad de entornos y sectores, tales como:

- Sanidad: monitorizar signos vitales, hacer recomendaciones de salud adecuadas, comprobar autenticidad y dosis recomendadas en medicamentos @IoT_IBM @IoT_Wiki @IoT_CdU_Ubi @IoTDef_Nougir @IoT_VideoClase @IoT_Survey.
- Agricultura y ganadería: controlar las condiciones del suelo y el crecimiento de los cultivos, localizar el ganado, controlar la calidad de la leche recolectada en un tanque @IoT_IBM @IoT_Wiki @IoT_CdU_Ubi @IoT_VideoClase @IoT_Survey.
- Transporte, conducción y logística: frenado automático de emergencia, cálculo de rutas óptimas, búsqueda de aparcamiento, mantener condiciones óptimas de remolques que transporten productos perecederos @IoT_IBM @IoT_Wiki @IoT_CdU_Ubi @IoTDef_Nougir @IoT_VideoClase @IoT_Survey.
- Fabricación: controlar temperatura y humedad de centros de fabricación, identificar áreas con necesidad de personal, crear controles de calidad a productos @IoT_IBM @IoT_Wiki @IoT_CdU_Ubi @IoT_VideoClase @IoT_Survey.
- Comercio: identificar posición óptima de los productos en las estanterías, guiar a clientes hasta determinados productos, trazabilidad en el producto desde la llegada en el almacén hasta su venta @IoT_IBM @IoT_VentDesv_Krypton @IoT_VideoClase @IoT_Survey.
- Ciudades y edificios inteligentes: mejor vigilancia y actuación por los equipos de emergencia, localizar áreas de contaminación, automatizar iluminación y calefacción @IoT_CdU_Ubi @IoT_VentDesv_Tokio @IoTDef_Nougir @IoT_VideoClase @IoT_Survey.

El [IoT](#IoT) no solo se reduce a estos sectores, es prácticamente aplicable a todos, como la educación, la construcción o el turismo, y a cualquier fase, desde el diseño hasta ofrecer y consumir el servicio o producto, gracias a la popularización de esta tecnología y al aumento de dispositivos que aparecen a nuestro alrededor @IoT_VideoClase @IoT_Survey.

### Factores, limitaciones y desafíos a tener en cuenta

Al desarrollar una arquitectura del [IoT](#IoT), es necesario tener en cuenta una serie de factores que afectan tanto a los dispositivos como a la comunicación entre ellos.

La primera consideración se refiere a los datos, el artefacto más importante en estos sistemas. Deben ser adecuados y el personal debe estar preparado para tratarlos y analizarlos. Sin embargo, debido a la gran cantidad de datos producidos, se presenta un reto significativo al analizarlos y extraer información, especialmente en casos de falta de herramientas o experiencia en análisis @IoT_IBM @IoT_VideoClase @Neurona_IoT @IoTDesf_Deing @Incibe_IoT.

Dependiendo del dispositivo, el uso que se le da y el entorno donde se instala, puede verse limitado por varios factores energéticos y físicos interdependientes, tales como la manera de alimentarlo, el consumo (coste de la energía y tiempo de uso), el rango de movilidad, el peso y el tamaño. Dar preferencia a un factor puede perjudicar a otro, por lo que es necesario buscar un equilibrio que satisfaga todas las necesidades o priorizar algunas sobre otras y aplicar cambios en las propias necesidades @IoT_VentDesv_Krypton @IoT_VideoClase @Redeweb_IoT @Neurona_IoT.

Las condiciones ambientales (como la lluvia, la humedad, las vibraciones y la temperatura), la disponibilidad de conexión en una zona (cobertura de red o electrificación), las interferencias electromagnéticas y otros factores del área donde se despliega el sistema pueden provocar un replanteamiento de ciertas partes. Por ejemplo, éstas pueden implicar la fiabilidad en el transporte de los datos mediante mecanismos de acuses de recibo y verificación de mensajes, o la frecuencia de transmisión y tamaño de los datos @IoT_CdU_Ubi @IoT_VentDesv_Tokio @Neurona_IoT @IoTDesf_Deing.

Debido a la heterogeneidad de los dispositivos en cuanto a fabricantes, características y capacidades, y a la falta de un estándar internacional de compatibilidad para dispositivos en [IoT](#IoT), es necesario dedicar un esfuerzo a identificar las tecnologías de comunicación compatibles (y que cumplan las necesidades de velocidad y alcance), configurar los dispositivos y usar dispositivos adicionales si es necesario @IoT_IBM @IoT_Wiki @IoT_CdU_Ubi @IoT_VentDesv_Krypton @IoT_VideoClase @IoTDesf_Deing.

Es importante además adaptar el despliegue al uso que se le vaya a dar, como puede ser tener una topología de conexión y comunicación adecuada según los dispositivos que interactúen, prepararlo para una futura escalabilidad, habilitar la gestión remota de los dispositivos para actualizarlos, reconfigurarlos, localizarlos o desconectarlos, y realizar una correcta recolección de los datos @IoT_CdU_Ubi @IoT_VentDesv_Krypton @Neurona_IoT @IoTDesf_Deing @Chakray_IoTArq.

Como consideración final, los datos transmitidos pueden contener cierto grado de sensibilidad, por lo que es preferible mantener una buena ciberseguridad y respetar la privacidad de los datos implementando medidas que aseguren la confidencialidad, la integridad y la disponibilidad, siendo importante conocer las regulaciones de la zona en la que opera el sistema [IoT](#IoT) para poder cumplirlas @IoT_IBM @IoT_CdU_Ubi @IoT_VentDesv_Tokio @IoT_VentDesv_Krypton @IoT_VideoClase @IoT_IHS @IoTDesf_Deing @Incibe_IoT.

### Primeros ejemplos de IoT

El primer dispositivo [IoT](#IoT) conocido fue una máquina de Coca-Cola conectada a [ARPANET](#ARPANET) a principios de la década de los 80 en la Universidad Carnegie Mellon de Pittsburgh, Pensilvania @IoT_VideoClase @IoT_Wiki. Esta máquina era mantenida por los usuarios de la universidad y tenía cierta popularidad que hacía que normalmente estuviera vacía o recién cargada con botellas calientes, lo que molestaba al departamento de Ciencias de la Computación. Para resolver este problema, instalaron microinterruptores en la máquina para detectar las botellas que había en cada ranura, los conectaron al ordenador Programmed Data Processor model 10 (PDP-10) del departamento y diseñaron un programa para registrar la hora cada vez que ocurría una transacción en cada ranura, así como otro programa para recibir información de la máquina. Utilizando el último programa desde la red del departamento, se podía consultar si había botellas en las ranuras, cuánto tiempo había transcurrido desde que se recargó con una nueva botella o si estaba fría @IoT_at3w @Coke_Home @Coke_History.

Más tarde, hicieron público el acceso a esta información, haciendo que cualquier persona conectada a [ARPANET](#ARPANET) en cualquier parte del mundo podía consultar el estado de la máquina de Coca-Cola durante más de una década utilizando el comando `finger coke@cmua`, hasta que la máquina fue reemplazada por ser incompatible con el nuevo diseño de las botellas de Coca-Cola @Coke_History.

Posteriormente, conectado a un Internet más similar al actual, apareció XCoffee o la cafetera de la Sala Trojan. En noviembre de 1991, Quentin Stafford-Fraser y Paul Jardetzky trabajaban junto a sus compañeros investigadores agrupados en el antiguo laboratorio de informática, también llamado Sala Trojan, de la Universidad de Cambridge, mientras que el resto de compañeros estaban dispersos por la universidad. Todos compartían un problema en común: una única máquina de café de goteo-filtro a la salida del laboratorio, cuya jarra estaba vacía o contenía café con un sabor horrible a excepción de cuando estaba recién hecho, siendo esta última opción solo para aquellos que se sentaban cerca. Para solucionar este problema, Stafford-Fraser y Jardetzky idearon el sistema XCoffee, y el Dr. Martyn Johnson y Daniel Gordon lo mejoraron. Fijaron una cámara apuntando a la jarra de la cafetera, la conectaron a una capturadora de fotogramas del ordenador Acorn Archimedes del rack de la sala y crearon un software para que cada vez que el servidor recibía una solicitud HTTP a través de la World Wide Web devolvía una página web con la imagen de la cafetera capturada más reciente. Desde el navegador se podía comprobar si valía la pena ir a por café (en el caso de estar en el mismo edificio que la cafetera), y esto convertía al sistema en la primera webcam de la historia, otorgándole una fama internacional. Estuvo operativa su última versión desde el 22 de noviembre de 1993 hasta el 22 de agosto de 2001 a las 09:54 UTC, cuando mostró su última imagen pocos segundos antes de su apagado debido a su difícil mantenimiento y al traslado de las instalaciones del laboratorio @Info_Trojan @Bio_Trojan @Switchoff_Trojan @Coffee_Video @BBC_Trojan @Coffee_Museum @HoI_Trojan @Trojan_Wiki @Quentin_Trojan.

Actualmente, la máquina de café se encuentra restaurada y expuesta en el museo de informática Heinz Nixdorf MuseumsForum de Paderborn, Alemania @Coffee_Museum @Trojan_Wiki.

### Tipos de dispositivos y redes

Como se ha mencionado anteriormente, el [IoT](#IoT) se basa en la transmisión de datos entre dispositivos. Estos datos pueden ser información recibida del entorno u órdenes de actuación, que salen o llegan a un dispositivo ubicado en un extremo de la red de conexión y que tiene conectado uno o ambos de los siguientes tipos de objetos @IoTBook @IoT_IBM:

- Sensores: miden una propiedad física y la representan digitalmente, siendo útiles para detectar cambios en el entorno.
- Actuadores: dispositivos que interpretan una señal eléctrica y desencadenan un efecto físico tras interpretarla, siendo útiles para producir cambios en el entorno.

Todos estos dispositivos suelen ser heterogéneos y están interconectados en una red que permite detectar, medir y actuar en relación con el entorno. Esta red, con el fin de ser efectiva y tolerante a fallos, debe pasar por un análisis de criterios como la topología de conexión entre los dispositivos, la distancia entre estos y cómo se procesan los datos @IoTBook @IoT_IBM.

Una red [IoT](#IoT), puede dividirse en capas según cómo se procesen los datos @IoTBook @EdgeCloudFog_ISA @EdgeCloudFog_Industria40:

- Computación en la nube o *cloud*: los datos se procesan en un servidor central remoto, lejos de su origen. Requiere una conexión a Internet para su acceso, lo cual implica lidiar con la latencia de la red y el uso del ancho de banda. Ofrece una gran capacidad de procesamiento, almacenamiento y análisis, adecuada para aquellas aplicaciones que no requieren respuestas rápidas. Puede agrupar y procesar los datos de todo un sistema.
- Computación en la niebla o *fog*: los datos se procesan cerca de donde se originan, en nodos *fog* de la red local. Estos nodos evitan el uso de Internet para enviar datos a la nube, mejorando la eficiencia y ofreciendo una respuesta más rápida que la computación *cloud*. Se pueden distribuir varios nodos *fog* para jerarquizar la red, agrupando y procesando datos de ciertos nodos.
- Computación en el borde o *edge*: los datos se procesan en los nodos donde se originan. Ofrece un procesamiento en tiempo real sin necesidad de comunicarse con otros dispositivos, liberando el uso de ancho de banda.

## Middleware y protocolos de mensajería usados en [IoT](#IoT)

El uso más común de [IoT](#IoT) es desplegar una arquitectura compuesta por varios dispositivos [IoT](#IoT). En mayor parte, estos dispositivos se designarán simplemente como dispositivos [IoT](#IoT), ya sean sensores o actuadores, que emiten o reciben datos. Adicionalmente, habrá unos pocos dispositivos (al menos uno) con el rol de centro de mensajería, que actuarán como intermediarios encargados de retransmitir los datos a los dispositivos correspondientes.

Tras escoger una tecnología para conectar los dispositivos entre sí, en el desarrollo de aplicaciones [IoT](#IoT) se requiere un protocolo de mensajería para intercambiar esos grandes volúmenes de datos que tratan. Un protocolo de comunicación permite que los dispositivos se comuniquen y transmitan mensajes entre los dispositivos [IoT](#IoT) y el centro de mensajería. Además, proporciona cierta fiabilidad a la comunicación, ya que permite que los mensajes lleguen y sus datos sean entendidos y procesados correctamente @Webby_IoTProts @A3logics_IoTProts.

La elección del protocolo se basa en cómo se adecua al escenario en el que se quiere implementar, considerando requisitos a tener en cuenta como la ubicación, las limitaciones físicas, el consumo y el coste. Por lo general, no cualquier protocolo de comunicación es apropiado @TechTarget_IoTProts. Los protocolos que se mencionan en este apartado se adecuan a la mayoría de escenarios [IoT](#IoT) debido a su rapidez y su fácil implementación, y es posible escoger aquel que se adapte mejor a los requisitos @Build_IoTProts @A3logics_IoTProts.

### Message Queue Telemetry Transport ([MQTT](#MQTT))

El protocolo [MQTT](#MQTT) es uno de los más populares en el ámbito del [IoT](#IoT). Diseñado para ser ligero y adecuado para redes con ancho de banda limitado y dispositivos con pocos recursos, este estándar del comité técnico [OASIS](#OASIS) permite el transporte bidireccional de mensajes con datos entre múltiples dispositivos @MQTT_Goto @MQTT_Emqx @MQTT_Wiki @Build_IoTProts.

[MQTT](#MQTT) utiliza el patrón de comunicación publicación-suscripción. En este patrón, los publicadores categorizan los mensajes, y los suscriptores recibirán mensajes de las categorías de su interés, a diferencia de la comunicación directa en la que los participantes se envían los mensajes directamente. En el caso de [MQTT](#MQTT), el patrón está basado en temas o *topics*, siendo posible que los suscriptores se interesen por uno o varios @MQTT_Goto @MQTT_Emqx @MQTT_Wiki @PubSub_Wiki.

En una red [MQTT](#MQTT), se definen dos roles principales: el broker o intermediario de mensajes y los clientes. El broker [MQTT](#MQTT) es un servidor comparable a una oficina de correos, que recibe todos los mensajes publicados por los clientes y los dirige a los clientes de destino apropiados. Por otra parte, un cliente es cualquier dispositivo conectado al broker a través de una red, y puede producir y recibir datos al publicar y suscribirse respectivamente. Este mecanismo es útil para compartir datos, controlar y gestionar dispositivos. El enrutamiento de mensajes realizado por el broker proporciona transparencia de localización y desacoplamiento en el espacio, ya que el publicador no necesita conocer las direcciones de los suscriptores y los suscriptores no necesitan conocer al publicador, ambos interactúan únicamente con el broker @MQTT_Goto @MQTT_Dzone @MQTT_Wiki.

Los mensajes están organizados en una jerarquía de temas o *topics*. Al publicar un mensaje, se publica en un tema específico, y en el caso de querer publicar en varios se deben realizar varias publicaciones. En cambio, un suscriptor puede suscribirse a un tema específico o a varios simultáneamente y recibirá una copia de todos los mensajes compatibles con los temas suscritos @MQTT_Goto @MQTT_Dzone @MQTT_Wiki. La manera de indicar varios temas es mediante el uso de los siguientes caracteres comodín @MQTT_Goto @MQTT_Dzone:

- Comodín de un nivel '+': coincide con un nivel de tema y puede utilizarse más de una vez en la especificación del tema.
- Comodín de varios niveles '#': coincide con cualquier número de niveles y debe ser el último carácter en la especificación del tema.

Por ejemplo, cuando se publica un mensaje en el tema "`edificioA/sensor1/temperatura`", el broker enviará una copia del mensaje los clientes suscritos a los temas "`edificioA/sensor1/temperatura`", "`edificioA/+/temperatura`" y "`edificioA/#`", pero no a un cliente suscrito a "`edificioB`" o a "`edificioA/+/humedad`".

La transmisión de mensajes se realiza de forma asíncrona, sin detener la ejecución de ambos componentes a la hora de publicar o recibir, y se puede realizar una comunicación uno a muchos (un publicador y varios suscriptores), muchos a uno (varios publicadores y un suscriptor), uno a uno (un publicador y un suscriptor, menos común) y muchos a muchos (varios publicadores y varios suscriptores) @MQTT_Goto @A3logics_IoTProts.

En el caso de que el broker reciba una publicación de un tema en el cual no hay nadie suscrito, el broker por defecto descarta el mensaje. Es posible activar la retención de mensajes configurando un campo en el mensaje para evitar esto, consiguiendo así que el broker almacene el último mensaje retenido de cada tema y lo distribuya inmediatamente a cualquier nuevo cliente suscrito, sin necesidad de que publicadores y suscriptores estén conectados simultáneamente @MQTT_Goto @MQTT_Dzone.

El protocolo soporta un mecanismo de limpieza de sesión. Por defecto, un cliente tras desconectarse y volverse a conectar no recibe los mensajes publicados durante su desconexión y el broker olvida las suscripciones del mismo cliente. Pero al desactivar dicho mecanismo, el broker mantiene tanto las relaciones de suscripción como los mensajes offline, enviándolos al cliente al momento de reconectarse, lo cual es útil para dispositivos que se conectan y desconectan constantemente, común en redes [IoT](#IoT). Además, [MQTT](#MQTT) enfrenta la inestabilidad de la red con un mecanismo *Keep Alive* que, al transcurrir un prolongado periodo sin interacción, ocurre un ping entre el cliente y el broker para evitar la desconexión. Si el ping falla y se identifica el cliente como desconectado, aplicará un mecanismo *Last Will*, que publica un último mensaje a un tema específico debido a una desconexión anormal, en el caso de estar configurado @MQTT_Goto @MQTT_Dzone @MQTT_Emqx.

El diseño de [MQTT](#MQTT) se basa en la simplicidad y en minimizar el ancho de banda, dejando la interpretación del contenido del mensaje en manos del desarrollador. Los mensajes transmitidos a través de la red tienen la posibilidad de configurar el [QoS](#QoS) o calidad de servicio por cada tema, asociados con distintas garantías de entrega. Aunque [MQTT](#MQTT) funciona sobre [TCP](#TCP), el cual tiene su propia garantía de entrega, históricamente los niveles [QoS](#QoS) eran necesarios para evitar la pérdida de datos en redes antiguas y poco fiables, una preocupación válida para las redes móviles actuales @MQTT_Goto @MQTT_Dzone @MQTT_Emqx.

La transmisión de datos se estructura en un formato con tamaño reducido y en 14 tipos de mensajes diferentes, utilizados para establecer y cerrar una conexión con el broker, comprobar si la conexión sigue viva, publicar mensajes, y suscribirse y desuscribirse a temas. Se realiza principalmente sobre la capa TCP/IP, pero existe la posibilidad de operar encima de otros protocolos de red que ofrezcan conexiones ordenadas, sin pérdidas y bidireccionales. Por defecto, las credenciales de conexión y los mensajes se envían en texto plano sin medidas de seguridad, pero admite utilizar conexiones [TLS](#TLS)/[SSL](#SSL) protegidas por certificado, nombre de usuario y contraseña para cifrar y proteger la información transferida contra la intercepción, modificación o falsificación. Además, un broker [MQTT](#MQTT) tiene soporte para conectar dispositivos [IoT](#IoT) a escala masiva, un factor tenido en cuenta durante su diseño y que resulta en una alta capacidad de concurrencia, rendimiento y escalabilidad, características deseables en una red [IoT](#IoT). Implementaciones como EMQX[^protocolosIoT:emqx] y HiveMQ[^protocolosIoT:hiveMq] han alcanzado hitos notables, con 100 y 200 millones de conexiones respectivamente, y un pico de 1 millón de mensajes gestionados por segundo @MQTT_Emqx @HiveMQ_200mil. A esto se le puede sumar la capacidad de implementar múltiples brokers, para así compartir la carga de clientes y tratar la redundancia y la copia de seguridad de los mensajes en caso de fallo @MQTT_Emqx @MQTT_Goto @MQTT_Dzone.

[^protocolosIoT:emqx]: <https://www.emqx.com/en>
[^protocolosIoT:hiveMq]: <https://www.hivemq.com/>

### Advanced Message Queuing Protocol ([AMQP](#AMQP))

[AMQP](#AMQP) es un protocolo binario avanzado que opera sobre la capa de aplicación, cuyo estándar abierto permite desarrollar patrones de comunicación entre dispositivos. Facilita la comunicación entre servicios definiendo el formato de los datos enviados a través de la red, así como la creación de mensajes, el encolamiento y enrutamiento de los mensajes producidos, y la manera de entregarlos a los consumidores. Este protocolo se basa en el concepto de publicar y consumir de colas de mensajes a través de una conexión fiable, persistente y orientada al envío de flujos de datos. Permite hacer uso de estas colas de mensajes mediante distintos tipos de comunicación, como la entrega directa punto a punto y el modelo publicación-suscripción, haciendo su uso adecuado para el [IoT](#IoT) pese a no ser diseñado originalmente para usarse en este ámbito @AMQP_Wiki @AMQP_Goto @AMQP_Emqx @Build_IoTProts @A3logics_IoTProts.

En [AMQP](#AMQP) se definen las dos siguientes entidades principales que interactúan entre sí @AMQP_Goto @AMQP_Wiki:

- Cliente: del tipo suscriptor o publicador (o consumidor y productor, respectivamente), se conecta a un broker a través de credenciales y, en caso de estar autorizado, puede recibir o publicar mensajes.
- Broker: servidor de mensajería al que los clientes se conectan y que se encarga de distribuir los mensajes. Internamente, posee *exchanges* o intercambiadores, donde se conectan los productores de mensajes, y colas, vinculadas a los exchanges dependiendo de varios criterios y a las que se conectan los consumidores para extraer los mensajes producidos.

De manera sencilla, se puede resumir el funcionamiento de este protocolo como un modelo en el que los mensajes son publicados y enviados a exchanges, los cuales enrutan los mensajes a las colas apropiadas según reglas o bindings que dependen del exchange y la clave de enrutamiento o *routing key*, y los consumidores reciben los mensajes a través de las mismas colas. Tanto publicadores como consumidores están desacoplados en tiempo y espacio, desconociendo ambos su existencia y ubicación. Al funcionamiento de la transmisión se le puede asociar la analogía del funcionamiento del envío de emails, ya que estos se envían a direcciones "routing key@exchange", siendo la clave de enrutamiento la dirección de correo y el exchange el servidor. En [AMQP](#AMQP) existen cuatro tipos de exchanges: topic (permite una comunicación publicación-suscripción según clave y exchange), direct (permite una comunicación punto a punto), fanout (permite una comunicación similar a broadcast) y headers (permite una comunicación publicación-suscripción según cabeceras) @AMQP_Wiki @AMQP_Goto @AMQP_Emqx.

Las colas son fragmentos de memoria creados por el cliente suscriptor identificadas unívocamente mediante un nombre, definido previamente por el cliente o automáticamente por el broker. Intrínsicamente, [AMQP](#AMQP) garantiza la recepción y procesamiento de mensajes, ya que dispone de un mecanismo de [ACK](#ACK) o acuse de recibo que permite confirmar la recepción y procesamiento del mensaje. En el caso de no recibir el [ACK](#ACK) de un mensaje por parte de un consumidor, por ejemplo, porque perdió la conexión o no se procesó correctamente, el broker encola de nuevo el mensaje para reintentar la entrega. Además, las colas admiten persistencia, para mantener la existencia de la cola incluso luego de que ocurra un reinicio en el broker @AMQP_Goto.

Tras crear el exchange y la cola, se indica al broker la vinculación de ambas mediante un binding, especificando una clave de enrutamiento que, según el tipo de exchange, enruta adecuadamente las colas. El exchange entregará como máximo una copia de mensaje a una cola si corresponden las propiedades del mensaje con las propiedades del binding. Con los bindings es posible vincular varias colas a un mismo exchange, al igual que una cola a varios exchanges @AMQP_Goto @AMQP_Emqx.

[AMQP](#AMQP) hace uso de la capa [TCP](#TCP) para la transmisión de mensajes y es extenso en cuanto a funciones. Ofrece interoperabilidad independientemente del lenguaje o del proveedor, cifrado de extremo a extremo, múltiples propiedades de mensajes y modos de entrega, fiabilidad en la entrega, persistencia de mensajes, enrutamiento basado en criterios, capacidad de escalabilidad y definición de topologías, entre otras características. Sin embargo, pese a su idoneidad para sistemas distribuidos, es un protocolo que conlleva un alto consumo de recursos @AMQP_Emqx @AMQP_Wiki @AMQP_Goto @Webby_IoTProts @A3logics_IoTProts.

### Extensible Messaging and Presence Protocol ([XMPP](#XMPP))

Otra manera de comunicar varios dispositivos [IoT](#IoT) es utilizar el [XMPP](#XMPP), anteriormente conocido como Jabber. Este protocolo se basa en la transmisión de datos estructurados en formato [XML](#XML) dentro de una red de arquitectura cliente-servidor, en la cual los dispositivos están identificados por un Jabber ID, cuyo formato es similar al de una dirección de correo electrónico (por ejemplo, "abc@example.com"). En esta red, el cliente establece una conexión TCP/IP con el servidor. Posteriormente, el cliente se autentica con el servidor, y tras una autenticación exitosa, se habilita la posibilidad de enviar y recibir mensajes @A3logics_IoTProts @XMPP_Wiki @XMPP_PubNub.

Una característica notable de [XMPP](#XMPP) es que cualquiera puede tener su propio servidor [XMPP](#XMPP), no restringiendo a los usuarios a conectarse únicamente con otros usuarios en el mismo servidor central. Al ser un protocolo abierto formalizado por la Internet Engineering Task Force ([IETF](#IETF))[^protocolosIoT:ietf], los desarrolladores disponen de un protocolo bien documentado y fiable, de este modo, es posible interoperar entre diferentes implementaciones de [XMPP](#XMPP) a través de Internet, independientemente del proveedor. En el caso de querer comunicarse con otro servidor, ambos servidores [XMPP](#XMPP) intercambian la información necesaria, habilitando un modelo federado @XMPP_Wiki @XMPP_PubNub.

[^protocolosIoT:ietf]: <https://www.ietf.org/>

Este protocolo está diseñado para ofrecer mensajería instantánea o casi en tiempo real a través de la red, sin importar la distancia entre los dispositivos, uno de los problemas más comunes en [IoT](#IoT) @Build_IoTProts. Además, permite obtener información sobre los usuarios conectados y mantener una lista de contactos para cada usuario. [XMPP](#XMPP) también es extensible, permitiendo a los desarrolladores añadir características y funcionalidades personalizadas, adaptando el protocolo a necesidades específicas de aplicaciones, como la transmisión de señales [VoIP](#VoIP), video, ficheros, chat grupal, conferencias multiusuario, suscripción de presencia y comunicación publicación-suscripción para recibir actualizaciones sobre temas específicos de interés @XMPP_Wiki @XMPP_PubNub.

En los mensajes [XMPP](#XMPP) se utilizan estructuras [XML](#XML) denominadas *stanzas* para transportar datos. Existen 3 tipos principales de stanzas: de mensaje (para enviar mensajes entre clientes), de presencia (para conocer el estado y la disponibilidad de un cliente) y de info/query (para hacer consultas al servidor) @XMPP_Blazeclan.

El protocolo [XMPP](#XMPP) es altamente escalable debido a su capacidad de manejar multitud de conexiones y mensajes simultáneos. Además, al ser descentralizado, permite implementar fácilmente más servidores para gestionar el aumento de usuarios y altos picos de uso. En cuanto a seguridad, [XMPP](#XMPP) es compatible con cifrado de extremo a extremo mediante [TLS](#TLS) o [SSL](#SSL), garantizando así la confidencialidad de los mensajes. Por último, cuenta con una amplia comunidad de usuarios, diversas implementaciones y guías que facilitan a los desarrolladores la creación de aplicaciones que integren este protocolo @XMPP_Wiki @XMPP_PubNub.

### Data Distribution Service ([DDS](#DDS))

[DDS](#DDS) es un estándar de middleware y [API](#API) máquina-máquina que facilita la comunicación y el intercambio de datos. Fue desarrollado por el Object Management Group con el fin de responder a las necesidades específicas de aplicaciones que requieren intercambios de datos fiables y de alto rendimiento en sistemas distribuidos en tiempo real, sin dejar de lado la eficiencia. Su arquitectura se basa en un modelo de publicación-suscripción sin servidor, ya que los dispositivos se conectan entre sí, y donde los datos son publicados en un dominio y los suscriptores se conectan a este para recibir la información que les interesa @DDS_Standard @Webby_IoTProts @TechTarget_IoTProts @Build_IoTProts.

Este middleware abstrae la comunicación entre el sistema operativo y las aplicaciones, y facilita la comunicación entre componentes de un sistema, gestionando automáticamente el formato de los mensajes, el protocolo de transporte a usar, la fiabilidad, la calidad de servicio y la seguridad, y simplificando así el desarrollo. [DDS](#DDS) se centra completamente en los datos, asegurando un buen transporte e incluyendo información contextual de los mismos, lo que lo hace ideal para el [IoT](#IoT) aplicado en entornos industriales @DDS_Standard @DDS_UTPL @TechTarget_IoTProts.

[DDS](#DDS) funciona con el concepto de espacio de datos global, un almacén de datos que a ojos del programador parece una memoria local accedida mediante [API](#API)s. Sin embargo, este espacio es solo una ilusión, ya que no existe un lugar donde residan todos los datos, se refiere a una colección de distintos almacenes locales en cada nodo por los cuales se reparten los datos. Aunque este espacio global es tan característico, no se pierde compatibilidad, ya que el middleware es independiente del lenguaje de programación y la plataforma, posibilitando la interoperabilidad entre distintos sistemas y aplicaciones y una implementación que se adapte a las necesidades sin afectar a las comunicaciones entre dispositivos. Tampoco pierde efectividad, ya que su velocidad, baja latencia, baja sobrecarga en la comunicación, optimización del transporte y capacidad de transmitir millones de mensajes a multitud de receptores instantáneamente, lo convierten en una tecnología ideal para sistemas de alto rendimiento en tiempo real @DDS_Standard @DDS_UTPL.

Al ser descentralizado y no requerir un nodo central, el servicio [DDS](#DDS) es mucho más eficiente y eficaz, ya que los mensajes no deben atravesar un dispositivo intermediario, ejecutando la comunicación punto a punto, y resultando en una mayor velocidad. Además, dispone de un servicio de descubrimiento dinámico de puntos finales, haciendo que las aplicaciones [DDS](#DDS) sean extensibles y escalables @DDS_Standard @DDS_UTPL.

[DDS](#DDS) soporta principalmente el modelo de publicación-suscripción, intercambiando información basada en temas con componentes suscritos. Al suscribirse, es posible especificar filtros de tiempo y subconjuntos de datos para obtener solo los requeridos, y tiene la capacidad de detectar cambios para que los suscriptores reciban actualizaciones adecuadas de los datos. También ofrece compatibilidad con RPC o llamadas a procedimientos remotos @DDS_Standard @DDS_UTPL.

El middleware es independiente del transporte, y puede funcionar sobre [UDP](#UDP), [TCP](#TCP) y memoria compartida, entre otros. Entre las características opcionales que ofrece, como el filtrado de grandes datos, se encuentra la gestión de calidad de servicio o [QoS](#QoS), donde se pueden especificar requisitos de rendimiento y confiabilidad, como la latencia, el ancho de banda, la prioridad, la disponibilidad de los datos, el uso de recursos y la sincronización. Además, incluye mecanismos de seguridad que proporcionan autenticación, encriptación, confidencialidad, control de acceso e integridad en la distribución de información @DDS_Standard.

### Constrained Application Control ([CoAP](#CoAP))

[CoAP](#CoAP) es un protocolo de la capa de aplicación que permite a dispositivos con recursos limitados, como los que se encuentran en una red [IoT](#IoT), comunicarse entre sí @Build_IoTProts. Funciona en un marco cliente-servidor, en el cual el cliente realiza una solicitud a un punto de comunicación del dispositivo servidor, y este responde, permitiendo la interoperabilidad entre los dispositivos uno a uno @rfc7252 @A3logics_IoTProts @CoAPIntro @CoAP_EMQX.

Este protocolo opera sobre el protocolo de transporte [UDP](#UDP) @TechTarget_IoTProts, que, a diferencia de [TCP](#TCP), no requiere que los dispositivos establezcan una conexión de datos previa al envío de datos. Esto trae tanto consecuencias positivas como negativas. La consecuencia negativa radica en la poca fiabilidad en la comunicación, ya que el protocolo [UDP](#UDP) no garantiza la entrega de los mensajes, sino que esta garantía se gestiona desde la implementación de [CoAP](#CoAP). Es posible establecer garantía de entrega mediante acuses de recibo ([ACK](#ACK)) y tiempos de espera. La consecuencia positiva del uso de [UDP](#UDP) es la posibilidad de funcionar en redes con pérdidas o inestables, adecuado para sistemas [IoT](#IoT), ya que suelen operar en entornos de red difíciles, y la rapidez en la comunicación, pues no requiere una conexión de datos previa, enviando directamente el mensaje @CoAPIntro @CoAP_EMQX.

Esta comunicación utiliza una arquitectura [REST](#REST)ful, en la cual los datos y las funcionalidades se consideran recursos a los que se accede mediante métodos [HTTP](#HTTP) estándar, permitiendo una interoperabilidad sencilla entre distintos tipos de dispositivos y facilitando a los desarrolladores el uso del protocolo. No es necesario que los recursos de la red sean conocidos por el dispositivo que vaya a utilizarlos, ya que [CoAP](#CoAP) implementa un mecanismo de descubrimiento integrado a través de un núcleo en la red, útil en redes [IoT](#IoT) en las que los dispositivos constantemente se conectan y desconectan. Además, el intercambio de mensajes entre dispositivos es asíncrono, lo que significa que un dispositivo puede enviar una solicitud a otro y continuar ejecutando otras tareas mientras que la respuesta puede recibirla en cualquier momento @CoAPIntro @CoAP_EMQX.

[CoAP](#CoAP) se basa en el intercambio de mensajes compactos codificados en un formato binario simple, cuyo tamaño no debe superar el necesario para encapsularlos dentro de un datagrama [IP](#IP). Los distintos tipos de mensajes son: confirmables (CON, para enviar mensajes fiables), no confirmables (NON, para enviar mensajes con menos fiabilidad), de acuse de recibo (ACK) y de reinicio (RST, para indicar que el receptor no puede procesar una solicitud) @CoAPIntro @CoAP_EMQX @rfc7252.

Además es un protocolo diseñado para utilizar un bajo consumo de recursos en la transferencia, y permite hacer uso del protocolo de seguridad de la capa de transporte (Data Transport Layer Security, [DTLS](#DTLS)) para aumentar la seguridad, además de extender su implementación con funcionalidades adicionales. Por el contrario, es menos maduro que sus alternativas, resultando en una menor cantidad de recursos, guías y herramientas, además de una compatibilidad reducida con otros dispositivos [IoT](#IoT) @A3logics_IoTProts @CoAPIntro @CoAP_EMQX.

### Comparación de middleware y protocolos

A partir de la información de los apartados anteriores, se pueden recopilar las diferencias y similitudes en los siguientes puntos:

1. *[MQTT](#MQTT)*:
   - **Descripción corta:** Basado en colas de mensajes y topics.
   - **Patrón de comunicación:** Publicación-suscripción.
   - **Necesita intermediario:** Sí, el broker.
   - **Protocolo de transporte:** [TCP](#TCP).
   - **Ventajas:** Muy utilizado, ligero, eficiente, útil en dispositivos y redes de recursos limitados, soporta distintas calidades de servicio @Webby_IoTProts @A3logics_IoTProts.
   - **Desventajas:** Encriptación y enrutación limitadas, bajo soporte para tipos de datos complejos @Webby_IoTProts @A3logics_IoTProts.
   - **Casos de uso:** Telemetría, mensajería ligera, automatización industrial, monitorización del entorno, hogares inteligentes, soluciones energéticas @MQTT_Dzone @Webby_IoTProts.

2. *[AMQP](#AMQP)*:
   - **Descripción corta:** Basado en colas de mensajes y exchanges.
   - **Patrón de comunicación:** Publicación-suscripción, directa o fanout.
   - **Necesita intermediario:** Sí, el broker.
   - **Protocolo de transporte:** [TCP](#TCP).
   - **Ventajas:** Alto rendimiento, seguro, ampliamente usado, parecido a [MQTT](#MQTT) @Webby_IoTProts @A3logics_IoTProts.
   - **Desventajas:** Alto consumo de recursos, difícil aprendizaje @A3logics_IoTProts.
   - **Casos de uso:** Servicios financieros, procesamiento de transacciones, envío de datos en tiempo real, comunicación segura entre entidades @A3logics_IoTProts.

3. *[XMPP](#XMPP)*:
   - **Descripción corta:** Comunicación de datos y presencia mediante mensajes [XML](#XML).
   - **Patrón de comunicación:** Cliente-servidor.
   - **Necesita intermediario:** Sí, el servidor XMPP.
   - **Protocolo de transporte:** [TCP](#TCP).
   - **Ventajas:** Robusto, extensible, muy ampliable de funciones @A3logics_IoTProts @Webby_IoTProts.
   - **Desventajas:** No optimizado para entornos limitados, complejo de implementar @Webby_IoTProts.
   - **Casos de uso:** Mensajería instantánea, redes sociales, plataformas de colaboración @Webby_IoTProts.

4. *[DDS](#DDS)*:
   - **Descripción corta:** Comunicación sin servidor.
   - **Patrón de comunicación:** Publicación-suscripción.
   - **Necesita intermediario:** No.
   - **Protocolo de transporte:** [TCP](#TCP) y [UDP](#UDP), compatible con otros.
   - **Ventajas:** Alto rendimiento, fácil de escalar, comunicación centrada en datos en tiempo real, soporte de tipos de datos complejos, configurable la calidad de servicio @Webby_IoTProts.
   - **Desventajas:** Complejo de implementar, altos recursos de dispositivos y de ancho de banda @Webby_IoTProts.
   - **Casos de uso:** Sistemas de tiempo real, aplicaciones de misión crítica, automatización industrial, automoción, gestión de cadenas de suministro, sistemas distribuidos de gran escala @Webby_IoTProts.

5. *[CoAP](#CoAP)*:
   - **Descripción corta:** Basada en recursos compartidos y accesibles mediante [REST](#REST).
   - **Patrón de comunicación:** Cliente-servidor.
   - **Necesita intermediario:** No.
   - **Protocolo de transporte:** [UDP](#UDP).
   - **Ventajas:** Eficiente en redes y dispositivos de recursos limitados, soporte nativo para tecnologías web @Webby_IoTProts @TechTarget_IoTProts.
   - **Desventajas:** Bajo soporte de clientes concurrentes.
   - **Casos de uso:** Dispositivos de recursos limitados, automatización en hogares @Webby_IoTProts.

## Espressif y sus dispositivos

Espressif Systems[^espressif:espressifSystems] es una multinacional de semiconductores fundada en 2008, que opera como líder mundial en el ámbito del [IoT](#IoT) y está comprometida a proporcionar a millones de usuarios algunos de los mejores dispositivos y plataformas de software de la industria, junto con una variedad de soluciones [IoT](#IoT) seguras, robustas, eficientes, versátiles, asequibles y orientadas al código abierto. Los productos de Espressif se utilizan ampliamente en dispositivos de electrónica de consumo, y es conocido por sus populares series de chips, módulos y placas de desarrollo ESP8266 y ESP32, los cuales se analizarán en los siguientes apartados @AboutEspressif @EurotronixEspressif @DigikeyEspressif.

[^espressif:espressifSystems]: <https://www.espressif.com/>

### ESP8266

El ESP8266 es un [SoC](#SoC) o sistema en un chip diseñado para dispositivos móviles, electrónica portátil y aplicaciones del [IoT](#IoT). Lanzado en agosto de 2014, integra un procesador mononúcleo Tensilica L106 con una arquitectura *Reduced Instruction Set Computer* ([RISC](#RISC)) de 32 bits de bajo consumo y una velocidad de reloj de entre 80 y 160 [MHz](#MHz). Presenta una arquitectura para el ahorro de energía, permitiendo establecer el chip en modo activo, reposo y reposo profundo, útil para conservar la batería en dispositivos que hagan uso de esta. En cuanto a memoria, no dispone de una memoria flash para almacenar programas, la cual debe ser proporcionada por el módulo que implemente este chip y puede tener un tamaño máximo de 16 [MiB](#MiB). Integra una [RAM](#RAM) para instrucciones de 32 [KiB](#KiB), una caché de instrucciones 32 [KiB](#KiB), 80 [KiB](#KiB) para almacenar datos del usuario y 16 [KiB](#KiB) para datos del sistema de [ETS](#ETS). Su bajo voltaje operativo oscila entre 2,5 y 3,6 [V](#V), con una corriente de operación alrededor de los 80 [mA](#mA). Cuenta con la capacidad de funcionar en entornos industriales gracias a su amplio rango de temperatura de operación, que va de -40 a 125 [ºC](#ºC) @ESP8266_Espressif @ESP8266_Datasheet @ProgFacil_ESP8266 @ESP8266_Llamas @ESP8266_Wiki.

Admite distintos tipos de protocolos de comunicación, como [IP](#IP)v4, [TCP](#TCP), [UDP](#UDP) y [HTTP](#HTTP). Es un dispositivo certificado para funcionar por Wi-Fi y compatible con los protocolos 802.11 b/g/n en una frecuencia de 2,4 [GHz](#GHz). Tiene la capacidad de actuar como cliente en redes protegidas por claves [WEP](#WEP), [WPA](#WPA) y [WPA](#WPA)2, además de poder actuar como punto de acceso inalámbrico. También integra en sus dimensiones compactas 16 pines [GPIO](#GPIO) para conectar dispositivos de entrada y salida, un conversor analógico de 10 bits, conmutadores de antena, un amplificador de potencia y de recepción, un balun de radiofrecuencia y módulos de gestión de potencia @ESP8266_Datasheet @ProgFacil_ESP8266 @ESP8266_Llamas @ESP8266_Wiki.

Este sistema admite varios [IDE](#IDE)s y lenguajes de programación, como C y C++, utilizando Arduino [IDE](#IDE)[^espressif:arduinoIde] o PlatformIO; MicroPython[^espressif:micropython], utilizando Mu Editor, Thonny [IDE](#IDE) o Pymakr @ESP_Micropython; y Lua[^espressif:lua], utilizando LuaLoader @ESP_Lua @ESP8266_Llamas.

[^espressif:arduinoIde]: <https://www.arduino.cc/en/software>
[^espressif:micropython]: <https://micropython.org/>
[^espressif:lua]: <https://www.lua.org/>

### ESP32

El ESP32 es el [SoC](#SoC) sucesor del ESP8266. Igual de apto para electrónica portátil e [IoT](#IoT), comparte muchas características y añade mejoras que lo convierten en un sistema muy superior. Integra un procesador Tensilica Xtensa LX6 de doble núcleo (o de uno, dependiendo de la variante utilizada) cuya frecuencia de reloj oscila entre los 160 y 240 [MHz](#MHz), que trabaja en conjunto con un coprocesador de ultra baja energía. La memoria experimenta un significativo aumento respecto a su predecesor, con un total de 520 [KiB](#KiB) de SRAM, 448 [KiB](#KiB) de memoria de solo lectura, 32 [KiB](#KiB) de caché y hasta 4 [MiB](#MiB) de memoria de almacenamiento (dependiendo del modelo) @ESP32_Datasheet @ESP32_Llamas @ESP32_Wiki.

Este chip, lanzado en septiembre de 2016, añade en comparación con el ESP8266 una mejora de potencia, soporte de Bluetooth 4.2 y [BLE](#BLE), sensor de temperatura, sensor hall, sensor táctil, reloj de tiempo real, más pines [GPIO](#GPIO) (hasta 34) y varios modos de energía. Además, incorpora arranque seguro, encriptado de la flash y soporte de aceleración por hardware para los algoritmos y protocolos de cifrado y encriptación [AES](#AES), [SHA](#SHA)-2, [RSA](#RSA), [ECC](#ECC) y el generador de números aleatorios @ESP32_Datasheet @ESP32_Llamas @ESP32_Wiki. El ESP32 tiene la posibilidad de funcionar como un sistema autónomo o como parte de un puente e interconexiones, y es capaz de interactuar con otros sistemas para proveer funcionalidad Wi-Fi y Bluetooth a través de sus interfaces @ESP32_Espressif.

Desde el lanzamiento del ESP32 original, han ido apareciendo variantes con distintas capacidades y procesadores, como el S3 con Bluetooth 5, el C6 con Thread, Zigbee y Matter, y el más reciente C5 con Wi-Fi 6, pero gran parte del código del ESP32 es compatible entre estas @ESP32Versions @ESP32_Wiki.

## ESP-NOW

El [IoT](#IoT) se forma a partir de la conectividad entre objetos, donde surge la necesidad de un protocolo que equilibre las necesidades de latencia, uso de energía, capacidad de transmisión, confiabilidad y seguridad en la transmisión de datos. Son factores determinantes en el futuro desarrollo de esta tecnología, y aparecen como candidatos un gran número de tecnologías y protocolos, destinados tanto para la comunicación en área local, como Wi-Fi, para áreas amplias, como LoRa y LoRaWAN, y para transmisión a corta distancia, como [RFID](#RFID). Recientemente, al mencionado grupo se ha añadido ESP-NOW, el cual, pese a sus limitaciones, tiene características notables y es adecuado para [IoT](#IoT).

ESP-NOW es un protocolo de comunicación inalámbrica diseñado por Espressif para su uso entre sus dispositivos, como los ESP8266 y ESP32. Con el objetivo de sustituir a Wi-Fi y a otras tecnologías, es capaz de realizar transmisiones de información y control rápidas, estables y con un bajo consumo de recursos de [CPU](#CPU) y memoria flash entre dispositivos inteligentes, sin necesidad de un enrutador @ESPNOW_Espressif @ESPNOW_FAQ.

Se caracteriza por la rapidez de la transmisión, lograda evitando la necesidad de establecer una conexión previa entre dispositivos. Permite a su vez poner a disposición los dispositivos para transmitir datos y recibir órdenes instantáneamente tras el encendido. Además, este protocolo está basado en la capa de enlace de datos y es capaz de omitir las capas de red, transporte, sesión, presentación y aplicación del modelo [OSI](#OSI), reduciendo el consumo de energía (mejorando la autonomía en dispositivos con batería) y el retardo en la recepción y en el procesamiento de mensajes debido a la nula necesidad de cabeceras de paquete o desempaquetadores de cada capa. En redes congestionadas, es una característica beneficiosa, ya que brinda la capacidad de respuestas rápidas que reducen el retraso causado por la pérdida de paquetes. En el modelo utilizado en ESP-NOW en comparación con el modelo [OSI](#OSI) estándar de la Figura \ref{espnow:modeloOsiEspNow} se puede observar la ausencia de las 5 capas mencionadas anteriormente @ESPNOW_Espressif @ESPNOW_Emariete.

![Comparación de las capas del modelo OSI con las del modelo ESP-NOW (Fuente: @ESPNOW_Espressif)\label{espnow:modeloOsiEspNow}](espnow_osi_model.png){width=92%}

Pese al objetivo de ESP-NOW de reemplazar Wi-Fi, en los dispositivos de Espressif es capaz de coexistir simultáneamente junto a Wi-Fi y Bluetooth. Esto es útil para utilizar un dispositivo como gateway y exportar los datos intercambiados entre ESP-NOW hacia otras redes @ESPNOW_Espressif @ESPNOW_FAQ.

Tiene la capacidad de transmitir datos de manera máquina a máquina o broadcast, y para establecer la comunicación solo se requiere la dirección [MAC](#MAC) del dispositivo de destino y establecer un canal de transmisión. No obstante, dispone de una cantidad limitada de dispositivos con los que se puede emparejar. En general, el número de dispotivos emparejados no puede exceder de 20, y la cantidad de estos con los que se puede establecer una comunicación cifrada es configurable. Por defecto, este valor es 7, y admite un valor máximo de 17. Esta limitación puede ser un inconveniente en caso de necesitar una gran cantidad de dispositivos interconectados, pero una solución sería formar jerarquías de dispositivos @ESPNOW_FAQ @ESPNOW_Emariete.

ESP-NOW utiliza tramas de entre 43 y 293 bytes en las que se encapsulan y transmiten datos de una longitud máxima de 250 bytes, con un alcance de transmisión de entre 100 y 500 metros según las condiciones atmosféricas, y con una tasa de velocidad de bits de 1 megabit por segundo. Esto es beneficioso para la comunicación a larga distancia debido a su gran alcance en dispositivos al aire libre o incluso separados por paredes o pisos. Sin embargo, su uso puede estar limitado por la pequeña carga útil que puede transmitir, por lo que en otros casos podría ser mejor utilizar otras tecnologías como Wi-Fi @ESPNOW_FAQ @ESPNOW_Docs @ESPNOW_Emariete.

Este protocolo permite establecer funciones de callback que serán llamadas instantáneamente tras el envío y la recepción de datos para poder gestionarlos adecuadamente. Cabe remarcar que el protocolo no garantiza que se reciban los datos correctamente, pero es posible establecer [ACK](#ACK)s para confirmar la correcta recepción y procesamiento de los datos, además de números de secuencia para afrontar la duplicidad. También existe la posibilidad de asegurar la transmisión de datos utilizando algoritmos de encriptación [ECDH](#ECDH) y [AES](#AES) y el método CBC-MAC Protocol (CCMP) que protegen las tramas de acción. Esto está limitado a comunicaciónes entre pares, no se admite el cifrado de tramas utilizadas para la multidifusión @ESPNOW_Docs @ESPNOW_FAQ.

En cuanto a la gestión de dispositivos, puede utilizarse como un protocolo que ayude al aprovisionamiento de datos y configuraciones a dispositivos, depurarlos y actualizar su firmware @ESPNOW_Espressif @ESPNOW_Emariete.

ESP-NOW no necesita ningún procedimiento especial aparte de la implementación para poder utilizarse con fines comerciales. En la actualidad, se encuentra ampliamente utilizado en electrodomésticos inteligentes, iluminación inteligente, control remoto, sensores y otros @ESPNOW_FAQ @ESPNOW_Emariete.

### Tecnologías alternativas más comunes

#### Wi-Fi

"Wi-Fi" es el nombre que otorga la Wi-Fi Alliance a esta tecnología de red inalámbrica basado en los estándares [IEEE](#IEEE) 802.11. Esta tecnología es ampliamente utilizada para enlazar dispositivos en redes [LAN](#LAN) y proveer de acceso a Internet utilizando ondas de radio de 2,4 o 5 [GHz](#GHz) (dependiendo de la versión) para transmitir la información, cumpliendo con la misión de ser una alternativa al envío de datos a través de cables @Wifi_WikiEn @Wifi_AZone @Wifi_Proofpoint @Wifi_WikiEs.

En una red Wi-Fi se pueden encontrar una variedad de dispositivos cliente, que son los que aprovechan las características de la red, y dispositivos que distribuyen la red. Estos últimos consisten en routers o enrutadores, que brindan la conexión a Internet a los dispositivos y enrutan los mensajes enviados a través de la red; puntos de acceso, que transmiten la señal inalámbrica y es donde se conectan los dispositivos introduciendo las credenciales de la red; y repetidores, utilizados para extender el área de cobertura de una red. Entre los dispositivos, tanto clientes como los distribuidores de red, se utilizan adaptadores de red inalámbrica, que convierten los datos en una señal de radio y viceversa @Wifi_AZone @Wifi_WikiEs.

Es una de las tecnologías más utilizadas a nivel mundial, siendo que la mayoría de hogares y establecimientos disponen de una red Wi-Fi. Esta popularidad es beneficiosa para el [IoT](#IoT), ya que ofrece una capa de compatibilidad con una amplia gama de dispositivos sin necesidad de antenas, adaptadores de red ni otro tipo de hardware adicional. Además, Wi-Fi no es una tecnología nueva, tiene un sólido legado de interoperabilidad, y permite enviar información entre dispositivos con baja latencia @Wifi_Official @Wifi_AZone @Wifi_WikiEn.

Entre sus características adicionales se encuentra la topología flexible, que permite conectar los dispositivos de distintas maneras; la seguridad, ya que es posible tener redes protegidas con contraseñas cifradas mediante distintos protocolos ([WEP](#WEP), [WPA](#WPA) y [WPA](#WPA)2), el bajo coste de instalación, que en comparación con la instalación de una red cableada, resulta más económico; y la capacidad de llegar a donde los cables no pueden llegar @Wifi_Official @Wifi_AZone.

Existen distintos estándares de Wi-Fi que definen cómo actúa la red, y que cada pocos años mejoran el alcance, la velocidad y la conectividad. Por lo general, los dispositivos certificados para un estándar son intercomunicables con los certificados para otro estándar Wi-Fi siempre que compartan la misma banda de frecuencia, por lo que no es una preocupación tener todos los dispositivos con la versión más reciente @Wifi_Official @Wifi_AZone @Wifi_WikiEn. Los estándares Wi-Fi se muestran en la Tabla \ref{espnow:estandaresWiFi}.

| Nombre comercial | Estándar [IEEE](#IEEE) | Año  | Frecuencia ([GHz](#GHz)) | Velocidad máxima  | Rango (metros)   |
|------------------|------------------------|------|--------------------------|-------------------|------------------|
| Wi-Fi 1          | 802.11a                | 1999 | 5                        | 54 [Mbps](#Mbps)  | 120              |
| Wi-Fi 2          | 802.11b                | 1999 | 2,4                      | 11 [Mbps](#Mbps)  | 140              |
| Wi-Fi 3          | 802.11g                | 2003 | 2,4                      | 54 [Mbps](#Mbps)  | 140              |
| Wi-Fi 4          | 802.11n                | 2009 | 2,4 y 5                  | 450 [Mbps](#Mbps) | 250              |
| Wi-Fi 5          | 802.11ac               | 2014 | 5                        | 2,3 [Gbps](#Gbps) | 35               |
| WiGig            | 802.11ad               | 2016 | 60                       | 7 [Gbps](#Gbps)   | 100              |
| Wi-Fi 6          | 802.11ax               | 2019 | 2,4, 5 y 6               | 9,6 [Gbps](#Gbps) | 240              |
| Wi-Fi 7          | 802.11be               | 2024 | 2,4, 5 y 6               | 46 [Gbps](#Gbps)  | (Por determinar) |

: Lista de estándares Wi-Fi (Fuentes: @WifiComparison_Intel @WifiComparison_Monolitic @WifiComparison_Makeuseof @WifiComparison_Netspot @WifiComparison_Xataka @WifiComparison_Geckoandfly @WifiComparison_Business)\label{espnow:estandaresWiFi}

La popularidad de Wi-Fi abarca una gran variedad de dispositivos soportados, como teléfonos inteligentes, ordenadores, televisores inteligentes, impresoras e incluso placas de desarrollo como ESP8266 y ESP32.

#### Bluetooth

Bluetooth es un estándar de tecnología que facilita el intercambio de datos entre dispositivos a través de distancias cortas @Bluetooth_Official @Bluetooth_Wiki. Desde su introducción en 1998, ha pasado por múltiples revisiones, siendo las más relevantes las de la última década @Bluetooth_Wiki @Bluetooth_Xataka:

- Versión 4.0 hasta 4.2: velocidad de transferencia de datos de 24 Mbps y alcance de hasta 100 metros, añadiendo soporte para el protocolo IPv6. Además, introdujo BLE o Bluetooth Low Energy, una nueva variante de esta tecnología.
- Versión 5.0 hasta 5.2: velocidad de transferencia de datos a 50 Mbps, alcance de hasta 200 metros, y realizó mejoras en la transmisión de audio y en el consumo de energía.

Bluetooth Low Energy fue diseñado para operaciones de bajo consumo de energía, capaz de soportar diferentes tipologías de comunicación (punto a punto, difusión y malla), a diferencia del clásico que solo admite punto a punto. Mientras que el Bluetooth clásico se usa para transferir datos y sonido, BLE es capaz de utilizarse para analizar con alta precisión la presencia, distancia y dirección del dispositivo @Bluetooth_Official @Bluetooth_Wiki.

Bluetooth utiliza ondas de radio UHF en las bandas ISM sin licencia de 2,4 GHz, y se utiliza como alternativa a las conexiones por cable para intercambiar ficheros y conectar transmisores de audio. Gracias a su bajo consumo de energía, seguridad, capacidad contra interferecias, compatibilidad con varios sistemas operativos y facilidad de implementación, esta tecnología se convierte en una buena opción para la implementación del [IoT](#IoT). Además, tiene la capacidad de agregar capas de cifrado, autenticación y verificación, y de construir redes PAN entre dispositivos al interconectar varios entre sí @Bluetooth_Official @Bluetooth_Wiki @Bluetooth_Xataka @Bluetooth_Mokosmart. Es común encontrarlo en pulseras y relojes inteligentes, teléfonos inteligentes, ordenadores, reproductores de música, altavoces, auriculares, y placas de desarrollo como ESP32.

#### Más tecnologías y protocolos [IoT](#IoT)

En el ámbito del [IoT](#IoT), existen otras tecnologías y protocolos populares que, a diferencia de Wi-Fi y Bluetooth, los cuales están integrados en las placas ESP32, requieren modificaciones para poder ser utilizados en estas placas. Sin embargo, esto no elimina la necesidad de conocerlas, al menos a través de un análisis no tan detallado.

**Zigbee**: es un protocolo basado en la especificación [IEEE](#IEEE) 802.15.4 que permite formar redes PAN sencillas. Estas redes son en malla y están formadas por un nodo coordinador. Zigbee opera en la banda de 2,4 [GHz](#GHz) y se utiliza en proyectos a pequeña escala que requieren una conexión inalámbrica de baja potencia, baja velocidad de transmisión (hasta 250 [Kbps](#Kbps)) y un rango próximo (hasta 10-100 metros) @Zigbee_Wiki.

**Thread**: es una tecnología que utiliza 6LoWPAN y la especificación [IEEE](#IEEE) 802.15.4, por lo que opera en la banda de 2,4 [GHz](#GHz) con una velocidad de hasta 250 [Kbps](#Kbps). Permite crear redes malladas de bajo consumo que comunica de manera encriptada más de 250 dispositivos, los cuales deben ser certificados y creados por empresas miembros del Thread Group @Thread_Wiki @Thread_ERF.

**LoRa**: es una tecnología inalámbrica de conexión punto a punto que emplea tecnología de modulación en radiofrecuencia. Es ideal cuando se necesitan conexiones que cubran largas distancias con dispositivos sin fácil acceso a la corriente eléctrica de red ni cobertura, ya que ofrece un bajo consumo de uso y un largo alcance de 10-20 km, con alta tolerancia a interferencias. Opera en bandas inferiores a 1 [GHz](#GHz) (dependiendo de la región), y transmite un máximo de 255 bytes a velocidades entre 0,3 [Kbps](#Kbps) y 50 [Kbps](#Kbps). Esta tecnología es conocida por ser utilizada en LoRaWAN @LoRa_Catsensors @LoRa_Vencoel.

#### Comparaciones entre Wi-Fi, Bluetooth y ESP-NOW

Es de alta relevancia comparar estas tecnologías y ESP-NOW entre sí, ya que son las más populares en el ámbito del [IoT](#IoT) y vienen incorporadas en las placas ESP32. En particular, ESP32 es compatible con Bluetooth 4.2 y con Wi-Fi b, g y n de 2,4 [GHz](#GHz), por lo que a lo largo de este apartado se comparan estas versiones. Estos tres protocolos son similares en varios aspectos, ya que utilizan ondas de radio para transmitir datos de forma inalámbrica a una amplia gama de dispositivos, de manera rápida y fiable. Esto puede resultar en una decisión compleja para elegir entre los tres, aunque hay escenarios en los que no es necesario elegir, ya que en un ESP32 pueden trabajar en conjunto.

De manera más resumida y a partir de lo mencionado en anteriores subsecciones, estas son las características teóricas que ofrecen los protocolos:

1. *ESP-NOW*:
	- **Alcance**: 220 metros.
	- **Cantidad de dispositivos conectables**: 20 a cada nodo.
	- **Unidad de Transmisión Máxima (MTU)**: 250 bytes.
	- **Velocidad de transmisión**: 1 [Mbps](#Mbps).
	- **Uso**: [IoT](#IoT) y comunicación entre dispositivos de Espressif.
2. *Wi-Fi b/g/n (2,4 [GHz](#GHz))*:
	- **Alcance**: 250 metros.
	- **Cantidad de dispositivos conectables**: depende de la configuración de la red y la asignación de direcciones [IP](#IP).
	- **Unidad de Transmisión Máxima (MTU)**: 1460 bytes, configurado en la librería de red de ESP32 @WifiESPMTU.
	- **Velocidad de transmisión**: 54 [Mbps](#Mbps).
	- **Uso**: conexión a internet, acceso a dispositivos e [IoT](#IoT).
3. *Bluetooth 4.2*:
	- **Alcance**: 50-100 metros.
	- **Cantidad de dispositivos conectables**: 7 a cada nodo @Bluetooth_Wiki.
	- **Unidad de Transmisión Máxima (MTU)**: 251 bytes @BlePacket.
	- **Velocidad de transmisión**: 1 [Mbps](#Mbps) @DiffBl542_Amar.
	- **Uso**: audio, dispositivos personales e [IoT](#IoT).

Para comparar estos protocolos, se han tomado los datos de distintas pruebas en escenarios de uso real realizadas y detalladas en una publicación de 2021, llevada a cabo por Dania Eridani, Adian Fatchur Rochim y Faiz Noerdiyan Cesara, miembros del Departamento de Ingeniería Informática de la Universidad de Diponegoro[^espnow:informaticaDiponegoro], en Indonesia. Esta publicación @ESPNOW_WiFi_BT_Comparison comparó el rango, la velocidad, la latencia, el consumo y la resistencia a barreras entre estas tecnologías y protocolos utilizando placas ESP32, obteniendo una serie de conclusiones, representadas en la Figura \ref{espnow:rendimientoComparacionProtocolos} y listadas de la siguiente manera:

![Comparación del rendimiento entre protocolos en distintos aspectos (Fuente: @ESPNOW_WiFi_BT_Comparison)\label{espnow:rendimientoComparacionProtocolos}](espnow_protocols_comparison.png){width=62%}

- La mayor ventaja de Bluetooth se encuentra en el consumo, ya que su rendimiento en el resto de los aspectos es muy deficiente.
- ESP-NOW es el mejor candidato cuando se requieren rangos elevados, una señal de comunicación resistente y mínima latencia en velocidades de datos muy pequeñas, pero su uso consume mucha energía relativamente.
- Wi-Fi es una tecnología muy equilibrada, y destaca por su velocidad.

[^espnow:informaticaDiponegoro]: <https://tekkom.ft.undip.ac.id/language/en/home/>
