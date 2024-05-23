# Estado del arte

## Internet de las Cosas

Dado que una de las principales motivaciones de este Trabajo de Fin de Grado es el aporte que puede ofrecer a la facilidad de implementación del Internet de las Cosas, es importante conocer el joven concepto que nos rodea en la actualidad.  

El siglo XX dio lugar al desarrollo de una cantidad de inventos que permitieron una revolución y un avance ágil en la sociedad, inventos nacidos de ideas creativas de sus desarrolladores y que en la actualidad son indispensables debido al frecuente uso y la manera en la que facilita la vida humana. Entre estos inventos se encuentra una de las herramientas más importantes y que mejoró la comunicación, el Internet. Nacido en 1969, ha permitido enlazar a personas con personas y tener acceso a información, pero hoy en día, no solo las personas están conectadas a Internet, también millones de objetos cuyas funciones son dependientes de la red.  

*Internet de las Cosas* o *Internet of Things* es un término cuyo origen está disputado. El primer uso de este término data del discurso que realizó en septiembre de 1985 Peter T. Lewis, cofundador de la primera compañía de telefonía móvil de Estados Unidos, Cellular One. En tal discurso realizado en la Conferencia Legislativa Anual de la [CBCF](#CBCF) en Washington D.C., Lewis comentó de manera acertada "Predigo que no sólo los humanos, sino también las máquinas y otras cosas se comunicarán interactivamente a través de Internet." **(mencionar al podcast)**. Por otro lado, el mismo término fue acuñado en 1999 cuando Kevin Ashton, directivo de Procter & Gamble, tuvo la iniciativa de investigar el uso de etiquetas de identificación por radiofrecuencia ([RFID](#RFID)) y otros sensores en los productos de la cadena de suministro, y para presentar el proyecto tuvo que idear un título llamativo para la presentación. Esta presentación le permitió encontrar financiación además de cofundar y dirigir el laboratorio Auto-ID Center del Instituto de Tecnología de Massachusetts, en el cuál construyó la base del Internet de las cosas.  

Es esencial tener una clara comprensión del significado del Internet de las Cosas, en mayor parte por la confusión inherente al término en sí y por las aplicaciones cotidianas de esta tecnología. A primera vista, "Internet de las Cosas" podría dar la impresión de ser un término moderno para referirse a "conectar a Internet algo para controlarlo", una definición bastante simple para alguien que por ejemplo simplemente controla las luces de su hogar desde su teléfono móvil. Es tanta la confusión que no existe una definición formal única, debido a que hay sistemas que implementan [IoT](#IoT) y no cumplen todas las definiciones, por lo tanto, no se ha llegado a un consenso para formalizar una definición única, y a la hora de intentar conocer su significado se encuentran una disparidad de definiciones. En 2012, la [ITU](#ITU) (Unión Internacional de Telecomunicaciones) recomendó una aclaración del términio, definiendo el Internet de las Cosas como una infraestructura global que permite ofrecer servicios avanzados a todo tipo de aplicaciones conectando objetos entre sí e interoperando tecnologías de la información y comunicación, aprovechando capacidades de identificación, obtención de datos, procesamiento y comunicación y cumpliendo con requisitos de seguridad y privacidad. Sin embargo, por lo general, podemos entender que el Internet de las Cosas trata de dotar de capacidades de comunicación además de procesamiento, captura y/o análisis de datos a distintos tipos de entes, como dispositivos físicos, objetos, edificaciones, terrenos, sistemas, hardware, software, e incluso contextos y situaciones, ya sea añadiéndoles dispositivos o integrando las capacidades en los propios objetos. Estos entes pueden estar compuestos de sensores, que recopilan datos, o actuadores, que controlan otros objetos, y a través de redes, privadas o públicas, pueden intercambiar información con otros dispositivos, recopilar la información en un mismo dispositivo y transferir órdenes, además que existe la posibilidad de formar una agrupación de dispositivos para identificarlos como un único sistema que trata los datos. Estas redes de conexión de dispositivos [IoT](#IoT) pueden utilizar la información transferida para poder automatizar sus comportamientos, pero el nodo final de la conexión suelen ser las personas, ya que utilizan los objetos como fuentes de información, para a su vez utilizar los datos recibidos como descubrimiento de oportunidades de negocio y nuevos servicios, monitorización y evaluación del estado y el comportamiento de los objetos y el entorno, y la toma de decisiones sobre los propios objetos manipulándolos remotamente y programándolos. Dependiendo del entorno en que se implemente, estos sistemas deben cumplir requisitos de seguridad y privacidad, evitando manipulaciones y accesos indebidos o incluso daños en los propios objetos y en el entorno que los rodea.

Un ejemplo concreto de la aplicación de Internet de las Cosas es un sistema de riego por aspersión inteligente. Como se puede comprobar en la figura **todo: insertar figura**, existe un jardín dividido en zonas, cada una con un dispositivo compuesto por sensores de temperatura y humedad y actuadores que activan y desactivan los aspersores que riegan la vegetación. Estos dispositivos están conectados y se comunican con un único gateway o puerta de enlace, teniendo la capacidad de recibir información de los dispositivos y mandar órdenes a estos. El gateway está comunicado a través de Internet con un servidor compuesto por una base de datos, donde se almacenan los datos históricos y registros, y un servicio que le permite ser controlado desde otro dispositivo conectado a Internet en cualquier sitio y momento. Este último dispositivo, denominado cliente, puede ser un teléfono móvil o un ordenador, y puede utilizarse para ver el estado del jardín y controlar los dispositivos manualmente desde una interfaz. La siguiente arquitectura, abstraída completamente de las limitaciones y los problemas que puede ofrecer su implementación, podrá dar lugar a dos casos de uso:

- El usuario quiere activar los aspersores. El usuario, desde la interfaz el dispositivo cliente como puede ser un botón, enviará la orden de activar los aspersores al servicio, que a su vez se lo enviará al gateway. El gateway enviará una orden compatible a los dispositivos instalados en el jardín, haciendo que los aspersores comiencen a funcionar. Esta secuencia de ejecución será parecida si el usuario desea desactivar los aspersores.
- Los aspersores funcionan cuando la temperatura es muy elevada y la humedad es baja. El usuario previamente, desde la interfaz del cliente, ha establecido que los aspersores funcionen de manera automática cuando, por ejemplo, el ambiente supere una temperatura de 42ºC y la humedad sea considerada baja. Estos parámetros los recibe el servidor y se los pasa al gateway, el cual los recordará. A partir de ese momento, el gateway irá recibiendo de los sensores de cada zona lecturas de temperatura y humedad, y las comparará con los parámetros establecidos. En el caso de que se superen la temperatura y humedad, se activarán los aspersores de la zona. Una vez activados, se mantendrá la lectura de temperatura y humedad, y cuando las lecturas sean inferiores, se desactivarán los aspersores. Además, con cada activación de los aspersores, el gateway notificará al servicio, que a su vez notifica al usuario, especificando la zona activada.

/*TODO: 
Dibujar una figura con 3 zonas:
- Jardin con sensores y aspersores
- Gateway, al que se conecta el jardin, y conectada a servicio internet y a bbdd
- Movil del usuario, app conectado a servicio internet
*/

Cabe recalcar que el mencionado ejemplo puede volverse más complejo, por ejemplo añadiendo comprobaciones de previsión meteorológica en los próximos días, sensores de luz, control del caudal del agua, pero igualmente cumple con los requisitos para ser un sistema que implementa el Internet de las Cosas, ya que dota a un jardín de capacidad de comunicación, captura y análisis de datos, y se comunica con otros dispositivos y con personas para informar del estado y recibir órdenes.


/*TODO: hablar ventajas, desventajas y cosas a tener en cuenta (bateria, limitaciones de computación, etc)*/
/*TODO: hablar de la importancia y el valor de los datos*/
/*TODO: hablar de usos de IoT*/

### Primeros ejemplos de IoT

El primer dispositivo [IoT](#IoT) que se conoce fue una máquina de Coca-Cola conectada a [ARPANET](#ARPANET) a principios de la década de los 80 en la Universidad Carnegie Mellon de Pittsburgh, Pensilvania. Desde los años 70, el departamento de Ciencias de la Computación se encargaba de mantener la máquina de refrescos, que era cargada por alumnos en horarios erráticos y cuyos precios eran los más baratos (unos 10 centavos menos) no solo del campus sino también de la zona de Pittsburgh, lo que provocó una gran popularidad en ventas. A mediados de la misma década, debido a la expansión del departamento, se tuvieron que desplazar las oficinas lejos de la máquina que se encontraba en la tercera planta del edificio, lo que provocaba molestias a los programadores al ir en busca de su dosis de cafeína, ya que al bajar a la máquina y gastar el dinero que tanto les había costado conseguir, se encontraban con que o bien estaba vacía o que la Coca-Cola conseguida estaba recién cargada y, por lo tanto, desagradablemente caliente. Cansados de este problema, un grupo de personas se reunió para idear una solución. Instalaron microinterruptores en la máquina de Coca-Cola para poder detectar cuántas botellas había en cada una de las 6 columnas disponibles. Estos interruptores estaban conectados, a través de una interfaz de red instalada en la máquina, al ordenador principal del departamento, el PDP-10 (denominado CMUA). Para este ordenador, diseñaron un programa, que apoyándose en un servidor programado para registrar la hora de la última transacción de cada columna, mostraba uno de los siguientes datos por cada columna de la máquina de Coca-Cola:  

- "EMPTY", si la columna estaba vacía.

- El tiempo que llevaba la nueva botella cargada, por ejemplo, "1h 3m".

- "COLD", si la columna contenía una botella fría, es decir, que llevaba 3 horas cargada.  

Para completar la idea, permitieron el acceso a esta información desde fuera del CMUA. Modificaron el servidor Finger ya existente en el CMUA, el cual era utilizado para obtener información sobre los usuarios conectados al sistema, para añadirle el usuario "coke", para que cada vez que se hiciese la petición a Finger con dicho usuario se ejecutase el programa de estado de la máquina de Coca-Cola. Debido a que las peticiones Finger formaban parte de los protocolos estándares de [ARPANET](#ARPANET), se podía descubrir el estado de la máquina de Coca-Cola tanto desde cualquier ordenador conectado en la Universidad Carnegie Mellon como desde cualquier parte del mundo conectada a la red, simplemente utilizando el comando `finger coke@cmua`.  
Esta innovación se mantuvo en pie durante más de una década, pasando por una reescritura del código cuando se tuvo que migrar del PDP-10 al más moderno Unix Vaxen a principios de los 80, hasta que Coca-Cola descontinuó las botellas antiguas y las nuevas no eran compatibles con la máquina de refrescos existente, lo que provocó que fuera sustituida por completo.  

La máquina de Coca-Cola de los 80 inspiró a que en 1992 un estudiante y un miembro del departamento de Ciencias de la Computación de la misma universidad instalasen a la nueva maquina y la de M&M que se encontraba cercana aisladores ópticos caseros para identificar la presencia del producto, y las conectasen a Internet para poder consultar el estado ejecutando un programa llamado "jf" ("junk food", comida basura).  

Incluir imágenes:
- Xerox Alto, ordenador fabricado en 1973, usado en la CMU para ver el estado de la maquina  
- Máquina de cocacola https://engineercom.wpenginepowered.com/wp-content/uploads/2016/02/IIot1.png  
- PDP-10 

Posteriormente apareció otro notable objeto conectado a un Internet más similar al actual pero con menos personas (rondando las 3 millones), y fue una tostadora en 1990. El origen de este objeto ocurrió en la edición de 1989 de Interop, una conferencia anual que reunía a profesionales de las tecnologías de la información, ingenieros de redes, desarrolladores y proveedores de tecnología, en la que se podía poner a prueba la interoperabilidad de dispositivos informáticos, electrónicos y productos relacionados con Internet. En dicha edición, el organizador Dan Lynch retó a John Romkey a poner un dispositivo en línea y presentarlo en la siguiente edición. Romkey aceptó, ya que no desconocía la tecnología de la época que le permitiría conseguir dicho reto. John Romkey fue cocreador de la primera pila de protocolos de Internet TCP/IP, PC/IP del Instituto Tecnológico de Massachusetts (MIT) para MS-DOS en el IBM PC, además de proveer pilas TCP/IP a través de la empresa FTP Software, la cual fundó.  

Por aquella época, Romkey trabajaba en el Protocolo Simple de Gestión de Redes ([SNMP](#SNMP)), junto a Karl Auerbach y David Bridgham, de Epilogue Technology, y Simon Hackett, de Internode. [SNMP](#SNMP) es un protocolo sencillo que permite a los usuarios leer y escribir variables en un agente remoto y que hasta ese momento se había utilizado únicamente para gestionar dispositivos como routers, para inspeccionar recuentos de paquetes y tablas de enrutamiento, borrar contadores y habilitar o deshabilitar interfaces de red. John Romkey quería aprovechar la oportunidad para demostrar que, dado que [SNMP](#SNMP) podía controlar dispositivos físicos, también podría ampliar su alcance para gestionar salas completas que albergaran equipos de red y ordenadores, y consideró que controlar una tostadora sería un buen punto de partida. La tostadora, al ser un electrodoméstico sencillo, si su implementación del protocolo funcionaba y podía demostrarlo, el público podría entender que la automatización es posible y se podría llevar a niveles industriales. También, la implementación de Internet en la tostadora podría plantear problemas de seguridad a tener en cuenta, ya que habría que gestionar quién puede tostar el pan y quién puede consultar los hábitos de uso del electrodoméstico, además de tener el factor ridículo de poner una tostadora en Internet.  

El primer paso que tomaron fue buscar una tostadora fácil de controlar físicamente, ya que la mayoría requería de bajar una palanca para también bajar el pan, algo fácil e intuitivo para el ser humano pero difícil de controlar por ordenadores sin hacer uso de la robótica. Con la ayuda de Two Guys and a Vax, una empresa amiga de Epilogue, descubrieron una tostadora Sunbeam Radiant Control, la cual no necesitaba ninguna palanca. Si la tostadora tiene energía y un pan insertado, el pan se baja automáticamente y se empieza a tostar, y finaliza cuando el pan se ha tostado hasta el punto deseado o se corta la corriente. Ese modelo era ideal para ser controlado por ordenador, ya que era más fácil de controlar la alimentación de energía que llegaba al dispositivo que una palanca mecánica de una tostadora.  
Con la tostadora ideal elegida, el siguiente paso fue construir hardware capaz de controlar la energía. A principios de la década de los 90, la sociedad se encontraba en un entorno pre-web y no existían las placas de desarrollo actuales como Arduino, ni Wi-Fi, y mucho menos dispositivos conectables de manera inalámbrica a través de Wi-Fi, por lo que este paso era obligatorio. El primer intento de John Romkey fue crear un relé simple controlable a través del puerto paralelo de un ordenador portátil, el cual funcionó brevemente, pero terminó tostando el puerto del portátil debido a que el relé consumía más energía de la que el puerto podía suministrar. El segundo intento, mucho más exitoso y resultando en una manera fácil de controlar la tostadora mediante software, fue usar un interruptor de menor consumo conectado directamente al puerto paralelo del portátil para controlar un relé más grande que, a su vez, controlaba la alimentación de la tostadora.  

El último paso fue la implementación del software para controlar la tostadora por Internet, es decir, programar la parte [SNMP](#SNMP) del proyecto que indicaba cómo de oscuro tostar el pan y el tipo de pan insertado. El lenguaje de [SNMP](#SNMP) permite especificar que controlar en un agente remoto, ya que cada dispositivo gestionado puede tener su propia base de información gestionada ([MIB](#MIB) por sus siglas en inglés). Dentro del [MIB](#MIB) se pueden especificar objetos, y por cada uno el tipo de objeto, el acceso permitido, el estado y la descripción, y en el caso de la tostadora, se habían especificado en el código como objetos el fabricante, modelo, los controles de la tostadora para subir y bajar la rebanada (o iniciar y terminar el tostado), cómo de hecha se deseaba la tostada y el tipo de pan. Como ejemplo, la siguiente porción de código controlaba el inicio del tostado:  

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

Gracias a los objetos especificados, se podía identificar qué tostadora se estaba controlando, además de establecer el inicio, el tipo de pan y el nivel de tostado final del pan al modificar los objetos, todo a través del agente [SNMP](#SNMP) conectado al hardware que controlaba la alimentación de la tostadora, permitiendo un control remoto del electrodoméstico. Por ejemplo, si un usuario a través de [SNMP](#SNMP) modificaba la variable adecuada para indicar que quiere iniciar la tostadora, la tostadora recibía alimentación e iniciaba el proceso de tostado. La tostadora de Internet fue demostrada finalmente en el expositor de Epilogue en la convención de Interop 1990, mostrando un uso alternativo de [SNMP](#SNMP), fuera de la gestión de routers, y aprovechando la ocasión para buscar licenciar su implementación [SNMP](#SNMP). Como curiosidad, no se podía realizar la demostración de forma legal, ya que tostar pan se consideraba preparación de alimentos, algo permitido solo al sindicato, y para evitar este problema, Epilogue Technology negoció con el sindicato y acordaron tostar repetidamente la misma rebanada de pan para que el público no se la comiera. Además, en la posterior edición de 1991, el hardware de la tostadora evolucionó para añadir un pequeño brazo robótico de LEGO, también controlado por Internet, capaz de tomar una rebanada de pan e insertarla en la tostadora, consiguiendo automatizar el sistema por completo. En la actualidad, John Romkey aún posee esta tostadora de Internet, la cual sigue activa de vez en cuando en Portland, Oregón.  

- Incluir imágenes tostadora (sacarla de url)


Como último ejemplo, también de la misma época de Internet, está la cafetera del laboratorio de informática de la Universidad de Cambridge. Desde los inicios de la computación, la Universidad de Cambridge ha jugado un papel fundamental, contando incluso los primeros ordenadores útiles de uso general, la EDSAC y la EDSAC 2. Además, ha albergado pioneros en ciencias de la computación, incluyendo al creador de las subrutinas, desarrolladores de los primeros procesadores ARM y de varios lenguajes de programación. Esto da lugar a que, por el entorno y por el talento que se encontraba en el campus, era natural que surgieran proyectos de informática. Uno de estos fue la máquina de café conectada a Internet, cuya primera versión fue creada por Quentin Stafford-Fraser y Paul Jardetzky. En 1991, mientras se implantaba la World Wide Web en el Centro Europeo de Investigación Nuclear (CERN), la cual no tenía la popularidad ni la presencia actual, los autores del objeto eran investigadores en el grupo de sistemas del campus, y se encontraban junto a entre 10 y 13 compañeros trabajando la mayoría en una sala del antiguo laboratorio de informática conocida como la Sala Trojan, en cambio otros estaban dispersos por la universidad. Debido a que eran académicos con recursos limitados, solo disponían de una única máquina de café de goteo-filtro para todos, que se encontraba en el pasillo junto a la salida de la Sala Trojan. Aunque la cafeína era esencial para mantener la investigación en informática (de hecho, por la necesidad las jarras de café no duraban mucho), el café de esta máquina era poco inspirador y considerado horrible, pero tolerable si se podía conseguir recién hecho, algo que pocas personas tenían suerte de disfrutar, como Stafford-Fraser que se sentaba al lado de la máquina, mientras otras personas que trabajaban en plantas distintas tenían que recorrer todo el edificio solo para encontrar los posos en el fondo de la jarra, café de muy mala calidad o descubrir que les tocaba rellenar la máquina. Este problema causó cierta angustia en el grupo, por lo que decidieron solucionarlo mediante la tecnología.  

En el laboratorio se disponía de cámaras de video económicas excedentes resultado de un proyecto, así como de varios racks de ordenadores simples utilizados para pruebas de redes. Así, en noviembre de 1991, en un lluvioso día, prepararon el sistema XCoffee. Primero fijaron una de las cámaras a un soporte de laboratorio, instalándola para que apuntara a la jarra de la cafetera ubicada en el pasillo. Los cables conectados a la cámara se extendieron por debajo del suelo hasta una tarjeta capturadora de fotogramas de vídeo, instalada en un ordenador Acorn Archimedes situado en el rack de la Sala Trojan. El software de este sistema constaba de dos partes: la parte servidor, escrita por Paul Jardetzky, que capturaba imágenes de la cafetera cada pocos segundos y en diversas resoluciones; y la parte cliente, escrita por Quentin Stafford-Fraser, ejecutable por cualquier usuario conectado a través de Ethernet en la misma red local que el servidor, y que mostraba una imagen obtenida del servidor del tamaño de un icono en una ventana en la esquina de la pantalla. Este sistema operaba utilizando el protocolo X Window System, donde XCoffee empleaba llamadas a procedimientos remotos en modo de transferencia asíncrona a través de Ethernet para obtener las imágenes de la cafetera que se mostraban al usuario, con una resolución de 768x576 píxeles y 8 bits de profundidad, en escala de grises y actualizada tres veces por minuto, una configuración no molesta ya que la jarra se llenaba despacio y para distinguir el tono del café bastaba con comprobar como de gris estaba la imagen.  

Teniendo este sistema, los investigadores del departamento, desde la comodidad de sus oficinas, podían comprobar la cafetera, su luz de encendido, el nivel y la oscuridad del café, y si consideraban oportuno bajaban a por su dosis de cafeína, solucionando finalmente el esfuerzo físico de comprobar la cafetera y evitando la angustia emocional de llegar y encontrarla vacía. Esta solución solo ayudaba a quienes estaban conectados a la red informática interna del laboratorio de Cambridge, mientras que a los que no y no tenían la posibilidad de ejecutar el software de la cámara de la cafetera, como el Dr. Martyn Johnson, el problema les seguía afectando. Influenciado por esta limitación y por la evolución de las páginas web, que pasaron en marzo de 1993 de ser páginas simples de texto que solo se les podía cambiar los colores y la fuente, a adquirir la capacidad de incluir imágenes en el código [HTML](#HTML) y mostrarlas, junto a Daniel Gordon, ambos crearon la primera webcam de la historia.

El 22 de noviembre de 1993, Gordon y Johnson, tras estudiar las capacidades de la web y analizar el código del servidor, y considerando que la tarea sería relativamente sencilla, tomaron el sistema de XCoffee y lo desplegaron a la World Wide Web. Johson desarrolló un script, cuya primera versión únicamente ocupaba unas 12 líneas de código, que, junto a algunas modificaciones del software original, hacía que, tras recibir una solicitud [HTTP](#HTTP), el servidor web desplegado solicitase el fotograma más reciente capturado por la tarjeta capturadora, y generara y sirviese la página que mostraba esta imagen, en otras palabras, una página con una imagen distinta cada vez. Esta implementación sirvió como prueba para el desarrollo de páginas web dinámicas que, en lugar de contener imágenes estáticas, presentaran imágenes que cambiasen constantemente. Además, ampliaron el acceso para poder acceder no solo desde la red local, sino también desde Internet.  

La posibilidad de consultar la cámara directamente desde el navegador web, sin necesidad de ejecutar software ni utilizar protocolos de red especiales, tuvo como efecto secundario, que, aunque no fuese muy útil para personas a varios kilómetros de distancia de la Sala Trojan, todo el mundo podía ver el estado de la cafetera, así ocurrió que cientos de miles de personas han mirado la cafetera, ganando notoriedad internacional y convirtiéndola en la cafetera más famosa del mundo. Esta fama llevó a la instalación de una lámpara apuntando a la jarra para permitir consultar su estado incluso por la noche.  

Tras una década en funcionamiento y habiendo pasado por varias cámaras y cafeteras, el grupo de investigación de encontraba frente a un nuevo desafío. Con el software volviéndose cada vez más difícil de mantener y la necesidad de trasladar el laboratorio a las nuevas instalaciones en el Edificio William Gates, se planteaba la urgencia de pasar página. Este software de investigación demostraba no tener la calidad óptima, como suele ocurrir con otro software del mismo estilo, y a su vez la imposibilidad de migrar el sistema a las nuevas máquinas del laboratorio complicaba aún más la situación. Finalmente, tomaron una decisión que tuvo gran cobertura mediática y no fue apoyada en las protestas nostálgicas de los aficionados a las webcams de todo el mundo: apagar la cámara y la cafetera. El 22 de agosto de 2001, a las 09:54 UTC, se observó en Internet la última imagen capturada por las cámaras que apuntaban a la máquina de café de la Sala Trojan, que muestra los dedos de Daniel Gordon, Martyn Johnson y Quentin Stafford-Fraser pulsando el interruptor de apagado del Acorn Archimedes que había capturado las imágenes durante estos años. En el mismo mes, una de las cuatro o cinco últimas máquinas de café de la Sala Trojan vistas en Internet, la que más tiempo estuvo en servicio, una Krups ProAroma 305, se puso en subasta en Internet a través del portal de subastas y comercio electrónico eBay con el fin de recaudar fondos para las instalaciones de café del nuevo laboratorio. Fue adquirida por 3.350 libras, siendo el mayor postor el sitio web alemán de noticias Der Spiegel. Posteriormente, la cafetera fue restaurada de manera gratuita por los empleados de Krups, y fue encendida de nuevo en la oficina de redacción de la revista. Desde el verano de 2016, la cafetera se encuentra en préstamo permanente en el museo de informática Heinz Nixdorf Museums Forum de Paderborn, Alemania.

### Redes IoT, comunicación entre dispositivos y roles
- Sensores
- Actuadores
- Smart objects
- PAN, WAN, etc




Aunque Internet de las Cosas se mencionase por primera vez a finales del siglo XX, no se comenzó a usar hasta bien entrados los 2010s
*Incluir grafica: https://trends.google.com/trends/explore?date=all&q=%2Fm%2F02vnd10&hl=es* 

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


/*TODO: apartados restantes*/


## Protocolos de mensajería usados en IoT

El uso más común de [IoT](#IoT) es desplegar una arquitectura compuesta por varios dispositivos [IoT](#IoT). En mayor parte, estos dispositivos se designarán simplemente como dispositivos [IoT](#IoT), ya sean sensores o actuadores, mientras que habrá pocos dispositivos (al menos uno) con el rol de centro de mensajería. Dependiendo del uso que se le dé a la arquitectura, estos objetos se comunicarán, y dependiendo de quién sea el emisor y el receptor, dan lugar a estos escenarios:

- Un mensaje ha llegado al centro de mensajería [IoT](#IoT). Este mensaje es procesado y se actúa en consecuencia, por ejemplo, enviando la información necesaria a ciertos dispositivos IoT o almacenándola a una base de datos.
- Un dispositivo [IoT](#IoT) ha generado datos. Estos datos son procesados y luego enviados al centro de mensajería.
- Un dispositivo [IoT](#IoT) ha recibido datos del centro de mensajería. Estos datos son procesados y se actúa en consecuencia.

Estos dispositivos, por sí solos, no son capaces de intercambiar esos grandes volúmenes de datos que tratan. Por ello, tras escoger una tecnología para conectar los dispositivos entre sí, es esencial en el desarrollo de aplicaciones IoT disponer de un protocolo de mensajería.

Un protocolo de comunicación permite que los dispositivos se comuniquen y transmitan mensajes entre los dispositivos [IoT](#IoT) y el centro de mensajería. Además, proporciona cierta fiabilidad a la comunicación, ya que permite que los mensajes lleguen y sus datos sean entendidos y procesados correctamente. Esta comunicación ocurre sobre [TCP](#TCP), o incluso sobre abstracciones de mayor nivel como [HTTPS](#HTTPS).

La elección del protocolo se basa en cómo se adecua al escenario en el que se quiere implementar, considerando requisitos a tener en cuenta como la ubicación, las limitaciones físicas, el consumo, la batería y el coste. Por lo general, no cualquier protocolo de comunicación es apropiado. Los protocolos que se mencionan en este apartado se adecuan a la mayoría de escenarios IoT debido a su rapidez y su fácil implementación, y es posible escoger aquel que se adapte mejor a los requisitos.

### MQTT
El protocolo Message Queue Telemetry Transport es uno de los más populares en el ámbito del Internet de las Cosas. Diseñado para ser ligero y adecuado para redes con ancho de banda limitado y dispositivos con pocos recursos, este estándar del comité técnico [OASIS](#OASIS) permite el transporte bidireccional de mensajes con datos entre múltiples dispositivos.

[MQTT](#MQTT) utiliza el patrón de comunicación publicación-suscripción. En este patrón, los publicadores categorizan los mensajes, y los suscriptores recibirán mensajes de las categorías de su interés, a diferencia de la comunicación tradicional en la que los publicadores envían los mensajes directamente a los suscriptores. En el caso de [MQTT](#MQTT), el patrón está basado en temas o topics, siendo posible que los suscriptores se interesen por uno o varios. Este patrón permite utilizar una red única para transmitir datos entre dispositivos y servidores, habilitando el control remoto de una gran cantidad de dispositivos a través de Internet.

En una red [MQTT](#MQTT), se definen dos roles principales: el broker o intermediario de mensajes y los clientes. El broker [MQTT](#MQTT) es un servidor comparable a una oficina de correos, que recibe todos los mensajes publicados por los clientes y los dirige a los clientes de destino apropiados. Por otra parte, un cliente es cualquier dispositivo conectado al broker a través de una red, y puede producir y recibir datos al publicar y suscribirse respectivamente. Este mecanismo es útil para compartir datos, controlar y gestionar dispositivos. Por ejemplo, un dispositivo cliente puede publicar datos de sensores y además recibir información de configuración o comandos de control. La enrutación de mensajes que realizada por el broker proporciona transparencia y desacoplamiento en el espacio, ya que el publicador no necesita conocer ni la cantidad ni las direcciones de los suscriptores, y los suscriptores no necesitan conocer al publicador, ambos interactúan únicamente con el broker.

Los mensajes están organizados en una jerarquía de temas o topics. Al publicar un mensaje, se publica en un tema específico, y en el caso de querer publicar a varios se deben realizar varias publicaciones. En cambio, un suscriptor puede suscribirse a un tema específico o a varios simultáneamente y recibirá una copia de todos los mensajes compatibles con los temas suscritos. La manera de indicar varios temas es mediante el uso de los siguientes caracteres comodín:

- Comodín de un nivel '+': coincide con un nivel de tema y puede utilizarse más de una vez en la especificación del tema.
- Comodín de varios niveles '#': coincide con cualquier número de niveles y debe ser el último carácter en la especificación del tema.

Como ejemplo de uso de los temas, cuando se publica un mensaje en el tema "edificioA/sensor1/temperatura", el broker enviará una copia del mensaje los clientes suscritos a los temas "edificioA/sensor1/temperatura", "edificioA/+/temperatura" y "edificioA/#", pero no a un cliente suscrito a "edificioB" o a "edificioA/+/humedad".

La transmisión de mensajes se realiza de forma asíncrona, sin detener la ejecución de ambos componentes a la hora de publicar o recibir, y se puede realizar una comunicación uno a muchos (un publicador y varios suscriptores), muchos a uno (varios publicadores y un suscriptor), uno a uno (un publicador y un suscriptor, menos común) y muchos a muchos (varios publicadores y varios suscriptores).

En el caso de que el broker reciba una publicación de un tema en el cual no hay nadie suscrito, el broker por defecto descarta el mensaje. Es posible activar la retención de mensajes configurando un campo en el mensaje para evitar esto, consiguiendo así que el broker almacene el último mensaje retenido de cada tema y lo distribuya inmediatamente a cualquier nuevo cliente suscrito, permitiendo así que el suscriptor reciba el valor más reciente en lugar de esperar a una nueva publicación, y además añadiendo soporte a una comunicación desacoplada en el tiempo, donde publicadores y suscriptores no necesitan estar conectados simultáneamente.

El protocolo soporta un mecanismo de limpieza de sesión. Por defecto, un cliente tras desconectarse y volverse a conectar no recibe los mensajes publicados durante su desconexión y el broker olvida las suscripciones del mismo cliente. Pero al desactivar dicho mecanismo, el broker mantiene tanto las relaciones de suscripción como los mensajes offline, enviándolos al cliente al momento de reconectarse, lo cual es útil para dispositivos que se conectan y desconectan constantemente, común en redes IoT. Además, [MQTT](#MQTT) enfrenta la inestabilidad de la red con un mecanismo Keep Alive que, al transcurrir un prolongado periodo sin interacción, ocurre un ping entre el cliente y el broker para evitar la desconexión. Si el ping falla y se identifica el cliente como desconectado, aplicará un mecanismo Last Will, que publica un último mensaje a un tema específico debido a una desconexión anormal, en el caso de estar configurado.

[MQTT](#MQTT) dispone de 14 tipos de mensajes diferentes, la mayoría utilizados para mecanismos internos y flujos de mensajes:

- CONNECT: establece una conexión con el broker, y si está configurado, se debe proporcionar un usuario y contraseña.
- DISCONNECT: finaliza una sesión [MQTT](#MQTT) enviando este mensaje para cerrar la conexión. Esta desconexión se denomina "graceful shutdown" o "apagado elegante", porque está la posibilidad de conectarse al broker con la misma sesión y reanudar el progreso.
- PINGREQ/PINGRESP: una operación de ping utilizada para saber si está viva la conexión y mantenerla.
- PUBLISH: contiene un mensaje para publicarlo en un tema específico.
- SUBSCRIBE: utilizado por los clientes para suscribirse a un tema específico y recibir las actualizaciones de este.
- UNSUBSCRIBE: mensaje que utiliza un cliente para indicar la pérdida de interés y anular la suscripción a un tema específico
- LWT: este mensaje "last will and testament" (última voluntad y testamento) se configura en un cliente para publicarse automáticamente si ocurre una desconexión inesperada. El broker mantiene un temporizador, y si comprueba que recientemente el cliente no ha publicado ni ha mandado un PINGREQ, se publica el mensaje LWT especificado notificando así a los suscriptores.

El diseño de [MQTT](#MQTT) se basa en la simplicidad y en minimizar el ancho de banda, dejando la interpretación de los mensajes en manos del desarrollador. Los mensajes transmitidos a través de la red tienen la posibilidad de configurar el [QoS](#QoS) o calidad de servicio por cada tema, asociados con distintas garantías de entrega y cómo se entregan los mensajes. Aunque [MQTT](#MQTT) depende de [TCP](#TCP), el cual tiene su propia garantía de entrega, históricamente los niveles [QoS](#QoS) eran necesarios para evitar la pérdida de datos en redes antiguas y poco fiables, una preocupación válida para las redes móviles actuales. Estos son los siguientes tipos de [QoS](#QoS):

- [QoS](#QoS) 0, a lo sumo una vez: los mensajes se envían y no se tiene en cuenta si llegan o no. Está la posibilidad de la pérdida de mensajes y no se hacen retransmisiones.
- [QoS](#QoS) 1, al menos una vez: el receptor recibe el mensaje por lo menos una vez. El receptor debe enviar un acuse de recibo al emisor en cuanto reciba el mensaje, y si este [ACK](#ACK) nunca llega (ya sea debido a que el mensaje nunca llegó o que el [ACK](#ACK) se perdió), el emisor retransmitirá el mensaje, pudiendo producirse mensajes duplicados.
- [QoS](#QoS) 2, exactamente una vez: asegura que el mensaje llegue exactamente una vez, manejado mediante la sobrecarga en la comunicación y el envío de una serie de acuses de recibo, y es la mejor opción cuando no se acepta ni la pérdida ni la duplicidad de mensajes.

La transmisión de datos se realiza principalmente sobre la capa TCP/IP, pero existe la posibilidad de operar encima de otros protocolos de red que ofrezcan conexiones ordenadas, sin pérdidas y bidireccionales, y se transmiten en un tamaño reducido de paquetes de datos, estructurado por los siguientes campos:

- Cabecera fija, en la que se especifica el tipo de mensaje, si el mensaje es un duplicado, el [QoS](#QoS), si es un mensaje que retener y el tamaño del paquete.
- Cabecera variable, no siempre presente en los mensajes, y puede transportar información adicional de control.
- Payload o carga útil.

Por defecto, este protocolo envía credenciales y mensajes en texto plano sin medidas de seguridad, pero admite utilizar conexiones [TLS](#TLS)/[SSL](#SSL) protegidas por certificado, nombre de usuario y contraseña para cifrar y proteger la información transferida contra la intercepción, modificación o falsificación. Además, un broker [MQTT](#MQTT) tiene soporte para conectar dispositivos IoT a escala masiva, un factor tenido en cuenta a la hora de su diseño y que resulta en una alta capacidad de concurrencia, rendimiento y escalabilidad, características útiles en una red IoT. Implementaciones como EMQX y HiveMQ han alcanzado hitos notables, con 100 y 200 millones de conexiones respectivamente, y un pico de 1 millón de mensajes gestionados por segundo. A esta escalabilidad se le puede sumar la capacidad de implementar múltiples brokers, para así compartir la carga de clientes y tratar la redundancia y la copia de seguridad de los mensajes en caso de fallo.


### AMQP
Protocolo de la capa de aplicación de estándar abierto para middleware orientado a mensajes
Protocolo binario diseñado para soportar una amplia gama de aplicaciones de mensajería y patrones de comunicación
No está diseñado específicamente para soluciones IoT, pero funciona muy bien para las comunicaciones de mensajes que incluyen muchos escenarios IoT
Protocolo binario de capa de aplicación
Puede utilizarse para mensajería punto a punto y pub-sub
Amplia compatibilidad con escenarios de mensajería
Admite el cifrado de mensajes extremo a extremo
Mensajes enviados sobre TCP y UDP

Cons: alto consumo de recursos (energía y memoria)
Orientación de mensajes, colas, enrutamiento, fiabilidad y seguridad
AMQP define como deben comportarse tanto el proveedor del servicio del mensajería como el cliente. Permite que implementaciones de diferentes vendedores puedan funcionar juntoas

AMQP es un protocolo a nivel de cable, que describe el formato de los datos que se envían a través de la red como un flujo de bytes. Cualquier herramienta que pueda crear e interpretar mensajes que se ajusten a este formato de datos puede interoperar con cualquier otra herramienta que lo cumpla, independientemente del lenguaje de implementación

Es un protocolo de mensajería avanzado
Permite la comunicación entre servicios y aplicaciones
Protocolo abierto que funciona a nivel de capa de aplicación
Define la creación de mensajes, encolamiento, enrutamiento de los mensajes producidos y exactitud para entregar los mensajes a los consumidores

Compuesto de un broker de mensajería. Este internamente posee exchanges, donde se conectan los productores de mensajes. También posee colas, vinculadas a exchanges a través de distintos criterios. Los consumidores de los datos se conectan a las colas para extraer los mensajes que producen los publicadores.

El protocolo establece el comportamiento del servidor de mensajería y de los clientes que se conectan al broker, de manera que las implementaciones de distintos proveedores son interoperables
AMQP proporciona la unidad de trabajo necesarioa para intercambiar información

Es un protocolo orientado a crear un "cable" entre aplicaciones conectadas
Incluye funcionalidad para entregar mensajes de manera fiable, representar los datos a través de diferentes formatos, flexixbilidad para definir datos, preparado para escalabilidad y capacidad de definir varias topologías

El objetivo de diseño de AMQP era conseguir la creación de un protocolo que permita interoperar mediante mensajes, tanto dentro de la misma organizacaión como entre organizaciones, mediante la creación de un mensaje con estándar abierto para realizar transacciones de negocio

Entidades AMQP:
- Broker: servidor de mensajería al que los clientes se conectan usando el protocolo AMQP y que se encarga de distribuir los mensajes
- Usuario
- Conexión: conexión física sobre algún protocolo de transporte como TCP/IP o SCTP (ligada a un usuario)
- Canal: conexión lógica ligada a una conexión

Entidades usadas para transferencia de mensajes entre aplicaciones son declaradas dentro de un canal, que garantiza la creación lógica de los elementos necesarios para la comunicación, como la creación de un exchange, una cola a la cual enviar mensajes y la vinculación entre las entidades.

Entidades que definen el protocolo para la creación y consumo de mensajes mediante AMQP:
- Exchanges: entidades a las que los productores envían mensajes, y desde donde se envían los datos a las diferentes colas. Los mensajes se envían a una o más colas según el exchange y la clave de enrutamiento/routing key con que se publican. Tipos de exchange:
	- Topic exchange: cuando se publica un mensaje, el determina qué colas lo recibirán comparando la routing key del mensaje con el patrón de enrutamiento que vinculan la cola con el exchange
	- Direct exchange: envía mensajes a un receptor concreto,
	TODO: seguir


### XMPP

Otra manera de comunicar varios dispositivos [IoT](#IoT) se logra mediante el Extensible Messaging and Presence Protocol, anteriormente conocido como Jabber. Este protocolo se basa en la transmisión de datos estructurados en formato [XML](#XML) dentro de una red de arquitectura cliente-servidor, en la cual los dispositivos están identificados por un Jabber ID, cuyo formato es similar al de una dirección de correo electrónico (por ejemplo, "abc@example.com"). En esta red, el cliente establece una conexión TCP/IP con el servidor, la cual permanece abierta. Posteriormente, el cliente se autentica con el servidor, y tras una autenticación exitosa, se habilita la posibilidad de enviar y recibir mensajes.

Una característica notable de [XMPP](#XMPP) es que no existe un servidor central que gestione todas las comunicaciones; el intercambio de mensajes entre clientes y servidores está descentralizado, permitiendo a los usuarios y organizaciones operar su propio servidor [XMPP](#XMPP). Esto no restringe a los usuarios a conectarse únicamente con otros usuarios en el mismo servidor, ya que, al ser un estándar abierto regido por la Internet Engineering Task Force, los desarrolladores disponen de un protocolo bien documentado y fiable. De este modo, es posible interoperar entre diferentes implementaciones de [XMPP](#XMPP) a través de Internet, independientemente del proveedor. En el caso de querer comunicarse con otro servidor, ambos servidores [XMPP](#XMPP) se intercambian la información necesaria, habilitando un modelo federado.

Este protocolo está diseñado para ofrecer mensajería instantánea o casi en tiempo real a través de la red, sin importar la distancia entre los dispositivos, uno de los problemas más comunes en [IoT](#IoT). Además, permite obtener información de presencia sobre los usuarios conectados y mantener una lista de contactos para cada usuario. [XMPP](#XMPP) también admite extensibilidad, permitiendo a los desarrolladores añadir características y funcionalidades personalizadas, ofreciendo más allá de la mensajería tradicional y adaptando [XMPP](#XMPP) a necesidades específicas de aplicaciones, como la transmisión de señales [VoIP](#VoIP), video, ficheros, chat grupal, conferencias multiusuario, suscripción de presencia para conocer cuándo alguien está conectado a la red, y comunicación publicación-suscripción para recibir actualizaciones sobre temas específicos de interés.

En los mensajes [XMPP](#XMPP) se utiliza el formato stanzas [XML](#XML) para estructurar y transportar los datos. Existen 3 tipos principales de stanzas:

- Stanza de mensaje (`message`): utilizado para enviar mensajes instantáneos entre clientes. Contiene los campos remitente, destinatario, cuerpo del mensaje y otros metadatos opcionales. Después de recibir el mensaje, el servidor utiliza el campo de destinatario para enrutar el propio mensaje. Ejemplo de uso de esta stanza: 
```xml
<message from='abc@example.com'
	to='xyz@example.com'
	type='chat'>
	<body>Hemos tenido una velada encantadora.</body>
</message>
```
- Stanza de presencia (`presence`): permite a las entidades conocer el estado y la disponibilidad online/offline de otros cliente. También puede transportar información adicional, como la actividad del cliente o su ubicación. Cuando un cliente se conecta o desconecta del servidor, envía una stanza de presencia para notificar a otros clientes de su lista de contactos. Ejemplo de uso de esta stanza:
``` xml
<presence from="abc@example.com">
	<show>away</show>
	<status>Paro para comer.</status>
	<priority>5</priority>
</presence>
```
- Stanza de IQ o info/query (`iq`): se usa para consultar al servidor, gestionar suscripciones o intercambiar datos estructurados entre clientes y servidores. Funciona de manera similar a los métodos [HTTP](#HTTP) GET y POST, siguiendo un patrón de petición-respuesta, en el cual un cliente envía una petición al servidor y este responde con la información solicitada o con una confirmación. Ejemplo de uso de esta stanza:
``` xml
<iq to="user@example.com" type="get" id="314">
	<query xmlns="http://jabber.org/protocol/disco#items" />
</iq>
```

El protocolo [XMPP](#XMPP) es altamente escalable debido a su capacidad de manejar multitud de conexiones y mensajes simultáneos. Además, al ser descentralizado, permite implementar fácilmente más servidores para gestionar el aumento de usuarios y altos picos de uso. En cuanto a seguridad, [XMPP](#XMPP) es compatible con cifrado de extremo a extremo mediante [TLS](#TLS) o [SSL](#SSL), garantizando así la confidencialidad de los mensajes. Por último, cuenta con una amplia comunidad de usuarios, diversas implementaciones y guías que facilitan a los desarrolladores la creación de aplicaciones que integren este protocolo.


### DDS
Diseñado para ser usado en sistemas en tiempo real, y es un estándar máquina-máquina del Object Management Group (OMG)
Objetivos DDS: permitir intercambios de datos fiables, de alto rendimiento, interoperables, en tiempo real y escalabes usando un patrón de mensajería publish subscribe
Protocolo DDS diseñado para responder a las necesidades específicas de aplicaciones
Diseñado para sistemas en tiempo real
Conecta dispositivos directamente entre ellos
Elimina el requisito del servidor intermediario: mayor velocidad y eficacia en el intercambio de datos
Mejor protocolo de aplicación segura, por su naturaleza sin servidor
Capaz de transmitir millones de mensajes a multitud de receptores de forma instantánea
Entrega en tiempo real, útil para cualquier sistema que lo requiera
Demuestra notable capacidad de adaptación, responde fácilmente a las neesidades únicas de cada ámbito de aplicaci´´on
Prioriza entrega de un intercambio de datos fiable, escalable, de alta velocidad e interoperable

Caract:
- Diseñado para sistemas en tiempo real
- Facilita comunicación directa entre dispositivos
- Minimiza sobre carga de comunicación

Ventajas:
- Arquitectura flexible y adaptable
- Baja sobrecarga, permite integración perfecta con sistemas de alto rendimiento
- Garantiza una entrega de datos determinista
- Altamente escalable para adaptarse a las crecientes demandas del sistema
- Optimiza la utilización del ancho de banda de transporte

//TODO: buscar más cosas de DDS (wikipedia o info)


### CoAP

El Constrained Application Control es un protocolo de la capa de aplicación que permite a dispositivos con recursos limitados, como los que se encuentran en una red [IoT](#IoT), comunicarse entre sí. Funciona en un marco cliente-servidor, en el cual el cliente realiza una solicitud a un punto de comunicación del dispositivo servidor, y este responde, permitiendo la interoperabilidad entre los dispositivos uno a uno.

Este protocolo opera sobre el protocolo de transporte [UDP](#UDP), que, a diferencia de [TCP](#TCP), no requiere que los dispositivos establezcan una conexión de datos previa al envío de datos. Esto trae tanto consecuencias positivas como negativas. La consecuencia negativa radica en la poca fiabilidad en la comunicación de base, ya que el protocolo [UDP](#UDP) no garantiza la entrega de los mensajes, sino que esta garantía se gestiona desde la implementación de [CoAP](#CoAP). Es posible establecer acuses de recibo ([ACK](#ACK)), de manera que, por cada mensaje enviado, el dispositivo espera un acuse de recibo y, en caso de no recibirlo en un tiempo determinado, el mensaje se retransmite. La consecuencia positiva del uso de [UDP](#UDP) es la posibilidad de funcionar en redes con pérdidas o inestables, adecuado para redes [IoT](#IoT), ya que suelen operar en entornos de red difíciles, y la rapidez en la comunicación, pues no requiere una conexión de datos previa, enviando directamente el mensaje.

Esta comunicación utiliza una arquitectura [REST](#REST)ful, en la cual los datos y las funcionalidades se consideran recursos a los que se accede mediante una interfaz estándar y uniforme. Estos recursos se acceden y se interactúa con ellos mediante métodos [HTTP](#HTTP) estándar (GET, POST, PUT, DELETE, que realizan las funciones "obtener", "crear", "actualizar" y "eliminar" recursos, respectivamente), permitiendo una interoperabilidad sencilla entre distintos tipos de dispositivos y facilitando a los desarrolladores la creación de aplicaciones que usan protocolo. No es necesario que los recursos de la red sean conocidos por el dispositivo que vaya a utilizarlos, ya que [CoAP](#CoAP) implementa un mecanismo de descubrimiento integrado, útil en redes [IoT](#IoT) en las que los dispositivos constantemente se conectan y desconectan. Esta función de descubrimiento trata de consultar un recurso conocido "núcleo" en la red, el cual provee la lista de los recursos de los dispositivos en la red. Es decir, si un dispositivo [IoT](#IoT) quiere interactuar con los recursos de otro, puede consultar al núcleo y comprobar qué recursos hay disponibles y cómo puede interactuar con ellos.

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

Además es un protocolo diseñado para requerir poca energía en la transferencia (tiene bajo consumo de recursos), y permite transferir tanto datos como archivos, utilizar el protocolo [DTLS](#DTLS) para aumentar la seguridad de las transferencias, y extender la implementación del protocolo con funcionalidades adicionales. Por el contrario, es un protocolo menos maduro y menos adoptado que sus alternativas, resultando en una menor cantidad de recursos, guías y herramientas, además de una compatibilidad reducida con otros dispositivos [IoT](#IoT).


https://webbylab.com/blog/mqtt-vs-other-iot-messaging-protocols-detailed-comparison/
https://www.techtarget.com/iotagenda/tip/Top-12-most-commonly-used-IoT-protocols-and-standards
https://build5nines.com/top-iot-messaging-protocols/
https://www.a3logics.com/blog/iot-messaging-protocols/
https://en.wikipedia.org/wiki/MQTT
https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern
https://www.emqx.com/en/blog/what-is-the-mqtt-protocol
https://www.gotoiot.com/pages/articles/mqtt_intro/index.html
https://dzone.com/refcardz/getting-started-with-mqtt
https://www.hivemq.com/resources/achieving-200-mil-concurrent-connections-with-hivemq/
http://www.steves-internet-guide.com/mqtt-protocol-messages-overview/
https://en.wikipedia.org/wiki/Advanced_Message_Queuing_Protocol
https://www.gotoiot.com/pages/articles/amqp_intro/index.html
https://en.wikipedia.org/wiki/XMPP
https://www.pubnub.com/guides/xmpp/
https://blazeclan.com/blog/xmpp-for-dummies-part-3-stanzas-in-detail/
https://slixmpp.readthedocs.io/en/latest/api/stanza/presence.html
https://slixmpp.readthedocs.io/en/latest/api/stanza/iq.html
https://www.emqx.com/en/blog/coap-protocol0
https://www.gotoiot.com/pages/articles/coap_intro/index.html
(DOCUMENTO) https://datatracker.ietf.org/doc/html/rfc7252







## Espressif y sus dispositivos

Espressif Systems es una multinacional pública de semiconductores sin fábrica fundada en 2008, que opera como líder mundial en el ámbito del Internet de las Cosas y está comprometida en proporcionar a millones de usuarios algunos de los mejores dispositivos y plataformas de software de la industria, junto con una variedad de soluciones [IoT](#IoT) seguras.

La empresa se identifica como una empresa compuesta por especialistas, ingenieros y científicos dedicados al desarrollo de soluciones de vanguardia de bajo consumo que aprovechan la comunicación inalámbrica, el [IoT](#IoT) y la inteligencia artificial de las cosas ([AIoT](#AIoT)). Estas soluciones se caracterizan por su seguridad, robustez, eficiencia energética, versatilidad, asequibilidad y enfoque código abierto.

Con el surgimiento de la inteligencia artificial y la evolución del [IoT](#IoT), la demanda de productos con conectividad inalámbrica segura ha ido creciendo considerablemente, y Espressif Systems ha respondido a este desafío desarrollando soluciones adaptadas a las necesidades del mercado. Espressif emplea los nodos de tecnología avanzada, la informática de bajo consumo, la comunicación inalámbrica, así como la tecnología de malla, para crear conjuntos de chips y módulos de alto rendimiento, que son más inteligentes, adaptables y versátiles.

El compromiso de esta empresa china con el código abierto se refleja en su oferta de una variedad de frameworks y herramientas de desarrollo para construir aplicaciones en diferentes ámbitos, como [IoT](#IoT), audio, malla, conectividad de dispositivos, reconocimiento facial y asistentes de voz. Gracias a las tecnologías y soluciones abiertas de Espressif, permiten acercar el [IoT](#IoT) a sus clientes, comerciales y no comerciales, y que desarrolladores de todos los ámbitos puedan utilizarlas a nivel mundial y construir sus propios dispositivos inteligentes conectados y soluciones a algunos problemas del presente. Con este acercamiento a sus clientes, estos últimos pueden efectuar una conectividad inalámbrica de sus productos optimizando el rendimiento de estos y en un reducido tiempo de desarrollo. A su vez, apoyan activamente proyectos de código abierto en la comunidad de makers, creyendo en la accesibilidad de la tecnología como motor para el desarrollo de la sociedad [AIoT](#AIoT) del futuro.

Además de su enfoque en el código abierto y en la tecnología accesible, Espressif se destaca por el compromiso con la sostenibilidad, la responsabilidad social corporativa y por la inversión en investigación y desarrollo de tecnologías ecológicas. A lo largo de su trayectoria, ha respaldado activamente soluciones que reducen el consumo de energía y el desperdicio de materiales.

Los productos de Espressif se utilizan ampliamente en productos como electrodomésticos, altavoces, bombillas, cámaras, tabletas, TV boxes, terminales de pago y otros dispositivos de electrónica de consumo, y son especialmente útiles en contextos donde es necesario el Internet de las Cosas, comunicación inalámbrica e Inteligencia Artificial. Espressif es conocido por sus populares series de chips, módulos y placas de desarrollo ESP8266, ESP32 y ESP32-S, ESP32-C y ESP32-H, los cuales se analizarán en el siguiente apartado.





https://www.espressif.com/en/company/about-espressif
https://www.eurotronix.com/es/fabricantes/espressif
https://www.digikey.es/es/supplier-centers/espressif-systems

