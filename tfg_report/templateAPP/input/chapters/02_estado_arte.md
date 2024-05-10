# Estado del arte

## Internet de las Cosas

Dado que una de las principales motivaciones de este Trabajo de Fin de Grado es el aporte que puede ofrecer a la facilidad de implementación del Internet de las Cosas, es importante conocer el joven concepto que nos rodea en la actualidad.  

El siglo XX dio lugar al desarrollo de una cantidad de inventos que permitieron una revolución y un avance ágil en la sociedad, inventos nacidos de ideas creativas de sus desarrolladores y que en la actualidad son indispensables debido al frecuente uso y la manera en la que facilita la vida humana. Entre estos inventos se encuentra una de las herramientas más importantes y que mejoró la comunicación, el Internet. Nacido en 1969, ha permitido enlazar a personas con personas y tener acceso a información, pero hoy en día, no solo las personas están conectadas a Internet, también millones de objetos cuyas funciones son dependientes de la red.  

*Internet de las Cosas* o *Internet of Things* es un término cuyo origen está disputado. El primer uso de este término data del discurso que realizó en septiembre de 1985 Peter T. Lewis, cofundador de la primera compañía de telefonía móvil de Estados Unidos, Cellular One. En tal discurso realizado en la Conferencia Legislativa Anual de la CBCF en Washington D.C., Lewis comentó de manera acertada "Predigo que no sólo los humanos, sino también las máquinas y otras cosas se comunicarán interactivamente a través de Internet." **(mencionar al podcast)**. Por otro lado, el mismo término fue acuñado en 1999 cuando Kevin Ashton, directivo de Procter & Gamble, tuvo la iniciativa de investigar el uso de etiquetas de identificación por radiofrecuencia (RFID) y otros sensores en los productos de la cadena de suministro, y para presentar el proyecto tuvo que idear un título llamativo para la presentación. Esta presentación le permitió encontrar financiación además de cofundar y dirigir el laboratorio Auto-ID Center del Instituto de Tecnología de Massachusetts, en el cuál construyó la base del Internet de las cosas.  

Es esencial tener una clara comprensión del significado del Internet de las Cosas, en mayor parte por la confusión inherente al término en sí y por las aplicaciones cotidianas de esta tecnología. A primera vista, "Internet de las Cosas" podría dar la impresión de ser un término moderno para referirse a "conectar a Internet algo para controlarlo", una definición bastante simple para alguien que por ejemplo simplemente controla las luces de su hogar desde su teléfono móvil. Es tanta la confusión que no existe una definición formal única, debido a que hay sistemas que implementan [IoT](#IoT) y no cumplen todas las definiciones, por lo tanto, no se ha llegado a un consenso para formalizar una definición única, y a la hora de intentar conocer su significado se encuentran una disparidad de definiciones. Sin embargo, por lo general, podemos entender que el Internet de las Cosas trata de dotar de capacidades de comunicación además de procesamiento, captura y/o análisis de datos a distintos tipos de entes, como dispositivos físicos, objetos, edificaciones, terrenos, sistemas, hardware, software, e incluso contextos y situaciones, ya sea añadiéndoles dispositivos o integrando las capacidades en los propios objetos. Estos entes pueden estar compuestos de sensores, que recopilan datos, o actuadores, que controlan otros objetos, y a través de redes, privadas o públicas, pueden intercambiar información con otros dispositivos, recopilar la información en un mismo dispositivo y transferir órdenes, además que existe la posibilidad de formar una agrupación de dispositivos para identificarlos como un único sistema que trata los datos. Estas redes de conexión de dispositivos [IoT](#IoT) pueden utilizar la información transferida para poder automatizar sus comportamientos, pero el nodo final de la conexión suelen ser las personas, ya que utilizan los objetos como fuentes de información, para a su vez utilizar los datos recibidos como descubrimiento de oportunidades de negocio y nuevos servicios, monitorización y evaluación del estado y el comportamiento de los objetos y el entorno, y la toma de decisiones sobre los propios objetos manipulándolos remotamente y programándolos.

Un ejemplo concreto de la aplicación de Internet de las Cosas es un sistema de riego por aspersión inteligente.
/*TODO: poner esquema de ejemplo simple de sistema de riego, con nodos sensores, actuadores, etc*/



/*TODO: hablar ventajas, desventajas y cosas a tener en cuenta (bateria, limitaciones de computación, etc)*/
/*TODO: hablar de la importancia y el valor de los datos*/
/*TODO: hablar de usos de IoT*/

### Primeros ejemplos de IoT

El primer dispositivo [IoT](#IoT) que se conoce fue una máquina de Coca-Cola conectada a ARPANET a principios de la década de los 80 en la Universidad Carnegie Mellon de Pittsburgh, Pensilvania. Desde los años 70, el departamento de Ciencias de la Computación se encargaba de mantener la máquina de refrescos, que era cargada por alumnos en horarios erráticos y cuyos precios eran los más baratos (unos 10 centavos menos) no solo del campus sino también de la zona de Pittsburgh, lo que provocó una gran popularidad en ventas. A mediados de la misma década, debido a la expansión del departamento, se tuvieron que desplazar las oficinas lejos de la máquina que se encontraba en la tercera planta del edificio, lo que provocaba molestias a los programadores al ir en busca de su dosis de cafeína, ya que al bajar a la máquina y gastar el dinero que tanto les había costado conseguir, se encontraban con que o bien estaba vacía o que la Coca-Cola conseguida estaba recién cargada y, por lo tanto, desagradablemente caliente. Cansados de este problema, un grupo de personas se reunió para idear una solución. Instalaron microinterruptores en la máquina de Coca-Cola para poder detectar cuántas botellas había en cada una de las 6 columnas disponibles. Estos interruptores estaban conectados, a través de una interfaz de red instalada en la máquina, al ordenador principal del departamento, el PDP-10 (denominado CMUA). Para este ordenador, diseñaron un programa, que apoyándose en un servidor programado para registrar la hora de la última transacción de cada columna, mostraba uno de los siguientes datos por cada columna de la máquina de Coca-Cola:  

- "EMPTY", si la columna estaba vacía.

- El tiempo que llevaba la nueva botella cargada, por ejemplo, "1h 3m".

- "COLD", si la columna contenía una botella fría, es decir, que llevaba 3 horas cargada.  

Para completar la idea, permitieron el acceso a esta información desde fuera del CMUA. Modificaron el servidor Finger ya existente en el CMUA, el cual era utilizado para obtener información sobre los usuarios conectados al sistema, para añadirle el usuario "coke", para que cada vez que se hiciese la petición a Finger con dicho usuario se ejecutase el programa de estado de la máquina de Coca-Cola. Debido a que las peticiones Finger formaban parte de los protocolos estándares de ARPANET, se podía descubrir el estado de la máquina de Coca-Cola tanto desde cualquier ordenador conectado en la Universidad Carnegie Mellon como desde cualquier parte del mundo conectada a la red, simplemente utilizando el comando `finger coke@cmua`.  
Esta innovación se mantuvo en pie durante más de una década, pasando por una reescritura del código cuando se tuvo que migrar del PDP-10 al más moderno Unix Vaxen a principios de los 80, hasta que Coca-Cola descontinuó las botellas antiguas y las nuevas no eran compatibles con la máquina de refrescos existente, lo que provocó que fuera sustituida por completo.  

La máquina de Coca-Cola de los 80 inspiró a que en 1992 un estudiante y un miembro del departamento de Ciencias de la Computación de la misma universidad instalasen a la nueva maquina y la de M&M que se encontraba cercana aisladores ópticos caseros para identificar la presencia del producto, y las conectasen a Internet para poder consultar el estado ejecutando un programa llamado "jf" ("junk food", comida basura).  

Incluir imágenes:
- Xerox Alto, ordenador fabricado en 1973, usado en la CMU para ver el estado de la maquina  
- Máquina de cocacola https://engineercom.wpenginepowered.com/wp-content/uploads/2016/02/IIot1.png  
- PDP-10 

Posteriormente apareció otro notable objeto conectado a un Internet más similar al actual pero con menos personas (rondando las 3 millones), y fue una tostadora en 1990. El origen de este objeto ocurrió en la edición de 1989 de Interop, una conferencia anual que reunía a profesionales de las tecnologías de la información, ingenieros de redes, desarrolladores y proveedores de tecnología, en la que se podía poner a prueba la interoperabilidad de dispositivos informáticos, electrónicos y productos relacionados con Internet. En dicha edición, el organizador Dan Lynch retó a John Romkey a poner un dispositivo en línea y presentarlo en la siguiente edición. Romkey aceptó, ya que no desconocía la tecnología de la época que le permitiría conseguir dicho reto. John Romkey fue cocreador de la primera pila de protocolos de Internet TCP/IP, PC/IP del Instituto Tecnológico de Massachusetts (MIT) para MS-DOS en el IBM PC, además de proveer pilas TCP/IP a través de la empresa FTP Software, la cual fundó.  

Por aquella época, Romkey trabajaba en el Protocolo Simple de Gestión de Redes (SNMP), junto a Karl Auerbach y David Bridgham, de Epilogue Technology, y Simon Hackett, de Internode. SNMP es un protocolo sencillo que permite a los usuarios leer y escribir variables en un agente remoto y que hasta ese momento se había utilizado únicamente para gestionar dispositivos como routers, para inspeccionar recuentos de paquetes y tablas de enrutamiento, borrar contadores y habilitar o deshabilitar interfaces de red. John Romkey quería aprovechar la oportunidad para demostrar que, dado que SNMP podía controlar dispositivos físicos, también podría ampliar su alcance para gestionar salas completas que albergaran equipos de red y ordenadores, y consideró que controlar una tostadora sería un buen punto de partida. La tostadora, al ser un electrodoméstico sencillo, si su implementación del protocolo funcionaba y podía demostrarlo, el público podría entender que la automatización es posible y se podría llevar a niveles industriales. También, la implementación de Internet en la tostadora podría plantear problemas de seguridad a tener en cuenta, ya que habría que gestionar quién puede tostar el pan y quién puede consultar los hábitos de uso del electrodoméstico, además de tener el factor ridículo de poner una tostadora en Internet.   

El primer paso que tomaron fue buscar una tostadora fácil de controlar físicamente, ya que la mayoría requería de bajar una palanca para también bajar el pan, algo fácil e intuitivo para el ser humano pero difícil de controlar por ordenadores sin hacer uso de la robótica. Con la ayuda de Two Guys and a Vax, una empresa amiga de Epilogue, descubrieron una tostadora Sunbeam Radiant Control, la cual no necesitaba ninguna palanca. Si la tostadora tiene energía y un pan insertado, el pan se baja automáticamente y se empieza a tostar, y finaliza cuando el pan se ha tostado hasta el punto deseado o se corta la corriente. Ese modelo era ideal para ser controlado por ordenador, ya que era más fácil de controlar la alimentación de energía que llegaba al dispositivo que una palanca mecánica de una tostadora.  
Con la tostadora ideal elegida, el siguiente paso fue construir hardware capaz de controlar la energía. A principios de la década de los 90, la sociedad se encontraba en un entorno pre-web y no existían las placas de desarrollo actuales como Arduino, ni Wi-Fi, y mucho menos dispositivos conectables de manera inalámbrica a través de Wi-Fi, por lo que este paso era obligatorio. El primer intento de John Romkey fue crear un relé simple controlable a través del puerto paralelo de un ordenador portátil, el cual funcionó brevemente, pero terminó tostando el puerto del portátil debido a que el relé consumía más energía de la que el puerto podía suministrar. El segundo intento, mucho más exitoso y resultando en una manera fácil de controlar la tostadora mediante software, fue usar un interruptor de menor consumo conectado directamente al puerto paralelo del portátil para controlar un relé más grande que, a su vez, controlaba la alimentación de la tostadora.  

El último paso fue la implementación del software para controlar la tostadora por Internet, es decir, programar la parte SNMP del proyecto que indicaba cómo de oscuro tostar el pan y el tipo de pan insertado. El lenguaje de SNMP permite especificar que controlar en un agente remoto, ya que cada dispositivo gestionado puede tener su propia base de información de gestión (MIB por sus siglas en inglés). Dentro del MIB se pueden especificar objetos, y por cada uno el tipo de objeto, el acceso permitido, el estado y la descripción, y en el caso de la tostadora, se habían especificado en el código como objetos el fabricante, modelo, los controles de la tostadora para subir y bajar la rebanada (o iniciar y terminar el tostado), cómo de hecha se deseaba la tostada y el tipo de pan. Como ejemplo, la siguiente porción de código controlaba el inicio del tostado:  

```
toasterControl OBJECT-TYPE
	SYNTAX INTEGER {
		up(1),
		down(2)
	}
	ACCESS read-write
	STATUS mandatory
	DESCRIPTION
		“This variable controls the current state of the toaster.
		To begin toasting, set it to down(2).
		To abort toasting (maybe in the event of an emergency), set it to up(2).”
	:: = {toaster 3}
```
(codigo tomado del articulo)  

Gracias a los objetos especificados, se podía identificar qué tostadora se estaba controlando, además de establecer el inicio, el tipo de pan y el nivel de tostado final del pan al modificar los objetos, todo a través del agente SNMP conectado al hardware que controlaba la alimentación de la tostadora, permitiendo un control remoto del electrodoméstico. Por ejemplo, si un usuario a través de SNMP modificaba la variable adecuada para indicar que quiere iniciar la tostadora, la tostadora recibía alimentación e iniciaba el proceso de tostado. La tostadora de Internet fue demostrada finalmente en el expositor de Epilogue en la convención de Interop 1990, mostrando un uso alternativo de SNMP, fuera de la gestión de routers, y aprovechando la ocasión para buscar licenciar su implementación SNMP. Como curiosidad, no se podía realizar la demostración de forma legal, ya que tostar pan se consideraba preparación de alimentos, algo permitido solo al sindicato, y para evitar este problema, Epilogue Technology negoció con el sindicato y acordaron tostar repetidamente la misma rebanada de pan para que el público no se la comiera. Además, en la posterior edición de 1991, el hardware de la tostadora evolucionó para añadir un pequeño brazo robótico de LEGO, también controlado por Internet, capaz de tomar una rebanada de pan e insertarla en la tostadora, consiguiendo automatizar el sistema por completo. En la actualidad, John Romkey aún posee esta tostadora de Internet, la cual sigue activa de vez en cuando en Portland, Oregón.  

- Incluir imágenes tostadora (sacarla de url)


Como último ejemplo, también de la misma época de Internet, está la cafetera del laboratorio de informática de la Universidad de Cambridge. Desde los inicios de la computación, la Universidad de Cambridge ha jugado un papel fundamental, contando incluso los primeros ordenadores útiles de uso general, la EDSAC y la EDSAC 2. Además, ha albergado pioneros en ciencias de la computación, incluyendo al creador de las subrutinas, desarrolladores de los primeros procesadores ARM y de varios lenguajes de programación. Esto da lugar a que, por el entorno y por el talento que se encontraba en el campus, era natural que surgieran proyectos de informática. Uno de estos fue la máquina de café conectada a Internet, cuya primera versión fue creada por Quentin Stafford-Fraser y Paul Jardetzky. En 1991, mientras se implantaba la World Wide Web en el Centro Europeo de Investigación Nuclear (CERN), la cual no tenía la popularidad ni la presencia actual, los autores del objeto eran investigadores en el grupo de sistemas del campus, y se encontraban junto a entre 10 y 13 compañeros trabajando la mayoría en una sala del antiguo laboratorio de informática conocida como la Sala Trojan, en cambio otros estaban dispersos por la universidad. Debido a que eran académicos con recursos limitados, solo disponían de una única máquina de café de goteo-filtro para todos, que se encontraba en el pasillo junto a la salida de la Sala Trojan. Aunque la cafeína era esencial para mantener la investigación en informática (de hecho, por la necesidad las jarras de café no duraban mucho), el café de esta máquina era poco inspirador y considerado horrible, pero tolerable si se podía conseguir recién hecho, algo que pocas personas tenían suerte de disfrutar, como Stafford-Fraser que se sentaba al lado de la máquina, mientras otras personas que trabajaban en plantas distintas tenían que recorrer todo el edificio solo para encontrar los posos en el fondo de la jarra, café de muy mala calidad o descubrir que les tocaba rellenar la máquina. Este problema causó cierta angustia en el grupo, por lo que decidieron solucionarlo mediante la tecnología.  

En el laboratorio se disponía de cámaras de video económicas excedentes resultado de un proyecto, así como de varios racks de ordenadores simples utilizados para pruebas de redes. Así, en noviembre de 1991, en un lluvioso día, prepararon el sistema XCoffee. Primero fijaron una de las cámaras a un soporte de laboratorio, instalándola para que apuntara a la jarra de la cafetera ubicada en el pasillo. Los cables conectados a la cámara se extendieron por debajo del suelo hasta una tarjeta capturadora de fotogramas de vídeo, instalada en un ordenador Acorn Archimedes situado en el rack de la Sala Trojan. El software de este sistema constaba de dos partes: la parte servidor, escrita por Paul Jardetzky, que capturaba imágenes de la cafetera cada pocos segundos y en diversas resoluciones; y la parte cliente, escrita por Quentin Stafford-Fraser, ejecutable por cualquier usuario conectado a través de Ethernet en la misma red local que el servidor, y que mostraba una imagen obtenida del servidor del tamaño de un icono en una ventana en la esquina de la pantalla. Este sistema operaba utilizando el protocolo X Window System, donde XCoffee empleaba llamadas a procedimientos remotos en modo de transferencia asíncrona a través de Ethernet para obtener las imágenes de la cafetera que se mostraban al usuario, con una resolución de 768x576 píxeles y 8 bits de profundidad, en escala de grises y actualizada tres veces por minuto, una configuración no molesta ya que la jarra se llenaba despacio y para distinguir el tono del café bastaba con comprobar como de gris estaba la imagen.  

Teniendo este sistema, los investigadores del departamento, desde la comodidad de sus oficinas, podían comprobar la cafetera, su luz de encendido, el nivel y la oscuridad del café, y si consideraban oportuno bajaban a por su dosis de cafeína, solucionando finalmente el esfuerzo físico de comprobar la cafetera y evitando la angustia emocional de llegar y encontrarla vacía. Esta solución solo ayudaba a quienes estaban conectados a la red informática interna del laboratorio de Cambridge, mientras que a los que no y no tenían la posibilidad de ejecutar el software de la cámara de la cafetera, como el Dr. Martyn Johnson, el problema les seguía afectando. Influenciado por esta limitación y por la evolución de las páginas web, que pasaron en marzo de 1993 de ser páginas simples de texto que solo se les podía cambiar los colores y la fuente, a adquirir la capacidad de incluir imágenes en el código HTML y mostrarlas, junto a Daniel Gordon, ambos crearon la primera webcam de la historia.

El 22 de noviembre de 1993, Gordon y Johnson, tras estudiar las capacidades de la web y analizar el código del servidor, y considerando que la tarea sería relativamente sencilla, tomaron el sistema de XCoffee y lo desplegaron a la World Wide Web. Johson desarrolló un script, cuya primera versión únicamente ocupaba unas 12 líneas de código, que, junto a algunas modificaciones del software original, hacía que, tras recibir una solicitud HTTP, el servidor web desplegado solicitase el fotograma más reciente capturado por la tarjeta capturadora, y generara y sirviese la página que mostraba esta imagen, en otras palabras, una página con una imagen distinta cada vez. Esta implementación sirvió como prueba para el desarrollo de páginas web dinámicas que, en lugar de contener imágenes estáticas, presentaran imágenes que cambiasen constantemente. Además, ampliaron el acceso para poder acceder no solo desde la red local, sino también desde Internet.  

La posibilidad de consultar la cámara directamente desde el navegador web, sin necesidad de ejecutar software ni utilizar protocolos de red especiales, tuvo como efecto secundario, que, aunque no fuese muy útil para personas a varios kilómetros de distancia de la Sala Trojan, todo el mundo podía ver el estado de la cafetera, así ocurrió que cientos de miles de personas han mirado la cafetera, ganando notoriedad internacional y convirtiéndola en la cafetera más famosa del mundo. Esta fama llevó a la instalación de una lámpara apuntando a la jarra para permitir consultar su estado incluso por la noche.  

Tras una década en funcionamiento y habiendo pasado por varias cámaras y cafeteras, el grupo de investigación de encontraba frente a un nuevo desafío. Con el software volviéndose cada vez más difícil de mantener y la necesidad de trasladar el laboratorio a las nuevas instalaciones en el Edificio William Gates, se planteaba la urgencia de pasar página. Este software de investigación demostraba no tener la calidad óptima, como suele ocurrir con otro software del mismo estilo, y a su vez la imposibilidad de migrar el sistema a las nuevas máquinas del laboratorio complicaba aún más la situación. Finalmente, tomaron una decisión que tuvo gran cobertura mediática y no fue apoyada en las protestas nostálgicas de los aficionados a las webcams de todo el mundo: apagar la cámara y la cafetera. El 22 de agosto de 2001, a las 09:54 UTC, se observó en Internet la última imagen capturada por las cámaras que apuntaban a la máquina de café de la Sala Trojan, que muestra los dedos de Daniel Gordon, Martyn Johnson y Quentin Stafford-Fraser pulsando el interruptor de apagado del Acorn Archimedes que había capturado las imágenes durante estos años. En el mismo mes, una de las cuatro o cinco últimas máquinas de café de la Sala Trojan vistas en Internet, la que más tiempo estuvo en servicio, una Krups ProAroma 305, se puso en subasta en Internet a través del portal de subastas y comercio electrónico eBay con el fin de recaudar fondos para las instalaciones de café del nuevo laboratorio. Fue adquirida por 3.350 libras, siendo el mayor postor el sitio web alemán de noticias Der Spiegel. Posteriormente, la cafetera fue restaurada de manera gratuita por los empleados de Krups, y fue encendida de nuevo en la oficina de redacción de la revista. Desde el verano de 2016, la cafetera se encuentra en préstamo permanente en el museo de informática Heinz Nixdorf Museums Forum de Paderborn, Alemania.

### Redes IoT, comunicación entre dispositivos y roles
- Sensores
- Actuadores
- Smart objects
- PAN, WAN, etc




Aunque Internet de las Cosas se mencionase por primera vez a finales del siglo XX, no se comenzó a usar hasta bien entrados los 2010s
*Incluir grafica: https://trends.google.com/trends/explore?date=all&q=%2Fm%2F02vnd10&hl=es* 

Apuntes IoT Tema 1 UCLM Rubén Cantarero  
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


/*TODO: apartados restantes*/


## Espressif y sus dispositivos


Espressif Systems es una empresa líder en el mundo de Internet-de las cosas (IoT). Son un innovador equipo de especialistas en diseño de chip, desarrolladores de software/firmware y comercializadores. Se han comprometido a proporcionar algunos de los mejores dispositivos de IoT y plataformas de software en la industria. También ayudan a sus clientes a construir sus propias soluciones y conectar con otros socios del ecosistema de IoT. Su pasión se encuentra en la creación de chipsets de vanguardia y permitir a sus socios ofrecer excelentes productos. Los productos de Espressif se han implementado principalmente en el mercado de tabletas, cajas OTT, cámaras e IoT.

Espressif Systems es una empresa multinacional pública establecida en 2008, con oficinas en China, República Checa, India, Singapur y Brasil. Cuenta con un equipo apasionado de ingenieros y científicos de todo el mundo, enfocados en desarrollar soluciones AIoT de bajo consumo, Wi-Fi y Bluetooth de vanguardia. Espressif ha creado las populares series de chips, módulos y placas de desarrollo ESP8266, ESP32 y ESP32-S que ofrecen soluciones seguras, robustas y energéticamente eficientes. Al mismo tiempo, mediante la tecnología y las soluciones de código abierto, Espressif tiene como objetivo permitir que los desarrolladores utilicen sus soluciones a nivel mundial y construyan sus propios dispositivos inteligentes conectados. En julio de 2019, Espressif realizó su Oferta Pública Inicial en la Junta de Innovación Sci-Tech (STAR) de la Bolsa de Valores de Shanghai (SSE).



https://www.espressif.com/en/company/about-espressif
https://www.eurotronix.com/es/fabricantes/espressif
https://www.digikey.es/es/supplier-centers/espressif-systems

