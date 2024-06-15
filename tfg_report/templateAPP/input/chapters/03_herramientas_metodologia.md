# Herramientas y Metodología

## Herramientas

En este apartado se identifican y describen las distintas herramientas hardware y software que han permitido llevar a cabo este Trabajo de Fin de Grado.

### Hardware

El núcleo de este [TFG](#TFG) se basa en la programación de una placa de desarrollo, por lo que es necesario ciertos elementos hardware para llevarlo a cabo:

**Ordenador portátil**: es el componente principal para el desarrollo de este [TFG](#TFG), en el cual se han instalado las herramientas necesarias, se ha escrito el código, se ha accedido a herramientas y recursos en línea, y ha permitido subir el código a la placa. En este caso, el ordenador personal del alumno es un Lenovo Ideapad 3 15ALC6, cuyas características destacadas para este trabajo son:

- Procesador AMD Ryzen 7 5700 U, de 64 bits y lanzado en enero de 2021, que permite ejecutar aplicaciones y servicios aprovechando sus 8 núcleos, su alta frecuencia de 1,8 GHz hasta 4,3 GHz y su bajo consumo @Ryzen7Specs.
- 12 GB de RAM DDR4, que almacenan la información temporal generada por los programas en ejecución. Su capacidad determina cuántas tareas simultáneas se pueden ejecutar y su velocidad determina la rapidez de ejecución de estas.
- Almacenamiento interno SSD de 1 TB, encargado de almacenar de manera persistente información como el sistema operativo, las herramientas instaladas y los ficheros de código utilizados en el proyecto.
- 3 puertos USB, que permiten conectar distintos dispositivos simultáneamente al ordenador, como en este trabajo, las placas para subir el código y observar la salida por terminal durante la ejecución.
- Lector de tarjetas SD, utilizado para acceder al contenido de la tarjeta SD que se conecta a una de las placas (detallado posteriormente).
- Adaptador de red Bluetooth y Wi-Fi, para poder conectar el ordenador a Internet y acceder a los recursos necesarios para el desarrollo.

**Dos placas ESP32 DEVKIT V1**: ambas fueron cedidas por la [UCLM](#UCLM) para el desarrollo de este [TFG](#TFG). este tipo de placas contienen las mismas características que el SoC ESP32 mencionado en el apartado \ref{02_estado_arte.esp32} /*TODO: comprobar funcionamiento referencia*/. Concretando, utiliza el módulo ESP32-WROOM-32.
Las placas están distribuidas en una placa de pruebas o breadboard, permitiendo conectar distintos elementos a los pines de las placas mediante jump wires o cables puente, sin necesidad de soldadura ni diseñar circuitos integrados y facilitando la prueba de componentes. En este caso, tienen conectados distintos módulos y sensores que permiten ampliar las funciones de estas:

 - **Módulo lector de tarjeta microSD**: compuesto por un socket para insertar tarjetas microSD en un circuito impreso del cuál salen 7 pines para poder utilizar el bus SPI de las tarjetas microSD. El SPI o Serial Peripheral Interface es un estándar que se utiliza para transferir información entre circuitos integrados, como pueden ser la placa ESP32 DEVKIT y el lector de tarjetas. Los pines que tiene este módulo son los siguientes:
	- VCC: Entrada de energía, se conecta a una fuente de alimentación para alimentar el lector.
	- GND: Conexión a tierra, se conecta al terminal negativo de la fuente de alimentación.
	- Data In: También conocido como MOSI o Master Output Slave Input, se utiliza para enviar datos desde la placa ESP32 hasta la tarjeta microSD.
	- Data Out: También conocido como MISO o Master Input Slave Output, se utiliza para enviar datos desde la tarjeta microSD hasta la placa ESP32.
	- Serial Clock: Reloj SPI, se utiliza para sincronizar la transferencia de datos entre las placas.
	- Chip Select: Se utiliza para activar y desactivar la comunicación con el lector.
	- Card Detect: Se utiliza para detectar si hay una tarjeta insertada en el lector.
	Para este trabajo, el lector, cedido por la UCLM, se utiliza para leer y escribir datos en una tarjeta microSD desde la ESP32 DEVKIT V1 que actúe como broker y gestione los registros o logs y las direcciones de los dispositivos suscritos contenidos. 
 - **Sensor DHT11**: sensor digital capaz de medir la temperatura y la humedad, cedido por la UCLM. Alimentado por 3,3 o 5 voltios, es capaz de leer la humedad en el ambiente entre los rangos 20 y 95% (con un 5% de fallo) y la temperatura entre 0 y 50 ºC (con 2 ºC de fallo).
 - **Potenciómetro BQ Zum Kit Advanced**: contenido originalmente en un kit junto a varios sensores y una placa controladora @Pot_TiendaBQ @Pot_KitBQ, este potenciómetro de señal analógica cedido por la UCLM es capaz de devolver un valor en función a su rotación, siendo su rotación máxima 300º, al alimentarlo con 3,3 o 5 voltios @Pot_TiendaRobotica.

**Placa ESP32-2432S028R**: esta placa proporcionada por el autor y popularmente conocida como Cheap-Yellow-Display o CYD para abreviar, se ha utilizado para hacer pruebas del funcionamiento de la herramienta desarrollada, y al igual que las anteriormente mencionadas placas ESP32, está potenciado por un ESP32-WROOM-32. En cuanto a componentes integra:

 - Pantalla LCD de 2,8 pulgadas con resolución 320x240 píxeles, y táctil de tipo resistivo.
 - LED multicolor RGB.
 - Lector de tarjeta microSD.
 - Sensor LDR, cuyo valor que devuelve depende de la resistencia que le otorga la luz que recibe.
 - Conectores y pines adicionales para conectar un altavoz y otros módulos.

**Tarjeta microSD**: tarjeta proporcionada por el alumno autor y utilizada por una de las placas con lector de tarjetas para almacenar los registros o logs y las direcciones de los dispositivos suscritos al broker. Las características de la tarjeta no son deterministas para la tarjeta, ya que las especificaciones no afectan al rendimiento de la herramienta resultante de este [TFG](#TFG). En este caso, la tarjeta microSD utilizada es de la marca Samsung y cuenta con capacidad de almacenamiento de 1 [GB](#GB).

**Adaptador de tarjeta microSD a SD**: proporcionada por el autor, permite utilizar una tarjeta microSD en un lector de tarjetas SD normal al adaptar su tamaño y forma. Se ha utilizado para leer, modificar y eliminar contenidos de la tarjeta microSD desde el ordenador portátil, útil para hacer probar el funcionamiento de la herramienta.

{
	https://www.sparkfun.com/products/544
	https://es.wikipedia.org/wiki/Serial_Peripheral_Interface
	https://tienda.bricogeek.com/sensores-temperatura/1574-modulo-sensor-dht11-humedad-y-temperatura.html
	https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/
}

### Software

Para poder realizar el desarrollo correcto de este [TFG](#TFG), se han requerido las siguientes piezas de software:

**Windows 10**[^herramientasSw:w10]: el sistema operativo es clave para poder hacer funcionar el Trabajo de Fin de Grado. En este caso, el autor ha utilizado la versión más reciente a fecha de la escritura de este documento, 22H2. Este sistema operativo desarrollado por Microsoft se encuentra instalado en el ordenador portátil mencionado en el apartado de hardware /*TODO: mencionar*/, y debido a su alta popularidad tiene una gran compatibilidad con la mayoría de aplicaciones existentes, y en este caso es beneficioso para el resto de software mencionado posteriormente. Además, integra:

- Windows Update y Windows Defender: Permite tener el sistema en la última versión y seguro gracias a los últimos parches de seguridad, una capa de protección importante para los ficheros, la información contenida y la integridad del propio sistema al estar conectado a Internet e instalar aplicaciones. 
- Explorador de archivos: Como su nombre lo indica, permite navegar entre carpetas y acceder a los archivos, tanto de los discos duros instalados internamente como los externos (por ejemplo, pendrives, tarjetas de memoria o discos).
- Bloc de notas: Esta herramienta es ideal para crear y editar ficheros de texto plano o, en el caso de este desarrollo, ver ficheros de código de manera rápida.
- Drivers: Ofrecen compatibilidad y rendimiento con todo el hardware contenido en el ordenador, como procesador, tarjeta gráfica, teclado y ratón, puertos USB, lectores de tarjetas y otros dispositivos externos. En este caso, para poder hacer uso de las placas, se ha necesitado instalar un driver adicional. /*TODO: añadir enlace*/

La relevancia de usar Windows 10 es mínima, ya que es posible de adaptar el proyecto a un entorno en Linux con pocas o nulas complicaciones. El uso de Windows 10 ha sido decisión del autor por gusto.

[^herramientasSw:w10]: <https://www.microsoft.com/es-es/software-download/windows10>

**GitHub**[^herramientasSw:gh]: es una plataforma en la nube desarrollada en abril de 2008 utilizando Ruby on Rails y adquirida por Microsoft en octubre de 2018. Permite a los equipos de desarrolladores almacenar código, colaborar y realizar cambios en proyectos compartidos, alojados en esta plataforma en forma de repositorios de Git.
Git es un sistema de control de versiones de código abierto creado en 2005 por Linus Torvalds, que permite a cualquier desarrollador gestionar el código fuente y el historial de cambios mediante comandos ejecutados en una terminal. Tiene la característica de ser distribuido, permitiendo usar ramas para aislar partes del código, como pueden ser nuevas funcionalidades en desarrollo, sin afectar al código final desplegado. Cada parte del equipo puede crear una rama, integrar los cambios necesarios y luego fusionarla con la rama principal para hacer efectivos estos cambios. Esto es útil para añadir varias funcionalidades simultáneamente, permitir que varias personas trabajen en los mismos archivos, comprobar las diferencias entre estos, aprobarlas y volver a una versión funcional anterior en caso de que errores. GitHub aprovecha estas funcionalidades con sus repositorios y las aplica a su interfaz web, haciendo su uso sea más accesible para usuarios con poco conocimiento técnico al evitar recordar comandos específicos.

Desde un repositorio en GitHub se pueden crear y modificar ramas, cargar ficheros, realizar *commits* (la unidad de trabajo de GitHub que representa un cambio en el repositorio), ver su histórico para hacer un seguimiento de los cambios realizados, obtener las modificaciones realizadas por otros usuarios y hacer *pull requests* (solicitudes de cambios) para integrar estos cambios en el proyecto. GitHub va un paso más allá de alojar proyectos, ya que permite la gestión de proyectos y la interacción del equipo de desarrollo a través de *issues* que retroalimentan el proyecto y ofrecen ideas, asignación de responsabilidades, hitos, etiquetas, discusiones, y gráficos y tableros estilo Kanban que permiten observar fácilmente el trabajo realizado y por hacer.

Los repositorios pueden ser públicos o privados, siendo en este último caso que el repositorio solo pueden ser vistos por los usuarios agregados y cuya funcionalidad está limitada. La plataforma permite a los usuarios interactuar con repositorios de otros usuarios, incluidos los públicos (GitHub es comúnmente utilizado para alojar proyectos de código abierto), contribuyendo o realizando una bifurcación para adaptarlo como un proyecto distinto. Otras funciones que incluye GitHub son:

- Documentación de proyectos, mediante la creación de ficheros de texto "readme" o "léeme" en lenguaje Markdown en los directorios del proyecto.
- Creación de wikis.
- Automatización de pruebas, lanzamientos y despliegues con GitHub Actions, especificando los pasos a ejecutar tras una acción específica realizada en el repositorio.
- GitHub Codespaces, un [IDE](#IDE) online.
- Alojamiento de páginas web estáticas con GitHub Pages como parte de un repositorio, como blogs, documentación de código y libros.
- Gists o fragmentos de código compartibles o utilizables con soporte de control de versiones.

GitHub además soporta planes de pago para aumentar la funcionalidad que ofrece, proporcionar soporte personalizado a los usuarios y quitar limitaciones de repositorios privados.

En el caso de este proyecto, se ha utilizado, con el plan gratuito de GitHub, un repositorio privado durante el desarrollo para alojar el código, compartirlo fácilmente con los tutores para enviar dudas e informar del estado del proyecto, y llevar un histórico de los cambios realizados. Posteriormente, se ha modificado la visibilidad del repositorio a público para compartir el proyecto a través de la plataforma de librerías de PlatformIO (mencionado en los siguientes puntos) y aprovechar la funcionalidad de GitHub Pages para incluir una página web estática que documente las distintas funciones que componen el proyecto, ambas funciones automatizadas a través de GitHub Actions /*TODO: realizar*/. Pese a conocer alternativas a la plataforma, como GitLab, se ha decidido utilizar GitHub por la experiencia previa del alumno y la facilidad de uso que ofrece.

Otra herramienta que ofrece GitHub para no separar la funcionalidad del escritorio local es **GitHub Desktop**[^herramientasSw:ghDesktop], que permite simplificar el flujo de trabajo del desarrollador y centrarse en su trabajo. Proporciona una interfaz gráfica que evita interactuar directamente con Git para clonar proyectos, hacer *commits*, cambiar de rama y ver los cambios y diferencias en los archivos.

[^herramientasSw:gh]: <https://github.com/>
[^herramientasSw:ghDesktop]: <https://desktop.github.com/>

{
	https://docs.github.com/es/get-started/start-your-journey/about-github-and-git
	https://www.hostinger.es/tutoriales/que-es-github
	https://en.wikipedia.org/wiki/GitHub
	https://docs.github.com/en/pull-requests/committing-changes-to-your-project/creating-and-editing-commits/about-commits
	https://docs.github.com/es/issues/tracking-your-work-with-issues/about-issues
	https://desktop.github.com/
}

**Visual Studio Code**[^herramientasSw:vsc]: es un [IDE](#IDE) ligero y de código abierto creado por Microsoft el 29 de abril de 2015, que funciona como un potente editor de código altamente personalizable y ejecutable en Windows, macOS, Linux y navegadores web. El editor no se basa en un sistema de proyectos, sino que permite al usuario abrir uno o varios directorios simultáneamente, formando workspaces o espacios de trabajos compuestos por ficheros que pueden contener distintos lenguajes de programación. Por defecto, soporta los lenguajes JavaScript, TypeScript y Node.js, pero esta lista se puede ampliar mediante extensiones para utilizarlo con C++, Java, Python y otros lenguajes. Estas extensiones, creadas por Microsoft o por terceros, están disponibles en un repositorio central, y además permiten personalizar y extender las funcionalidades del editor, adaptándose a las necesidades del usuario.

Visual Studio Code integra una serie de funcionalidades que lo convierten en un editor ideal para incrementar la productividad del usuario y perfecto para su uso diario, tales como el subrayado de sintaxis y errores, sangría automática, refactorización, autocompletado, sugerencias y fragmentos de código. Ofrece la posibilidad de compilar y ejecutar fácilmente los ficheros de código y proyectos simplemente haciendo clic en el botón de "play", evitando la necesidad de aprender comandos o repetirlos constantemente y agilizando el trabajo del desarrollador. En aquellas ejecuciones de código que pueden resultar en error o son difíciles de comprender ayuda a realizar comprobaciones mediante un depurador interactivo, que permite recorrer el código fuente con puntos de interrupción, inspeccionar variables, ver pilas de llamadas y modificar líneas de código en ejecución.

Es compatible con Git y con el control de versiones en dispositivos con Git instalado y en proyectos que formen parte de un repositorio Git, ofreciendo al usuario la posibilidad de ver las diferencias y cambios con la versión localizada en el repositorio, sin necesidad de salir de la aplicación ni usar comandos complejos en la terminal.

La funcionalidad que ofrece Visual Studio Code no se ve limitada únicamente a la interfaz de usuario, ya que dispone de una lista de comandos ejecutables que se pueden asignar a atajos de teclado.

Este ha sido el [IDE](#IDE) de preferencia para el desarrollo de este trabajo, y se ha complementado con las siguientes extensiones:

- PlatformIO IDE[^herramientasSw:vscPlatformIO]: habilita el uso de Visual Studio Code como [IDE](#IDE) para el desarrollo de software embebido para distintas plataformas y frameworks utilizando el sistema de PlatformIO (explicado posteriormente) @PlatformIO_VSMarketplace. 
- C/C++ Extension Pack[^herramientasSw:vscCppPack]: un conjunto de tres extensiones que permiten utilizar Visual Studio Code para el desarrollo de proyectos en C/C++, incluyendo características como resaltado de sintaxis, completado de código, depuración y comprobación de errores @CppExtension_VSMarketplace @CppProgrammingVSC.
- GitHub Copilot[^herramientasSw:vscGHCopilot]: una herramienta de programación basada en inteligencia artificial que ayuda al desarrollador a escribir código de forma rápida e inteligente @GHCopilot_VSMarketplace. Esta herramienta se puede utilizar para recibir ayuda en cualquier librería, lenguaje y framework popular, ya que el entrenamiento de esta IA se ha realizado a partir de los repositorios públicos alojados en GitHub @GHCopilot_VSMarketplace. GitHub Copilot ofrece sugerencias de código inteligentes mientras se escribe, basándose en el contexto y en los comentarios del propio código. Asimismo, proporciona un chat para realizar consultas sobre cualquier tarea del código, como pedir explicaciones, informarse acerca de conceptos de programación y guiar al usuario para mejorar su código o implementar nuevas funcionalidades @GHCopilot_VSMarketplace @GHCopilot_Overview.
El uso de esta herramienta está limitado a los usuarios de pago o a quienes disponen de un GitHub Student Developer Pack tras asociar la cuenta de GitHub con el correo de la institución académica. También dispone de una versión de prueba @GHEducation.
- Better Comments[^herramientasSw:vscBetterComments]: añade diferencias de estilo y enfatizaciones a comentarios en el código destinados a alertar, hacer peticiones, indicar acciones por realizar o TODOs, o remarcar información importante, logrando así comentarios más comprensibles @BetterComments_VSMarketplace.
- TODO Highlight[^herramientasSw:vscTodoHighlight] y Todo Tree[^herramientasSw:vscTodoTree]: ambas extensiones se utilizan en conjunto para llevar un seguimiento de las tareas que se deben realizar en el código, evitando que el desarrollador las olvide. La primera extensión resalta las líneas que contienen el texto "TODO" y "FIXME" @TODOHighlight_VSMarketplace, útil para llamar la atención del usuario que recorre las líneas del código, mientras que la segunda muestra en forma de árbol todos los "TODO" y "FIXME" que se encuentren en el código @TodoTree_VSMarketplace, para poder agruparlos en un mismo lugar y acceder a ellos fácilmente.
- Code Spell Checker[^herramientasSw:vscSpellChecker]: un corrector ortográfico que marca los errores ortográficos detectados en los comentarios y en el código, y que ayuda a solucionarlos a través de sugerencias @SpellChecker_VSMarketplace.
- Doxygen Documentation Generator[^herramientasSw:vscDoxygenDoc]: permite generar automáticamente en formato Doxygen los comentarios junto a parámetros como las descripciones, los parámetros y los valores retornados para su uso en la documentación. Además, ofrece soporte para autocompletado y sugerencias de comandos Doxygen @DoxygenGenerator_VSMarketplace.

[^herramientasSw:vsc]: <https://code.visualstudio.com/>
[^herramientasSw:vscPlatformIO]: <https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide>
[^herramientasSw:vscCppPack]: <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack>
[^herramientasSw:vscGHCopilot]: <https://marketplace.visualstudio.com/items?itemName=GitHub.copilot>
[^herramientasSw:vscBetterComments]: <https://marketplace.visualstudio.com/items?itemName=aaron-bond.better-comments>
[^herramientasSw:vscTodoHighlight]: <https://marketplace.visualstudio.com/items?itemName=wayou.vscode-todo-highlight>
[^herramientasSw:vscTodoTree]: <https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree>
[^herramientasSw:vscSpellChecker]: <https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker>
[^herramientasSw:vscDoxygenDoc]: <https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen>

{
	https://code.visualstudio.com/docs/editor/whyvscode
	https://en.wikipedia.org/wiki/Visual_Studio_Code
}

**PlatformIO**[^herramientasSw:platformIO]: es una herramienta de código abierto para ingenieros y desarrolladores de software de sistemas embebidos. Permite desarrollar software desde cualquiera de los sistemas operativos modernos de manera sencilla para todo tipo de usuarios, tanto aficionados como profesionales, incluyendo las herramientas necesarias para compilar, ejecutar, subir y escribir el código. Ofrece una amplia compatibilidad, con soporte para más de mil placas embebidas diferentes, más de 40 plataformas de desarrollo y más de 20 marcos de trabajo o frameworks.

PlatformIO aloja uno de los mayores registros de librerías embebidas en PlatformIO Registry, lo que permite explorar e instalar de manera sencilla distintas bibliotecas de código, plataformas y herramientas, listadas junto a ejemplos e instrucciones de uso. Este registro se puede utilizar desde la interfaz gráfica de la herramienta, por línea de comandos y desde su página web[^herramientasSw:platformIOReg].

Una de sus características más importantes es la gestión de dependencias integrada. Es común que los proyectos aprovechen funcionalidades ofrecidas en bibliotecas, por lo que el usuario debe referenciar la biblioteca y PlatformIO se encarga de resolver las dependencias al compilar el código. Estas bibliotecas soportadas pueden estar en local (como carpetas o ficheros comprimidos), en un repositorio con control de versiones (como Git) o en el PlatformIO Registry.

Además, contiene un depurador de código, un analizador estático de código, un monitor de puerto serial y soporte para pruebas unitarias.

La manera de utilizar PlatformIO en un proyecto es sencilla, solo es necesario instalar el [IDE](#IDE), indicar la placa y el framework de interés, y PlatformIO se encarga de la descarga e instalación de las herramientas necesarias de forma automática. Además, ofrece cierta flexibilidad y opciones a los desarrolladores, que pueden decidir si usar la herramienta por línea de comandos o con la versión gráfica.

Esta herramienta se integra con otros [IDE](#IDE)s o editores de texto a través de extensiones, siendo Visual Studio Code el más recomendado.

El código de este proyecto se ha creado con PlatformIO y se ha configurado para utilizar la placa ESP32 DEVKIT V1 con la plataforma Espressif32. En cuanto al framework, se ha utilizado el de Arduino, pese a ser posible también utilizar el de Espressif (ESP-IDF), debido a que cumple las necesidades del desarrollador, a la experiencia previa con placas de desarrollo Arduino por parte del autor y a la facilidad de uso. Las diferencias entre ambos son las siguientes:

- El framework ESP-IDF ofrece un soporte completo de los lenguajes C y C++, permitiendo escribir código eficiente y de alto rendimiento. Por otro lado, Arduino utiliza una implementación simplificada y adaptada a los microcontroladores, limitando la flexibilidad y funcionalidad del código.
- Las aplicaciones desarrolladas con ESP-IDF están preparadas para hacer uso de los núcleos disponibles en la placa y  su estructura se basa en tareas, mientras que en Arduino por defecto solo se aprovecha de un núcleo y las aplicaciones siguen una estructura en la que se debe declarar una función `setup` y otra `loop`.
- El framework de Arduino es útil si previamente el desarrollador lo ha utilizado para desarrollar en otras placas, además de ser fácil de usar para quienes no tienen mucha experiencia, y contiene un gran rango de librerías y APIs por defecto que facilitan el desarrollo. En cambio, ESP-IDF se puede utilizar para desarrollar software que requiera controlar funciones avanzadas del hardware, como el consumo de energía y recursos, e incluye un mayor conjunto de herramientas para depurar la placa y gestionar el uso de la memoria.
- En cuanto a la comunidad, debido a la implementación de Arduino en una gran variedad de placas, es la que mayor comunidad tiene en comparación con ESP-IDF.

[^herramientasSw:platformIO]: <https://platformio.org/>
[^herramientasSw:platformIOReg]: <https://registry.platformio.org/>

{
	https://docs.platformio.org/en/latest/what-is-platformio.html
	https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide
	https://docs.platformio.org/en/latest/platforms/index.html
	https://docs.platformio.org/en/latest/librarymanager/dependencies.html
	https://docs.platformio.org/en/latest/integration/ide/index.html
	https://registry.platformio.org/
	https://www.espboards.dev/blog/esp-idf-vs-arduino-core/
}

**Trello**[^herramientasSw:trello]: es una aplicación web que permite elaborar listas con tareas de forma visual al estilo Kanban. Fue creada en 2011 por Fog Creek Software y vendida a Atlassian, su actual dueño, en 2017.

Se basa en tableros personalizables donde se muestran y categorizan ideas o tareas, compuestos principalmente por:

- Listas: representadas en formato de columnas, suelen hacer referencia a las distintas fases que puede tener una tarea. Por ejemplo, en un tablero puede haber tres listas: "por hacer", "en curso" y "hecho".
- Tarjetas: cada tarjeta en un tablero puede ser una tarea o idea relacionada con el trabajo o proyecto, y se colocan en las columnas correspondientes según su estado o tipo. La idea de las tarjetas es moverlas según avance el desarrollo del proyecto. Se les puede además añadir un miembro asignado para reflejar qué usuario está encargado de la tarea, evitando la necesidad de preguntar personalmente; fechas de vencimiento de la tarea, con capacidad de notificar según se acerque la fecha y de marcarlas como realizadas; ficheros adjuntos para organizarlos, descripción, comentarios y checklists para dividir una tarea grande en varias tareas pequeñas.
- Miembros: cada uno con responsabilidades asignadas a las tarjetas y permisos para utilizar el tablero.

Trello se puede utilizar tanto para fines personales como empresariales, sin importar el tamaño del proyecto, utilizando los tableros para, por ejemplo, la gestión de proyectos de software, realizar anuncios escolares, planificar clases o gestionar los casos en un despacho de abogados. Gracias a la concentración de la información en un tablero, que permite observar todo de un rápido vistazo, se puede realizar un seguimiento sencillo de las tareas y sus plazos, coordinar a los miembros de un equipo y llevar a cabo reuniones productivas y motivadoras.

Trello tiene la capacidad de ampliar la funcionalidad gracias a las integraciones con otras aplicaciones (como Slack, Gmail o GitHub), a las automatizaciones de tablero sin código (por ejemplo, mover una tarjeta a una determinada lista cuando se complete) para centrarse únicamente en el trabajo, y a los *power-ups*, que actúan como extensiones de la funcionalidad básica de Trello recopiladas en un catálogo.

Para el proyecto, el alumno ha creado un tablero adaptado a sus necesidades (detallado posteriormente) usando el plan gratuito de Trello. Este tablero permite llevar un seguimiento de todas las tareas, tanto de código como de la memoria, realizadas durante el desarrollo, y ha facilitado las reuniones de seguimiento al poder mostrar a los tutores el estado de las tareas. Utiliza los siguientes *power-ups*:

- GitHub[^herramientasSw:trelloGH]: sirve para llevar un seguimiento de lo sucedido en GitHub desde el tablero, como adjuntar a tarjetas ramas, commits, incidencias y pull requests y asociar repositorios a tarjetas @GH_TrelloPU.
- Smart Fields[^herramientasSw:trelloSmartFields]: permite crear campos personalizados en las tarjetas, como campos de texto, de número o de fecha, y soporta el uso de fórmulas para calcular el valor del campo. Estos campos se pueden mostrar desde la vista general del tablero, sin necesidad de entrar a ver los detalles de la tarjeta @SmartFields_TrelloPU.

[^herramientasSw:trello]: <https://trello.com/es>
[^herramientasSw:trelloGH]: <https://trello.com/power-ups/55a5d916446f517774210004/github>
[^herramientasSw:trelloSmartFields]: <https://trello.com/power-ups/5e2212c3ba57415ef2ef9352/smart-fields>

{
	https://en.wikipedia.org/wiki/Trello
	https://trello.com/es
	https://trello.com/es/about
	https://trello.com/es/tour

}
	
**Doxygen**[^herramientasSw:doxygen]: Utilizada para la documentación de este trabajo, esta herramienta de código abierto, muy empleada en el desarrollo de software, permite obtener documentación a partir del código de forma sencilla. Desde su primera versión, lanzada el 26 de octubre de 1997, posibilita la generación automática de documentación en distintos formatos, como [HTML](#HTML), [PDF](#PDF), Word y [XML](#XML), a partir de los comentarios insertados en el código durante el desarrollo, analizando la información de las distintas clases, funciones y variables. Gracias a esta automatización, se agiliza y estandariza el proceso de documentación de proyectos, lo cual es beneficioso para entender el proyecto y el código que lo compone, además de mejorar la colaboración entre los miembros del equipo de desarrollo y el mantenimiento del propio código.

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

En el caso de este trabajo, se ha generado documentación en formato [HTML](#HTML) para crear una página web con toda la información de las distintas funciones que componen el proyecto, y se ha personalizado con Doxygen Awesome[^herramientasSw:doxygenAwesome], un tema [CSS](#CSS) aplicable a la página para disponer de una página con un aspecto moderno, limpio y compatible con la interfaz móvil.

[^herramientasSw:doxygen]: <https://doxygen.nl/>
[^herramientasSw:doxygenAwesome]: <https://jothepro.github.io/doxygen-awesome-css/>

{
	https://doxygen.nl/
	https://en.wikipedia.org/wiki/Doxygen
	https://jothepro.github.io/doxygen-awesome-css/
}

**Plantilla de [TFG](#TFG)**[^herramientasSw:plantilla]: Fue desarrollada por Félix Albertos Marco, profesor del Grado de Ingeniería Informática de la sede de la [UCLM](#UCLM) de Talavera de la Reina, ofreciendo una alternativa para desarrollar la memoria del Trabajo de Fin de Grado. Esta plantilla, utilizada en este [TFG](#TFG), se caracteriza por emplear Markdown para redactar todos los apartados, evitando las complicaciones del formato del documento (como el interlineado, fuentes, cabeceras y pie de página y saltos de página), además de proporcionar la portabilidad del trabajo, ya que estos ficheros son de marcado ligero y no necesitan editores ni sistemas operativos específicos. El soporte de Markdown también incluye todos los elementos que este lenguaje ofrece, como tablas, listados, fragmentos de código o formateado del texto.

Esta plantilla está compuesta por una serie de ficheros y directorios donde el autor debe ir cumplimentando todo lo necesario que quiera reflejar en el documento final. En la raíz del proyecto se encuentra un fichero `config.yaml` donde especificar las propiedades del [TFG](#TFG) (título, autor, tutores, departamento y fecha), y en el mismo nivel se encuentra la carpeta `input`. Dentro de esta, existen ficheros ya creados con ciertos apartados del documento, como el resumen, los acrónimos, la dedicatoria y la declaración de autoría, además de una carpeta para introducir los apartados de anexo y otra para los capítulos. Los apartados y capítulos se escriben en ficheros nombrados con el formato `XX_nombre_capitulo.md`. Además, esta plantilla soporta la inserción de imágenes y las referencias bibliográficas, ambas se deben realizar desde la carpeta de recursos.

El funcionamiento de esta plantilla es sencillo, ya que opera con una imagen Docker que, utilizando la herramienta Pandoc, convierte los ficheros a LaTeX y genera el documento PDF final, simplemente ejecutando el comando `make docker` (en el caso de tener instalado Docker) o ejecutando la herramienta en una máquina GNU/Linux. La combinación de las características de la plantilla de Félix Albertos permite al alumno centrarse únicamente en el contenido que tiene que escribir, agilizando notablemente el desarrollo del trabajo.

[^herramientasSw:plantilla]: <https://www.felixalbertos.com/resources/downloads/tfg_template.html>

{
	https://www.felixalbertos.com/resources/downloads/tfg_template.html
}

**Teams**[^herramientasSw:teams]: es una aplicación multiplataforma de colaboración en equipo, desarrollada en marzo de 2017 por Microsoft como competencia a Slack. Se puede utilizar de manera gratuita con el plan personal o con una licencia Microsoft 365, diferenciándose en ambos casos la versión empresarial de la personal debido a sus limitaciones.

Microsoft 365 es una suscripción que incluye las aplicaciones de Microsoft Office (Word, PowerPoint y Excel), almacenamiento en la nube, copias de seguridad y correo electrónico, que habilita el uso en la nube de éstas y permite mantener siempre la última versión con los parches de seguridad correctos mediante un pago mensual o anual. La [UCLM](#UCLM) provee a sus usuarios de cuentas de Microsoft 365 Empresa, por lo que se ha aprovechado esta suscripción para este desarrollo.

Teams permite comunicarse con personas a través de mensajes instantáneos formateables, con soporte para menciones, respuestas, adjuntos y traducciones; y a través de reuniones de dos o varios participantes, en forma de llamadas de audio o videollamadas, con capacidad de compartir pantalla, grabar la reunión, colaborar en aplicaciones (como una pizarra compartida) y traducción y transcripción en tiempo real. Tanto las traducciones como las transcripciones reducen la barrera del lenguaje que puede surgir entre personas de diferentes regiones al trabajar en conjunto. Estas opciones de comunicación evitan el uso de múltiples programas o tecnologías, centralizando así toda la comunicación.

Se basa en el concepto de equipos o *teams*, espacios de trabajo compartido para comunidades, grupos o equipos de personas. Se utilizan para compartir mensajes, contenido y herramientas entre los miembros que lo componen, y pueden ser privados o públicos, permitiendo asignar roles y responsabilidades sobre el propio equipo a los miembros. Dentro de los equipos están los canales, áreas para tener conversaciones sobre temas específico en los que es posible restringir el acceso únicamente a ciertos miembros del equipo. Tener canales dentro de los equipos permite subdividir el equipo en grupos de trabajo, agrupar las conversaciones, almacenar ficheros compartidos y reunirse con el resto de miembros.

Por otro lado, para realizar una comunicación directa o en grupos pequeños se pueden utilizar chats normales en lugar de equipos.

Teams dispone de otras funciones, como aplicaciones instalables dentro del propio software que permiten ampliar la funcionalidad, y un calendario con capacidad de programar reuniones y enviarlas a otros usuarios para que las acepten o las declinen.

Para este [TFG](#TFG), Microsoft Teams ha permitido mantener un contacto directo entre los tutores y el alumno a través de un equipo organizado por canales destinados a las partes de desarrollo y memoria. Estos han agilizado la consulta de dudas y de disponibilidad, y organizar archivos compartidos. Por ejemplo, en el canal destinado a la memoria se alojaron las distintas versiones del documento de la memoria, mientras que en el canal de desarrollo se encuentran enlaces, manuales y códigos de ejemplo. Además, se han programado y celebrado reuniones de seguimiento en esta aplicación, de la cual tanto el alumno como los tutores tenían experiencia de uso.

[^herramientasSw:teams]: <https://www.microsoft.com/es-es/microsoft-teams/group-chat-software/>

{
	https://teamsdemo.office.com
	https://en.wikipedia.org/wiki/Microsoft_Teams
	https://www.microsoft.com/es-es/microsoft-teams/compare-microsoft-teams-business-options
	https://www.microsoft.com/es-ES/microsoft-365/buy/compare-all-microsoft-365-products
	}


**Visio**[^herramientasSw:visio]: Es un programa para crear diagramas y vectores, creado por Visio Corporation en 1992 y traspasado a Microsoft tras la compra de la empresa el 7 de enero de 2000. Su uso está limitado a los usuarios con licencia de Microsoft 365, servicio mencionado anteriormente y del cual la [UCLM](#UCLM) distribuye la licencia a todos los usuarios de la universidad, como es el caso del autor, quien ha destinado el uso de la aplicación al dibujo de algunos esquemas de la memoria. Este programa, disponible tanto en línea como en una aplicación descargable, permite crear diagramas, imágenes vectoriales y objetos fácilmente, facilitando la visualización de datos e ideas de forma atractiva, lo cual es útil en equipos y en documentación para asegurar de manera sencilla la comprensión de los conceptos.

El programa contiene plantillas personalizables para que los usuarios no partan desde cero en la creación del diagrama, y con las extensas librerías de objetos que incluye se pueden crear diagramas profesionales, como los de flujo, red, Venn, bloques, UML, PERT, organigramas, matrices de negocio o mapas mentales. También ofrece compatibilidad con otras herramientas de Microsoft, como Teams para realizar diagramas en colaboración, y Power BI o Excel, para ofrecer una manera alternativa de visualizar los datos. Los objetos creados con este programa se pueden compartir en su propio formato VSDX, o exportarlos en otros más comunes como [JPEG](#JPEG), [PNG](#PNG) y [PDF](#PDF) para hacerlos accesibles.

[^herramientasSw:visio]: https://www.microsoft.com/es-es/microsoft-365/visio/flowchart-software/

{
	https://www.microsoft.com/es-es/microsoft-365/visio/flowchart-software#x68bca46524744e268ea489ad8cc29bbb
	https://en.wikipedia.org/wiki/Microsoft_Visio
}


**Inkscape**[^herramientasSw:inkscape]: Es una herramienta de software gratuita, multiplataforma y de código abierto que permite diseñar gráficos vectoriales. Surgió en 2003 como una bifurcación de otro editor con el mismo propósito, Sodipodi. Este programa permite generar y manipular ficheros [SVG](#SVG), en los cuales las imágenes no están dibujadas por píxeles ni puntos, sino por líneas y vectores, lo que permite ampliar la imagen sin pérdida de calidad. Inkscape se centra en este formato y permite a los diseñadores crear una gran variedad de gráficos, como ilustraciones, diagramas, iconos, logotipos, mapas, diseños y otras imágenes complejas, de forma sencilla. Permite crear imágenes renderizables utilizando formas vectoriales, como líneas, rectángulos, eclipses, estrellas, y texto, los cuales pueden rellenarse con colores, patrones y gradientes, además de modificar el borde de dichos objetos. En caso de que las herramientas incluidas no sean suficientes, dispone de una galería de extensiones instalables para personalizar y aumentar la funcionalidad del programa.

En este trabajo, el uso de Inkscape ha sido para casos específicos en los que se ha requerido una imagen, como puede ser para el logo de la herramienta. /*TODO: todavia no se sabe*/

[^herramientasSw:inkscape]: <https://inkscape.org/es/>

{
	https://inkscape.org/es/acerca-de/
	https://inkscape.es/
	https://en.wikipedia.org/wiki/Inkscape
}

**Navegador web**, como Firefox[^herramientasSw:firefox] y Microsoft Edge[^herramientasSw:edge]: utilizados en este proyecto para acceder a las herramientas web mencionadas anteriormente y realizar búsquedas de información acerca de partes del código en desarrollo y del contenido de esta memoria.

[^herramientasSw:firefox]: <https://www.mozilla.org/es-ES/firefox/new/>
[^herramientasSw:edge]: <https://www.microsoft.com/es-es/edge/>


/*TODO: poner lo que vaya a utilizar para diagramas*/


### Lenguajes

C++, con librerias Arduino y otras usadas para ESP32

Lenguaje de programación
Diseñado en 1979 por Bjarne Stroustrup
Creado para extender C y añadir mecanismos de manipulación de objetos
Desde el punto de vista de los lenguajes orientados a objetos, C++ es híbrido
Luego se añadieron facilidades de programación genérica, sumados a los paradigmas de prog estructurada y progr orientada a objetos. C++ es multiparadigma
Lenguaje compilado, multiparadigma, de tipo imperativo y orientado a objetos
	Programa escrito en lenguaje imperativo: conjunto de instrucciones que indican al computador cómo realizar una tarea
	Significado lenguaje imperativo:
	- Se conoce en cada paso del programa su estado, determinado por el valor que toman las variables usadas. Variables: posiciones de memoria
	- Se altera el estado del programa a través de sentencias (instrucciones)
	El hw de la mayoría de computadores está diseñado para ejecutar código máquina escrito de forma imperativo
Incluye tambien programacion generica y funcional





/*TODO: hablar del framework	Bajo el framework espressif*/

Junto a este lenguaje, se han utilizado las siguientes librerías compatibles con la placa ESP32 y que la añaden funcionalidades y mejoran el desarrollo de código:

 - bblanchon/ArduinoJson[^herramientasSw:arduinoJson]: es capaz de abstraer documentos [JSON](#JSON) y las herramientas para serializarlos y deserializarlos, añadiendo una inexistente compatibilidad de C++ con [JSON](#JSON). El formato de texto plano JavaScript Object Notation o [JSON](#JSON) almacena datos de manera estructurada, y es común su uso en sistemas de comunicación que intercambian información y en la operación de páginas web. Soporta objetos como texto, números, booleanos y nulos, los cuales se pueden agrupar dentro de otros objetos o en arrays; y se almacenan en formato clave-valor, facilitando el acceso al valor a través de su clave. Este proyecto utiliza ArduinoJson 7.0.4 para crear ficheros estructurados en los que almacenar propiedades de objetos, como una lista de placa suscriptoras, y almacenarlos en una tarjeta microSD, para poder recuperarlos durante el arranque de la placa ESP32.
 - x385832/Elog[^herramientasSw:elog]: creada para manejar eficientemente los logs o registros sin que impacte en el rendimiento de la ejecución, añade la capacidad de mostrar los registros por terminal serial, agregarlos a un fichero en una tarjeta SD y almacenarlos en la memoria flash. Admite distintos tipos de registros, dependiendo de cómo de crítico sea el mensaje, diferenciar mensajes por clases especificadas y mostrar marcas de tiempo. En el caso de este trabajo, se utiliza en la versión 1.1.5 para añadir mensajes de registro, como avisos o errores, para informar del estado de la ejecución del código, y ofrecer la posibilidad de almacenar los registros en una tarjeta microSD.

[^herramientasSw:arduinoJson]: <https://registry.platformio.org/libraries/bblanchon/ArduinoJson>
[^herramientasSw:elog]: <https://registry.platformio.org/libraries/x385832/Elog>

{
	https://es.wikipedia.org/wiki/C%2B%2B
	https://www2.eii.uva.es/fund_inf/cpp/temas/1_introduccion/introduccion.html
	https://arduinojson.org/v7/faq/automatically-serialize-an-object/
	https://www.luisllamas.es/en/arduino-json/
	https://registry.platformio.org/libraries/x385832/Elog
}

**Markdown**: es un lenguaje de marcado ligero utilizado en este [TFG](#TFG) para redactar los distintos apartados de la memoria. Fue creado por John Gruber en 2004, con el objetivo de ser una sintaxis legible y discreta. Markdown permite escribir en documentos de texto plano, utilizando su propia sintaxis para indicar formatos especiales y el aspecto que debe tener (como negrita, cursiva o títulos), con la característica de mantener una lectura natural del documento en casos en los que no sea posible previsualizar el formato. A pesar de ser un lenguaje ligero, no limita el uso a únicamente texto, ya que permite insertar imágenes, tablas, listados y otros tipos de elementos.

Otra característica notable es su portabilidad, ya que se trata de ficheros de texto que se pueden abrir con cualquier editor y en cualquier plataforma. Esta portabilidad permite comparar este lenguaje con Word, ya que este último mantiene el contenido encerrado en un formato de archivo propietario. Sin embargo, no todo lo escrito en Markdown se mantiene en ficheros .md, ya que es posible realizar conversiones a otros formatos, como [HTML](#HTML), para ver el contenido desde un navegador web, o [PDF](#PDF), para transformarlo en documento portátil, mediante scripts o aplicaciones. Estas características convierten a Markdown en un candidato ideal para todo tipo de usos, como la creación de sitios web, documentos, libros, presentaciones y mensajes de correo electrónico.

{
	https://www.markdownguide.org/getting-started/
}


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
