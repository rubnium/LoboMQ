# Herramientas y Metodología

## Herramientas

En este apartado se identifican y describen las distintas herramientas hardware y software que han permitido llevar a cabo este Trabajo de Fin de Grado.

### Hardware

El núcleo de este [TFG](#TFG) se basa en la programación de una placa de desarrollo, por lo que es necesario ciertos elementos hardware para llevarlo a cabo:

**Ordenador portátil**: 
	Wifi
	USBs
	Lector tarjetas SD

**Dos placas ESP32 DEVKIT V1**: Ambas fueron cedidas por la [UCLM](#UCLM) para el desarrollo de este [TFG](#TFG). este tipo de placas contienen las mismas características que el SoC ESP32 mencionado en el apartado \ref{02_estado_arte.esp32} /*TODO: comprobar funcionamiento referencia*/. Concretando, utiliza el módulo ESP32-WROOM-32.
Las placas están distribuidas en una placa de pruebas o breadboard, permitiendo conectar distintos elementos a los pines de las placas mediante jump wires o cables puente, sin necesidad de soldadura ni diseñar circuitos integrados y facilitando la prueba de componentes. En este caso, tienen conectados distintos módulos y sensores que permiten ampliar las funciones de estas:

 - **Módulo lector de tarjeta microSD**: Compuesto por un socket para insertar tarjetas microSD en un circuito impreso del cuál salen 7 pines para poder utilizar el bus SPI de las tarjetas microSD. El SPI o Serial Peripheral Interface es un estándar que se utiliza para transferir información entre circuitos integrados, como pueden ser la placa ESP32 DEVKIT y el lector de tarjetas. Los pines que tiene este módulo son los siguientes:
	- VCC: Entrada de energía, se conecta a una fuente de alimentación para alimentar el lector.
	- GND: Conexión a tierra, se conecta al terminal negativo de la fuente de alimentación.
	- Data In: También conocido como MOSI o Master Output Slave Input, se utiliza para enviar datos desde la placa ESP32 hasta la tarjeta microSD.
	- Data Out: También conocido como MISO o Master Input Slave Output, se utiliza para enviar datos desde la tarjeta microSD hasta la placa ESP32.
	- Serial Clock: Reloj SPI, se utiliza para sincronizar la transferencia de datos entre las placas.
	- Chip Select: Se utiliza para activar y desactivar la comunicación con el lector.
	- Card Detect: Se utiliza para detectar si hay una tarjeta insertada en el lector.
	Para este trabajo, el lector, cedido por la UCLM, se utiliza para leer y escribir datos en una tarjeta microSD desde la ESP32 DEVKIT V1 que actúe como broker y gestione los registros o logs y las direcciones de los dispositivos suscritos contenidos. 
 - **Sensor DHT11**: Sensor digital capaz de medir la temperatura y la humedad, cedido por la UCLM. Alimentado por 3,3 o 5 voltios, es capaz de leer la humedad en el ambiente entre los rangos 20 y 95% (con un 5% de fallo) y la temperatura entre 0 y 50 ºC (con 2 ºC de fallo).
 - **Potenciómetro BQ Zum Kit Advanced**: Contenido originalmente en un kit junto a varios sensores y una placa controladora, este potenciómetro de señal analógica cedido por la UCLM es capaz de devolver un valor en función a su rotación, siendo su rotación máxima 300º, al alimentarlo con 3,3 o 5 voltios.

**Placa ESP32-2432S028R**: Esta placa proporcionada por el autor y popularmente conocida como Cheap-Yellow-Display o CYD para abreviar, se ha utilizado para hacer pruebas del funcionamiento de la herramienta desarrollada, y al igual que las anteriormente mencionadas placas ESP32, está potenciado por un ESP32-WROOM-32. En cuanto a componentes integra:

 - Pantalla LCD de 2,8 pulgadas con resolución 320x240 píxeles, y táctil de tipo resistivo.
 - LED multicolor RGB.
 - Lector de tarjeta microSD.
 - Sensor LDR, cuyo valor que devuelve depende de la resistencia que le otorga la luz que recibe.
 - Conectores y pines adicionales para conectar un altavoz y otros módulos.

**Tarjeta microSD**: Tarjeta proporcionada por el alumno autor y utilizada por una de las placas con lector de tarjetas para almacenar los registros o logs y las direcciones de los dispositivos suscritos al broker. Las características de la tarjeta no son deterministas para la tarjeta, ya que las especificaciones no afectan al rendimiento de la herramienta resultante de este TFG. En este caso, la tarjeta microSD utilizada es de la marca Samsung y cuenta con capacidad de almacenamiento de 1 GB.

**Adaptador de tarjeta microSD a SD**: Proporcionada por el autor, permite utilizar una tarjeta microSD en un lector de tarjetas SD normal al adaptar su tamaño y forma. Se ha utilizado para leer, modificar y eliminar contenidos de la tarjeta microSD desde el ordenador portátil, útil para hacer probar el funcionamiento de la herramienta.

{
	https://www.sparkfun.com/products/544
	https://es.wikipedia.org/wiki/Serial_Peripheral_Interface
	https://tienda.bricogeek.com/sensores-temperatura/1574-modulo-sensor-dht11-humedad-y-temperatura.html
	https://centroderobotica.com/producto/potenciometro-para-proyectos/
	https://tienda.bq.com/products/componentes-zum-kit-advanced?variant=37589957935292
	https://educacion.bq.com/zum-kit-advanced/
	https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/
}

### Software

Para poder realizar el desarrollo correcto de este TFG, se han requerido las siguientes piezas de software:

**Windows 10**: El sistema operativo es clave para poder hacer funcionar el Trabajo de Fin de Grado. En este caso, el autor ha utilizado la versión más reciente a fecha de la escritura de este documento, 22H2. Este sistema operativo desarrollado por Microsoft se encuentra instalado en el ordenador portátil mencionado en el apartado de hardware /*TODO: mencionar*/, y debido a su alta popularidad tiene una gran compatibilidad con la mayoría de aplicaciones existentes, y en este caso es beneficioso para el resto de software mencionado posteriormente. Además, integra:

- Windows Update y Windows Defender: Permite tener el sistema en la última versión y seguro gracias a los últimos parches de seguridad, una capa de protección importante para los ficheros, la información contenida y la integridad del propio sistema al estar conectado a Internet e instalar aplicaciones. 
- Explorador de archivos: Como su nombre lo indica, permite navegar entre carpetas y acceder a los archivos, tanto de los discos duros instalados internamente como los externos (por ejemplo, pendrives, tarjetas de memoria o discos).
- Bloc de notas: Esta herramienta es ideal para crear y editar ficheros de texto plano o, en el caso de este desarrollo, ver ficheros de código de manera rápida.
- Drivers: Ofrecen compatibilidad y rendimiento con todo el hardware contenido en el ordenador, como procesador, tarjeta gráfica, teclado y ratón, puertos USB, lectores de tarjetas y otros dispositivos externos. En este caso, para poder hacer uso de las placas, se ha necesitado instalar un driver adicional. /*TODO: añadir enlace*/
La relevancia de usar Windows 10 es mínima, ya que es posible de adaptar el proyecto a un entorno en Linux con pocas o nulas complicaciones. El uso de Windows 10 ha sido decisión del autor por gusto.

**GitHub**: 
Es ...
Creado en ...
Poryectos en repos
GitHub permite a los equipos de desarrolladores colaborar y realizar cambios en proyectos compartidos alojados en repositorios de Git.

Git es un sistema de control de versiones de código abierto creado en 2005 por Linus Torvalds, que permite a cualquier desarrollador gestionar el código fuente y el historial de cambios mediante comandos ejecutados en una terminal. Tiene la característica de ser distribuido, permitiendo usar ramas para aislar partes del código, como pueden ser nuevas funcionalidades que están en desarrollo, y que no afecte al código final desplegado. Cada parte del equipo puede crear una rama, integrar los cambios que vea necesarios, y luego fusionarla con la rama principal para hacer efectivos estos cambios, lo cual es útil para añadir varias funcionalidades simultáneamente, trabajar varias personas en los mismos ficheros, comprobar las diferencias entre estos, aprobarlas, y volver a una versión funcional anterior en caso de que se encuentren errores. GitHub aprovecha estas funcionalidades y las aplica a su interfaz web, haciendo más accesible los repositorios Git a usuarios con poco conocimiento técnico al evitar recordar comandos específicos.

Desde el repositorio Git se puede


Los repositorios pueden ser públicos o privados, siendo en este último caso que el repositorio solo pueden verlo los usuarios agregados y cuya funcionalidad está limitada.
...

Otras funciones que incluye GitHub son:

- Documentación de proyectos, mediante la creación de ficheros de texto "readme" o "leeme" en lenguaje Markdown en directorios del proyecto.
- Creación de Wikis.
- Automatizar pruebas, lanzamientos y despliegues con GitHub Actions, especificando los pasos a ejecutar tras una acción específica realizada en el repositorio.
- GitHub Codespaces, un IDE online.
- Alojar páginas web estáticas con GitHub Pages como parte de un repositorio, como blogs, documentación de código y libros.
- Gists o fragmentos de código compartibles o utilizables con soporte de control de versiones.
...

GitHub además soporta planes de pago para aumentar la funcionalidad que ofrece, dar un soporte personalizado a los usuarios y quitar limitaciones de repositorios privados.

En el caso de este proyecto, se ha utilizado en el plan gratuito de GitHub un repositorio privado a lo largo del desarrollo para alojar el código, compartirlo fácilmente con los tutores para enviar dudas e informar del estado del proyecto, y llevar un histórico de los cambios realizados. Posteriormente, se ha modificado la visibilidad del repositorio a público para compartir el proyecto a través de la plataforma de librerías de PlatformIO (mencionado posteriormente) y aprovechar la funcionalidad de GitHub Pages para incluir una página web estática que documente las distintas funciones que componen el proyecto, ambas funciones automatizadas a través de GitHub Actions /*TODO: realizar*/

Otra herramienta que ofrece GitHub para no separar la funcionalidad del escritorio local es **GitHub Desktop**, permitiendo simplificar el flujo de trabajo del desarrollador y centrarse en su trabajo. Proporciona una interfaz gráfica que evita interactuar directamente con Git para clonar proyectos, hacer commits, cambiar de rama y ver los cambios y diferencias en los ficheros.


///
Es una plataforma donde se pueden almacenar, compartir y trabajar junto a otros usuarios para escribir codigo


Almacenar codigo en un repositorio para:
- Presentar o compartir trabajo
- Seguir y administrar cambios en el codigo a lo largo del tiempo
- Dejar que otros users revisen el codigo y realicen sugerencias
- Colaborar en un proyecto compartido, sin preocuparse de que los cambios afectarán al trabajo de los otros colaboradores
Trabajo colaborativo es la caracterisitica fundamental de GH. Es posible gracias a Git, en el que se basa GitHub

Al cargar archivos a GitHub se guardan en repositorio de Git. Git se inicializa para administrar los cambios en el momento de hacer cambios en archivos GitHub

Las herramientas están disponibles tanto desde el naavegador como desde la terminal en un equipo local (crear ramas, cargar archivos, crear repo)

Para colaborar con otros usuarios teneis que estar en el mismo repositorio, extraer los cambios más recientes de los colaboradores, y hacer subidas de los cambios al mismo repositorio

GitHub es un servicio en la nube que aloja un sistema de control de versiones llamado Git
Permite a los desarrolladores colaborar y realizar cambios en proyectoc compartidos. Y mantener un seguimiento detallado del progreso
GitHub es una platf de gestión y organización de proyectos basada en la nube que incorpora funciones de control de versiones de Git.


GitHub desarrollado en Abril 2008 usando Ruby on Rails. Comprado por Microsoft el 26 de octubre de 2018
Es plataforma de desarrollo que permite a los desarrollaodres crear, almacenar, gestionar y compartir su codigo
Usa Git, proporcionando control de acceso, trackeo de bugs, peticiones de software funciones, gestion de tareas, integración continua y wikis para los proyectos. 
Usado comunmente para alojar proyectos open source
Los proyectos se pueden acceder usando el git cli, y todos los comandos de git funcionan
Permite a los usuarios tambien explorar repositorios publicos
Ofrece funciones de red social, como feeds, followers, wikis y bifurcaciones de proyectos
Usuarios pueden contribuir a repositorios publicos
Tambien ofrece repos privados (solo lo pueden usar gente asignada al repositorio) gratuitos y con funcionalidades limitadas de manera gratuita

El proposito principal de GitHub es facilitar el control de versiones y el tracking de issues del desarrollo software. Dispone de labels, milestones, asignación de responsabilidades y un buscador para el trackeo de issues. Luego el control de versiones, se pueden hacer pull requests, ver las diferencias que proponen los cambios y aprobarlas, commiteando esos cambios. Luego hay un historico de commits que se pueden ver

Mas funcionalidades:
- Informacion de contribuyentes, lenguajes de codigo utilizados, commits
- Notificaciones
- Discusiones


//
	GitHub Desktop


{
	https://docs.github.com/es/get-started/start-your-journey/about-github-and-git
	https://www.hostinger.es/tutoriales/que-es-github
	https://en.wikipedia.org/wiki/GitHub
	https://desktop.github.com/
}




**Visual Studio Code**: Es un [IDE](#IDE) ligero y de código abierto creado por Microsoft el 29 de abril de 2015, que funciona como un potente editor de código altamente personalizable y ejecutable en Windows, macOS, Linux y navegadores web. El editor no se basa en un sistema de proyectos, sino que permite al usuario abrir uno o varios directorios simultáneamente, formando workspaces o espacios de trabajos compuestos por ficheros que pueden contener distintos lenguajes de programación. Por defecto, soporta los lenguajes JavaScript, TypeScript y Node.js, pero esta lista se puede ampliar mediante extensiones para utilizarlo con C++, Java, Python y otros lenguajes. Estas extensiones, creadas por Microsoft o por terceros, están disponibles en un repositorio central, y además permiten personalizar y extender las funcionalidades del editor, adaptándose a las necesidades del usuario.
Visual Studio Code integra una serie de funcionalidades que lo convierten en un editor ideal para incrementar la productividad del usuario y perfecto para su uso diario, tales como el subrayado de sintaxis y errores, sangría automática, refactorización, autocompletado, sugerencias y fragmentos de código. Ofrece la posibilidad de compilar y ejecutar fácilmente los ficheros de código y proyectos simplemente haciendo clic en el botón de "play", evitando la necesidad de aprender comandos o repetirlos constantemente y agilizando el trabajo del desarrollador. En aquellas ejecuciones de código que pueden resultar en error o son difíciles de comprender ayuda a realizar comprobaciones mediante un depurador interactivo, que permite recorrer el código fuente con puntos de interrupción, inspeccionar variables, ver pilas de llamadas y modificar líneas de código en ejecución.
Es compatible con Git y con el control de versiones en dispositivos con Git instalado y en proyectos que formen parte de un repositorio Git, ofreciendo al usuario la posibilidad de ver las diferencias y cambios con la versión localizada en el repositorio, sin necesidad de salir de la aplicación ni usar comandos complejos en la terminal.
La funcionalidad que ofrece Visual Studio Code no se ve limitada únicamente a la interfaz de usuario, ya que dispone de una lista de comandos ejecutables que se pueden asignar a atajos de teclado.
Este ha sido el [IDE](#IDE) de preferencia para el desarrollo de este trabajo, y se ha complementado con las siguientes extensiones:

- **PlatformIO**:
- C/C++ Extension Pack:
- Better Comments: 
- Code Spell Checker:
- Doxygen Documentation Generator: 
- TODO Highlight y Todo Tree:
- GitHub Copilot:

/*TODO: poner enlaces y explicar*/
{
	https://code.visualstudio.com/docs/editor/whyvscode
	https://en.wikipedia.org/wiki/Visual_Studio_Code
}

**Trello**: Es una aplicación web que permite elaborar listas con tareas de forma visual al estilo Kanban, creada en 2011 por Fog Creek Software y vendido a Atlassian, su actual dueño, en 2017.

Se basa en tableros, compuesto principalmente por los siguientes componentes:
- Listas: Representadas en formato de columnas, suelen hacer referencia a las distintas fases que puede tener una tarea. Por ejemplo, en un tablero puede haber tres columnas: "por hacer", "en curso", "hecho".
- Tarjetas: Cada tarjeta en un tablero puede ser una tarea o idea relacionada al trabajo o proyecto, y se colocan en las columnas correspondientes según su estado o tipo. La idea de las tarjetas es moverlas según avance el desarrollo del proyecto. Se les puede además añadir un miembro asignado para reflejar qué usuario está encargado de la tarea, evitando la necesidad de preguntar personalmente; fechas de vencimiento de la tarea, con capacidad de notificar según se acerque la fecha y de marcarlas como realizadas; ficheros adjuntos para organizarlos, descripción, comentarios, y checklists para dividir una tarea grande en distintas tareas pequeñas.
- Miembros: Cada uno con responsabilidades asignadas a las tarjetas y permisos para utilizar el tablero.





Herramienta en linea para gestionar proyectos y tareas personales
Herramienta visual que permite a equipos gestionar cualquier tipo de proyecto y flujo de trabajo, y supervisar tareas
Sencillo, flexible y potente.

Usuarios pueden crear tablones de tareas con diferentes columnas y mover tareas entre ellas
Puede utilizarse para fines personales y empresariales (gesti´´on inmobiliaria, de proyectos sw, tablones de anuncios escolares, planificación de clases, contabilidad, diseño web, juegos, gestión de casos en despachos de abogados)

Tablero Personalizable según necesidades
Tableros, listas y tarjetas para ver de forma clara quién está haciendo qué y las tareas pendientes
Tableros Trello mantienen las tareas organizadas y ayudan a que el equipo avance. Puedes ver todo de un vistazo (tareas pendientes hasta tareas hechas)
Miembros del tablero: asignar responsabilidades añadiendo miembros a tarjetaas de proyectos y tareas, evita preguntar personalmente quien hace que
Trello sirve para flujos de trabajo de cualquier proyecto, grande o pequeño
Gestión de proyectos: mantener tareas ordenadas, plazos controlados y miembros del equipo coordinados
Consigue reuniones productivas, motivadoras
Lluvia de ideas: creatividad en el equipo, mantiene visibilidad de las ideas, la colaboración en ellas y su utilidad práctica

Admite integraciones: intregar aplicaciones que utilice el equipo en el flujo de trabajo de trello, o añade power-up que te ayude con necesidades concretas
Admite automatización: por cada tablero, se puede crear automatizaciones sin código. Permite centrarse en el trabajo
	Crea proceso infalible para hacer avanzar el trabajo con el sistema de automatizacion integrado de trello
	Ejecuta comandos y establece reglas automatizadas para casi cualquier cosa, para centrarse en lo importante

Gestiona usuarios de forma sencilla en tiempo real y controla permisos de usuario.

Permite integrarlo con aplicaciones y servicios que usa el equipo, como Slack, Outlook, Gmail, Jira o GitHub
catalogo powerups
Permite powerups para crear flujos de trabajo, que conviertan a trello en casi cualquier cosa que necesites: solucion CRM, tickets de soporte, calendarios

Tiene distintos planes de pago, tanto para equipos pequeños como para organizaciones con varios equipos. En mi caso, uso el gratis

/*TODO: hablar de extensiones, automatizaciones*/
{
	https://en.wikipedia.org/wiki/Trello
	https://trello.com/es
	https://trello.com/es/about
	https://trello.com/es/tour

}
	
**Doxygen**: Utilizada para la documentación de este trabajo, esta herramienta de código abierto, muy empleada en el desarrollo de software, permite obtener documentación a partir del código de forma sencilla. Desde su primera versión, lanzada el 26 de octubre de 1997, posibilita la generación automática de documentación en distintos formatos, como [HTML](#HTML), [PDF](#PDF), Word y [XML](#XML), a partir de los comentarios insertados en el código durante el desarrollo, analizando la información de las distintas clases, funciones y variables. Gracias a esta automatización, se agiliza y estandariza el proceso de documentación de proyectos, lo cual es beneficioso para entender el proyecto y el código que lo compone, además de mejorar la colaboración entre los miembros del equipo de desarrollo y el mantenimiento del propio código.
Originalmente ofrece un robusto soporte a C++, pero es compatible con otros lenguajes como C, Python, Java y PHP. La documentación se realiza a partir de comentarios, como el siguiente:

```c++
/**
 * <Descripción corta de la función>
 *
 * <Descripción larga de la función>
 *
 * @param  parametro1 Descripción del primer parámetro de entrada
 * @param  parametro2 Descripción del segundo parámetro de entrada
 * @param <Descripción del resto de parámetros>
 * @return <Descripción del valor o valores que retorna>
 */
public int ejemploFuncion(int parametro1, bool parametro2, ...)
```

Entre las capacidades adicionales se encuentran las referencias cruzadas entre distintas partes de la documentación, soporte de Markdown en los comentarios, dibujo de diagramas para representar gráficamente clases, herencias y relaciones entre partes del código, personalización de la documentación resultante y configuración mediante un fichero Doxyfile con distintos parámetros establecidos por el usuario.
En el caso de este trabajo, se ha generado documentación en formato [HTML](#HTML) para crear una página web con toda la información de las distintas funciones que componen el proyecto, y se ha personalizado con Doxygen Awesome, un tema [CSS](#CSS) aplicable a la página para disponer de una página con un aspecto moderno, limpio y compatible con la interfaz móvil.

{
	https://doxygen.nl/
	https://en.wikipedia.org/wiki/Doxygen
	https://jothepro.github.io/doxygen-awesome-css/
}

**Plantilla de TFG**: Fue desarrollada por Félix Albertos Marco, profesor del Grado de Ingeniería Informática de la sede de la [UCLM](#UCLM) de Talavera de la Reina, ofreciendo una alternativa para desarrollar la memoria del Trabajo de Fin de Grado. Esta plantilla, utilizada en este [TFG](#TFG), se caracteriza por emplear Markdown para redactar todos los apartados, evitando las complicaciones del formato del documento (como el interlineado, fuentes, cabeceras y pie de página y saltos de página), además de proporcionar la portabilidad del trabajo, ya que estos ficheros son de marcado ligero y no necesitan editores ni sistemas operativos específicos. El soporte de Markdown también incluye todos los elementos que este lenguaje ofrece, como tablas, listados, fragmentos de código o formateado del texto.
Esta plantilla está compuesta por una serie de ficheros y directorios donde el autor debe ir cumplimentando todo lo necesario que quiera reflejar en el documento final. En la raíz del proyecto se encuentra un fichero `config.yaml` donde especificar las propiedades del [TFG](#TFG) (título, autor, tutores, departamento y fecha), y en el mismo nivel se encuentra la carpeta `input`. Dentro de esta, existen ficheros ya creados con ciertos apartados del documento, como el resumen, los acrónimos, la dedicatoria y la declaración de autoría, además de una carpeta para introducir los apartados de anexo y otra para los capítulos. Los apartados y capítulos se escriben en ficheros nombrados con el formato `XX_nombre_capitulo.md`. Además, esta plantilla soporta la inserción de imágenes y las referencias bibliográficas, ambas se deben realizar desde la carpeta de recursos.
El funcionamiento de esta plantilla es sencillo, ya que opera con una imagen Docker que, utilizando la herramienta Pandoc, convierte los ficheros a LaTeX y genera el documento PDF final, simplemente ejecutando el comando `make docker` (en el caso de tener instalado Docker) o ejecutando la herramienta en una máquina GNU/Linux. La combinación de las características de la plantilla de Félix Albertos permite al alumno centrarse únicamente en el contenido que tiene que escribir, agilizando notablemente el desarrollo del trabajo.

{
	https://www.felixalbertos.com/resources/downloads/tfg_template.html
}

**Teams**:
Aplicacion de colaboracion en equipo desarrollada por Microsoft, como parte de los productos Microsoft 365.
Ofrende chat y videoconferencia en el espacio de trabajo, almacenamiento de ficheros e integración de aplicaciones propias y de terceros.
para las reuniones (se usa tambien el calendario interno)
Es de uso personal y empresarial. Empresarial permite tener equipos. Viene con microsoft 365, cuenta uclm.
Se puede meet, call y collaborate con cualquiera con quien trabajes, todo en el mismo lugar
Team: coleccion de gente, contenido y herramientas basado en un proyecto o grupo especifico. 
	Pueden ser privados, publicos, y se pueden asignar roles

Canales, dentro de teams: areas designadas para tener conversaciones de un tema específico. 
	Agrupan conversaciones 
	Pueden ser privados para ciertos miembros o publico para todo el equipo
	Soporta conversaciones en hilo
	Soporta traduccion
	Se pueden compartir ficheros adjuntandolos a mensajes
	Permite subir ficheros

Para grupos pequeños y comunicacion 1 a 1, se pueden usar chats normales
Mensajes formateables (negrita, cursiva, fragmento de codigo, fuente, tamaño), tambien @

Creado en marzo 2017 como competencia a Slack

Funciones
- Chats: permite a usuarios comunicarse en chats bidireccionales persistentes con uno o varios participantes. Pueden enviarse mensajes, emojis, imagenes, enlaces y archivos
- Teams/equipos: permite a comunidades, g rupos o equipos contribuir en un espacio de trabajo compartido donde se comparten mensajes y contenidos digitales sobre un tema específico
- Canales de equipos: permiten a miembros de equipo comunicarse sin usar email ni sms. Usuarios pueden responder a mensajes con texto, imagenes. Mensajes directos envian pmensajes privados, no a todo el canal
- Conversaciones en grupo: mensajeria instantanea, llamadas de audio y video
- Reuniones: con multiples participantes, capaces de compartir audio, video, chat y contenido presentado con todos los participantes. Funciones de grabar llamadas y obtener transcripcion y traducciones en tiempo real. Supresión de ruido

Chatas de uno a uno o en grupo pequeño

MI USO: REUNIONES CON TUTORES, PONERLAS EN EL CALENDARIO

Hablar de 365 y de que tengo licencia por la uclm

{
	https://teamsdemo.office.com
	https://en.wikipedia.org/wiki/Microsoft_Teams
}


**Visio**: Es un programa para crear diagramas y vectores, creado por Visio Corporation en 1992 y traspasado a Microsoft tras la compra de la empresa el 7 de enero de 2000. Su uso está limitado a los usuarios con licencia de Microsoft 365, servicio mencionado anteriormente y del cual la [UCLM](#UCLM) distribuye la licencia a todos los usuarios de la universidad, como es el caso del autor, quien ha destinado el uso de la aplicación al dibujo de algunos esquemas de la memoria. Este programa, disponible tanto en línea como en una aplicación descargable, permite crear diagramas, imágenes vectoriales y objetos fácilmente, facilitando la visualización de datos e ideas de forma atractiva, lo cual es útil en equipos y en documentación para asegurar de manera sencilla la comprensión de los conceptos.
El programa contiene plantillas personalizables para que los usuarios no partan desde cero en la creación del diagrama, y con las extensas librerías de objetos que incluye se pueden crear diagramas profesionales, como los de flujo, red, Venn, bloques, UML, PERT, organigramas, matrices de negocio o mapas mentales. También ofrece compatibilidad con otras herramientas de Microsoft, como Teams para realizar diagramas en colaboración, y Power BI o Excel, para ofrecer una manera alternativa de visualizar los datos. Los objetos creados con este programa se pueden compartir en su propio formato VSDX, o exportarlos en otros más comunes como [JPEG](#JPEG), [PNG](#PNG) y [PDF](#PDF) para hacerlos accesibles.

{
	https://www.microsoft.com/es-es/microsoft-365/visio/flowchart-software#x68bca46524744e268ea489ad8cc29bbb
	https://en.wikipedia.org/wiki/Microsoft_Visio
}


**Inkscape**: Es una herramienta de software gratuita, multiplataforma y de código abierto que permite diseñar gráficos vectoriales. Surgió en 2003 como una bifurcación de otro editor con el mismo propósito, Sodipodi. Este programa permite generar y manipular ficheros [SVG](#SVG), en los cuales las imágenes no están dibujadas por píxeles ni puntos, sino por líneas y vectores, lo que permite ampliar la imagen sin pérdida de calidad. Inkscape se centra en este formato y permite a los diseñadores crear una gran variedad de gráficos, como ilustraciones, diagramas, iconos, logotipos, mapas, diseños y otras imágenes complejas, de forma sencilla. Permite crear imágenes renderizables utilizando formas vectoriales, como líneas, rectángulos, eclipses, estrellas, y texto, los cuales pueden rellenarse con colores, patrones y gradientes, además de modificar el borde de dichos objetos. En caso de que las herramientas incluidas no sean suficientes, dispone de una galería de extensiones instalables para personalizar y aumentar la funcionalidad del programa.
En este trabajo, el uso de Inkscape ha sido para casos específicos en los que se ha requerido una imagen, como puede ser para el logo de la herramienta. /*TODO: todavia no se sabe*/

{
	https://inkscape.org/es/acerca-de/
	https://inkscape.es/
	https://en.wikipedia.org/wiki/Inkscape
}

Navegador Web Firefox y Edge para hacer busquedas de informacion del codigo

/*TODO: poner lo que vaya a utilizar para diagramas*/


### Lenguajes

C/C++, con librerias Arduino y otras usadas para ESP32
	Bajo el framework espressif
MD para escribir la memoria



## Metodología
En este apartado se deben indicar las metodologías empleadas para planificación y desarrollo del TFG, así como explicar de modo claro y conciso cómo se han aplicado dichas metodologías.

Aqui se dicen como se han aplicado las herramientas

/*TODO: HABLAR AUTOMATIZACIONES, USO DE EXTENSIONES, TRELLO Y MI PLANTILLA, CONTROL DE VERSIONES*/

### Guía Rápida de las Metodologías de Desarrollo del Software

A continuación, se incluye una guía rápida que puede ser de gran utilidad en la elaboración de este capítulo.

#### Proceso de Desarrollo de Software

El proceso de desarrollo de software se denomina también ciclo de vida del desarrollo del software (SDLC, Software Development Life-Cycle) y cubre las siguientes actividades:

- Obtención y análisis de requisitos (requirements analysis). Es la definición de la funcionalidad del software a desarrollar. Suele requerir entrevistas entre los ingenieros de software y el cliente para obtener el 'qué' y 'cómo'. Permite obtener una especificación funcional del software.

- Diseño (SW design). Consiste en la definición de la arquitectura, los componentes, las interfaces y otras características del sistema o sus componentes.

- Implementación (SW construction and coding). Es el proceso de codificación del software en un lenguaje de programación. Constituye la fase en que tiene lugar el desarrollo de software.

- Pruebas (testing and verification). Verificación del correcto funcionamiento del software para detectar fallos lo antes posible. Persigue la obtención de software de calidad. Consisten en pruebas de caja negra y caja blanca. Las primeras comprueban que la funcionalidad es la esperada y para ello se verifica que, ante un conjunto amplio de entradas, la salida es correcta. Con las segundas se comprueba la robustez del código sometiéndolo a pruebas cuya finalidad es provocar fallos de software. Esta fase también incorpora las pruebas de integración en las que se verifica la interoperabilidad del sistema con otros existentes.

- Documentación (documentation). Persigue facilitar la mejora continua del software y su mantenimiento.

- Despliegue (deployment). Consiste en la instalación del software en un entorno de producción y puesta en marcha para explotación. En ocasiones implica una fase de entrenamiento de los usuarios del software.

- Mantenimiento (maintenance). Su propósito es la resolución de problemas, mejora y adaptación del software en explotación.

#### Metodologías de Desarrollo Software

Las metodologías son el modo en que las fases del proceso software se organizan e interaccionan para conseguir que dicho proceso sea reproducible y predecible para aumentar la productividad y la calidad del software.

Una metodología es una colección de:

- Procedimientos: indican cómo hacer cada tarea y en qué momento,

- Herramientas: ayudas para la realización de cada tarea, y

- Ayudas documentales.

Cada metodología es apropiada para un tipo de proyecto dependiendo de sus características técnicas, organizativas y del equipo de trabajo. En los entornos empresariales es obligado, a veces, el uso de una metodología concreta (p. ej. para participar en concursos públicos). El estándar internacional ISO/IEC 12270 describe el método para seleccionar, implementar y monitorear el ciclo de vida del software.

Mientras que unas intentan sistematizar y formalizar las tareas de diseño, otras aplican técnicas de gestión de proyectos para dicha tarea. Las metodologías de desarrollo se pueden agrupar dentro de varios enfoques según se señala a continuación.

- Metodología de Análisis y Diseño de Sistemas Estructurados (SSADM, Structured Systems Analysis and Design Methodology). Es uno de los paradigmas más antiguos. En esta metodología se emplea un modelo de desarrollo en cascada (waterfall). Las fases de desarrollo tienen lugar de modo secuencial. Una fase comienza cuando termina la anterior. Es un método clásico poco flexible y adaptable a cambios en los requisitos. Hace hincapié en la planificación derivada de una exhaustiva definición y análisis de los requisitos. Son metodologías que no lidian bien con la flexibilidad requerida en los proyectos de desarrollo software. Derivan de los procesos en ingeniería tradicionales y están enfocadas a la reducción del riesgo. Emplea tres técnicas clave:

  - Modelado lógico de datos (Logical Data Modelling),
  - Modelado de flujo de datos (Data Flow Modelling), y
  - Modelado de Entidades y Eventos (Entity EventModelling).

- Metodología de Diseño Orientado a Objetos (OOD, Object-Oriented Design). Está muy ligado a la OOP (Programación Orientada a Objetos) en que se persigue la reutilización. A diferencia del anterior, en este paradigma los datos y los procesos se combinan en una única entidad denominada objetos (o clases). Esta orientación pretende que los sistemas sean más modulares para mejorar la eficiencia, calidad del análisis y el diseño. Emplea extensivamente el Lenguaje Unificado de Modelado (UML) para especificar, visualizar, construir y documentar los artefactos de los sistemas software y también el modelo de negocio. UML proporciona una serie diagramas de básicos para modelar un sistema:

  - Diagrama de Clases (Class Diagram). Muestra los objetos del sistema y sus relaciones.
  - Diagrama de Caso de Uso (Use Case Diagram). Plasma la funcionalidad del sistema y quién interacciona con él.
  - Diagrama de secuencia (Sequence Diagram). Muestra los eventos que se producen
en el sistema y como este reacciona ante ellos.
  - Modelo de Datos (Data Model).

- Desarrollo Rápido de Aplicaciones (RAD, Rapid Application Developmnent). Su filosofía es sacrificar calidad a cambio de poner en producción el sistema rápidamente con la funcionalidad esencial. Los procesos de especificación, diseño e implementación son simultáneos. No se realiza una especificación detallada y se reduce la documentación de diseño. El sistema se diseña en una serie de pasos, los usuarios evalúan cada etapa en la que proponen cambios y nuevas mejoras. Las interfaces de usuario se desarrollan habitualmente mediante sistemas interactivos de desarrollo. En vez de seguir un modelo de desarrollo en cascada sigue un modelo en espiral (Boehm). La clave de este modelo es el desarrollo continuo que ayuda a minimizar los riesgos. Los desarrolladores deben definir las características de mayor prioridad. Este tipo de desarrollo se basa en la creación de prototipos y realimentación obtenida de los clientes para definir e implementar más características hasta alcanzar un sistema aceptable para despliegue.

- Metodologías Ágiles. "[...] envuelven un enfoque para la toma de decisiones en los proyectos de software, que se refiere a métodos de ingeniería del software basados en el desarrollo iterativo e incremental, donde los requisitos y soluciones evolucionan con el tiempo según la necesidad del proyecto. Así el trabajo es realizado mediante la colaboración de equipos auto-organizados y multidisciplinarios, inmersos en un proceso compartido de toma de decisiones a corto plazo. Cada iteración del ciclo de vida incluye: planificación, análisis de requisitos, diseño, codificación, pruebas y documentación. Teniendo gran importancia el concepto de "Finalizado" (Done), ya que el objetivo de cada iteración no es agregar toda la funcionalidad para justificar el lanzamiento del producto al mercado, sino incrementar el valor por medio de "software que funciona" (sin errores). Los métodos ágiles enfatizan las comunicaciones cara a cara en vez de la documentación. [...]"}[^agiles_wikipedia] 

[^agiles_wikipedia]: Fuente: [Wikipedia](https://es.wikipedia.org/wiki/Desarrollo_%C3%A1gil_de_software)

### Proceso de Testing

Se debe indicar qué tipo de pruebas se han realizado, por ejemplo las siguientes:

- Pruebas modulares (pruebas unitarias). Su propósito es hacer pruebas sobre un módulo tan pronto como sea posible. Las pruebas unitarias que comprueban el correcto funcionamiento de una unidad de código. Dicha unidad elemental de código consistiría en cada función o procedimiento, en el caso de programación estructurada y cada clase, para la programación orientada a objetos. Las características de una prueba unitaria de calidad son: automatizable (sin intervención manual), completa, reutilizable, independiente y profesional.
- Pruebas de integración. Pruebas de varios módulos en conjunto para comprobar su interoperabilidad.
- Pruebas de caja negra.
- Beta testing.
- Pruebas de sistema y aceptación.
- ...


###  Marco Tecnológico

En esta sección se enumeran las tecnologías y herramientas utilizadas en la elaboración del TFG. A continuación, se citan algunos ejemplos.

#### Herramientas CASE (Computer Aided Software Engineering)

Las herramientas CASE están destinadas a facilitar una o varias de las tareas implicadas en el ciclo de vida del desarrollo de software. Se pueden dividir en la siguientes categorías:

- Modelado y análisis de negocio.
- Desarrollo. Facilitan las fases de diseño y construcción.
- Verificación y validación.
- Gestión de configuraciones.
- Métricas y medidas.
- Gestión de proyecto. Gestión de planes, asignación de tareas, planificación, etc.

#### IDE (Integrated Development Environment)

- Notepad++: [https://notepad-plus-plus.org/](https://notepad-plus-plus.org/)
- Visual Studio Code: [https://code.visualstudio.com/](https://code.visualstudio.com/)
- Atom: [https://atom.io/](https://atom.io/)
- GNU Emacs: [https://www.gnu.org/s/emacs/](https://www.gnu.org/s/emacs/)
- NetBeans: [https://netbeans.org/](https://netbeans.org/)
- Eclipse: [https://eclipse.org/](https://eclipse.org/)
- QtCreator: [https://www.qt.io/ide/](https://www.qt.io/ide/)
- jEdit: [http://www.jedit.org/](http://www.jedit.org/)

#### Depuración

- GNU Debugger: [https://www.gnu.org/s/gdb/](https://www.gnu.org/s/gdb/)

#### Repositorios y control de versiones

- Git: [https://git-scm.com/](https://git-scm.com/)
- Mercurial: [[https://www.mercurial-scm.org/](https://www.mercurial-scm.org/)
- Github: [https://github.com/](https://github.com/)
- Bitbucket: [https://bitbucket.org/](https://bitbucket.org/)
- SourceTree: [https://www.sourcetreeapp.com/](https://www.sourcetreeapp.com/)

#### Documentación

- LaTeX: [https://www.latex-project.org/](https://www.latex-project.org/)
- Markdown: [https://markdown.es/](https://markdown.es/)
- Doxygen: [https://www.doxygen.nl/](https://www.doxygen.nl/)
- DocGen: [http://mtmacdonald.github.io/docgen/docs/index.html](http://mtmacdonald.github.io/docgen/docs/index.html)
- Pandoc: [http://pandoc.org/](http://pandoc.org/)

#### Gestión y Planificación de Proyectos

- Trello: [https://trello.com/](https://trello.com/)
- Jira: [https://es.atlassian.com/software/jira](https://es.atlassian.com/software/jira)
- Asana: [https://asana.com/](https://asana.com/)
- Slack: [https://slack.com/](https://slack.com/)
- Basecamp: [https://basecamp.com/](https://basecamp.com/)
- Teamwork Proyects: [https://www.teamwork.com/project-management-software](https://www.teamwork.com/project-management-software)
- Zoho Projects: [https://www.zoho.com/projects/](https://www.zoho.com/projects/)
