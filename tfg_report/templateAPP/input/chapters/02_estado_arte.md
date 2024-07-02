# Estado del arte

## Internet de las Cosas

Dado que una de las principales motivaciones de este Trabajo de Fin de Grado es el aporte que puede ofrecer a la facilidad de implementación del Internet de las Cosas, Internet of Things ([IoT](#IoT)) en inglés, es importante conocer el joven concepto que nos rodea en la actualidad.  

El siglo XX dio lugar al desarrollo de numerosos inventos que impulsaron una revolución y un avance ágil en la sociedad, que en la actualidad son frecuentemente usados y facilitan la vida humana. Este es el caso del Internet, que desde 1969 ha permitido la comunicación entre personas y el acceso a información. Hoy en día, también millones de objetos están conectados a la red, cuyas funcionalidades dependen de esta.

[IoT](#IoT) es un término utilizado por primera vez en un discurso realizado en septiembre de 1985, cuando Peter T. Lewis predijo que "no sólo los humanos, sino también las máquinas y otras cosas se comunicarán interactivamente a través de Internet" /**TODO: mencionar al podcast**/; también empleado por Kevin Ashton en 1999 al realizar una presentación del uso de etiquetas de identificación por radiofrecuencia, o radio frequency identification ([RFID](#RFID)) en inglés, y otros sensores en los productos de la cadena de suministro. Sin embargo, es esencial tener una clara comprensión del significado del [IoT](#IoT), en mayor parte por la confusión inherente al término en sí y por las aplicaciones cotidianas de esta tecnología. A primera vista, "Internet de las Cosas" podría dar la impresión de ser un término moderno para referirse a "conectar a Internet algo para controlarlo", una definición bastante simple para alguien que por ejemplo controla las luces de su hogar desde su teléfono móvil. Es tanta la confusión que no existe una definición formal única, sino que se pueden encontrar una disparidad de definiciones que no todos los sistemas [IoT](#IoT) cumplen. En 2012, la Unión Internacional de Telecomunicaciones ([ITU](#ITU)) recomendó definir el [IoT](#IoT) como una infraestructura global que permite ofrecer servicios avanzados a todo tipo de aplicaciones conectando objetos entre sí e interoperando tecnologías de la información y comunicación, aprovechando capacidades de identificación, obtención de datos, procesamiento y comunicación y cumpliendo con requisitos de seguridad y privacidad. Sin embargo, por lo general, podemos entender que el [IoT](#IoT) trata de dotar de capacidades de comunicación además de procesamiento, captura y/o análisis de datos a distintos tipos de entes, como dispositivos físicos, objetos, edificaciones, terrenos, sistemas, hardware, software, e incluso contextos y situaciones, ya sea añadiéndoles dispositivos o integrando ciertas capacidades en los propios objetos. Estos entes pueden estar compuestos de sensores, que recopilan datos, o actuadores, que controlan otros objetos, y a través de redes, privadas o públicas, pueden intercambiar información con otros dispositivos, recopilar la información en un mismo dispositivo y transferir órdenes, además que existe la posibilidad de formar una agrupación de dispositivos para identificarlos como un único sistema que trata los datos. Estas redes de conexión de dispositivos [IoT](#IoT) pueden utilizar la información transferida para poder automatizar sus comportamientos, pero el nodo final de la conexión suelen ser las personas, ya que utilizan los objetos como fuentes de información, para a su vez utilizar los datos recibidos como descubrimiento de oportunidades de negocio y nuevos servicios, monitorización y evaluación del estado y el comportamiento de los objetos y el entorno, y la toma de decisiones sobre los propios objetos manipulándolos remotamente y programándolos. Dependiendo del entorno en que se implemente, estos sistemas deben cumplir requisitos de seguridad y privacidad, evitando manipulaciones y accesos indebidos o incluso daños en los propios objetos y en el entorno que los rodea.

Con el objetivo de ilustrar cómo funciona un sistema [IoT](#IoT), la Figura \ref{iot:ejemploRiegoIoT} muestra un sistema de riego por aspersión inteligente en un jardín. El jardín está dividido en zonas, cada una con un dispositivo compuesto por sensores de temperatura y humedad y actuadores que activan y desactivan los aspersores que riegan la vegetación. Estos dispositivos están conectados y se comunican con un único gateway o puerta de enlace, teniendo la capacidad de recibir información de los dispositivos y mandar órdenes a estos. El gateway está comunicado a través de Internet con un servidor compuesto por una base de datos, donde se almacenan los datos históricos y registros, y un servicio que le permite ser controlado desde otro dispositivo conectado a Internet en cualquier sitio y momento. Este último dispositivo, denominado cliente, puede ser un teléfono móvil o un ordenador, y puede utilizarse para ver el estado del jardín y controlar los dispositivos manualmente desde una interfaz. La siguiente arquitectura, abstraída completamente de las limitaciones y los problemas que puede ofrecer su implementación, podrá dar lugar a dos casos de uso:

- El usuario quiere activar los aspersores. El usuario, desde la interfaz el dispositivo cliente como puede ser un botón, enviará la orden de activar los aspersores al servicio, que a su vez se lo enviará al gateway. El gateway enviará una orden compatible a los dispositivos instalados en el jardín, haciendo que los aspersores comiencen a funcionar. Esta secuencia de ejecución será parecida si el usuario desea desactivar los aspersores.
- Los aspersores funcionan cuando la temperatura es muy elevada y la humedad es baja. El usuario previamente, desde la interfaz del cliente, ha establecido que los aspersores funcionen de manera automática cuando, por ejemplo, el ambiente supere una temperatura de 42 [ºC](#ºC) y la humedad sea considerada baja. Estos parámetros los recibe el servidor y se los pasa al gateway, el cual los recordará. A partir de ese momento, el gateway irá recibiendo de los sensores de cada zona lecturas de temperatura y humedad, y las comparará con los parámetros establecidos. En el caso de que se superen la temperatura y humedad, se activarán los aspersores de la zona. Una vez activados, se mantendrá la lectura de temperatura y humedad, y cuando las lecturas sean inferiores, se desactivarán los aspersores. Además, con cada activación de los aspersores, el gateway notificará al servicio, que a su vez notifica al usuario, especificando la zona activada.

![Esquema de un sistema de riego por aspersión utilizando dispositivos [IoT](#IoT)\label{iot:ejemploRiegoIoT}](iot_example.png){width=75%}

Cabe recalcar que el mencionado ejemplo puede volverse más complejo, por ejemplo añadiendo comprobaciones de previsión meteorológica en los próximos días, sensores de luz, control del caudal del agua, pero igualmente cumple con los requisitos para ser un sistema que implementa el [IoT](#IoT), ya que dota a un jardín de capacidad de comunicación, captura y análisis de datos, y se comunica con otros dispositivos y con personas para informar del estado y recibir órdenes.

### Ventajas y usos

Hoy en día vivimos en un mundo conectado, en el cual estamos rodeados de numerosos dispositivos, gran parte de ellos interconectados como sistemas, ya que la información es crucial para la sociedad. Por ejemplo, a nivel empresarial es la que permite crear nuevas posibilidades, modelos, interacciones y soluciones únicas, entender y anticiparse a tendencias, identificar nuevas oportunidades, encontrar ventajas competitivas y detectar problemas internos, entre otras aplicaciones beneficiosas para la sociedad. Esta información se obtiene a partir del procesamiento y análisis de colecciones de datos, recopilados de diversas fuentes potenciales, como es el caso de los sistemas [IoT](#IoT). El [IoT](#IoT) permite conectar dispositivos a la red con el fin de enviar y transmitir datos de forma rápida y en tiempo real, mejorando la recopilación de datos del entorno y el control e interacción con el mismo. La rapidez permite que los datos y el control sean accesibles en cualquier momento y lugar, según requiera el usuario, siempre que el sistema haya sido configurado para ello. Sumado a lo anterior, tiene la característica de poder implementarse de diferentes maneras en una gran variedad de entornos, adaptándose al uso que se le vaya a dar y a otras necesidades.

El control y los datos generados tras aplicar técnicas adecuadas de análisis, como las que emplean inteligencia artificial, convierten al [IoT](#IoT) en un factor fundamental en el funcionamiento de las empresas y en su transformación digital En términos generales, gracias al [IoT](#IoT) es posible monitorear los procesos que ocurren en un negocio para controlar y optimizar los recursos utilizados, ya sean energéticos o de personal humano; además de encontrar tareas manuales o repetitivas que pueden ser automatizadas mediante el propio [IoT](#IoT), mejorando así la eficiencia, el tiempo y la productividad. Asimismo, permite la toma de decisiones informadas a partir de datos de negocio, tanto internos como externos, que permitan agregar valor al negocio de manera más rápida, y la mejora de experiencia y de calidad de vida de los usuarios o clientes basándose en los datos recibidos sobre estos.

En cuanto a tareas más específicas que [IoT](#IoT) mejora y habilita, pueden estar la administración del inventario, localizar errores fácilmente, o incluso aún más específicas según el sector en el que se aplica:

- Sanidad: monitorizar signos vitales, hacer recomendaciones de salud adecuadas, comprobar autenticidad y dosis recomendadas en medicamentos.
- Agricultura y ganadería: controlar las condiciones del suelo y el crecimiento de los cultivos, localizar el ganado, controlar la calidad de la leche recolectada en un tanque.
- Transporte, conducción y logística: frenado automático de emergencia, cálculo de rutas óptimas, búsqueda de aparcamiento, mantener condiciones óptimas de remolques que transporten productos perecederos.
- Fabricación: controlar temperatura y humedad de centros de fabricación, identificar áreas con necesidad de personal, crear controles de calidad a productos.
- Comercio: identificar posición óptima de los productos en las estanterías, guiar a clientes hasta determinados productos, trazabilidad en el producto desde la llegada en el almacén hasta su venta.
- Ciudades y edificios inteligentes: mejor vigilancia y actuación por los equipos de emergencia, localizar áreas de contaminación, automatizar iluminación y calefacción.

El [IoT](#IoT) no solo se reduce a estos sectores, es prácticamente aplicable a todos, como la educación, la construcción o el turismo, y a cualquier fase, desde el diseño hasta ofrecer y consumir el servicio o producto, gracias a la popularización de esta tecnología y al aumento de dispositivos que aparecen a nuestro alrededor.

{
https://es.wikipedia.org/wiki/Internet_de_las_cosas
https://www.ibm.com/es-es/topics/internet-of-things
https://blog.ubisolutions.net/es/iot-tecnologias-casos-de-uso-ventajas-y-limitaciones-guia-completa
https://www.tokioschool.com/noticias/ventajas-desventajas-internet-cosas/
https://kryptonsolid.com/principales-ventajas-y-desventajas-de-iot-en-los-negocios/
	https://www.campusbigdata.com/big-data-blog/item/101-relacion-iot-con-big-data
	https://www.ibm.com/es-es/topics/internet-of-things
	https://www.nougir.com/index.php/blog-3/item/13-que-es-iot-o-internet-de-las-cosas-y-sus-aplicaciones
	https://innovayaccion.com/blog/aplicando-el-internet-de-las-cosas-a-las-empresas-2
	https://cdn.ihs.com/www/pdf/IoT_ebook.pdf
	https://www2.deloitte.com/content/dam/Deloitte/nl/Documents/real-estate/deloitte-nl-fsi-real-estate-smart-buildings-how-iot-technology-aims-to-add-value-for-real-estate-companies.pdf
	https://www.researchgate.net/publication/325373920_Internet_of_things_IoT_a_survey_on_architecture_enabling_technologies_applications_and_challenges
}


### Factores, limitaciones y desafíos a tener en cuenta

Al desarrollar una arquitectura del [IoT](#IoT), es necesario tener en cuenta una serie de factores que afectan tanto a los dispositivos como a la comunicación entre ellos.

La primera consideración se refiere a los datos, el artefacto más importante en estos sistemas. Deben ser adecuados y el personal debe estar preparado para tratarlos y analizarlos. Sin embargo, debido a la gran cantidad de datos producidos, se presenta un reto significativo al analizarlos y extraer información, especialmente en casos de falta de herramientas o experiencia en análisis.

Dependiendo del dispositivo, el uso que se le da y el entorno donde se instala, puede verse limitado por varios factores energéticos y físicos interdependientes, tales como la manera de alimentarlo, el consumo (coste de la energía y tiempo de uso), el rango de movilidad, el peso y el tamaño. Dar preferencia a un factor puede perjudicar a otro, por lo que es necesario buscar un equilibrio que satisfaga todas las necesidades o priorizar algunas sobre otras y aplicar cambios en las propias necesidades. Por ejemplo, puedo tener un dispositivo instalado en un hueco pequeño que consuma poco pero que tenga una batería pequeña, o puedo hacer el hueco más grande para añadir una batería de mayor capacidad.

Las condiciones ambientales (como la lluvia, la humedad, las vibraciones y la temperatura), la disponibilidad de conexión en una zona (cobertura de red o electrificación), las interferencias electromagnéticas y otros factores del área donde se despliega el sistema pueden provocar un replanteamiento de ciertas partes. Por ejemplo, éstas pueden implicar la fiabilidad en el transporte de los datos mediante mecanismos de acuses de recibo y verificación de mensajes, o la frecuencia de transmisión y tamaño de los datos.

Debido a la heterogeneidad de los dispositivos en cuanto a fabricantes, características y capacidades, y a la falta de un estándar internacional de compatibilidad para dispositivos en [IoT](#IoT), es necesario dedicar un esfuerzo a identificar las tecnologías de comunicación compatibles (y que cumplan las necesidades de velocidad y alcance), configurar los dispositivos y usar dispositivos adicionales si es necesario. Esto convierte al sistema en una fuente de datos complicada de analizar e integrar en otros.

Es importante además adaptar el despliegue al uso que se le vaya a dar, como puede ser tener una topología de conexión y comunicación adecuada según los dispositivos que interactúen, prepararlo para una futura escalabilidad, habilitar la gestión remota de los dispositivos para actualizarlos, reconfigurarlos, localizarlos o desconectarlos, y realizar una correcta recolección de los datos.

Los dispositivos pueden recopilar datos sensibles de usuarios y empresas que son transmitidos constantemente, y los dispositivos destinados a [IoT](#IoT) no suelen tener altas capacidades de procesamiento para establecer controles de seguridad. Además, los fabricantes pueden haberse centrado en optimizar los recursos, descuidando aspectos como la seguridad en el cifrado o en los controles de acceso. Junto a posibles creaciones de redes insuficientes, esto convierte a los sistemas [IoT](#IoT) en un cebo para infiltraciones, sustracciones de datos, modificaciones de los datos transmitidos y corrupción de configuraciones y de dispositivos, entre otros tipos de ataques. Al implementar [IoT](#IoT), es preferible mantener una buena ciberseguridad y respetar la privacidad de los datos implementando medidas que aseguren la confidencialidad, la integridad y la disponibilidad (como el control de acceso, autenticación y cifrado), siendo importante conocer las regulaciones de la zona en la que opera el sistema para poder cumplirlas.

De manera general, los desarrolladores de software en estos sistemas tienen la responsabilidad de que tanto las capacidades como las limitaciones influyan en el código, aplicando métodos como la suspensión del funcionamiento del dispositivo cuando no está en uso o la optimización del código para reducir el consumo de recursos.

Como consideración final, el aumento de la brecha tecnológica que generan los sistemas [IoT](#IoT) impacta en la sociedad y limita el grupo social que tiene la capacidad de comprender su funcionamiento y sabe acceder y hacer uso de esta tecnología correctamente. Esto implica una necesidad de educación hacia los usuarios.

Un sistema [IoT](#IoT) se puede llevar a cabo en una gran cantidad de situaciones y entornos, pero es una complejidad que debe ser gestionada. Está conformado por dispositivos que por sí solos realizan tareas sencillas, pero al formar parte de un sistema requieren una inversión en dispositivos, una instalación correcta, un mantenimiento realizado por personal capacitado y tener en cuenta otros factores técnicos, del entorno y de la propia implementación. Para obtener una arquitectura eficiente que aporte los resultados esperados, es recomendable analizar los requisitos y las posibles limitaciones, listar las soluciones, diseñar la arquitectura del sistema, planificar un presupuesto, desarrollar una estrategia de implementación y de mantenimiento en caso de errores o mal funcionamiento, y realizar pruebas y evaluaciones.
{
 “IoT fundamentals: Networking technologies, protocols, and use cases for the internet of things”. David Hanes, Gonzalo Salgueiro, Patrick Grossetete, Jerome Henry, Robert Barton
	https://www.redeweb.com/articulos/sensores/los-sensores-inalambricos-iot-y-el-problema-de-la-corta-duracion-de-las-baterias
	https://neurona-ba.com/iot-a-tu-alcance/
	https://www.ittrends.es/infraestructura/2021/12/los-problemas-de-conectividad-estan-dificultando-los-despliegues-de-iot
	https://deingenierias.com/curso/iot/1-4-desafios-y-limitaciones-de-iot/
	https://www.chakray.com/es/5-requesitos-de-una-arquitectura-iot/
	https://www.incibe.es/incibe-cert/blog/riesgos-y-retos-ciberseguridad-y-privacidad-iot
	https://es.wikipedia.org/wiki/Internet_de_las_cosas
https://www.ibm.com/es-es/topics/internet-of-things
https://blog.ubisolutions.net/es/iot-tecnologias-casos-de-uso-ventajas-y-limitaciones-guia-completa
https://www.tokioschool.com/noticias/ventajas-desventajas-internet-cosas/
https://kryptonsolid.com/principales-ventajas-y-desventajas-de-iot-en-los-negocios/
}

### Primeros ejemplos de IoT

El primer dispositivo [IoT](#IoT) conocido fue una máquina de Coca-Cola conectada a [ARPANET](#ARPANET) a principios de la década de los 80 en la Universidad Carnegie Mellon de Pittsburgh, Pensilvania. Esta máquina era mantenida por los usuarios de la universidad y tenía cierta popularidad que hacía que normalmente estuviera vacía o recién cargada con botellas calientes, lo que molestaba al departamento de Ciencias de la Computación. Para resolver este problema, instalaron microinterruptores en la máquina para detectar las botellas que había en cada ranura, los conectaron al ordenador Programmed Data Processor model 10 (PDP-10) del departamento y diseñaron un programa para registrar la hora cada vez que ocurría una transacción en cada ranura, así como otro programa para recibir información de la máquina. Utilizando el último programa desde la red del departamento, se podía consultar si había botellas en las ranuras, cuánto tiempo había transcurrido desde que se recargó con una nueva botella o si estaba fría.

Más tarde, hicieron público el acceso a esta información, haciendo que cualquier persona conectada a [ARPANET](#ARPANET) en cualquier parte del mundo podía consultar el estado de la máquina de Coca-Cola durante más de una década utilizando el comando `finger coke@cmua`, hasta que la máquina fue reemplazada por ser incompatible con el nuevo diseño de las botellas de Coca-Cola.

Incluir imágenes:
- Xerox Alto, ordenador fabricado en 1973, usado en la CMU para ver el estado de la maquina  
- Máquina de cocacola https://engineercom.wpenginepowered.com/wp-content/uploads/2016/02/IIot1.png  
- PDP-10 

Posteriormente, en 1990, apareció otro notable objeto conectado a un Internet más similar al actual, una tostadora. La idea surgió en la edición de 1989 de Interop, una conferencia en la que se pone a prueba la interoperabilidad de dispositivos, cuando el organizador retó a John Romkey, cocreador de la primera pila de protocolos de Internet TCP/IP, a conectar un dispositivo a Internet. En esa época, Romkey trabajaba en el Protocolo Simple de Gestión de Redes o *Simple Network Management Protocol* ([SNMP](#SNMP)) junto a sus compañeros de Epilogue, un protocolo utilizado para leer y escribir variables en un agente remoto y comúnmente empleado para gestionar routers. Romkey quiso aprovechar la oportunidad para demostrar de forma sencilla que el [SNMP](#SNMP) podía controlar dispositivos físicos, con una tostadora. Utilizó un modelo de tostadora capaz de bajar el pan insertado al momento de recibir energía, lo cual hacía que necesitase controlar la alimentación del dispositivo en vez de emplear robótica que accione la típica palanca que tienen las tostadoras comunes. La alimentación se controlaba con un relé, accionado a su vez por un interruptor accionado a través del puerto paralelo de su ordenador portátil, el cual recibía órdenes de un agente [SNMP](#SNMP) que detectaba los cambios. [SNMP](#SNMP) permite controlar dispositivos remotos definiendo objetos en su base de información gestionada (Management Information Base o [MIB](#MIB)) con valores posibles, acceso permitido, estado y descripción. En este caso, se especificaron los objetos necesarios para que el usuario pudiera modificarlos a través de [SNMP](#SNMP) y así especificar la tostadora que se está controlando, el inicio del tostado, el tipo de pan y el nivel de tostado final.

La tostadora de Internet se presentó en la Interop de 1990, y se mejoró en la edición de 1991 añadiendo un brazo robótico de LEGO también controlado por Internet para insertar rebanadas de pan en la tostadora, consiguiendo así un sistema completamente automatizado. En la actualidad, la tostadora creada por Romkey sigue en su posesión.

- TODO: Incluir imágenes tostadora (sacarla de url)

Como último ejemplo, también de la misma época de Internet, está XCoffee o la cafetera de la Sala Trojan. En noviembre de 1991, Quentin Stafford-Fraser y Paul Jardetzky trabajaban junto a sus compañeros investigadores agrupados en el antiguo laboratorio de informática, también llamado Sala Trojan, de la Universidad de Cambridge, mientras que el resto de compañeros estaban dispersos por la universidad. Todos compartían un problema en común: una única máquina de café de goteo-filtro a la salida del laboratorio, cuya jarra estaba vacía o contenía café con un sabor horrible a excepción de cuando estaba recién hecho, siendo esta última opción solo para aquellos que se sentaban cerca. Para solucionar este problema, Stafford-Fraser y Jardetzky idearon el sistema XCoffee, y el Dr. Martyn Johnson y Daniel Gordon lo mejoraron. Fijaron una cámara apuntando a la jarra de la cafetera, la conectaron a una capturadora de fotogramas del ordenador Acorn Archimedes del rack de la sala y crearon un software para que cada vez que el servidor recibía una solicitud HTTP a través de la World Wide Web devolvía una página web con la imagen de la cafetera capturada más reciente. Desde el navegador se podía comprobar si valía la pena ir a por café (en el caso de estar en el mismo edificio que la cafetera), y esto convertía al sistema en la primera webcam de la historia, otorgándole una fama internacional. Estuvo operativa su última versión desde el 22 de noviembre de 1993 hasta el 22 de agosto de 2001 a las 09:54 UTC, cuando mostró su última imagen pocos segundos antes de su apagado debido a su difícil mantenimiento y al traslado de las instalaciones del laboratorio.

Actualmente, la máquina de café se encuentra restaurada y expuesta en el museo de informática Heinz Nixdorf MuseumsForum de Paderborn, Alemania.


https://www.nougir.com/index.php/blog-3/item/13-que-es-iot-o-internet-de-las-cosas-y-sus-aplicaciones
https://informationmatters.net/internet-of-things-definitions/
(DOCUMENTO) https://www.itu.int/ITU-T/recommendations/rec.aspx?rec=11559&lang=es
(LIBRO) https://www.taylorfrancis.com/chapters/oa-edit/10.1201/9781003337584-3/internet-things-cognitive-transformation-technology-research-trends-applications-ovidiu-vermesan-markus-eisenhauer-harald-sundmaeker-patrick-guillemin-martin-serrano-elias-tragos-javier-vali%C3%B1o-arthur-van-derwees-alex-gluhak-roy-bahr
(LIBRO) https://books.google.es/books/about/La_Red_de_Todo.html?id=wUydnQAACAAJ&redir_esc=y
(DOCUMENTO) https://cdn.ihs.com/www/pdf/IoT_ebook.pdf
(DOCUMENTO) https://www.researchgate.net/publication/352541626_Analysis_of_IoT_Concept_Applications_Smart_Home_Perspective
https://www.microsoft.com/insidetrack/blog/transforming-microsoft-buildings-with-iot-technology-and-indoor-mapping/
(LIBRO) https://www.se.com/us/en/download/document/998-20233517/
(DOCUMENTO) https://www.researchgate.net/publication/320135661_Efficient_IoT-based_Sensor_BIG_Data_Collection-Processing_and_Analysis_in_Smart_Buildings
(DOCUMENTO) https://www2.deloitte.com/content/dam/Deloitte/nl/Documents/real-estate/deloitte-nl-fsi-real-estate-smart-buildings-how-iot-technology-aims-to-add-value-for-real-estate-companies.pdf
https://innovayaccion.com/blog/aplicando-el-internet-de-las-cosas-a-las-empresas-2
(DOCUMENTO) https://ieeexplore.ieee.org/document/7879243
https://www.intel.com/content/www/us/en/internet-of-things/overview.html
https://www.fundacionbankinter.org/ftf-informes/internet-de-las-cosas/
https://www.statista.com/statistics/471264/iot-number-of-connected-devices-worldwide/
(VIDEO) https://www.youtube.com/watch?v=RnasX1bFBh8
(LIBRO) https://www.amazon.com/IoT-Fundamentals-Networking-Technologies-Protocols/dp/1587144565
(LIBRO) https://www.ra-ma.es/libro/internet-de-las-cosas_93304/
https://es.wikipedia.org/wiki/Internet_de_las_cosas  
https://www.eexcellence.es/expertos/kevin-ashton-un-tecnologo-visionario  
https://www.redhat.com/es/topics/internet-of-things/what-is-iot  
https://at3w.com/blog/iot-internet-of-things-tecnologia-proteccion-contra-rayo-tomas-tierra/  
https://www.itop.es/blog/item/iot-origen-importancia-en-el-presente-y-perspectiva-de-futuro.html  
https://www.linkedin.com/pulse/el-origen-del-internet-de-las-cosas-iot-comnet-s-a-/   
https://www.ui1.es/blog-ui1/historia-y-origen-del-iot  
https://blog.avast.com/es/kevin-ashton-named-the-internet-of-things  
https://www.datacenterdynamics.com/en/podcasts/zero-downtime/episode-18-the-origin-of-the-internet-of-things-with-peter-lewis/
https://swifttalk.net/2021/10/06/the-concept-of-iot-internet-of-things/
https://www.cs.cmu.edu/~coke/
https://www.cs.cmu.edu/~coke/history_long.txt
https://www.ibm.com/docs/es/aix/7.1?topic=protocols-namefinger-protocol
https://www.livinginternet.com/i/ia_myths_toast.htm
https://en.wikipedia.org/wiki/John_Romkey
https://ieeexplore.ieee.org/document/7786805 Romkey, J. (2017). Toast of the IoT: The 1990 Interop Internet Toaster. IEEE Consumer Electronics Magazine, 6(1), 116–119. doi:10.1109/mce.2016.2614740 
https://romkey.com/about/
https://blog.avast.com/the-internets-first-smart-device
https://en.wikipedia.org/wiki/Trojan_Room_coffee_pot
https://www.cl.cam.ac.uk/coffee/qsf/coffee.html
https://www.cl.cam.ac.uk/coffee/coffee.html
https://www.youtube.com/watch?v=uF982_aRKrI
https://www.bbc.com/news/technology-20439301
https://www.historyofinformation.com/detail.php?id=1507
https://quentinsf.com/coffeepot/metcalfe/
https://www.cl.cam.ac.uk/coffee/qsf/switchoff.html
https://owl.museum-digital.de/object/3761


### Tipos de dispositivos y redes

Como se ha mencionado anteriormente, el [IoT](#IoT) se basa en la transmisión de datos entre dispositivos. Estos datos pueden ser información recibida del entorno u órdenes de actuación, que salen o llegan a un dispositivo ubicado en un extremo de la red de conexión y que tiene conectado uno o ambos de los siguientes tipos de objetos:

- Sensores: miden una propiedad física y la representan digitalmente, siendo útiles para detectar cambios en el entorno. Tienen mayor precisión y capacidad de percepción que los órganos sensoriales humanos, y pueden integrarse en cualquier objeto físico para interpretar su entorno. Actualmente están experimentado una proliferación debido a su disminución en tamaño y coste.
- Actuadores: dispositivos que interpretan una señal eléctrica y desencadenan un efecto físico tras interpretarla, siendo útiles para producir cambios en el entorno. Si un sensor se puede comparar con los órganos sensoriales humanos, un actuador se puede comparar con las acciones que pueden ejecutar las extremidades.

En una red [IoT](#IoT), tanto sensores como actuadores son el corazón del sistema, ya que permiten interactuar con el mundo físico. Pueden ser parte de objetos inteligentes, dotados de procesador, fuente de energía y capacidad para comunicarse con otros componentes, y son objetos cotidianos que integran todo lo necesario para interactuar con el entorno.

Todos estos dispositivos heterogéneos están interconectados en una red que permite detectar, medir y actuar en relación con el entorno. Esta red, con el fin de ser efectiva y tolerante a fallos, debe pasar por un análisis de criterios como la topología de conexión entre los dispositivos, la distancia entre estos y cómo se procesan los datos.

Una red [IoT](#IoT), puede dividirse en capas según cómo se procesen los datos @EdgeCloudFog_ISA @EdgeCloudFog_Industria40:

- Computación en la nube o *cloud*: los datos se procesan en un servidor central remoto, lejos de su origen. Requiere una conexión a Internet para su acceso, lo cual implica lidiar con la latencia de la red y el uso del ancho de banda. Ofrece una gran capacidad de procesamiento, almacenamiento y análisis, adecuada para aquellas aplicaciones que no requieren respuestas rápidas. Puede agrupar y procesar los datos de todo un sistema.
- Computación en la niebla o *fog*: los datos se procesan cerca de donde se originan, en nodos *fog* de la red local. Estos nodos evitan el uso de Internet para enviar datos a la nube, mejorando la eficiencia y ofreciendo una respuesta más rápida que la computación *cloud*. Se pueden distribuir varios nodos *fog* para jerarquizar la red, agrupandos y procesando datos de ciertos nodos.
- Computación en el borde o *edge*: los datos se procesan en los nodos donde se originan. Ofrece un procesamiento en tiempo real sin necesidad de comunicarse con otros dispositivos, liberando el uso de ancho de banda.

{
	https://www.ibm.com/es-es/topics/internet-of-things
	(LIBRO, el de los apuntes) “IoT fundamentals: Networking technologies, protocols, and use cases for the internet of things”. David Hanes, Gonzalo Salgueiro, Patrick Grossetete,
Jerome Henry, Robert Barton.
https://www.cloudflare.com/es-es/learning/network-layer/what-is-a-personal-area-network/
https://www.cloudflare.com/es-es/learning/network-layer/what-is-a-lan/
https://www.cloudflare.com/learning/network-layer/what-is-a-metropolitan-area-network/
https://www.cloudflare.com/learning/network-layer/what-is-a-wan/
https://www.gadae.com/blog/tipos-de-redes-informaticas-segun-su-alcance/
}


## Middleware y protocolos de mensajería usados en [IoT](#IoT)

---

Versión original:
El uso más común de [IoT](#IoT) es desplegar una arquitectura compuesta por varios dispositivos [IoT](#IoT). En mayor parte, estos dispositivos se designarán simplemente como dispositivos [IoT](#IoT), ya sean sensores o actuadores, mientras que habrá pocos dispositivos (al menos uno) con el rol de centro de mensajería, un intermediario encargado de retransmitir los datos a los dispositivos adecuados. Dependiendo del uso que se le dé a la arquitectura, estos objetos se comunicarán, y dependiendo de quién sea el emisor y el receptor, dan lugar a estos escenarios:
- Un mensaje ha llegado al centro de mensajería [IoT](#IoT). Este mensaje es procesado y se actúa en consecuencia, por ejemplo, enviando la información necesaria a ciertos dispositivos IoT o almacenándola a una base de datos.
- Un dispositivo [IoT](#IoT) ha generado datos. Estos datos son procesados y luego enviados al centro de mensajería.
- Un dispositivo [IoT](#IoT) ha recibido datos del centro de mensajería. Estos datos son procesados y se actúa en consecuencia.

---

Versión 2:  

El uso más común de [IoT](#IoT) es desplegar una arquitectura compuesta por varios dispositivos [IoT](#IoT). En mayor parte, estos dispositivos se designarán simplemente como dispositivos [IoT](#IoT), ya sean sensores o actuadores, que emiten o reciben datos. Adicionalmente, habrá unos pocos dispositivos (al menos uno) con el rol de centro de mensajería, que actuarán como intermediarios encargados de retransmitir los datos a los dispositivos correspondientes.

---

/*TODO: elegir entre las dos versiones. El comentario de la v. original decia que era un caso de uso muy específico, pero es que **pongo que es un uso común**, es decir, **especifico que es concreto***/

---

Tras escoger una tecnología para conectar los dispositivos entre sí, en el desarrollo de aplicaciones [IoT](#IoT) se requiere un protocolo de mensajería para intercambiar esos grandes volúmenes de datos que tratan.

Un protocolo de comunicación permite que los dispositivos se comuniquen y transmitan mensajes entre los dispositivos [IoT](#IoT) y el centro de mensajería. Además, proporciona cierta fiabilidad a la comunicación, ya que permite que los mensajes lleguen y sus datos sean entendidos y procesados correctamente.

La elección del protocolo se basa en cómo se adecua al escenario en el que se quiere implementar, considerando requisitos a tener en cuenta como la ubicación, las limitaciones físicas, el consumo y el coste. Por lo general, no cualquier protocolo de comunicación es apropiado. Los protocolos que se mencionan en este apartado se adecuan a la mayoría de escenarios IoT debido a su rapidez y su fácil implementación, y es posible escoger aquel que se adapte mejor a los requisitos.

### Message Queue Telemetry Transport ([MQTT](#MQTT))

El protocolo [MQTT](#MQTT) es uno de los más populares en el ámbito del [IoT](#IoT). Diseñado para ser ligero y adecuado para redes con ancho de banda limitado y dispositivos con pocos recursos, este estándar del comité técnico [OASIS](#OASIS) permite el transporte bidireccional de mensajes con datos entre múltiples dispositivos.

[MQTT](#MQTT) utiliza el patrón de comunicación publicación-suscripción. En este patrón, los publicadores categorizan los mensajes, y los suscriptores recibirán mensajes de las categorías de su interés, a diferencia de la comunicación directa en la que los participantes se envían los mensajes directamente. En el caso de [MQTT](#MQTT), el patrón está basado en temas o *topics*, siendo posible que los suscriptores se interesen por uno o varios.

En una red [MQTT](#MQTT), se definen dos roles principales: el broker o intermediario de mensajes y los clientes. El broker [MQTT](#MQTT) es un servidor comparable a una oficina de correos, que recibe todos los mensajes publicados por los clientes y los dirige a los clientes de destino apropiados. Por otra parte, un cliente es cualquier dispositivo conectado al broker a través de una red, y puede producir y recibir datos al publicar y suscribirse respectivamente. Este mecanismo es útil para compartir datos, controlar y gestionar dispositivos. Por ejemplo, un dispositivo cliente puede publicar datos de sensores y además recibir información de configuración o comandos de control. El enrutamiento de mensajes realizado por el broker proporciona transparencia de localización y desacoplamiento en el espacio, ya que el publicador no necesita conocer las direcciones de los suscriptores y los suscriptores no necesitan conocer al publicador, ambos interactúan únicamente con el broker.

Los mensajes están organizados en una jerarquía de temas o *topics*. Al publicar un mensaje, se publica en un tema específico, y en el caso de querer publicar en varios se deben realizar varias publicaciones. En cambio, un suscriptor puede suscribirse a un tema específico o a varios simultáneamente y recibirá una copia de todos los mensajes compatibles con los temas suscritos. La manera de indicar varios temas es mediante el uso de los siguientes caracteres comodín:

- Comodín de un nivel '+': coincide con un nivel de tema y puede utilizarse más de una vez en la especificación del tema.
- Comodín de varios niveles '#': coincide con cualquier número de niveles y debe ser el último carácter en la especificación del tema.

Por ejemplo, cuando se publica un mensaje en el tema "`edificioA/sensor1/temperatura`", el broker enviará una copia del mensaje los clientes suscritos a los temas "`edificioA/sensor1/temperatura`", "`edificioA/+/temperatura`" y "`edificioA/#`", pero no a un cliente suscrito a "`edificioB`" o a "`edificioA/+/humedad`".

La transmisión de mensajes se realiza de forma asíncrona, sin detener la ejecución de ambos componentes a la hora de publicar o recibir, y se puede realizar una comunicación uno a muchos (un publicador y varios suscriptores), muchos a uno (varios publicadores y un suscriptor), uno a uno (un publicador y un suscriptor, menos común) y muchos a muchos (varios publicadores y varios suscriptores).

En el caso de que el broker reciba una publicación de un tema en el cual no hay nadie suscrito, el broker por defecto descarta el mensaje. Es posible activar la retención de mensajes configurando un campo en el mensaje para evitar esto, consiguiendo así que el broker almacene el último mensaje retenido de cada tema y lo distribuya inmediatamente a cualquier nuevo cliente suscrito, permitiendo así que el suscriptor reciba el valor más reciente en lugar de esperar a una nueva publicación, y además añadiendo soporte a una comunicación desacoplada en el tiempo, donde publicadores y suscriptores no necesitan estar conectados simultáneamente.

El protocolo soporta un mecanismo de limpieza de sesión. Por defecto, un cliente tras desconectarse y volverse a conectar no recibe los mensajes publicados durante su desconexión y el broker olvida las suscripciones del mismo cliente. Pero al desactivar dicho mecanismo, el broker mantiene tanto las relaciones de suscripción como los mensajes offline, enviándolos al cliente al momento de reconectarse, lo cual es útil para dispositivos que se conectan y desconectan constantemente, común en redes [IoT](#IoT). Además, [MQTT](#MQTT) enfrenta la inestabilidad de la red con un mecanismo *Keep Alive* que, al transcurrir un prolongado periodo sin interacción, ocurre un ping entre el cliente y el broker para evitar la desconexión. Si el ping falla y se identifica el cliente como desconectado, aplicará un mecanismo *Last Will*, que publica un último mensaje a un tema específico debido a una desconexión anormal, en el caso de estar configurado.

[MQTT](#MQTT) dispone de 14 tipos de mensajes diferentes, la mayoría utilizados para mecanismos internos y flujos de mensajes:

- CONNECT: establece una conexión con el broker, y si está configurado, se debe proporcionar un usuario y contraseña.
- DISCONNECT: finaliza una sesión [MQTT](#MQTT) enviando este mensaje para cerrar la conexión. Esta desconexión se denomina "graceful shutdown" o "apagado elegante", porque está la posibilidad de conectarse al broker con la misma sesión y reanudar el progreso.
- PINGREQ/PINGRESP: una operación de ping utilizada para saber si está viva la conexión y mantenerla.
- PUBLISH: contiene un mensaje para publicarlo en un tema específico.
- SUBSCRIBE: utilizado por los clientes para suscribirse a un tema específico y recibir las actualizaciones de este.
- UNSUBSCRIBE: mensaje que utiliza un cliente para indicar la pérdida de interés y anular la suscripción a un tema específico
- LWT: este mensaje "last will and testament" (última voluntad y testamento) se configura en un cliente para publicarse automáticamente si ocurre una desconexión inesperada. El broker mantiene un temporizador, y si comprueba que recientemente el cliente no ha publicado ni ha mandado un PINGREQ, se publica el mensaje LWT especificado notificando así a los suscriptores.

El diseño de [MQTT](#MQTT) se basa en la simplicidad y en minimizar el ancho de banda, dejando la interpretación del contenido del mensaje en manos del desarrollador. Los mensajes transmitidos a través de la red tienen la posibilidad de configurar el [QoS](#QoS) o calidad de servicio por cada tema, asociados con distintas garantías de entrega. Aunque [MQTT](#MQTT) funciona sobre [TCP](#TCP), el cual tiene su propia garantía de entrega, históricamente los niveles [QoS](#QoS) eran necesarios para evitar la pérdida de datos en redes antiguas y poco fiables, una preocupación válida para las redes móviles actuales. Estos son los siguientes tipos de [QoS](#QoS):

- [QoS](#QoS) 0, a lo sumo una vez: los mensajes se envían y no se tiene en cuenta si llegan o no. Está la posibilidad de la pérdida de mensajes y no se hacen retransmisiones.
- [QoS](#QoS) 1, al menos una vez: el receptor recibe el mensaje por lo menos una vez. El receptor debe enviar un acuse de recibo al emisor en cuanto reciba el mensaje, y si este [ACK](#ACK) nunca llega (ya sea debido a que el mensaje nunca llegó o que el [ACK](#ACK) se perdió), el emisor retransmitirá el mensaje, pudiendo producirse mensajes duplicados.
- [QoS](#QoS) 2, exactamente una vez: asegura que el mensaje llegue exactamente una vez, manejado mediante la sobrecarga en la comunicación y el envío de una serie de acuses de recibo, y es la mejor opción cuando no se aceptan ni la pérdida ni la duplicidad de mensajes.

La transmisión de datos se realiza principalmente sobre la capa TCP/IP, pero existe la posibilidad de operar encima de otros protocolos de red que ofrezcan conexiones ordenadas, sin pérdidas y bidireccionales, y se transmiten en un tamaño reducido de paquetes de datos, estructurado por los siguientes campos mostrados en la figura \ref{mqtt:frame}:

- Cabecera fija, en la que se especifica el tipo de mensaje, si el mensaje es un duplicado, el [QoS](#QoS), si es un mensaje que retener y el tamaño del paquete.
- Cabecera variable, no siempre presente en los mensajes, y puede transportar información adicional de control.
- Payload o carga útil.

![Formato de una trama MQTT (Fuente: @MQTT_Frame)\label{mqtt:frame}](mqtt_frame.png){width=100%}

Por defecto, este protocolo envía credenciales y mensajes en texto plano sin medidas de seguridad, pero admite utilizar conexiones [TLS](#TLS)/[SSL](#SSL) protegidas por certificado, nombre de usuario y contraseña para cifrar y proteger la información transferida contra la intercepción, modificación o falsificación. Además, un broker [MQTT](#MQTT) tiene soporte para conectar dispositivos IoT a escala masiva, un factor tenido en cuenta durante su diseño y que resulta en una alta capacidad de concurrencia, rendimiento y escalabilidad, características deseables en una red [IoT](#IoT). Implementaciones como EMQX[^protocolosIoT:emqx] y HiveMQ[^protocolosIoT:hiveMq] han alcanzado hitos notables, con 100 y 200 millones de conexiones respectivamente, y un pico de 1 millón de mensajes gestionados por segundo. A esto se le puede sumar la capacidad de implementar múltiples brokers, para así compartir la carga de clientes y tratar la redundancia y la copia de seguridad de los mensajes en caso de fallo.

[^protocolosIoT:emqx]: <https://www.emqx.com/en>
[^protocolosIoT:hiveMq]: <https://www.hivemq.com/>

{
	https://en.wikipedia.org/wiki/MQTT
	https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern
	https://www.emqx.com/en/blog/what-is-the-mqtt-protocol
	https://www.gotoiot.com/pages/articles/mqtt_intro/index.html
	https://dzone.com/refcardz/getting-started-with-mqtt
	https://www.hivemq.com/resources/achieving-200-mil-concurrent-connections-with-hivemq/
	http://www.steves-internet-guide.com/mqtt-protocol-messages-overview/
}

### Advanced Message Queuing Protocol ([AMQP](#AMQP))

[AMQP](#AMQP) es un protocolo binario avanzado que opera sobre la capa de aplicación, cuyo estándar abierto permite desarrollar mensajería y patrones de comunicación entre dispositivos. Facilita la comunicación entre servicios definiendo el formato de los datos enviados a través de la red como un flujo de bytes, así como la creación de mensajes, el encolamiento y enrutamiento de los mensajes producidos, y la manera de entregarlos a los consumidores.

Este protocolo se basa en el concepto de publicar y consumir de colas de mensajes a través de una conexión fiable, persistente y orientada al envío de flujos de datos. Además, es compatible con el envío de múltiples flujos de datos simultáneos mediante múltiples canales en una única conexión. Permite hacer uso de estas colas de mensajes mediante distintos tipos de comunicación, como la entrega directa punto a punto y el modelo publicación-suscripción, y, pese a no ser un protocolo diseñado originalmente para su uso en el [IoT](#IoT), funciona muy bien en este ámbito y en la gran variedad de escenarios de comunicación y mensajería posibles.

En [AMQP](#AMQP) se definen las dos siguientes entidades principales que interactúan entre sí:

- Cliente: del tipo suscriptor o publicador (o consumidor y productor, respectivamente), se conecta a un broker a través de credenciales y, en caso de estar autorizado, puede recibir o publicar mensajes.
- Broker: servidor de mensajería al que los clientes se conectan y que se encarga de distribuir los mensajes. Internamente, posee *exchanges* o intercambiadores, donde se conectan los productores de mensajes, y colas, vinculadas a los exchanges dependiendo de varios criterios y a las que se conectan los consumidores para extraer los mensajes producidos.

De manera sencilla, se puede resumir el funcionamiento de este protocolo como un modelo en el que los mensajes son publicados y enviados a exchanges, los cuales enrutan los mensajes a las colas apropiadas según reglas o bindings, y los consumidores reciben los mensajes a través de las mismas colas.

Los exchages, además de recibir mensajes de los productores, se encargan de enviar los datos a las colas apropiadas, ya sean a una o a varias dependiendo del exchange y la clave de enrutamiento o routing key con la que se publica el mensaje. A este funcionamiento se le puede asociar la analogía del funcionamiento del envío de emails, ya que estos se envían a direcciones "routing key@exchange", siendo la clave de enrutamiento la dirección de correo y el exchange el servidor. En [AMQP](#AMQP) existen cuatro tipos de exchanges:
 
- Topic, que permite una comunicación publicación-suscripción: los mensajes se enrutan a las colas adecuadas en función de la clave de enrutamiento y el patrón de vinculación al exchange.
- Direct, que permite una comunicación punto a punto: los mensajes se reciben en un exchange con una clave de enrutamiento específica y son enrutados directamente a una cola creada con la misma clave. Es posible que una cola tenga varias claves, conectándose a varios exchange simultáneamente, al igual que varias colas pueden compartir una misma clave de enrutamiento, enviando los mensajes a varios destinatarios.
- Fanout, que permite una comunicación parecida a broadcast: los mensajes son enrutados a todas las colas vinculadas al exchange.
- Cabeceras, que permite una comunicación publicación-suscripción: los mensajes se encaminan a las colas dependiendo de la coincidencia de las cabeceras de los mensajes.

Las colas son fragmentos de memoria creados por el cliente suscriptor identificadas unívocamente mediante un nombre, definido previamente por el cliente o automáticamente por el broker. Intrínsicamente, [AMQP](#AMQP) garantiza la recepción y procesamiento de mensajes, ya que dispone de un mecanismo de [ACK](#ACK) o acuse de recibo que permite confirmar la recepción y procesamiento del mensaje. En el caso de no recibir el [ACK](#ACK) de un mensaje por parte de un consumidor, por ejemplo, porque perdió la conexión o no se procesó correctamente, el broker encola de nuevo el mensaje para reintentar la entrega. Junto a este mecanismo, también está la posibilidad de rechazar mensajes mediante un mensaje [NACK](#NACK) o acuse de recibo negativo, útil para indicar que no se ha procesado bien el mensaje, pero que el broker puede borrar el mensaje de esa cola. Además, las colas admiten persistencia, para mantener la existencia de la cola incluso luego de que ocurra un reinicio en el broker.

Tras crear el exchange y la cola, se indica al broker la vinculación de ambas mediante un binding, especificando una clave de enrutamiento que, según el tipo de exchange, enruta adecuadamente las colas. El exchange entregará como máximo una copia de mensaje a una cola si corresponden las propiedades del mensaje con las propiedades del binding. Con los bindings es posible vincular varias colas a un mismo exchange, al igual que una cola a varios exchanges.

Con los tres conceptos mencionados previamente, exchange, binding y cola, se produce un desacople en tiempo y espacio entre los productores y los consumidores, ya que ambos están aislados entre sí y desconocen su existencia y ubicación. 

Este protocolo especifica el comportamiento del servidor y de los clientes conectados, junto al formato de los mensajes enviados a través de la red, permitiendo interoperar independientemente del lenguaje o del proveedor. Los mensajes se transmiten sobre la capa [TCP](#TCP), y disponen de propiedades como las siguientes:

- Clave de enrutamiento.
- Modo de entrega, si es un mensaje persistente.
- Prioridad del mensaje en un rango entre 0 y 9.
- Vencimiento, indicado en milisegundos, es el tiempo que el broker debe esperar antes de descartar el mensaje si no fue consumido.
- Contador de intentos de entrega.
- Anotaciones de mensaje.
- Propiedades, como el ID del mensaje, usuario y tiempo de creación.
- Payload o carga útil.
- Footer, que contiene detalles del mensaje como hashes o firmas.

[AMQP](#AMQP) es extenso en cuanto a funciones, ofreciendo cifrado de extremo a extremo, múltiples propiedades de mensajes y modos de entrega, fiabilidad en la entrega, persistencia de mensajes, enrutamiento basado en criterios, capacidad de escalabilidad y definición de topologías, entre otros. Sin embargo, pese a su idoneidad para sistemas distribuidos, es un protocolo que conlleva un alto consumo de recursos como energía y memoria.


### Extensible Messaging and Presence Protocol ([XMPP](#XMPP))

Otra manera de comunicar varios dispositivos [IoT](#IoT) es utilizar el [XMPP](#XMPP), anteriormente conocido como Jabber. Este protocolo se basa en la transmisión de datos estructurados en formato [XML](#XML) dentro de una red de arquitectura cliente-servidor, en la cual los dispositivos están identificados por un Jabber ID, cuyo formato es similar al de una dirección de correo electrónico (por ejemplo, "abc@example.com"). En esta red, el cliente establece una conexión TCP/IP con el servidor. Posteriormente, el cliente se autentica con el servidor, y tras una autenticación exitosa, se habilita la posibilidad de enviar y recibir mensajes.

Una característica notable de [XMPP](#XMPP) es que cualquiera puede tener su propio servidor [XMPP](#XMPP), no restringiendo a los usuarios a conectarse únicamente con otros usuarios en el mismo servidor central. Al ser un protocolo abierto formalizado por la Internet Engineering Task Force ([IETF](#IETF))[^protocolosIoT:ietf], los desarrolladores disponen de un protocolo bien documentado y fiable, de este modo, es posible interoperar entre diferentes implementaciones de [XMPP](#XMPP) a través de Internet, independientemente del proveedor. En el caso de querer comunicarse con otro servidor, ambos servidores [XMPP](#XMPP) intercambian la información necesaria, habilitando un modelo federado.

[^protocolosIoT:ietf]: <https://www.ietf.org/>

Este protocolo está diseñado para ofrecer mensajería instantánea o casi en tiempo real a través de la red, sin importar la distancia entre los dispositivos, uno de los problemas más comunes en [IoT](#IoT). Además, permite obtener información sobre los usuarios conectados y mantener una lista de contactos para cada usuario. [XMPP](#XMPP) también es extensible, permitiendo a los desarrolladores añadir características y funcionalidades personalizadas, adaptando el protocolo a necesidades específicas de aplicaciones, como la transmisión de señales [VoIP](#VoIP), video, ficheros, chat grupal, conferencias multiusuario, suscripción de presencia y comunicación publicación-suscripción para recibir actualizaciones sobre temas específicos de interés.

En los mensajes [XMPP](#XMPP) se utilizan estructuras [XML](#XML) denominadas *stanzas* para transportar los datos. Existen 3 tipos principales de stanzas:

- Stanza de mensaje (`message`): utilizado para enviar mensajes instantáneos entre clientes. Contiene los campos remitente, destinatario, cuerpo del mensaje y otros metadatos opcionales. Después de recibir el mensaje, el servidor utiliza el campo de destinatario para enrutar el propio mensaje.
- Stanza de presencia (`presence`): permite a las entidades conocer el estado y la disponibilidad online/offline de otros clientes. También puede transportar información adicional, como la actividad del cliente o su ubicación. Cuando un cliente se conecta o desconecta del servidor, envía una stanza de presencia para notificar a otros clientes de su lista de contactos.
- Stanza de IQ o info/query (`iq`): se usa para consultar al servidor, gestionar suscripciones o intercambiar datos estructurados entre clientes y servidores. Funciona de manera similar a los métodos [HTTP](#HTTP) GET y POST, siguiendo un patrón de petición-respuesta, en el cual un cliente envía una petición al servidor y este responde con la información solicitada o con una confirmación.

El protocolo [XMPP](#XMPP) es altamente escalable debido a su capacidad de manejar multitud de conexiones y mensajes simultáneos. Además, al ser descentralizado, permite implementar fácilmente más servidores para gestionar el aumento de usuarios y altos picos de uso. En cuanto a seguridad, [XMPP](#XMPP) es compatible con cifrado de extremo a extremo mediante [TLS](#TLS) o [SSL](#SSL), garantizando así la confidencialidad de los mensajes. Por último, cuenta con una amplia comunidad de usuarios, diversas implementaciones y guías que facilitan a los desarrolladores la creación de aplicaciones que integren este protocolo.


### Data Distribution Service ([DDS](#DDS))

[DDS](#DDS) es un estándar de middleware y [API](#API) máquina-máquina que facilita la comunicación y el intercambio de datos. Fue desarrollado por el Object Management Group con el fin de responder a las necesidades específicas de aplicaciones que requieren intercambios de datos fiables y de alto rendimiento en sistemas distribuidos en tiempo real, sin dejar de lado la eficiencia. Su arquitectura se basa en un modelo de publicación-suscripción sin servidor, ya que los dispositivos se conectan entre sí, y donde los datos son publicados en un dominio y los suscriptores se conectan a este para recibir la información que les interesa.

Este middleware se corresponde con la capa de software que se encuentra entre el sistema operativo y las aplicaciones, abstrayendo la comunicación entre ambos y, por tanto, los detalles del tranporte de red y de los datos a bajo nivel. Permite que los distintos componentes de un sistema compartan y comuniquen datos, gestionando automáticamente el formato de los mensajes, el protocolo de transporte a usar, la fiabilidad, la calidad de sevicio y la seguridad, y simplificando así el desarrollo. [DDS](#DDS) se centra completamente en los datos, asegurando un buen transporte e incluyendo información contextual de los mismos, lo que lo hace ideal para el [IoT](#IoT) aplicado en entornos industriales.

[DDS](#DDS) funciona con el concepto de espacio de datos global, un almacén de datos que a ojos del programador parece una memoria local accedida mediante [API](#API)s. Sin embargo, este espacio es solo una ilusión, ya que no existe un lugar donde residan todos los datos, se refiere a una colección de distintos almacenes locales en cada nodo por los cuales se reparten los datos. El programador piensa que está enviando mensajes a un almacén global, pero en realidad [DDS](#DDS) envía mensajes a los almacenes locales apropiados.

Aunque este espacio global es tan característico, no se pierde compatibilidad, ya que el middleware es independiente del lenguaje de programación y la plataforma, posibilitando la interoperabilidad entre distintos sistemas y aplicaciones y una implementación que se adapte a las necesidades sin afectar a las comunicaciones entre dispositivos. Tampoco pierde efectividad, ya que su velocidad, baja latencia, baja sobrecarga en la comunicación, optimización del transporte y capacidad de transmitir millones de mensajes a multitud de receptores instantáneamente, lo convierten en una tecnología ideal para sistemas de alto rendimiento en tiempo real.

Al ser descentralizado, es decir, al no requerir un nodo central, el servicio [DDS](#DDS) es mucho más eficiente y eficaz, ya que los mensajes no deben atravesar un dispositivo intermediario, ejecutando la comunicación punto a punto, y resultando en una mayor velocidad. Además, dispone de un servicio de descubrimiento dinámico, haciendo que las aplicaciones [DDS](#DDS) sean extensibles y escalables. La aplicación no necesita conocer ni configurar los puntos finales de los dispositivos para la comunincación, ya que estos se descubren automáticamente en ejecución, y es capaz de identificar si el punto final se utiliza para publicar datos, para suscribirse o para ambos, el tipo de dato publicado o suscrito, y las características específicas de la comunicación.

[DDS](#DDS) soporta principalmente el modelo de publicación-suscripción, intercambiando información basada en un tema o topic identificado por su nombre. En este modelo, cualquier nodo conectado puede publicar mensajes con el tema especificado o suscribirse a un tema, y [DDS](#DDS) se encarga de que los datos se entreguen a los suscriptores correctos en el momento adecuado mediante comunicación peer-to-peer. Al suscribirse, es posible especificar filtros de tiempo y subconjuntos de datos para obtener solo los requeridos, y tiene la capacidad de detectar cambios para que los suscriptores reciban actualizaciones adecuadas de los datos. Por otro lado, al publicar, es [DDS](#DDS) quien gestiona la complejidad de la transmisión y se encarga de almacenar los datos de manera segura. También ofrece compatibilidad con RPC o llamadas a procedimientos remotos.

El middleware es independiente del transporte, y puede funcionar sobre [UDP](#UDP), [TCP](#TCP) y memoria compartida, entre otros. Entre las características opcionales que ofrece, como el filtrado de grandes datos, se encuentra la gestión de calidad de servicio o [QoS](#QoS), donde se pueden especificar requisitos de rendimiento y confiabilidad, como la latencia, el ancho de banda, la prioridad, la disponibilidad de los datos, el uso de recursos y la sincronización. Además, incluye mecanismos de seguridad que proporcionan autenticación, encriptación, confidencialidad, control de acceso e integridad en la distribución de información.

### Constrained Application Control ([CoAP](#CoAP))

[CoAP](#CoAP) es un protocolo de la capa de aplicación que permite a dispositivos con recursos limitados, como los que se encuentran en una red [IoT](#IoT), comunicarse entre sí. Funciona en un marco cliente-servidor, en el cual el cliente realiza una solicitud a un punto de comunicación del dispositivo servidor, y este responde, permitiendo la interoperabilidad entre los dispositivos uno a uno.

Este protocolo opera sobre el protocolo de transporte [UDP](#UDP), que, a diferencia de [TCP](#TCP), no requiere que los dispositivos establezcan una conexión de datos previa al envío de datos. Esto trae tanto consecuencias positivas como negativas. La consecuencia negativa radica en la poca fiabilidad en la comunicación, ya que el protocolo [UDP](#UDP) no garantiza la entrega de los mensajes, sino que esta garantía se gestiona desde la implementación de [CoAP](#CoAP). Es posible establecer garantía de entrega mediante acuses de recibo ([ACK](#ACK)) y tiempos de espera. La consecuencia positiva del uso de [UDP](#UDP) es la posibilidad de funcionar en redes con pérdidas o inestables, adecuado para sistemas [IoT](#IoT), ya que suelen operar en entornos de red difíciles, y la rapidez en la comunicación, pues no requiere una conexión de datos previa, enviando directamente el mensaje.

Esta comunicación utiliza una arquitectura [REST](#REST)ful, en la cual los datos y las funcionalidades se consideran recursos a los que se accede mediante una interfaz estándar y uniforme. Estos recursos se acceden y se interactúa con ellos mediante métodos [HTTP](#HTTP) estándar (GET, POST, PUT, DELETE, que realizan las funciones "obtener", "crear", "actualizar" y "eliminar" recursos, respectivamente), permitiendo una interoperabilidad sencilla entre distintos tipos de dispositivos y facilitando a los desarrolladores el uso del protocolo. No es necesario que los recursos de la red sean conocidos por el dispositivo que vaya a utilizarlos, ya que [CoAP](#CoAP) implementa un mecanismo de descubrimiento integrado, útil en redes [IoT](#IoT) en las que los dispositivos constantemente se conectan y desconectan. Esta función de descubrimiento trata de consultar un recurso conocido como "núcleo" en la red, el cual provee la lista de los recursos de los dispositivos en la red. Es decir, si un dispositivo [IoT](#IoT) quiere interactuar con los recursos de otro, puede consultar al núcleo y comprobar qué recursos hay disponibles y cómo puede interactuar con ellos.

El intercambio de mensajes [CoAP](#CoAP) entre dispositivos es asíncrono, lo que significa que un dispositivo puede enviar una solicitud a otro y continuar ejecutando otras tareas mientras que la respuesta puede recibirla en cualquier momento. Esto se logra mediante un id en los mensajes, permitiendo al dispositivo relacionar peticiones con respuestas, asegurando un alto nivel de fiabilidad en el intercambio de mensajes. Esta comunicación asíncrona es crucial en redes [IoT](#IoT), ya que los dispositivos pueden no estar siempre conectados o disponibles para responder en el momento de la solicitud.

[CoAP](#CoAP) se basa en el intercambio de mensajes compactos codificados en un formato binario simple. El tamaño de estos mensajes no puede superar al necesario para encapsularlos dentro de un datagrama [IP](#IP), y tienen distintos campos:

- Versión de [CoAP](#CoAP).
- Tipo de mensaje.
- Longitud del Token.
- Código, en formato "c.dd", siendo "c" la clase indicando si es una solicitud, una respuesta satisfactoria, un error del cliente o un error del servidor, y "dd" el detalle.
- ID de mensaje.
- Token, usado para correlacionar solicitudes y respuestas.
- Opciones.
- Payload o carga útil.

Los distintos tipos de mensajes que se pueden transmitir son los siguientes:

- Mensajes confirmables (CON): utilizados cuando se necesita asegurar que el mensaje llegue al destinatario. Contienen un temporizador y un mecanismo de retroceso. Al transmitir una petición CON, se espera recibir un mensaje ACK con el mismo ID de la petición o una respuesta en un mensaje CON y con un ID distinto.
- Mensajes no confirmables (NON): son mensajes menos fiables, usados para enviar información no crítica, que no requieren un acuse de recibo (ACK). En el caso de enviarse una solicitud como un mensaje NON, la respuesta también se recibirá como un mensaje NON (en el caso que el servidor tenga la información necesaria para responder).
- Mensajes de acuse de recibo (ACK): son transmitidos para reconocer que ha llegado un mensaje confirmable específico identificado por su ID de transacción. Estos mensajes pueden tener su propio payload y algunas opciones para detallar la recepción.
- Mensaje de reinicio (RST): cuando al receptor le falta información para procesar una solicitud, transmite un mensaje RST. Esto ocurre cuando el receptor se ha reiniciado y no ha persistido adecuadamente la petición recibida anteriormente, o cuando cancela una transacción.

Además es un protocolo diseñado para utilizar un bajo consumo de recursos en la transferencia, y permite hacer uso del protocolo de seguridad de la capa de transporte (Data Transport Layer Security, [DTLS](#DTLS)) para aumentar la seguridad, además de extender su implementación con funcionalidades adicionales. Por el contrario, es menos maduro que sus alternativas, resultando en una menor cantidad de recursos, guías y herramientas, además de una compatibilidad reducida con otros dispositivos [IoT](#IoT).


https://webbylab.com/blog/mqtt-vs-other-iot-messaging-protocols-detailed-comparison/
https://www.techtarget.com/iotagenda/tip/Top-12-most-commonly-used-IoT-protocols-and-standards
https://build5nines.com/top-iot-messaging-protocols/
https://www.a3logics.com/blog/iot-messaging-protocols/
https://en.wikipedia.org/wiki/Advanced_Message_Queuing_Protocol
https://www.gotoiot.com/pages/articles/amqp_intro/index.html
https://www.emqx.com/en/blog/mqtt-vs-amqp-for-iot-communications#what-is-amqp
http://docs.oasis-open.org/amqp/core/v1.0/os/amqp-core-messaging-v1.0-os.html#section-message-format
https://en.wikipedia.org/wiki/XMPP
https://www.pubnub.com/guides/xmpp/
https://blazeclan.com/blog/xmpp-for-dummies-part-3-stanzas-in-detail/
https://slixmpp.readthedocs.io/en/latest/api/stanza/presence.html
https://slixmpp.readthedocs.io/en/latest/api/stanza/iq.html
https://www.dds-foundation.org/omg-dds-standard/
https://www.utpl.edu.ec/proyectomiddleware/?q=tutorial-dds 
https://www.emqx.com/en/blog/coap-protocol0
https://www.gotoiot.com/pages/articles/coap_intro/index.html
(DOCUMENTO) https://datatracker.ietf.org/doc/html/rfc7252

### Comparación de middleware y protocolos

A partir de la información de los apartados anteriores, se pueden recopilar las diferencias y similitudes en los siguientes puntos:

1. *[MQTT](#MQTT)*:
   - **Descripción corta:** Basado en colas de mensajes y topics.
   - **Patrón de comunicación:** Publicación-suscripción.
   - **Necesita intermediario:** Sí, el broker.
   - **Protocolo de transporte:** [TCP](#TCP).
   - **Ventajas:** Muy utilizado, ligero, eficiente, útil en dispositivos y redes de recursos limitados, soporta distintas calidades de servicio.
   - **Desventajas:** Encriptación y enrutación limitadas, bajo soporte para tipos de datos complejos.
   - **Casos de uso:** Telemetría, mensajería ligera, automatización industrial, monitorización del entorno, hogares inteligentes, soluciones energéticas.

2. *[AMQP](#AMQP)*:
   - **Descripción corta:** Basado en colas de mensajes y exchanges.
   - **Patrón de comunicación:** Publicación-suscripción, directa o fanout.
   - **Necesita intermediario:** Sí, el broker.
   - **Protocolo de transporte:** [TCP](#TCP).
   - **Ventajas:** Alto rendimiento, seguro, ampliamente usado, parecido a [MQTT](#MQTT).
   - **Desventajas:** Alto consumo de recursos, difícil aprendizaje.
   - **Casos de uso:** Servicios financieros, procesamiento de transacciones, envío de datos en tiempo real, comunicación segura entre entidades.

3. *[XMPP](#XMPP)*:
   - **Descripción corta:** Comunicación de datos y presencia mediante mensajes [XML](#XML).
   - **Patrón de comunicación:** Cliente-servidor.
   - **Necesita intermediario:** Sí, el servidor XMPP.
   - **Protocolo de transporte:** [TCP](#TCP).
   - **Ventajas:** Robusto, extensible, muy ampliable de funciones.
   - **Desventajas:** No optimizado para entornos limitados, complejo de implementar.
   - **Casos de uso:** Mensajería instantánea, redes sociales, plataformas de colaboración.

4. *[DDS](#DDS)*:
   - **Descripción corta:** Comunicación sin servidor.
   - **Patrón de comunicación:** Publicación-suscripción.
   - **Necesita intermediario:** No.
   - **Protocolo de transporte:** [TCP](#TCP) y [UDP](#UDP), compatible con otros.
   - **Ventajas:** Alto rendimiento, fácil de escalar, comunicación centrada en datos en tiempo real, soporte de tipos de datos complejos, configurable la calidad de servicio.
   - **Desventajas:** Complejo de implementar, altos recursos de dispositivos y de ancho de banda.
   - **Casos de uso:** Sistemas de tiempo real, aplicaciones de misión crítica, automatización industrial, automoción, gestión de cadenas de suministro, sistemas distribuidos de gran escala.

5. *[CoAP](#CoAP)*:
   - **Descripción corta:** Basada en recursos compartidos y accesibles mediante [REST](#REST).
   - **Patrón de comunicación:** Cliente-servidor.
   - **Necesita intermediario:** No.
   - **Protocolo de transporte:** [UDP](#UDP).
   - **Ventajas:** Eficiente en redes y dispositivos de recursos limitados, soporte nativo para tecnologías web.
   - **Desventajas:** Bajo soporte de clientes concurrentes.
   - **Casos de uso:** Dispositivos de recursos limitados, automatización en hogares.

{
	https://webbylab.com/blog/mqtt-vs-other-iot-messaging-protocols-detailed-comparison/
	https://www.a3logics.com/blog/iot-messaging-protocols/

}


## Espressif y sus dispositivos

Espressif Systems[^espressif:espressifSystems] es una multinacional de semiconductores sin fábrica fundada en 2008, que opera como líder mundial en el ámbito del [IoT](#IoT) y está comprometida en proporcionar a millones de usuarios algunos de los mejores dispositivos y plataformas de software de la industria, junto con una variedad de soluciones [IoT](#IoT) seguras.

[^espressif:espressifSystems]: <https://www.espressif.com/>

La empresa se identifica como una empresa compuesta por especialistas, ingenieros y científicos dedicados al desarrollo de soluciones de vanguardia de bajo consumo que aprovechan la comunicación inalámbrica, el [IoT](#IoT) y la inteligencia artificial de las cosas ([AIoT](#AIoT)). Estas soluciones se caracterizan por su seguridad, robustez, eficiencia energética, versatilidad, asequibilidad y enfoque código abierto.

Con el surgimiento de la inteligencia artificial y la evolución del [IoT](#IoT), la demanda de productos con conectividad inalámbrica segura ha ido creciendo considerablemente, y Espressif Systems ha respondido a este desafío desarrollando soluciones adaptadas a las necesidades del mercado. Espressif emplea los nodos de tecnología avanzada, la informática de bajo consumo, la comunicación inalámbrica, así como la tecnología de malla, para crear conjuntos de chips y módulos de alto rendimiento, que son más inteligentes, adaptables y versátiles.

El compromiso de esta empresa china con el código abierto se refleja en su oferta de una variedad de frameworks y herramientas de desarrollo para construir aplicaciones en diferentes ámbitos, como [IoT](#IoT), audio, reconocimiento facial y asistentes de voz. Las tecnologías y soluciones abiertas de Espressif permiten acercar el [IoT](#IoT) a sus clientes, comerciales y no comerciales, y que desarrolladores de todos los ámbitos puedan utilizarlas a nivel mundial y construir sus propios dispositivos inteligentes y soluciones con una conectividad inalámbrica de rendimiento óptimo y un tiempo de desarrollo reducido.

Los productos de Espressif se utilizan ampliamente en dispositivos de electrónica de consumo, y es conocido por sus populares series de chips, módulos y placas de desarrollo ESP8266 y ESP32, los cuales se analizarán en los siguientes apartados.

{
https://www.espressif.com/en/company/about-espressif
https://www.eurotronix.com/es/fabricantes/espressif
https://www.digikey.es/es/supplier-centers/espressif-systems
}

### ESP8266

El ESP8266 es un [SoC](#SoC) o sistema en un chip diseñado para dispositivos móviles, electrónica portátil y aplicaciones del [IoT](#IoT). Lanzado en agosto de 2014, integra un procesador mononúcleo Tensilica L106 con una arquitectura *Reduced Instruction Set Computer* ([RISC](#RISC)) de 32 bits de bajo consumo y una velocidad de reloj de entre 80 y 160 [MHz](#MHz).

Presenta una arquitectura para el ahorro de energía, permitiendo establecer el chip en modo activo, reposo y reposo profundo, lo cual es útil para que los dispositivos diseñados para alimentarse por batería funcionen durante mucho más tiempo.

En cuanto a memoria, no dispone de una memoria flash para almacenar programas, la cual debe ser proporcionada por el módulo que implemente este chip y puede tener un tamaño máximo de 16 [MiB](#MiB). Integra una [RAM](#RAM) para instrucciones de 32 [KiB](#KiB), una caché de instrucciones 32 [KiB](#KiB), 80 [KiB](#KiB) para almacenar datos del usuario y 16 [KiB](#KiB) para datos del sistema de [ETS](#ETS).

Su bajo voltaje operativo oscila entre 2,5 y 3,6 [V](#V), con una corriente de operación alrededor de los 80 [mA](#mA). Cuenta con la capacidad de funcionar en entornos industriales gracias a su amplio rango de temperatura de operación, que va de -40 y 125 [ºC](#ºC).

Admite distintos tipos de protocolos de comunicación, como [IP](#IP)v4, [TCP](#TCP), [UDP](#UDP) y [HTTP](#HTTP). Es un dispositivo certificado para funcionar por Wi-Fi y compatible con los protocolos 802.11 b/g/n en una frecuencia de 2,4 [GHz](#GHz). Tiene la capacidad de actuar como cliente en redes protegidas por claves [WEP](#WEP), [WPA](#WPA) y [WPA](#WPA)2, además de poder actuar como punto de acceso inalámbrico.

También integra en sus dimensiones compactas 16 pines [GPIO](#GPIO) para conectar dispositivos de entrada y salida, un conversor analógico de 10 bits, conmutadores de antena, un amplificador de potencia y de recepción, un balun de radiofrecuencia y módulos de gestión de potencia.

Este sistema admite varios [IDE](#IDE)s y lenguajes de programación, como C y C++, utilizando Arduino [IDE](#IDE) o PlatformIO; MicroPython, utilizando Mu Editor, Thonny [IDE](#IDE) o Pymakr; y Lua, utilizando LuaLoader.

{
	https://www.espressif.com/en/products/socs/esp8266
	https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf
	https://en.wikipedia.org/wiki/ESP8266
	https://www.luisllamas.es/esp8266/
	https://programarfacil.com/podcast/esp8266-wifi-coste-arduino
	https://randomnerdtutorials.com/micropython-ides-esp32-esp8266/
	https://www.danielmartingonzalez.com/es/usando-lua-en-esp8266-nodemcu-con-lualoader-y-esplorer/
}

### ESP32

El ESP32 es el [SoC](#SoC) sucesor del ESP8266. Igual de apto para electrónica portátil e [IoT](#IoT), comparte muchas características y añade mejoras que lo convierten en un sistema muy superior.

Integra un procesador Tensilica Xtensa LX6 de doble núcleo (o de uno, dependiendo de la variante utilizada) cuya frecuencia de reloj oscila entre los 160 y 240 [MHz](#MHz), que trabaja en conjunto con un coprocesador de ultra baja energía.

La memoria experimenta un significativo aumento respecto a su predecesor, con un total de 520 [KiB](#KiB) de SRAM, 448 [KiB](#KiB) de memoria de solo lectura, 32 [KiB](#KiB) de caché y hasta 4 [MiB](#MiB) de memoria de almacenamiento (dependiendo del modelo).

Este chip, lanzado en septiembre de 2016, añade en comparación con el ESP8266 una mejora de potencia, soporte de Bluetooth 4.2 y [BLE](#BLE), sensor de temperatura, sensor hall, sensor táctil, reloj de tiempo real, más pines [GPIO](#GPIO) (hasta 34) y varios modos de energía.

Además, incorpora arranque seguro, encriptado de la flash y soporte de aceleración por hardware para los algoritmos y protocolos de cifrado y encriptación [AES](#AES), [SHA](#SHA)-2, [RSA](#RSA), [ECC](#ECC) y el generador de números aleatorios.

El ESP32 tiene la posibilidad de funcionar como un sistema autónomo o como parte de un puente e interconexiones, y tiene la capacidad de interactuar con otros sistemas para proveer funcionalidad Wi-Fi y Bluetooth a través de sus interfaces.

Desde el lanzamiento del ESP32 original, han ido apareciendo variantes con distintas capacidades y procesadores, pero gran parte del código del ESP32 es compatible. Estas variantes son:

- ESP32-S2: enfocado en el consumo, integra un procesador mononúcleo LX7, reduce la memoria disponible y no tiene soporte de Bluetooth.
- ESP32-S3: utiliza el mismo procesador que el anterior, contiene más memoria y da soporte a Bluetooth 5 y [BLE](#BLE), enfocado al soporte de inteligencia artificial.
- ESP32-C3: contiene un procesador [RISC](#RISC)-V mononúcleo y admite Bluetooth 5 y [BLE](#BLE), enfocado en la seguridad.
- ESP32-C6: centrado en la conectividad, la principal diferencia con el anterior es el soporte de Bluetooth 5.3, Wi-Fi 6 (802.11ax) y conectividad de radio (802.15.4) compatible con los protocolos Thread, Zigbee y Matter.
- ESP32-C2: incorpora un procesador [RISC](#RISC)-V mononúcleo y admite Bluetooth 5 y [BLE](#BLE). Es un chip de pequeñas dimensiones que mantiene una conectividad robusta y estándares de seguridad.
- ESP32-C5: es la versión más reciente con mayor velocidad de reloj y capacidad de memoria, y es el primero que soporta Wi-Fi 6 a 5 [GHz](#GHz). Su enfoque en la conectividad también proviene de la capacidad de conexión con Bluetooth 5.2.

{
	https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf
	https://www.espressif.com/en/products/socs/esp32
	https://en.wikipedia.org/wiki/ESP32
	https://www.luisllamas.es/esp32/
	https://www.espboards.dev/blog/esp32-soc-options/
}

## ESP-NOW

El [IoT](#IoT) se forma a partir de la conectividad entre objetos, donde surge la necesidad de un protocolo que equilibre las necesidades de latencia, uso de energía, capacidad de transmisión, confiabilidad y seguridad en la transmisión de datos. Son factores determinantes en el futuro desarrollo de esta tecnología, y aparecen como candidatos un gran número de tecnologías y protocolos, destinados tanto para la comunicación en área local, como Wi-Fi, para áreas amplias, como LoRa y LoRaWAN, y para transmisión a corta distancia, como [RFID](#RFID). Recientemente, al mencionado grupo se ha añadido ESP-NOW, el cual, pese a sus limitaciones, tiene características notables y es adecuado para [IoT](#IoT).

ESP-NOW es un protocolo de comunicación inalámbrica diseñado por Espressif para su uso entre sus dispositivos, como los ESP8266 y ESP32. Con el objetivo de sustituir a Wi-Fi y a otras tecnologías, ESP-NOW es capaz de realizar transmisiones de información y control rápidas, estables y con un bajo consumo de recursos de [CPU](#CPU) y memoria flash entre dispositivos inteligentes, sin necesidad de un enrutador.

Se caracteriza por la rapidez de la transmisión, lograda evitando la necesidad de establecer una conexión previa entre dispositivos. Permite a su vez poner a disposición los dispositivos para transmitir datos y recibir órdenes instantáneamente tras el encendido. Además, este protocolo está basado en la capa de enlace de datos y es capaz de omitir las capas de red, transporte, sesión, presentación y aplicación del modelo [OSI](#OSI), reduciendo el consumo de energía (mejorando la autonomía en dispositivos con batería) y el retardo en la recepción y en el procesamiento de mensajes debido a la nula necesidad de cabeceras de paquete o desempaquetadores de cada capa. En redes congestionadas, es una característica beneficiosa, ya que brinda la capacidad de respuestas rápidas que reducen el retraso causado por la pérdida de paquetes. En el modelo utilizado en ESP-NOW en comparación con el modelo [OSI](#OSI) estándar de la figura \ref{espnow:modeloOsiEspNow} se puede observar la ausencia de las 5 capas mencionadas anteriormente. 

![Comparación de las capas del modelo OSI con las del modelo ESP-NOW **TODO: REFERENCIAR**\label{espnow:modeloOsiEspNow}](espnow_osi_model.png){width=88%}

Pese al objetivo de ESP-NOW de reemplazar Wi-Fi, en los dispositivos de Espressif es capaz de coexistir simultáneamente junto a Wi-Fi y Bluetooth. Esto es útil para utilizar un dispositivo como gateway y exportar los datos intercambiados entre ESP-NOW hacia otras redes.

Tiene la capacidad de transmitir datos de manera máquina a máquina o broadcast, y para establecer la comunicación solo se requiere la dirección [MAC](#MAC) del dispositivo de destino y establecer un canal de transmisión. No obstante, dispone de una cantidad limitada de dispositivos con los que se puede emparejar. En general, el número de dispotivos emparejados no puede exceder de 20, y la cantidad de estos con los que se puede establecer una comunicación cifrada es configurable. Por defecto, este valor es 7, y admite un valor máximo de 17. Esta limitación puede ser un inconveniente en caso de necesitar una gran cantidad de dispositivos interconectados, pero una solución sería formar jerarquías de dispositivos.

Para el envío de datos, permite establecer una función de callback que será llamada instantáneamente tras el envío para poder gestionarlo. Esto puede llegar a ser útil debido a los posibles fallos que puedan ocurrir, por ejemplo, si el dispositivo de destino no existe, los canales de transmisión establecidos en ambos dispositivos no son los mismos o la trama de acción se pierde por interferencias. De la misma manera, se puede establecer una función de callback que sea llamada al recibir datos para poder tratarlos. Cabe remarcar que el protocolo no garantiza que se reciban los datos correctamente, pero existe la posibilidad de establecer [ACK](#ACK)s para confirmar la correcta recepción y procesamiento de los datos, además de números de secuencia para afrontar la duplicidad.

ESP-NOW utiliza tramas de acción específicas del proveedor para encapsular y transmitir datos de una longitud máxima de 250 bytes, con un alcance de transmisión de entre 100 y 500 metros, dependiendo de las condiciones atmosféricas, y con una tasa de velocidad de bits de 1 megabit por segundo. Esto es beneficioso para la comunicación a larga distancia debido a su gran alcance en dispositivos al aire libre o incluso separados por paredes o pisos. Sin embargo, su uso puede estar limitado por la pequeña carga útil que puede transmitir, por lo que en otros casos podría ser mejor utilizar otras tecnologías como Wi-Fi. ESP-NOW utiliza tramas de un tamaño entre 43 y 293 bytes, cuyo formato, mostrado en la figura \ref{espnow:frame}, está compuesto por los siguientes campos:

![Formato de una trama ESP-NOW (Fuente: @ESPNOW_Frame)\label{espnow:frame}](espnow_frame.png){width=82%}

- Cabecera [MAC](#MAC), distinta de una cabecera [MAC](#MAC) común debido a su funcionamiento sin conexión.
- Código de categoría, establecido a 127 para indicar la categoría específica del proveedor.
- Identificador de la organización único, que son los 3 primeros bytes de la dirección [MAC](#MAC) aplicada por Espressif.
- Valores aleatorios, utilizados para prevenir ataques de retransmisión.
- Contenido específico del proveedor, que ocupa entre 7 y 257 bytes y contiene los siguientes campos específicos del proveedor:
	- ID del elemento, establecido a 221 para indicar que se trata del elemento específico del proveedor.
	- Longitud total del resto de campos.
	- Identificador de la organización, igual que el mencionado antes, los 3 primeros bytes de la dirección [MAC](#MAC).
	- Tipo, con valor 4 para indicar ESP-NOW.
	- Versión de ESP-NOW.
	- Cuerpo, que contiene los datos de ESP-NOW y puede ocupar entre 0 y 250 bytes.
- Frame Check Sequence, utilizado para verificar la integridad de la información recibida.

Existe la posibilidad de asegurar la transmisión de datos a través de ESP-NOW utilizando algoritmos de encriptación [ECDH](#ECDH) y [AES](#AES) y el método CBC-MAC Protocol (CCMP) que protegen las tramas de acción. El funcionamiento de estos se realiza mediante dos tipos de claves en los dispositivos: una Clave Maestra Principal (PMK) y varias Claves Maestras Locales (LMK) que corresponden a cada dispositivo emparejado. La PMK se utiliza para cifrar la LMK, y la LMK del dispositivo emparejado se utiliza para cifrar la trama de acción específica del proveedor. Esto está limitado a comunicaciónes entre pares, ya que no se admite el cifrado de tramas utilizadas para la multidifusión.

En cuanto a la gestión de dispositivos, puede utilizarse como un protocolo que ayude al aprovisionamiento de datos y configuraciones a dispositivos, depurarlos y actualizar su firmware.

ESP-NOW no necesita ningún procedimiento especial aparte de la implementación para poder utilizarse con fines comerciales. En la actualidad, se encuentra ampliamente utilizado en electrodomésticos inteligentes, iluminación inteligente, control remoto, sensores y otros.

{
	(imagen, fuente): https://www.espressif.com/sites/all/themes/espressif/images/esp-now/model-en-mobile.png
	https://www.espressif.com/en/solutions/low-power-solutions/esp-now
	https://docs.espressif.com/projects/espressif-esp-faq/en/latest/application-solution/esp-now.html
	https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html
	https://emariete.com/esp8266-esp32-espnow/
}

### Comparaciones con otras tecnologías

#### Wi-Fi

"Wi-Fi" es el nombre que otorga la Wi-Fi Alliance a esta tecnología de red inalámbrica basado en los estándares [IEEE](#IEEE) 802.11. Esta tecnología es ampliamente utilizado para enlazar dispositivos en redes [LAN](#LAN) y proveer de acceso a Internet utilizando ondas de radio de 2,4 o 5 [GHz](#GHz) (dependiendo de la versión) para transmitir la información, cumpliendo con la misión de ser una alternativa al envío de datos a través de cables.

En una red Wi-Fi se pueden encontrar una variedad de dispositivos cliente, que son los que aprovechan las características de la red, y dispositivos que distribuyen la red. Estos últimos consisten en routers o enrutadores, que brindan la conexión a Internet a los dispositivos y enrutan los mensajes enviados a través de la red; puntos de acceso, que transmiten la señal inalámbrica y es donde se conectan los dispositivos introduciendo las credenciales de la red; y repetidores, utilizados para extender el área de cobertura de una red. Entre los dispositivos, tanto clientes como los distribuidores de red, se utilizan adaptadores de red inalámbrica, que convierten los datos en una señal de radio y viceversa.

Es una de las tecnologías más utilizadas a nivel mundial, siendo que la mayoría de hogares y establecimientos disponen de una red Wi-Fi, y que los dispositivos que integran esta tecnología son fabricados con un Certificado Wi-Fi otorgado por la Wi-Fi Alliance tras superar las pruebas homologadas de interoperabilidad. Esta popularidad es beneficiosa para el [IoT](#IoT), ya que ofrece una capa de compatibilidad con una amplia gama de dispositivos sin necesidad de antenas, adaptadores de red ni otro tipo de hardware adicional. Además, Wi-Fi no es una tecnología nueva, tiene un sólido legado de interoperabilidad, y permite enviar información entre dispositivos con baja latencia.

Entre sus características adicionales se encuentra la topología flexible, que permite conectar los dispositivos de distintas maneras; la seguridad, ya que es posible tener redes protegidas con contraseñas cifradas mediante distintos protocolos ([WEP](#WEP), [WPA](#WPA) y [WPA](#WPA)2), el bajo coste de instalación, que en comparación con la instalación de una red cableada, resulta más económico; y la capacidad de llegar a donde los cables no pueden llegar.

Existen distintos estándares de Wi-Fi que definen cómo actúa la red, y que cambian cada pocos años trayendo mejoras en el alcance, la velocidad y la conectividad. Por lo general, los dispositivos certificados para un estándar son intercomunicables con los certificados para otro estándar Wi-Fi siempre que compartan la misma banda de frecuencia, por lo que no es una preocupación tener todos los dispositivos con la versión más reciente. Los estándares Wi-Fi se muestran en la tabla \ref{espnow:estandaresWiFi}.

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

: Lista de estándares Wi-Fi *TODO: REFERENCIAR*\label{espnow:estandaresWiFi}

La popularidad de Wi-Fi abarca una gran variedad de dispositivos soportados, como teléfonos inteligentes, ordenadores, televisores inteligentes, impresoras e incluso placas de desarrollo como ESP8266 y ESP32.

{
	https://en.wikipedia.org/wiki/Wi-Fi
	https://es.wikipedia.org/wiki/Wifi
	https://emariete.com/esp8266-esp32-espnow/
	https://www.wi-fi.org/discover-wi-fi/internet-things
	https://www.adslzone.net/reportajes/tecnologia/que-es-wifi-como-funciona/
	https://www.proofpoint.com/es/threat-reference/wifi#:~:text=Wifi%2C%20que%20es%20una%20contracci%C3%B3n,red%20mediante%20frecuencias%20de%20radio.
	
	Fuentes de tabla
	https://www.intel.la/content/www/xl/es/support/articles/000005725/wireless/legacy-intel-wireless-products.html
	https://www.monolitic.com/cual-es-la-mejor-tecnologia-wifi-para-desarrollos-iot/
	https://www.makeuseof.com/tag/understanding-common-wifi-standards-technology-explained/
	https://www.netspotapp.com/es/blog/wifi-standards/
	https://www.xataka.com/nuevo/nuevo-wifi-7-informacion
	https://www.geckoandfly.com/10041/wireless-wifi-802-11-abgn-router-range-and-distance-comparison/
	https://www.business.com/articles/what-is-802-11-ax-wi-fi/

}

#### Bluetooth

Bluetooth es un estándar de tecnología que facilita el intercambio de datos entre dispositivos a través de distancias cortas, con un máximo de 10 metros. 

Desde su introducción en 1998, ha pasado por múltiples revisiones, siendo las más relevantes las de la última década:

- Versión 4.0 hasta 4.2: aumentó la velocidad de transferencia de datos a 24 Mbps y el alcance hasta 100 metros, y añadió soporte al protocolo IPv6. Además, introdujo BLE o Bluetooth Low Energy, una nueva variante de esta tecnología.
- Versión 5.0 hasta 5.2: aumentó la velocidad de transferencia de datos a 50 Mbps y el alcance hasta 200 metros, y realizó mejoras en la transmisión de audio y en el consumo de energía.

Bluetooth Low Energy fue diseñado para operaciones de bajo consumo de energía, capaz de soportar diferentes tipologías de comunicación (punto a punto, difusión y malla), a diferencia del clásico que solo admite punto a punto. Mientras que el Bluetooth clásico se usa para transferir datos y sonido, BLE es capaz de utilizarse para analizar con alta precisión la presencia, distancia y dirección del dispositivo.

Bluetooth utiliza ondas de radio UHF en las bandas ISM sin licencia de 2,4 GHz, y se utiliza como alternativa a las conexiones por cable para intercambiar ficheros y conectar transmisores de audio. Gracias a su bajo consumo de energía, seguridad, capacidad contra interferecias, compatibilidad con varios sistemas operativos y facilidad de implementación, esta tecnología se convierte en una buena opción para la implementación del [IoT](#IoT). Además, tiene la capacidad de agregar capas de cifrado, autenticación y verificación, y de construir redes PAN entre dispositivos al interconectar varios entre sí. Es común encontrarlo en pulseras y relojes inteligentes, teléfonos inteligentes, ordenadores, reproductores de música, altavoces, auriculares, y placas de desarrollo como ESP32.

{
	https://www.bluetooth.com/learn-about-bluetooth/tech-overview/
	https://en.wikipedia.org/wiki/Bluetooth
	https://www.xatakahome.com/curiosidades/bluetooth-su-evolucion-estas-diferencias-distintas-versiones
	https://www.mokosmart.com/es/what-is-bluetooth-iot-and-why-choose-it/
}

#### Más tecnologías y protocolos [IoT](#IoT)

En esta sección se hacen menciones honoríficas a otras tecnologías y protocolos relevantes al [IoT](#IoT), sin entrar en un análisis detallado.

**Zigbee**: es un protocolo basado en la especificación [IEEE](#IEEE) 802.15.4 que permite formar redes PAN sencillas. Estas redes son en malla y están formadas por un nodo coordinador. Zigbee opera en la banda de 2,4 [GHz](#GHz) y se utiliza en proyectos a pequeña escala que requieren una conexión inalámbrica de baja potencia, baja velocidad de transmisión (hasta 250 [Kbps](#Kbps)) y un rango próximo (hasta 10-100 metros) @Zigbee_Wiki.

**Thread**: es una tecnología que utiliza 6LoWPAN y la especificación [IEEE](#IEEE) 802.15.4, por lo que opera en la banda de 2,4 [GHz](#GHz) con una velocidad de hasta 250 [Kbps](#Kbps). Permite crear redes malladas de bajo consumo que comunica de manera encriptada más de 250 dispositivos, los cuales deben ser certificados y creados por empresas miembros del Thread Group @Thread_Wiki @Thread_ERF.

**LoRa**: es una tecnología inalámbrica de conexión punto a punto que emplea tecnología de modulación en radiofrecuencia. Es ideal cuando se necesitan conexiones que cubran largas distancias con dispositivos sin fácil acceso a la corriente eléctrica de red ni cobertura, ya que ofrece un bajo consumo de uso y un largo alcance de 10-20 km, con alta tolerancia a interferencias. Opera en bandas inferiores a 1 [GHz](#GHz) (dependiendo de la región), y transmite un máximo de 255 bytes a velocidades entre 0,3 [Kbps](#Kbps) y 50 [Kbps](#Kbps). Esta tecnología es conocida por ser utilizada en LoRaWAN @LoRa_Catsensors @LoRa_Vencoel.

#### Comparaciones entre Wi-Fi, Bluetooth y ESP-NOW

Es de alta relevancia comparar estas tecnologías y ESP-NOW entre sí, ya que son los más populares en el ámbito del [IoT](#IoT) y son compatibles con las placas ESP32 que incorporan el reciente e innovador ESP-NOW. En particular, ESP32 es compatible con Bluetooth 4.2 y con Wi-Fi b, g y n de 2,4 GHz, por lo que a lo largo de este apartado se comparan estas versiones. Estos tres protocolos son similares en varios aspectos, ya que utilizan ondas de radio para transmitir datos de forma inalámbrica a una amplia gama de dispositivos, de manera rápida y fiable. Esto puede resultar en una decisión compleja para elegir entre los tres, aunque hay escenarios en los que no es necesario elegir, ya que en un ESP32 pueden trabajar en conjunto.

De manera más resumida, estas son las características teóricas que ofrecen los protocolos:

1. *ESP-NOW*:
	- **Alcance**: 220 metros.
	- **Cantidad de dispositivos conectables**: 20 a cada nodo.
	- **Unidad de Transmisión Máxima (MTU)**: 250 bytes.
	- **Velocidad de transmisión**: 1 [Mbps](#Mbps).
	- **Uso**: [IoT](#IoT) y comunicación entre dispositivos de Espressif.
2. *Wi-Fi b/g/n (2,4 [GHz](#GHz))*:
	- **Alcance**: 250 metros.
	- **Cantidad de dispositivos conectables**: depende de la configuración de la red y la asignación de direcciones [IP](#IP).
	- **Unidad de Transmisión Máxima (MTU)**: 1460 bytes, configurado en la librería de red de ESP32.
	- **Velocidad de transmisión**: 54 [Mbps](#Mbps).
	- **Uso**: conexión a internet, acceso a dispositivos e [IoT](#IoT).
3. *Bluetooth 4.2*:
	- **Alcance**: 50 metros.
	- **Cantidad de dispositivos conectables**: 7 a cada nodo.
	- **Unidad de Transmisión Máxima (MTU)**: 251 bytes.
	- **Velocidad de transmisión**: 1 [Mbps](#Mbps).
	- **Uso**: audio, dispositivos personales e [IoT](#IoT).

/*TODO: referenciar*/

Para detallar las comparaciones aplicando los protocolos en escenarios de uso real, se han tomado los datos de distintas pruebas realizadas y detalladas en una publicación de 2021 llevada a cabo por Dania Eridani, Adian Fatchur Rochim y Faiz Noerdiyan Cesara, miembros del Departamento de Ingeniería Informática de la Universidad de Diponegoro[^espnow:informaticaDiponegoro], en Indonesia.

[^espnow:informaticaDiponegoro]: <https://tekkom.ft.undip.ac.id/language/en/home/>

En esta publicación @ESPNOW_WiFi_BT_Comparison se realizaron pruebas de rango, velocidad, latencia, consumo y resistencia a barreras. Para ello, se utilizaron una placa ESP32 Development Board, una ESP32-CAM y una ESP32U, además de una antena externa de 2.4GHz conectada a la última placa mencionada y utilizada en ciertas pruebas.

| Prueba realizada                                | ESP-NOW  | Wi-Fi     | Bluetooth |
| ----------------------------------------------- | :------: | :-------: | :-------: |
| *Rango máximo (metros), más valor es mejor:*    | | | |
| · con antena interna                            | **185**  | 84        | 15        |
| · con antena externa                            | **220**  | 88        | 25        |
| *Velocidad de transmisión, más valor es mejor:* | | | |
| · de 200 bytes ([Kbps](#Kbps))                  | 588      | **2048**  | 938       |
| · del [MTU](#MTU) ([Mbps](#Mbps))               | 0,63     | **24,86** | 0,98      |
| *Latencia ([μs](#μs)), menos valor es mejor:*   | | | |
| · con 100 bytes de datos                        | **1869** | 3435      | 8514      |
| · con 50 bytes de datos                         | **1435** | 3388      | 6460      |
| · con 10 bytes de datos                         | **1133** | 3367      | 6200      |
| · con 1 byte de datos                           | **1059** | 3359      | 6048      |
| *Consumo ([mW](#mW)), menos valor es mejor:*    | | | |
| · solo conectado, como receptor                 | 489      | 214       | **141**   |
| · solo conectado, como emisor                   | 449      | 465       | **212**   |
| · transfiriendo datos, como receptor            | 511      | 477       | **338**   |
| · transfiriendo datos, como emisor              | 1042     | 538       | **441**   |

: Resultados de las pruebas comparativas realizadas entre los protocolos (Fuente: @ESPNOW_WiFi_BT_Comparison)\label{espnow:pruebasComparacionProtocolos}

A partir de los resultados de estas pruebas, mostrados en la Tabla \ref{espnow:rendimientoComparacionProtocolos}, se puede ver que:

- El rango máximo aumenta con el uso de una antena externa en un 18,9%, 4,7% y 66,6% en los protocolos ESP-NOW, Wi-Fi y Bluetooth, respectivamente. Además, ESP-NOW es el protocolo que soporta una mayor distancia entre dos dispositivos interconectados.
- Wi-Fi es la tecnología con mayor capacidad para transmitir datos rápidamente, tanto en la velocidad como en el tamaño de los datos.
- ESP-NOW tiene la menor latencia, 1ms para 1 byte, tres veces menos que Wi-Fi y seis veces menos que Bluetooth, siendo la mejor opción en cuanto a esta propiedad de la conexión. Debido a la baja compatibilidad de dispositivos que admiten ESP-NOW, una buena alternativa sería utilizar Wi-Fi para la transmisión de datos con poco retardo.
- En el consumo, Wi-Fi y ESP-NOW tienen un valor similar al estar conectados como transmisor, mientras que Bluetooth consume menos tanto como transmisor como receptor. En el caso de transmitir datos, ESP-NOW es el que más consume ya que necesita activar internamente Wi-Fi para funcionar. La prueba demuestra que, en el caso de tener limitada la vida útil de un dispositivo con batería, la mejor solución puede ser Bluetooth, aunque hay diversas maneras de mejorar el código que se utilice en la placa ESP32 para mejorar la eficiencia energética, como añadir paradas y suspensión.

Finalmente, tras la prueba de resistencia a barreras, se demostró que las barreras de madera y cristal no afectan gravemente a la señal en comparación con la transmisión al aire libre, que el metal afecta de manera más notoria a decenas de metros de distancia del receptor, y que el Bluetooth sin una antena externa no es capaz de atravesar muros a 10 metros o más de distancia.

![Comparación del rendimiento entre protocolos en distintos aspectos (Fuente: @ESPNOW_WiFi_BT_Comparison)\label{espnow:rendimientoComparacionProtocolos}](espnow_protocols_comparison.png){width=62%}

Las conclusiones a las que se llega en esta publicación se pueden representar en la figura \ref{espnow:rendimientoComparacionProtocolos}, que muestra que:

- La mayor ventaja de Bluetooth se encuentra en el consumo, ya que su rendimiento en el resto de los aspectos es muy deficiente.
- ESP-NOW es el mejor candidato cuando se requieren rangos elevados, una señal de comunicación resistente y mínima latencia en velocidades de datos muy pequeñas, pero su uso consume mucha energía relativamente.
- Wi-Fi es una tecnología muy equilibrada, y destaca por su velocidad.

{
	https://es.wikipedia.org/wiki/Bluetooth_(especificaci%C3%B3n)
https://docs.espressif.com/projects/esp-faq/en/latest/application-solution/esp-now.html
https://www.amarinfotech.com/differences-comparisons-bluetooth-5-vs-4-2.html
https://www.symmetryelectronics.com/blog/bluetooth-5-versus-bluetooth-4-2-what-s-the-difference/
https://docs.arduino.cc/tutorials/nano-esp32/esp-now/
https://github.com/espressif/arduino-esp32/blob/master/libraries/Network/src/NetworkUdp.cpp
https://www.electronicdesign.com/technologies/communications/article/21801788/ble-v42-creating-faster-more-secure-power-efficient-designspart-1

	(documento)https://ieeexplore.ieee.org/document/9573246
	}


## Ejemplo de modelo tradicional publicador-broker-suscriptor con MQTT y ESP32

Tras introducir una serie de conceptos sobre el [IoT](#IoT), en este apartado se detallará el ejemplo visto en el apartado de [Internet de las Cosas](#internet-de-las-cosas), en la figura \ref{iot:ejemploRiegoIoT}, que trata de un sistema de riego por aspersión.

La primera parte consiste en identificar los dispositivos a utilizar. Los sensores y actuadores deben estar conectados a un dispositivo capaz de interactuar con ellos, como puede ser una placa ESP32.

El broker utilizará una comunicación basada en colas para recibir todos los datos, integrando así una implementación del protocolo de mensajería [MQTT](#MQTT), como puede ser Mosquitto, que únicamente se puede llevar a cabo si el broker es un ordenador, como un ordenador portátil o un single board computer. Para este ejemplo, se puede suponer que el broker será una placa Raspberry Pi.

Teniendo las placas ESP32 y la Raspberry Pi con Mosquitto, es necesario establecer la comunicación entre ambos. Una de las opciones a evaluar que sea compatible con ambas placas es Bluetooth, pero no es adecuado para una comunicación a larga distancia, ni para transmitir datos en tiempo casi real debido a su su baja velocidad, y tampoco es compatible con Mosquitto. Por lo tanto, se debe utilizar Wi-Fi para que las placas ESP32 publiquen los datos que generen y se suscriban a las órdenes y configuraciones mediante las colas adecuadas de Mosquitto. En este caso, se deberá desplegar una serie de puntos de acceso y routers para formar una red [LAN](#LAN) o [MAN](#MAN) que dote de Internet a todos los dispositivos.

Finalmente, se configuran las placas ESP32 para que, con la ayuda de alguna librería de código, puedan interactuar con las colas de Mosquitto, y también el broker para poder interactuar con el servidor.

La implementación de este sistema de riego presenta una serie de inconvenientes. En cuanto a inversión de dinero y tiempo, implica el despliegue de numerosos puntos de acceso y routers, así como su configuración y mantenimiento. Además, se debe asegurar una buena señal al aire libre, evaluar la zona donde se instalarán y proveer más baterías en los dispositivos que formen esta red.

Todos los dispositivos están conectados en la misma red, por lo que un tráfico alto de datos o una interrupción en el servicio puede provocar una congestión de la red y un mal funcionamiento de la misma.

Finalmente, en cuanto a seguridad, a todos los dispositivos de esta red se les otorga acceso a Internet, por lo que deben estar preparados para no sufrir un ciberataque que pueda invalidar el sistema por completo y todos los dispositivos conectados. Esto supone una mayor complejidad en el despliegue y mayor mantenimiento para evitar un riesgo significativo en la red.

Aunque la implementación de este sistema de riego se puede realizar de distintas maneras, en este ejemplo se intenta demostrar la complejidad que supone un despliegue limitado por utilizar [MQTT](#MQTT) y ESP32 en la actualidad. Pese a que, de manera independiente, ambos tienen grandes ventajas, su combinación supone una complejidad difícil de evitar.

/*TODO: añadir un nuevo esquema*/

{
	https://www.prometec.net/esp32-mqtt/ (libreria de codigo)
}
