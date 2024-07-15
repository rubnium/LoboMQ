# Herramientas y metodología

## Herramientas

En este apartado se identifican y describen las distintas herramientas hardware y software que han permitido llevar a cabo este [TFG](#TFG).

### Hardware

El núcleo de este [TFG](#TFG) se basa en la programación de una placa de desarrollo, por lo que es necesario ciertos elementos hardware para llevarlo a cabo:

**Ordenador portátil**: es el componente principal para el desarrollo de este [TFG](#TFG), en el cual se han instalado las herramientas necesarias, se ha escrito el código, se ha accedido a herramientas y recursos en línea, y ha permitido subir el código a la placa. En este caso, el ordenador personal del alumno es un Lenovo Ideapad 3 15ALC6, cuyas características destacadas para este trabajo son:

- Procesador AMD Ryzen 7 5700 U, de 64 bits. Lanzado en enero de 2021, con 8 núcleos y una frecuencia de 1,8 [GHz](#GHz) hasta 4,3 [GHz](#GHz) @Ryzen7Specs.
- 12 GB de [RAM](#RAM) DDR4.
- Almacenamiento interno SSD de 1 [TB](#TB).
- 3 puertos USB.
- Lector de tarjetas SD.
- Adaptador de red Bluetooth y Wi-Fi.

![Hardware utilizado. De izquierda a derecha: ESP32 DEVKIT V1, lector de tarjeta microSD, DHT11, potenciómetro y ESP32 CYD (Fuentes: @ESP32_Precio @ModuloSDSF @DHT11_Specs @Pot_TiendaBQ @ESP32CYDAliexpress)\label{hardware:placas}](hardware_placas.png){width=100%}


**Dos placas ESP32 DEVKIT V1**: ambas fueron cedidas por la [UCLM](#UCLM) para el desarrollo de este [TFG](#TFG). Este tipo de placas, mostrado en la Figura \ref{hardware:placas}, contienen las mismas características que el SoC ESP32 mencionado en la Subsección [2.3.2](#esp32). Utilizan el módulo ESP32-WROOM-32.

Las placas están distribuidas en una placa de pruebas o breadboard, permitiendo conectar distintos elementos a los pines de las placas mediante jump wires o cables puente, sin necesidad de soldadura ni diseñar circuitos integrados y facilitando la prueba de componentes. En este caso, tienen conectados distintos módulos y sensores que permiten ampliar las funciones de estas:

 - **Módulo lector de tarjeta microSD**: observable en la Figura \ref{hardware:placas}, está compuesto por un socket para insertar tarjetas microSD en un circuito impreso del cuál salen 7 pines para poder utilizar el bus SPI de las tarjetas microSD @ModuloSDSF. El SPI o Serial Peripheral Interface es un estándar que se utiliza para transferir información entre circuitos integrados, como pueden ser la placa ESP32 DEVKIT y el lector de tarjetas. Los pines que tiene este módulo son los siguientes @Wiki_Spi:
	- VCC: entrada de energía, se conecta a una fuente de alimentación para alimentar el lector.
	- GND: conexión a tierra, se conecta al terminal negativo de la fuente de alimentación.
	- Data In o Master Output Slave Input: se utiliza para enviar datos desde la placa ESP32 hasta la tarjeta microSD.
	- Data Out o Master Input Slave Output: se utiliza para enviar datos desde la tarjeta microSD hasta la placa ESP32.
	- Serial Clock: reloj SPI, se utiliza para sincronizar la transferencia de datos entre las placas.
	- Chip Select: se utiliza para activar y desactivar la comunicación con el lector.
	- Card Detect: se utiliza para detectar si hay una tarjeta insertada en el lector.

	Para este trabajo, el lector, cedido por la UCLM, se utiliza para leer y escribir datos en una tarjeta microSD desde la ESP32 DEVKIT V1 que actúe como broker y gestione los registros o logs y las direcciones de los dispositivos suscritos contenidos. 
 - **Sensor DHT11**: sensor digital capaz de medir la temperatura y la humedad, cedido por la [UCLM](#UCLM). Alimentado por 3,3 o 5 voltios, es capaz de leer la humedad en el ambiente entre los rangos 20 y 95% (con un 5% de fallo) y la temperatura entre 0 y 50 [ºC](#ºC) (con 2 [ºC](#ºC) de fallo) @DHT11_Specs. Está representado en la Figura \ref{hardware:placas}.
 - **Potenciómetro BQ Zum Kit Advanced**: contenido originalmente en un kit junto a varios sensores y una placa controladora @Pot_TiendaBQ @Pot_KitBQ, este potenciómetro de señal analógica cedido por la [UCLM](#UCLM) es capaz de devolver un valor en función a su rotación, siendo su rotación máxima 300º, al alimentarlo con 3,3 o 5 voltios @Pot_TiendaRobotica. Se muestra en la Figura \ref{hardware:placas}.

**Placa ESP32-2432S028R**: esta placa proporcionada por el autor y popularmente conocida como Cheap-Yellow-Display o CYD para abreviar, se ha utilizado para hacer pruebas del funcionamiento de la herramienta desarrollada, y al igual que las anteriormente mencionadas placas ESP32, está potenciado por un ESP32-WROOM-32 @ESP32_CYD_Git. Se puede observar en la Figura \ref{hardware:placas}. En cuanto a componentes integra @ESP32_CYD_Git:

 - Pantalla LCD de 2,8 pulgadas con resolución 320x240 píxeles, y táctil de tipo resistivo.
 - LED multicolor RGB.
 - Lector de tarjeta microSD.
 - Sensor LDR, cuyo valor que devuelve depende de la resistencia que le otorga la luz que recibe.
 - Conectores y pines adicionales para conectar un altavoz y otros módulos.

**Tarjeta microSD**: tarjeta proporcionada por el alumno autor y utilizada por una de las placas con lector de tarjetas para almacenar los registros o logs y las direcciones de los dispositivos suscritos al broker.

### Software

Para poder realizar el desarrollo correcto de este [TFG](#TFG), se han requerido las siguientes piezas de software:

**Windows 10**[^herramientasSw:w10]: el sistema operativo es clave para poder hacer funcionar el [TFG](#TFG). Este sistema operativo de Microsoft se encuentra instalado en el ordenador portátil mencionado en la Subsección [3.1.1](#hardware). El autor ha utilizado la reciente versión 22H2 con el apropiado driver[^herramientasSw:driver] instalado para poder hacer uso de las placas. Pese a que la alta popularidad de Windows asegura una gran compatibilidad con las aplicaciones existentes, es posible de adaptar el proyecto a un entorno en Linux con pocas o nulas complicaciones, haciendo irrelevante la elección del sistema operativo. Su uso ha sido por gusto del autor.

[^herramientasSw:w10]: <https://www.microsoft.com/es-es/software-download/windows10>
[^herramientasSw:driver]: <https://www.wch-ic.com/downloads/CH341SER_ZIP.html>

**GitHub**[^herramientasSw:gh]: es una plataforma en la nube propiedad de Microsoft que permite a los equipos de desarrolladores almacenar código, colaborar y realizar cambios en proyectos compartidos, alojados en esta plataforma en forma de repositorios de Git @GitAndGitHubDocs @WikiGitHub.

Git es un sistema de control de versiones de código abierto que permite gestionar el código fuente y el historial de cambios. Tiene la característica de ser distribuido, permitiendo usar ramas para aislar partes del código, como pueden ser nuevas funcionalidades en desarrollo por distintas partes de un mismo equipo. Estos cambios se pueden integrar y luego fusionar las ramas con la principal para hacerlos efectivos, y revertir a una versión funcional en caso de errores @GitAndGitHubDocs @Hostinger_Git.

Los repositorios en GitHub pueden ser públicos o privados, y desde estos se pueden crear y modificar ramas, cargar ficheros, realizar *commits* (la unidad de trabajo que representa un cambio en el repositorio), ver su histórico de cambios, obtener las modificaciones realizadas por otros usuarios y hacer *pull requests* (solicitudes de cambios) para integrar estos cambios en el proyecto @GitHub_Commits. GitHub va un paso más allá de alojar proyectos, ya que permite la gestión de proyectos y la interacción del equipo de desarrollo a través de *issues* que retroalimentan el proyecto y ofrecen ideas, asignación de responsabilidades, hitos, etiquetas, discusiones, y tableros estilo Kanban @GitHub_Issues @GitAndGitHubDocs @WikiGitHub. Otras funciones que permite esta plataforma son @GitAndGitHubDocs @WikiGitHub:

- Documentación de proyectos con ficheros "readme" o "léeme" en Markdown en los directorios del proyecto.
- Creación de wikis.
- Automatización de pruebas, lanzamientos y despliegues con GitHub Actions, especificando los pasos a ejecutar tras una acción específica realizada en el repositorio.
- Alojamiento de páginas web estáticas con GitHub Pages como parte de un repositorio.
- Gists o fragmentos de código compartibles.
- GitHub Codespaces, un [IDE](#IDE) online.

En el caso de este proyecto, se ha utilizado, con el plan gratuito de GitHub, un repositorio privado durante el desarrollo para alojar el código, compartirlo fácilmente con los tutores para enviar dudas e informar del estado del proyecto, y llevar un histórico de los cambios realizados. Posteriormente, se ha modificado la visibilidad del repositorio a público para compartir el proyecto a través de la plataforma de librerías de PlatformIO y aprovechar la funcionalidad de GitHub Pages para incluir una página web estática que documente las distintas funciones que componen el proyecto, ambas funciones automatizadas a través de GitHub Actions. Pese a conocer alternativas a la plataforma, como GitLab, se ha decidido utilizar GitHub por la experiencia previa del alumno y la facilidad de uso que ofrece.

Otra herramienta que ofrece GitHub para no separar la funcionalidad del escritorio local es **GitHub Desktop**[^herramientasSw:ghDesktop], que permite simplificar el flujo de trabajo del desarrollador y centrarse en su trabajo. Proporciona una interfaz gráfica que evita interactuar directamente con Git para clonar proyectos, hacer *commits*, cambiar de rama y ver los cambios y diferencias en los archivos @GHDesktop_Whatis.

[^herramientasSw:gh]: <https://github.com/>
[^herramientasSw:ghDesktop]: <https://desktop.github.com/>

**Visual Studio Code**[^herramientasSw:vsc]: es un [IDE](#IDE) ligero, potente, multiplataforma, personalizable y de código abierto, creado por Microsoft. Permite abrir directorios como espacios de trabajo capaces de contener múltiples lenguajes de programación, ofreciendo soporte nativo para JavaScript, TypeScript y Node.js. Visual Studio Code integra funcionalidades clave para incrementar la productividad del desarrollador, tales como el subrayado de sintaxis y errores, la sangría automática, la refactorización, el autocompletado, las sugerencias, la compilación y ejecución mediante clics, el depurador interactivo y la compatibilidad con repositorios Git. Tanto la funcionalidad como la compatibilidad con lenguajes son ampliables mediante extensiones @WhyVSC @VSC_Wiki.

Este ha sido el [IDE](#IDE) de preferencia para el desarrollo de este trabajo, y se ha complementado con las siguientes extensiones:

- PlatformIO IDE[^herramientasSw:vscPlatformIO]: habilita el desarrollo de software embebido para distintas plataformas y frameworks utilizando el sistema de PlatformIO (explicado posteriormente) @PlatformIO_VSMarketplace. 
- C/C++ Extension Pack[^herramientasSw:vscCppPack]: añade compatibilidad con el desarrollo de proyectos en C/C++.
- GitHub Copilot[^herramientasSw:vscGHCopilot]: una herramienta de programación basada en inteligencia artificial entrenada a partir de repositorios públicos y que ayuda a escribir código de forma rápida e inteligente, mediante sugerencias y un chat para realizar consultas @GHCopilot_VSMarketplace @GHCopilot_Overview.
- Better Comments[^herramientasSw:vscBetterComments]: añade diferencias de estilo y enfatizaciones a comentarios en el código destinados a alertar, hacer peticiones, indicar acciones por realizar o TODOs, o remarcar información importante, logrando así comentarios más comprensibles @BetterComments_VSMarketplace.
- TODO Highlight[^herramientasSw:vscTodoHighlight] y Todo Tree[^herramientasSw:vscTodoTree]: ambas extensiones se utilizan en conjunto para llevar un seguimiento de las tareas que se deben realizar en el código, permitiendo resaltar líneas que contienen el texto "TODO" y "FIXME" @TODOHighlight_VSMarketplace y mostrarlas de manera agrupada en forma de árbol @TodoTree_VSMarketplace.
- Code Spell Checker[^herramientasSw:vscSpellChecker]: un corrector ortográfico que marca los errores ortográficos detectados en los comentarios y en el código, y que ayuda a solucionarlos a través de sugerencias @SpellChecker_VSMarketplace.
- Doxygen Documentation Generator[^herramientasSw:vscDoxygenDoc]: permite generar automáticamente en formato Doxygen los comentarios junto a parámetros como las descripciones, los parámetros y los valores retornados para su uso en la documentación @DoxygenGenerator_VSMarketplace.

[^herramientasSw:vsc]: <https://code.visualstudio.com/>
[^herramientasSw:vscPlatformIO]: <https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide>
[^herramientasSw:vscCppPack]: <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack>
[^herramientasSw:vscGHCopilot]: <https://marketplace.visualstudio.com/items?itemName=GitHub.copilot>
[^herramientasSw:vscBetterComments]: <https://marketplace.visualstudio.com/items?itemName=aaron-bond.better-comments>
[^herramientasSw:vscTodoHighlight]: <https://marketplace.visualstudio.com/items?itemName=wayou.vscode-todo-highlight>
[^herramientasSw:vscTodoTree]: <https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree>
[^herramientasSw:vscSpellChecker]: <https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker>
[^herramientasSw:vscDoxygenDoc]: <https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen>

**PlatformIO**[^herramientasSw:platformIO]: es una herramienta de código abierto y multiplataforma, destinada a ingenieros y desarrolladores de software de sistemas embebidos, ya sean aficionados y profesionales, que incluye lo necesario para compilar, ejecutar, subir y escribir el código. Ofrece una amplia compatibilidad, con soporte para más de mil placas embebidas diferentes, más de 40 plataformas de desarrollo y más de 20 marcos de trabajo o frameworks @WhatIsPlatformIO @PlatformIOPlatforms.

PlatformIO aloja uno de los mayores registros de bibliotecas embebidas en PlatformIO Registry[^herramientasSw:platformIOReg], lo que permite explorar e instalar de manera sencilla distintas bibliotecas de código, plataformas y herramientas, listadas junto a ejemplos e instrucciones de uso @PlatformIODependencies @PlatformIORegistry. Junto a esta, una de sus características más importantes es la gestión de dependencias integrada para que los proyectos aprovechen funcionalidades de otras bibliotecas @PlatformIODependencies. Además, contiene un depurador de código, un analizador estático de código, un monitor de puerto serial y soporte para pruebas unitarias @PlatformIO_VSMarketplace. Esta herramienta se pone a disposición del usuario mediante la integración con otros [IDE](#IDE)s o editores de texto a través de extensiones, siendo Visual Studio Code el más recomendado @PlatformIOIdeIntegration.

El código de este proyecto se ha creado con PlatformIO y se ha configurado para utilizar la placa ESP32 DEVKIT V1 con la plataforma Espressif32. En cuanto al framework, se ha utilizado el de Arduino, pese a ser posible también utilizar el de Espressif (ESP-IDF), debido a que cumple las necesidades del desarrollador, a la experiencia previa con placas de desarrollo Arduino por parte del autor y a la facilidad de uso. Las diferencias entre ambos son las siguientes @PIOFramework:

- El framework ESP-IDF ofrece un soporte completo de los lenguajes C y C++, permitiendo escribir código eficiente y de alto rendimiento. Por otro lado, Arduino utiliza una implementación simplificada y adaptada a los microcontroladores, limitando la flexibilidad y funcionalidad del código.
- Las aplicaciones desarrolladas con ESP-IDF están preparadas para hacer uso de los núcleos disponibles en la placa y  su estructura se basa en tareas, mientras que en Arduino por defecto solo se aprovecha de un núcleo y las aplicaciones siguen una estructura en la que se debe declarar una función `setup` y otra `loop`.
- El framework de Arduino es útil si previamente el desarrollador lo ha utilizado para desarrollar en otras placas, además de ser fácil de usar para quienes no tienen mucha experiencia, y contiene un gran rango de librerías y [API](#API)s por defecto que facilitan el desarrollo. En cambio, ESP-IDF se puede utilizar para desarrollar software que requiera controlar funciones avanzadas del hardware, como el consumo de energía y recursos, e incluye un mayor conjunto de herramientas para depurar la placa y gestionar el uso de la memoria.
- En cuanto a la comunidad, debido a la implementación de Arduino en una gran variedad de placas, es la que mayor comunidad tiene en comparación con ESP-IDF.

[^herramientasSw:platformIO]: <https://platformio.org/>
[^herramientasSw:platformIOReg]: <https://registry.platformio.org/>

**Trello**[^herramientasSw:trello]: desarrollado por Atlassian, es una aplicación web que facilita la gestión de tareas utilizando tableros visuales al estilo Kanban, cuyos componentes clave son @Trello_Main @Trello_Tour @Trello_Wiki:

- Listas: columnas que representan las fases de una tarea.
- Tarjetas: tareas o ideas que se mueven entre listas según su estado. Pueden incluir miembros asignados, fechas de vencimiento, archivos adjuntos, descripciones, comentarios y checklists.
- Miembros: usuarios con tareas asignadas y permisos en el tablero.

Trello tiene la capacidad de ampliar la funcionalidad gracias a las integraciones con otras aplicaciones, a las automatizaciones sin código para centrarse únicamente en el trabajo, y a los powerups, que actúan como extensiones de la funcionalidad básica de Trello @Trello_Main @Trello_Tour.

Para el proyecto, el alumno ha creado un tablero adaptado a sus necesidades (detallado posteriormente) usando el plan gratuito de Trello. Este tablero permite llevar un seguimiento de todas las tareas, tanto de código como de la memoria, realizadas durante el desarrollo, y ha facilitado las reuniones de seguimiento al poder mostrar a los tutores el estado de las tareas. Utiliza los siguientes *power-ups*:

- GitHub[^herramientasSw:trelloGH]: sirve para llevar un seguimiento de lo sucedido en GitHub desde el tablero, como adjuntar a tarjetas ramas, commits, incidencias y pull requests y asociar repositorios a tarjetas @GH_TrelloPU.
- Smart Fields[^herramientasSw:trelloSmartFields]: permite crear campos personalizados en las tarjetas, como campos de texto, de número o de fecha, y soporta el uso de fórmulas para calcular el valor del campo. Estos campos se pueden mostrar desde la vista general del tablero, sin necesidad de entrar a ver los detalles de la tarjeta @SmartFields_TrelloPU.

[^herramientasSw:trello]: <https://trello.com/es>
[^herramientasSw:trelloGH]: <https://trello.com/power-ups/55a5d916446f517774210004/github>
[^herramientasSw:trelloSmartFields]: <https://trello.com/power-ups/5e2212c3ba57415ef2ef9352/smart-fields>

**Doxygen**[^herramientasSw:doxygen]: utilizada para la documentación de este trabajo, esta herramienta de código abierto, muy empleada en el desarrollo de software, permite obtener documentación a partir del código de forma sencilla. Posibilita la generación automática de documentación en distintos formatos, como [HTML](#HTML), [PDF](#PDF), Word y [XML](#XML), a partir de los comentarios insertados en el código durante el desarrollo, analizando la información de las distintas clases, funciones y variables. Gracias a esta automatización, se agiliza y estandariza el proceso de documentación de proyectos, lo cual es beneficioso para entender el proyecto y el código que lo compone, además de mejorar la colaboración entre los miembros del equipo de desarrollo y el mantenimiento del propio código. Soporta C++, C, Python, Java, PHP y otros lenguajes @Doxygen_Main. La documentación se realiza a partir de comentarios, como se muestra en el Listado \ref{herramientasSw:ejemploDoxygen}.

```{.cpp #herramientasSw:ejemploDoxygen .numberLines caption="Ejemplo de uso de Doxygen" frame=single}
/**
 * <Descripción corta de la función>
 *
 * <Descripción larga de la función>
 *
 * @param  parametro1 <Descripción del primer parámetro de entrada>
 * @param  parametro2 <Descripción del segundo parámetro de entrada>
 * @param <Descripción del resto de parámetros>
 * @return <Descripción del valor o valores que retorna>
 */
public int ejemploFuncion(int parametro1, bool parametro2, ...)
```

Entre las capacidades adicionales se encuentran las referencias cruzadas entre distintas partes de la documentación, soporte de Markdown en los comentarios, dibujo de diagramas para representar gráficamente clases, herencias y relaciones entre partes del código, personalización de la documentación resultante y configuración mediante un fichero Doxyfile con distintos parámetros establecidos por el usuario @Doxygen_Main.

En el caso de este trabajo, se ha generado documentación en formato [HTML](#HTML) para crear una página web con toda la información de las distintas funciones que componen el proyecto, y se ha personalizado con Doxygen Awesome[^herramientasSw:doxygenAwesome], un tema [CSS](#CSS) aplicable a la página para disponer de una página con un aspecto moderno, limpio y compatible con la interfaz móvil @DoxyAwesome_Main.

[^herramientasSw:doxygen]: <https://doxygen.nl/>
[^herramientasSw:doxygenAwesome]: <https://jothepro.github.io/doxygen-awesome-css/>

**Plantilla de [TFG](#TFG)**[^herramientasSw:plantilla]: fue desarrollada por Félix Albertos Marco, profesor del Grado de Ingeniería Informática de la sede de la [UCLM](#UCLM) de Talavera de la Reina, ofreciendo una alternativa para desarrollar la memoria del Trabajo de Fin de Grado. Esta plantilla, utilizada en este [TFG](#TFG), se caracteriza por emplear Markdown para redactar todos los apartados, evitando las complicaciones del formato del documento (como el interlineado, fuentes, cabeceras y pie de página y saltos de página), además de proporcionar la portabilidad del trabajo, ya que estos ficheros son de marcado ligero y no necesitan editores ni sistemas operativos específicos. El soporte de Markdown también incluye todos los elementos que este lenguaje ofrece, como tablas, listados, fragmentos de código o formateado del texto @FelixTemplate.

[^herramientasSw:plantilla]: <https://www.felixalbertos.com/resources/downloads/tfg_template.html>

**Teams**[^herramientasSw:teams]: es una aplicación multiplataforma de colaboración en equipo, disponible de forma gratuita con un plan personal limitado o mediante una licencia Microsoft 365 @MSTeams_Wiki @MSTeams_Buy.

Microsoft 365 es una suscripción que incluye las aplicaciones de Microsoft Office (Word, PowerPoint y Excel), almacenamiento en la nube, copias de seguridad y correo electrónico, que habilita el uso en la nube de éstas y permite mantener siempre la última versión con los parches de seguridad correctos mediante un pago mensual o anual @Microsoft365WhatIs. La [UCLM](#UCLM) provee a sus usuarios de cuentas de Microsoft 365 Empresa, la cual se ha aprovechado para este desarrollo.

Teams centraliza la comunicación en los equipos al permitir la interacción a través de mensajes instantáneos y reuniones. Su funcionamiento se basa en el concepto de equipos o *teams*, espacios de trabajo compartidos donde se intercambian mensajes, contenido y herramientas entre los miembros. Dentro de los equipos existen los canales, que son áreas para conversaciones sobre temas específicos en los que es posible restringir el acceso únicamente a ciertos miembros del equipo, permitiendo crear subdivisiones en el equipo. Por otro lado, para comunicaciones directas o en grupos pequeños, se pueden utilizar chats normales en lugar de equipos. Además, Teams dispone de otras funciones, como aplicaciones instalables dentro del propio software para ampliar la funcionalidad, y un calendario con capacidad para programar reuniones @Teams_Demo @MSTeams_Wiki.

Para este [TFG](#TFG), Microsoft Teams ha permitido mantener un contacto directo entre los tutores y el alumno a través de un equipo organizado por canales destinados a las partes de desarrollo y memoria. Estos han agilizado la consulta de dudas y de disponibilidad y organizado archivos compartidos. Por ejemplo, en el canal destinado a la memoria se alojaron las distintas versiones del documento de la memoria, mientras que en el canal de desarrollo se encuentran enlaces, manuales y códigos de ejemplo. Además, se han programado y celebrado reuniones de seguimiento en esta aplicación, de la cual tanto el alumno como los tutores tenían experiencia de uso.

[^herramientasSw:teams]: <https://www.microsoft.com/es-es/microsoft-teams/group-chat-software/>

**Visio**[^herramientasSw:visio]: es un programa para crear diagramas y vectores profesionales de manera fácil gracias a su incluida y extensa librería de objetos. Su uso está limitado a los usuarios con licencia de Microsoft 365, servicio mencionado anteriormente y del cual la [UCLM](#UCLM) distribuye la licencia a todos los usuarios de la universidad, como es el caso del autor, quien ha destinado el uso de la aplicación al dibujo de algunos esquemas de la memoria. Este programa facilita la visualización de datos e ideas de manera atractiva, lo cual resulta útil en equipos y en la documentación para asegurar la comprensión sencilla de los conceptos @Visio_Main @Visio_Wiki.

[^herramientasSw:visio]: https://www.microsoft.com/es-es/microsoft-365/visio/flowchart-software/

**Visual Paradigm**[^herramientasSw:visualParadigm]: es una herramienta que soporta los diagramas resultantes de todas las fases del ciclo de vida del desarrollo de software, entre otros, los diagramas de casos de uso, de clases, de secuencia, de flujo y de arquitectura. Este programa facilita al usuario la realización de diagramas que cumplen con el Lenguaje Unificado de Modelado, ya sea de manera manual o a través de ingeniería inversa, es decir, a partir de código. Además, tiene la capacidad de generar código a partir de los diagramas creados, ayudando al desarrollo @VisualParadigm. En este caso, se ha utilizado esta herramienta para ofrecer una comprensión visual de la solución mediante el modelado de una serie de diagramas integrados en esta memoria.

[^herramientasSw:visualParadigm]: <https://www.visual-paradigm.com/>

**Navegador web**, como Firefox[^herramientasSw:firefox] y Microsoft Edge[^herramientasSw:edge]: utilizados en este proyecto para acceder a las herramientas web mencionadas anteriormente y realizar búsquedas de información acerca de partes del código en desarrollo y del contenido de esta memoria.

[^herramientasSw:firefox]: <https://www.mozilla.org/es-ES/firefox/new/>
[^herramientasSw:edge]: <https://www.microsoft.com/es-es/edge/>

### Lenguajes

**C++**: es un lenguaje de programación diseñado en 1979 para extender el ya existente C con mecanismos de manipulación de objetos. Es un lenguaje que requiere una compilación para que el programa pueda ser ejecutado, además de ser multiparadigma, abarcando programación estructurada, orientada a objetos, genérica e imperativa (es decir, las instrucciones indican cómo realizar una tarea y se conoce el estado del programa durante la ejecución @ProgImperativaDef) @FundamentosCpp @CppAprendiendoArdu. La orientación a objetos permite descomponer los proyectos en distintos archivos con tipos de datos abstractos o clases, asignar propiedades y funciones a un objeto de esa clase y relacionar las propias clases entre sí, por ejemplo, para que una clase pueda heredar de otra @Cpp_Wiki.

Tanto C++ como su predecesor C requieren que el programador tenga claro qué hacer y cómo hacerlo, ya que permiten al programador expresar lo que quiere hacer sin restringir lo que está permitido. Son lenguajes simples, concisos y rápidos, pero, por otro lado, la compilación no comprueba las conversiones incorrectas de tipos, los índices erróneos de arrays ni el mal uso de punteros. Además, no cuentan con un recolector de basura, por lo que la gestión de la memoria debe realizarse manualmente. Esto convierte a C++ en un lenguaje frágil y exigente en la gestión de recursos @EssentialC @Cpp_Wiki. 

C++ fue diseñado teniendo en cuenta la programación de sistemas, tanto grandes como embebidos y con recursos limitados, utilizando el rendimiento, la eficiencia y la flexibilidad como puntos clave de diseño. @CppAprendiendoArdu

En el caso de este trabajo, se utiliza el framework de Arduino, una implementación de C++ que limita las funciones por defecto e incluye algunas propias. Junto a este lenguaje, se han utilizado las siguientes librerías compatibles con la placa ESP32 y que la añaden funcionalidades y mejoran el desarrollo de código:

 - FreeRTOS[^herramientasSw:freeRtos]: permite utilizar FreeRTOS como un sistema operativo en el proyecto, gestionando el acceso al hardware y las tareas. Es un sistema operativo en tiempo real, centrado en el control preciso del tiempo y destinado a ser utilizado en dispositivos embebidos @Wiki_FreeRTOS @FreeRTOSArduino.

	FreeRTOS se basa en tareas definidas por el desarrollador, cada una con su frecuencia de ejecución. Estas tareas se ejecutan dependiendo de su estado, los cuales pueden ser: disponible, en ejecución, suspendida o bloqueada. El núcleo de FreeRTOS es el scheduler o planificador, que se encarga de gestionar y ejecutar las tareas. Este distribuye el tiempo de ejecución del procesador entre las tareas y asigna las tareas a los núcleos del procesador disponibles (solo se puede ejecutar una tarea por núcleo), permitiendo la ejecución en paralelo o alternando la ejecución entre varias tareas. Además, es el responsable de cambiar los estados entre las tareas. FreeRTOS también incluye otras funcionalidades y herramientas, como semáforos para sincronizar tareas, colas para compartir datos entre tareas, temporizadores y un bus de notificaciones @FreeRTOSArduino.

 - bblanchon/ArduinoJson[^herramientasSw:arduinoJson]: es capaz de abstraer documentos [JSON](#JSON) y las herramientas para serializarlos y deserializarlos, añadiendo una inexistente compatibilidad de C++ con este formato de datos estructurado @ArduinoJson_Serialize @ArduinoJson_Tutorial. Este proyecto utiliza ArduinoJson 7.0.4 para crear ficheros en los que almacenar propiedades de objetos, como una lista de placa suscriptoras, y almacenarlos en una tarjeta microSD, para poder recuperarlos durante el arranque de la placa ESP32.
 - x385832/Elog[^herramientasSw:elog]: creada para manejar eficientemente los logs o registros sin que impacte en el rendimiento de la ejecución, añade la capacidad de mostrar los registros por terminal serial, agregarlos a un fichero en una tarjeta SD y almacenarlos en la memoria flash. Admite distintos tipos de registros, dependiendo de cómo de crítico sea el mensaje, diferenciar mensajes por clases especificadas y mostrar marcas de tiempo @Elog_PIOReg. En el caso de este trabajo, se utiliza en la versión 1.1.6 para añadir mensajes de registro, como avisos o errores, para informar del estado de la ejecución del código, y ofrecer la posibilidad de almacenar los registros en una tarjeta microSD.

[^herramientasSw:freeRtos]: <https://www.freertos.org/>
[^herramientasSw:arduinoJson]: <https://registry.platformio.org/libraries/bblanchon/ArduinoJson>
[^herramientasSw:elog]: <https://registry.platformio.org/libraries/x385832/Elog>

**Markdown**: es un lenguaje de marcado ligero utilizado en este [TFG](#TFG) para redactar los distintos apartados de la memoria. Markdown permite escribir en documentos de texto plano, utilizando su propia sintaxis para indicar formatos especiales y el aspecto que debe tener (como negrita, cursiva o títulos), con la característica de mantener una lectura natural del documento en casos en los que no sea posible previsualizar el formato. A pesar de ser un lenguaje ligero, no limita el uso a únicamente texto, ya que permite insertar imágenes, tablas, listados y otros tipos de elementos @MD_Description.

## Metodología

En este apartado se tratan conceptos básicos de la metodología junto a la forma en la que se aplica a este [TFG](#TFG).

### Metodologías tradicionales y ágiles en el desarrollo de software

Las metodologías de desarrollo de software son marcos, compuestos de técnicas y métodos, utilizados con el fin de estructurar, planear y controlar el proceso para aumentar la productividad y la calidad del software. Estas se deben elegir con precaución, ya que, si son apropiadas para el equipo y para el proyecto y su implementación se lleva a cabo correctamente, benefician al desarrollo con estimaciones superiores de tiempo y esfuerzo, priorización de tareas, clara comprensión de los esfuerzos futuros y previos, tiempo adicional suficiente para hacer ajustes, reportes al cliente el estado del proyecto y, además, entregas de sistemas y productos estables y con calidad @UsoMets @Mets_Tecnitium.

Las metodologías se organizan en dos grandes bloques: las tradicionales y las ágiles.

#### Metodología tradicional

Las metodologías tradicionales en el desarrollo de software se caracterizan por su enfoque estructurado y secuencial en la gestión de proyectos. Enfatizan la planificación exhaustiva y la fijación de los requisitos a lograr en las primeras etapas del proyecto, y siguen de manera lineal unas fases bien definidas, abarcando el inicio del proyecto, la planificación, la implementación, la verificación y el mantenimiento, durante las cuales se genera el producto junto a la documentación clara @Mets_Tecnitium @Mets_Feda.

Por un lado, ofrecen unos objetivos claramente definidos y sus procesos son controlables, pero, por otro lado, el desarrollo requiere más responsabilidad por parte de los involucrados y es poco tolerante a cambios tardíos, ya sean de requisitos o para resolver problemas, influyendo negativamente en el presupuesto y los plazos de entrega @Mets_Tecnitium @Mets_Feda @MetsTradicionales_TecnoDigital.

Entre la variedad de esta clase de metodologías se encuentran:

- Desarrollo en cascada: planificación y desarrollo lineal de etapas que entregan un único producto que cumple con los requisitos especificados. Es adecuado en proyectos con requisitos estables y entornos regulados por normativas @MetsTradicionales_TecnoDigital.
- Proceso Unificado de Desarrollo: ciclos iterativos e incrementales centrados en casos de uso y en la gestión de riesgos. Su uso resulta adecuado en proyectos complejos y que necesitan una gestión de riesgos cuidadosa @MetsTradicionales_TecnoDigital.
- Desarrollo en espiral: ciclos iterativos e incrementales formados por fases. Es utilizada en proyectos complejos con requisitos cambiantes y un alto nivel de incertidumbre o riesgos @MetsTradicionales_TecnoDigital.

#### Metodología ágil

La metodología ágil es una metodología de gestión de proyectos que impulsa el desarrollo iterativo mediante entregas incrementales, la colaboración en equipo y la planificación y el aprendizaje continuos @Agile_MS @AgileDev_MS @Agile_Wikipedia. Está basada en el Manifiesto Ágil, acordado en 2001 por 17 desarrolladores de software agrupados como la Agile Alliance @Agile_Wikipedia, y valora @ManifiestoAgil:

- Los individuos e interacciones sobre los procesos y las herramientas.
- El software funcionando sobre la documentación extensiva.
- La colaboración con el cliente sobre la negociación contractual.
- La respuesta ante el cambio sobre seguir un plan.

En esta metodología, el desarrollo se realiza en ciclos iterativos breves o sprints de una duración entre 1 y 4 semanas, cuyo resultado es un pequeño incremento de la funcionalidad del software. En los sprints, el equipo realiza la codificación, las pruebas y la comprobación de calidad, fases regidas por requisitos bien definidos y priorizados de trabajo pendiente. En el desarrollo existe el rol del propietario del producto, @AgileDev_MS @Agile_Wikipedia quien se encarga de representar a las partes interesadas del proyecto y se compromete a responder a las preguntas de los desarrolladores a lo largo de las iteraciones @Agile_Wikipedia. El propietario del producto añade, modifica y reprioriza las tareas pendientes dentro de un listado o backlog al principio de cada sprint, en función de las necesidades del cliente @AgileDev_MS; y al final de cada iteración es quien se reúne con las partes interesadas para revisar el progreso del desarrollo y reevaluar la priorización de las tareas, con la intención de satisfacer a los interesados @Agile_Wikipedia. Además, las tareas con las que se trabaja deben ser claras para el equipo de desarrollo, por lo que requieren una continua refinación por parte del propietario y el equipo hasta que el propio equipo decida que están listas para trabajarlas @AgileDev_MS.

Los incrementos permiten corregir constantemente errores que surjan y adaptarse a cambios, en vez de tener que enfrentarlos al final del proyecto o en etapas en las que puede resultar muy costoso @Agile_Wikipedia.

Una característica fundamental del desarrollo ágil es la comunicación directa y eficaz entre los involucrados, lo que se traduce en la capacidad de comunicar de forma efectiva las necesidades del cliente y las tareas con el equipo de desarrollo. Es común apoyarse en un radiador de información que muestra el estado del proyecto, como un tablero con post-its o una pantalla grande. Esto se aplica a otra característica del desarrollo: la realización de sesiones de retroalimentación diarias para revisar el progreso, las tareas a completar en el día, los impedimentos y los riesgos. Son sesiones breves, de unos 15 minutos y sin entrar en detalle, ya que tienen el fin de reforzar la comunicación y la coordinación del equipo de desarrollo @Agile_Wikipedia.

En esta metodología, es común utilizar herramientas y técnicas de integración continua y entrega continua que mejoren la calidad del proyecto y agilicen el desarrollo. Por ejemplo, automatizar la compilación, la ejecución de pruebas y el despliegue. Esto evita procesos lentos y propensos a errores, y permite demostrar un producto de calidad al final de cada iteración @AgileDev_MS @Agile_Wikipedia.

La metodología ágil es adaptativa, es decir, se centra en adaptarse rápidamente a las necesidades cambiantes. Durante la planificación se identifican hitos, pero estos son flexibles, además de que difícilmente se describe el futuro del desarrollo. Esta característica es muy importante, ya que es la que la separa de las metodologías tradicionales predictivas. Las metodologías predictivas planifican las tareas y características previstas en detalle y tienen en cuenta los riesgos conocidos, resultados de un primer análisis exhaustivo. En el caso de no haber tenido en cuenta algún riesgo o que ocurra algún otro imprevisto, puede ser difícil realizar cambios @Agile_Wikipedia. Esta comparación no intenta demostrar que una es superior a la otra, ya que ambas son adecuadas dependiendo de las necesidades específicas del proyecto, e incluso existe la posibilidad de realizar un enfoque híbrido combinándolas @AgileDiffs. 

En adición, los principios del Manifiesto Ágil también enfatizan la colaboración continua entre los responsables de negocio y un equipo de desarrollo motivado y confiado a lo largo de todo el proyecto. Reflexionan y perfeccionan constantemente la efectividad técnica, con el fin de mantener un ritmo de desarrollo constante para alcanzar la principal medida de progreso: el software funcionando @ManifiestoAgil_Principios.

Dentro de este tipo de metodología se pueden encontrar, entre otros:

- Scrum: define roles, eventos, artefactos y reglas para mejorar la productividad y la comunicación en equipos de menos de 10 personas a través de sprints iterativos, pero puede complicar la visión general en proyectos grandes y no siempre es fácil de integrar en todas las organizaciones @Scrum_Ionos.
- Kanban: se centra en la mejora del flujo de trabajo, de la productividad y de la calidad a través del uso de un tablero Kanban, con tarjetas que se desplazan entre columnas según el estado de la tarea. Soporta la priorización y limitación de tareas, las cuales se deben completar antes que otras y revisar regularmente. Es una metodología fácil de integrar que muestra los avances del proyecto de manera sencilla, pero requiere que el trabajo sea divisible en fases y que los miembros se adapten a trabajar en distintas etapas del proceso @Kanban_Ionos.
- Programación Extrema (eXtreme Programming): se basa en un entorno de comunicación constante entre desarrolladores y cliente, y en el cual existe respeto para tratar errores y críticas. Es utilizada en proyectos en los cuales el cliente no tiene una idea clara del producto final, por lo que ocurren procesos iterativos para entregar una versión y revisarla. Sin embargo, requiere una gran inversión de tiempo y disciplina para llevarla a cabo @XtremeProgram_Ionos.

### Scrum

Como está definido en la Guía de Scrum @ScrumGuide, Scrum es un marco de trabajo ligero para el desarrollo ágil de software que ayuda a personas, equipos y organizaciones a generar valor a través de soluciones adaptativas. Busca conseguir un equipo que trabaje en colaboración y obtener el mejor resultado posible de los proyectos, pero en vez de detallar instrucciones específicas a seguir, ofrece una guía de relaciones e interacciones en el equipo. Esta libertad permite usar varios procesos, técnicas y métodos que visibilicen la eficacia de la gestión, el entorno y las técnicas de trabajo para poder mejorarlas.

Se basa en el conocimiento adquirido a partir de la experiencia, en la toma de decisiones basada en observaciones, y en el pensamiento centrado en lo esencial. Utiliza un enfoque iterativo e incremental en el cual un equipo con las habilidades necesarias para el proyecto celebra ciertos eventos que previenen y controlan riesgos, inspeccionan, adaptan y desarrollan el trabajo. Estos eventos están envueltos en uno principal, el sprint.

Los sprints son etapas de desarrollo que duran entre 1 y 4 semanas de trabajo (según se establezca en el equipo). En estos se convierten las ideas en valor para el producto, llamados incrementos, los cuales se producen con cada sprint y avanzan el desarrollo hacia el objetivo del producto final. Los incrementos pasan por una revisión con los interesados del proyecto, y se ajusta lo necesario para poder comenzar el siguiente sprint, uno detrás de otro.

Tanto el sprint como los otros eventos tienen utilidad, ya que se puede visibilizar el trabajo realizado en los artefactos, inspeccionar los mismos para detectar variaciones o problemas y adaptar los procesos y los materiales en caso de que el desarrollo se desvíe fuera de los límites aceptables o si el producto resultante es inaceptable.

El proceso de llevar a cabo Scrum se define por sus eventos, roles y artefactos, resumidos en inglés en la Figura \ref{scrum:resumenProceso} y que se detallan a lo largo de este apartado.

![Esquema de la ejecución de Scrum (Fuente: @Scrum_image)\label{scrum:resumenProceso}](scrum_process.jpg){width=90%}

Durante los sprints y en toda la implementación de Scrum, se encuentra una pequeña unidad de personas responsables: el equipo Scrum. Este equipo es multifuncional, y sus miembros poseen las habilidades necesarias para generar valor en cada sprint. Es autogestionado, asignándose internamente las tareas y la forma de realizarlas, y está enfocado en el objetivo del producto. El equipo Scrum es responsable de llevar a cabo todas las actividades relacionadas con el producto (colaboración con interesados, mantenimiento, desarrollo, investigación y otras), además de crear un incremento útil y valioso en cada sprint. No tiene jerarquías ni subequipos, todos sus miembros están al mismo nivel. El tamaño ideal del equipo es de 10 personas o menos, pero no implica que no pueda haber más personas, en dicho caso se organizarán varios equipos Scrum. En el equipo existen tres roles principales:

- Equipo de desarrollo: grupo de personas comprometidas a crear cualquier aspecto de un incremento de calidad en cada sprint. Se encargan de crear el Sprint Backlog con las tareas a realizar durante el sprint y de adaptar su plan de trabajo diario para cumplir con el objetivo del sprint.
- Propietario del Producto o Product Owner: única persona responsable de maximizar el valor del producto resultante. Se encarga o se responsabiliza de que el Product Backlog contenga las tareas necesarias para alcanzar el objetivo del producto, representen las necesidades de los interesados, estén ordenadas y priorizadas, y sean comprendidas. Toda la organización debe respetar sus decisiones, y cualquier posible Product Backlog debe ser justificado ante él.
- Scrum Master: responsable de asegurar que Scrum sea comprendido y ejecutado tal y como está definido en la Guía de Scrum, tanto por el equipo de desarrollo como por la organización en su conjunto, por lo que puede ser común a toda la organización. Ayuda a comprender el trabajo, facilita su realización, elimina barreras y mejora las prácticas utilizadas.

Estos miembros, junto a los interesados, tienen una idea clara del estado del desarrollo y de las tareas realizadas a partir de los siguientes artefactos, tratados a lo largo de los sprints:

- Pila del Producto o Product Backlog: lista ordenada y emergente de las tareas a realizar necesarias para mejorar el producto. Estas tareas se refinan mediante su detallado y división en partes más pequeñas y precisas, listas para ser seleccionadas en la planificación del siguiente sprint. Esta lista se basa en el cumplimiento del objetivo del producto, que es el objetivo a largo plazo.
- Pila del Sprint o Sprint Backlog: lista de tareas creada por los desarrolladores, que representa el plan de trabajo para el sprint con el fin de lograr el objetivo del sprint. No es fija y se actualiza a lo largo del sprint.
- Incremento: representa un avance hacia el objetivo del producto. Se generan uno o varios incrementos al final del sprint, los cuales se añaden a los anteriores y se verifican para garantizar su correcto funcionamiento en conjunto. Un incremento se considera completo cuando cumple con los estándares de calidad definidos en la definición de terminado.

Una característica importante de Scrum es la celebración de eventos que permiten inspeccionar y adaptar los artefactos de manera formal. Estos eventos se utilizan para aplicar regularidad a las reuniones y minimizar la necesidad de reuniones no planificadas. La Guía de Scrum recomienda que siempre se realicen en el mismo lugar y a la misma hora para reducir la complejidad. Los distintos tipos de eventos son los siguientes:

- Sprint: además de lo mencionado anteriormente, cabe detallar algunas características de este evento. El sprint es una etapa en la que se procura mantener constante la calidad del desarrollo y no se realizan cambios que puedan comprometer el objetivo del sprint. Permite modificaciones en el Product Backlog para refinar los elementos, así como aclaraciones y negociaciones con el Product Owner. La ejecución del sprint garantiza la inspección y adaptación del progreso hacia el objetivo del producto al menos una vez al mes. Su duración se justifica porque periodos más largos pueden hacer que el objetivo del sprint se vuelva inválido e incrementen la complejidad y los riesgos. Los sprints cortos limitan el riesgo de coste y esfuerzo a intervalos pequeños, comparables a proyectos de menor envergadura. Los sprints anteriores son útiles para la toma de decisiones y para pronosticar el progreso del sprint, mediante prácticas como el análisis de trabajo pendiente (burn-downs), de trabajo completado (burn-ups) y los flujos acumulativos. Existe la posibilidad de cancelar el sprint si su objetivo se vuelve obsoleto, y solo el Product Owner tiene la autoridad para hacerlo.

- Planificación del Sprint: sirve para establecer el trabajo que se realizará durante el sprint. Es el primer evento que se ejecuta antes de comenzar el sprint, en el cual el equipo Scrum colabora para crear un plan. El Product Owner debe asegurarse de que los asistentes estén preparados para discutir los elementos importantes del Product Backlog y su relación con el objetivo del producto. Los temas que se tratan son:
	- El valor que aporta el sprint y el incremento resultante al producto y a los interesados, definiendo un objetivo del sprint.
	- Las tareas a realizar durante el sprint, seleccionadas por los desarrolladores a partir del Product Backlog. El equipo Scrum puede refinar estos elementos para aumentar su comprensión y confianza.
	- El plan del trabajo necesario para crear un incremento que cumpla con la definición de terminado, elaborado por los desarrolladores.

	Este evento no se limita únicamente al equipo Scrum, se pueden invitar a otras personas que asesoren al equipo.

- Scrum diario: es un evento diario de unos 15 minutos realizado durante el sprint en el que los desarrolladores inspeccionan el progreso hacia el objetivo del sprint y adaptan el Sprint Backlog según sea necesario. Los participantes informan brevemente sobre el progreso y generan un plan viable para el siguiente día laboral, identificando impedimentos, promoviendo una toma de decisiones rápida y eliminando la necesidad de reuniones no planificadas. Esto se traduce en un equipo bien comunicado, enfocado y autogestionado. El Scrum diario no tiene una estructura fija y no excluye la posibilidad de realizar discusiones más detalladas a lo largo del día.

- Revisión del Sprint: es una sesión de trabajo colaborativo que se realiza con el fin de inspeccionar los resultados al final del sprint y determinar futuras adaptaciones del proyecto. Durante este evento, el equipo Scrum presenta los resultados de su trabajo a los interesados y se discute el progreso hacia el objetivo del producto, incluyendo posibles ajustes al Product Backlog para satisfacer nuevas oportunidades.

- Retrospectiva del Sprint: es la última reunión del sprint, con el fin de planificar formas de aumentar la calidad y efectividad del desarrollo. El equipo Scrum analiza las interacciones entre personas, los procesos y herramientas, y la definición de terminado para identificar qué salió bien durante el sprint, los problemas encontrados y la forma de resolverlos (en el caso de hacerlo). Tras ello, identifican cambios útiles para mejorar, y se abordan al momento o se añaden al Sprint Backlog.

### OpenUP

OpenUP es definido @OpenUP_UTM como una metodología de desarrollo de software iterativa e incremental que manifiesta el proceso de construir un sistema mediante el desarrollo colaborativo de software, con un enfoque pragmático y una filosofía ágil. A su vez, permite centrar el desarrollo en los casos de uso del usuario final, en la identificación y mitigación de riesgos, y en la arquitectura del sistema desde las primeras fases. Esta metodología está concebida para ser utilizada como una base, conteniendo los elementos fundamentales para el desarrollo, y se le puede añadir o adaptar el contenido de otros procesos según las necesidades del proyecto.

OpenUP se apoya en equipos saludables, colaborativos y con conocimiento compartido acerca del proyecto, en maximizar los beneficios y cumplir con los requisitos, y en utilizar prácticas que permitan obtener retroalimentación temprana y continua a partir de incrementos en la funcionalidad del producto.

Los proyectos que implementan OpenUP se dividen en iteraciones cortas planificadas. El uso de las iteraciones evita la generación innecesaria de documentación, diagramas e iteraciones excesivas, y facilita la detección temprana de errores, haciendo más eficiente el uso de recursos y tiempo. Durante las iteraciones, el equipo se organiza y se compromete para alcanzar los objetivos. Se define una lista de tareas detalladas que resultan en microincrementos y en la entrega de valor a las partes interesadas. Los microincrementos se producen a un ritmo constante y permiten comprender el valor que aporta la iteración al proyecto y el progreso del mismo.

OpenUP organiza las iteraciones en cuatro fases del ciclo de vida del proyecto, compuestas por objetivos y actividades que permiten gestionar eficientemente el proyecto:

- Inicio: se determina el alcance del proyecto y los objetivos a cumplir. Tras esta fase, si se considera viable, el proyecto se continúa.
- Elaboración: trata la mitigación de riesgos, la arquitectura del sistema, la validación de requisitos, el diseño, los costos y los cronogramas.
- Construcción: detalla los requisitos y su cumplimiento, el diseño, la implementación de funcionalidades y las pruebas del software.
- Transición: se centra en la transferencia del software al entorno del cliente, en la aceptación y conformidad del producto por parte de las partes interesadas, en la corrección de defectos y otros ajustes finales.

### Implementación en este proyecto

Tras la definición de los conceptos necesarios acerca de las metodologías, esta sección desarrolla la manera en la que se aplicaron Scrum y OpenUP. El desarrollo de este proyecto se ha realizado teniendo OpenUP en mente, mientras que el esfuerzo de este proyecto se ha gestionado utilizando la metodología Scrum. Pese a conocer que la aplicación no es la más adecuada al ser un equipo más pequeño de lo normal y en el que existe un único desarrollador, la aplicación de esta metodología procura ser fiel con todos los elementos esenciales que la componen. Se ha optado por metodologías ágiles debido a que es un proyecto cuyo desarrollo comienza con unos requisitos básicos y atraviesa fases en las que se identifican fallos de rendimiento, posibles mejoras y nuevos requisitos. Una característica importante es la constante retroalimentación de los interesados, que permitieron redirigir el proyecto según transcurría, y la baja formalidad en cuanto a documentación permitía centrar el esfuerzo en el funcionamiento del proyecto. Por otro lado, la elección ha sido influida por la preferencia y la previa experiencia del autor con estas metodologías.

#### Roles y artefactos

En este proyecto han participado los tutores y el alumno con los roles distribuidos de la siguiente manera:

- Interesados: los tutores Rubén Cantarero Navarro y Ana Rubio Ruiz.
- Equipo de desarrollo: compuesto únicamente por el alumno Rubén Gómez Villegas.
- Product Owner: los tutores Rubén Cantarero Navarro y Ana Rubio Ruiz.
- Scrum Master: tanto el alumno como los tutores. Debido a que ambas partes tienen conocimiento acerca de Scrum y llegaron a un acuerdo acerca de como gestionar este proyecto, no ha sido necesaria la intervención de este rol. 

Los distintos artefactos Scrum se han representado en un tablero Kanban creado con Trello para facilitar el seguimiento de la metodología. Un tablero Kanban funciona como una herramienta ágil para gestionar proyectos, ayudando a visualizar el trabajo, limitar el trabajo en curso y maximizar la eficiencia del mismo @Kanban_Atlassian @Kanban_Miro, además de tener equipos comprometidos con una cantidad de trabajo adecuada @Kanban_Atlassian. Está compuesto por tarjetas y otras señales visuales que describen el trabajo, permitiendo que los compañeros y los interesados conozcan su estado @Kanban_Atlassian. Las tarjetas están agrupadas en columnas que representan etapas del flujo de trabajo, y se van moviendo entre columnas según avanza la tarea hasta su finalización @Kanban_Atlassian @Kanban_Miro.

![Tablero Kanban utilizado durante el desarrollo\label{metodologia:tableroTrello}](trello_tablero.png){width=90%}

El tablero de Trello utilizado, mostrado en la Figura \ref{metodologia:tableroTrello}, es una representación digital de Kanban, creado por y para el alumno y las necesidades del desarrollo, y contiene las siguientes columnas:

- *Info, templates and utils*: contiene información del tablero y una tarjeta que actúa como plantilla para representar tareas.
- *Product backlog*: contiene las tareas propias de un Product Backlog de Scrum.
- *Sprint backlog*: contiene las tareas propias de un Sprint Backlog de Scrum.
- *In progress*: lista las tareas que se están ejecutando a lo largo del sprint. Son tareas que aún no están finalizadas.
- *Review/Testing*: representa las tareas que se han terminado de desarrollar pero que deben pasar por una revisión de su correcto funcionamiento y otra del cumplimiento con las necesidades de los interesados, siendo esta última ejecutada durante la revisión del sprint.
- *Done (Sprint X)*: cuando las tareas están terminadas, acaban en esta lista, en la cual se marcan apropiadamente como finalizadas. Existe una lista por cada sprint, para poder diferenciar qué tarea se hizo cuándo, siendo "X" el número del sprint.

![Vistas de las tarjetas del tablero: vista previa (izquierda) y detallada (derecha)\label{metodologia:vistasTarjetasTrello}](trello_vistasTarjeta.png){width=80%}

Las tarjetas representan tareas, y se muestran en dos vistas, mostradas en la Figura \ref{metodologia:vistasTarjetasTrello}: la vista previa, que muestra la tarjeta resumida en una columna, y la vista detallada, la cual se abre al hacer clic en la tarjeta resumida. Las tarjetas tienen las siguientes propiedades configuradas:

- Miembros: quienes se encargan de la tarea. Son usuarios registrados en Trello y miembros del tablero que pueden autoasignarse o ser asignados por otros.
- Etiquetas: se utilizan para clasificar de manera visual el tipo de tarjeta. Existen 6 tipos distintos, cada uno con un color y patrón (útil para las personas con daltonismo) como se puede ver en la Figura \ref{metodologia:etiquetasTrello}, siendo posible aplicar varios simultáneamente. Son los siguientes:

	![Etiquetas disponibles en el tablero\label{metodologia:etiquetasTrello}](trello_etiquetas.png){width=40%}

	- *New feature*, verde: la tarjeta representa una tarea cuyo resultado es una nueva funcionalidad en el proyecto.
	- *Test*, amarillo: la tarjeta representa una tarea que prueba funciones y elementos ya existentes en el proyecto.
	- *Fix*, naranja: la tarjeta representa una tarea que arregla funciones y elementos ya existentes en el proyecto.
	- *Blocked*, rojo: la tarjeta representa una tarea pausada debido a un impedimento u obstáculo, como una dependencia de otra tarea.
	- *Details card*, azul: la tarjeta muestra información, no representa ninguna tarea.
	- *Report*, rosa: la tarjeta representa una tarea relacionada con esta memoria del proyecto.

- Vencimiento: fecha límite de realización de la tarea.
- Sprint: un campo personalizado que representa el número del sprint de la tarea.
- Weight: un campo personalizado numérico que representa el número del sprint de la tarea. El weight o peso es un número subjetivo que representa la dificultad, el tiempo a dedicar y la experiencia o falta de esta por parte del desarrollador respecto a una tarea.
- Card count: un campo personalizado numérico utilizado para contabilizar la cantidad de tarjetas en una lista. Siempre tiene el valor 1 y está oculto.
- Descripción: en el caso de necesitar detallar o añadir información adicional a las tareas, existe este campo.
- Actividad: muestra las acciones que han ocurrido (como el paso de una lista a otra o la asignación de miembros) y permite a los miembros del tablero hacer comentarios.

En este tablero se pueden identificar dos tipos de tarjetas: las tarjetas de información y las de tareas. Las de tareas se crean a partir de una plantilla y se mueven entre las listas durante los sprints. En cambio, las de información son fijas y sirven para detallar el uso de una lista y resumir su contenido. Éstas se encuentran en la primera posición de las listas, tienen la etiqueta azul y dos campos que se pueden observar desde la vista previa:

- Sum of Weight: calcula la suma de los pesos de una lista de tareas. Útil para calcular el peso total de un sprint.
- Sum of Card count: calcula la cantidad de tareas en una lista. Debido a que Trello por defecto no proporciona una forma de realizar esto, el campo es útil en las listas en las que no caben todas las tarjetas en pantalla, además que sirve para comparar entre sprints la cantidad de tareas hechas.

Además, las tarjetas de información en los sprints indican la fecha de inicio y fin del sprint. En el caso de ser un sprint finalizado, se le adjunta el pull request realizado en GitHub para conocer fácilmente el incremento del producto al que dio lugar.

En el tablero se ha habilitado la automatización que ofrece Trello a través de la selección de varios triggers o disparadores y de acciones consecuentes relacionadas con las propiedades de las tarjetas y las acciones realizables sobre ellas. En este proyecto, las reglas activadas son las siguientes, mostradas en la Figura \ref{metodologia:reglasAutomTrello}:

![Reglas de automatización utilizadas en el tablero\label{metodologia:reglasAutomTrello}](trello_automatizaciones.png){width=100%}

1. *Cuando una tarjeta sin miembro asignado se mueve al Sprint backlog por un miembro X, el miembro X se le asigna, se establece la fecha de vencimiento a 1 semana y se añade el comentario "Añadido al Sprint backlog"*: automatiza la selección de una tarea para ejecutarla durante el sprint.
2. *Cuando una tarjeta se mueve a cualquier lista "Done" por cualquiera, marcar la fecha de vencimiento como completa*: automatiza el completado de una tarea.
3. *Cuando la fecha de vencimiento de una tarjeta se marca como completa, se añade el comentario "Completado"*: automatiza el registro del completado de una tarea.
4. *Cuando una tarjeta se mueve fuera de cualquier lista "Done" por cualquiera, marcar la fecha de vencimiento como incompleta*: automatiza la reversión del completado de una tarea.
5. *Cuando la fecha de vencimiento de una tarjeta se marca como incompleta, se añade el comentario "Tarea reabierta"*: automatiza el registro de la reapertura de una tarea.

Cabe recalcar que este tablero lo ofrece el alumno para su uso en cualquier desarrollo de software, y que en este caso su contenido está en inglés debido a que su uso ha sido en gran parte para gestionar la parte codificada, también en inglés, de este [TFG](#TFG).


#### Ejecución de los eventos

Los eventos definidos en [Scrum](#Scrum) se han realizado mediante Teams, donde se programan las reuniones para crear recordatorios y llevarlas a cabo, evitando el consumo de tiempo que supone para el alumno y los tutores el desplazamiento, y facilitando la manera de mostrar código y otros aspectos del proyecto. Se han ejecutado de la siguiente forma:

**Planificación del sprint**: antes de iniciar el sprint, el desarrollador y los Product Owners comparan los objetivos del proyecto y las necesidades con las tareas ya realizadas, y debaten sobre qué tareas nuevas añadir en forma de tarjetas al product backlog para realizar a lo largo del desarrollo. Estas tareas también se pueden basar en ideas surgidas tanto por el desarrollador como por los propietarios. Asimismo, se planifica el fin del sprint, limitando el tiempo a 1 semana si el incremento se basa en el código del producto, o a 2 semanas si el incremento se basa en la documentación y la memoria de este proyecto; y se consideran las tareas para añadirlas al sprint backlog y así realizarlas en el sprint entrante, con el suficiente refinamiento y que resulten en uno o varios incrementos previamente debatidos. Estas tareas son añadidas a la lista correspondiente del tablero y el desarrollador rellena los campos de manera apropiada, incluyendo el peso de la tarea, siendo este un valor útil para conocer si es demasiada tarea a realizar en un sprint. Normalmente, si el equipo de desarrollo fuera de mayor tamaño habría que llevar a cabo procesos como el *planning poker* para estimar un peso con el que el equipo esté de acuerdo. Pero como no es el caso, el desarrollador elige un valor de la secuencia modificada de Fibonacci: 0.5, 1, 2, 3, 5, 8, 13, 20, 40 o 100. Como parte final del sprint, se programan las demás reuniones y la próxima planificación del sprint. Finalmente, en el tablero Kanban se prepara una nueva lista *Done* con el número del sprint.

**Sprint**: a lo largo del sprint, el desarrollador ejecuta las tareas establecidas en el sprint backlog haciendo uso de las herramientas correspondientes. En cuanto comienza una tarea, la tarjeta es añadida a la lista *In progress* y se moverá hacia la lista *Review/Testing* cuando se finalice. Dentro de esta fase, la tarea puede pasar por pruebas realizadas dentro del sprint, y si se reconsidera como no completada, se mueve de vuelta a *In progress*. Dichas tareas se cumplen siguiendo la calidad definida en los siguientes apartados, y durante su progreso se irán realizando *commits* o publicaciones con los cambios al repositorio, concretando más, en la rama `develop` (se explica acerca de esta rama en posteriores apartados). A modo de añadir métricas de tiempo invertido en el desarrollo, los sprints se han realizado a lo largo de los días de la semana, con una jornada no fija de entre 1 y 8 horas diarias.

**Scrum diario**: no se ha realizado debido a que el equipo de desarrolladores está formado únicamente por el autor y a que los otros roles de Scrum ya conocen la tarea a realizar a lo largo del sprint por la reunión de planificación. Por otro lado, los tutores han mostrado la predisposición de atender lo antes posible cualquier consulta, ya sea a través de llamada rápida o mensaje de Teams, siendo esto un buen sustitutivo del Scrum diario.

**Revisión del sprint**: el desarrollador y los product owners revisan el estado final de las tareas establecidas en el sprint, además de probar la nueva funcionalidad del incremento. Tras una posible modificación rápida, las tarjetas de tareas del tablero Kanban son movidas a la columna *Done* del correspondiente sprint, marcándose así como completadas, y se realiza un pull request desde la rama `develop` a `main`, aumentando la versión del producto (ramas y versionado explicados en posteriores apartados). En el caso de ser una versión superior a la 1.0.0, se ejecuta el proceso de crear un release en el repositorio, subir la nueva versión del producto al registro de PlatformIO y generar la página web de documentación.

**Retrospectiva del sprint**: utilizadas para comentar el rendimiento de los sprints, la idoneidad de la cantidad de tareas, mejoras en la gestión del proyecto y en las propias reuniones. Por ejemplo, en una reunión de este tipo se debatió el paso de sprints de 1 semana a 2 semanas cuando las tareas están relacionadas con la redacción y no con el código, debido a que las primeras consumían más tiempo. No existía un procedimiento para el desarrollo de esta reunión, simplemente el tema se exponía y se resolvía en consecuencia.

### Control de versiones

En este apartado se detalla la forma en la que se ha implementado el control de versiones, una característica beneficiosa en el desarrollo de software, ya que permite a los equipos de desarrollo trabajar en paralelo evitando conflictos en el código. Además, facilita el rastreo y la gestión de los cambios realizados a lo largo del desarrollo, y permite comparar el estado actual del código fuente con versiones previas para resolver errores @ControlVersiones. Para este [TFG](#TFG), se han aprovechado las herramientas que ofrece GitHub, como las ramas, los pull requests y las liberaciones o releases.

En cuanto a la ramificación del repositorio, se utiliza una adaptación del flujo de trabajo Gitflow, un modelo de creación de ramas publicado en 2010 por Vincent Driessen, útil para proyectos de entrega continua @Gitflow_Atlassian. Según la publicación @Gitflow_Nvie, y para detallar la Figura \ref{metodologia:gitflow}, existen dos ramas principales que perduran a lo largo del tiempo: `master` o `main`, que registra el historial de publicación oficial del proyecto, y `develop`, en la cual se van integrando las funciones para la siguiente liberación del código. Cuando el código de la rama `develop` se encuentra en un punto estable y listo para la liberación, todos los cambios se fusionan hacia la rama `master`, lo que se traduce en una nueva versión del producto que se etiqueta. Junto a estas ramas, se utilizan otras con un tiempo de vida limitado y que en algún momento se eliminarán:

![Ilustración de Gitflow (Fuente: @Gitflow_Img)\label{metodologia:gitflow}](gitflow.png){width=75%}

- Ramas de características o *feature*: se utilizan para desarrollar nuevas características para una futura versión. Se crean a partir de `develop`, existen mientras la característica está en desarrollo, y finalmente se fusionan de nuevo hacia `develop` añadiendo la característica, o se descartan.
- Ramas de lanzamiento o *release*: nombradas `release-<next-version>`, se utilizan para preparar una nueva versión de producción. Se crea una a partir de `develop` cuando este último refleja las características destinadas a la versión a construir, se le asigna un número de versión, se mantiene la rama para añadir cambios ligeros y metadatos, hasta que finalmente está lista para el lanzamiento y se fusiona en `master`, representando una nueva versión. También se fusiona hacia `develop`, para mantener esos pequeños cambios realizados a esta rama.
- Ramas de parche rápido o *hotfix*: nombradas `hotfix-<next-version>`, se utilizan para resolver un fallo crítico en una versión de producción. Se crea a partir de `master`, se solventa el problema y finalmente se fusiona en `master`, aumentando la versión del producto, y en `develop`.

El uso de Gitflow por parte del alumno proviene de la previa experiencia utilizándolo y la compatibilidad que tiene con las metodologías del proyecto, pero en este caso difiere respecto a lo definido anteriormente:

- No se utilizan ramas de características. Al ser un equipo de desarrollo de un solo miembro y al no haberse planeado el desarrollo de distintas características en paralelo (la complejidad del proyecto no lo requiere), se ha considerado innecesaria la creación de este tipo de ramas, por lo que todos los cambios se van publicando a la rama `develop`.
- No se utilizan ramas de lanzamiento. Para simplificar el desarrollo, la única rama que contiene los lanzamientos es `main`, y en caso de realizar un ligero cambio en el código se crean ramas *hotfix*. `develop` se fusiona directamente hacia `main`, y si luego ocurre un *hotfix* en `main`, `main` se fusiona hacia `develop`.

Para etiquetar las versiones se ha utilizado un versionado semántico, que sirve para lanzar versiones que puedan indicar a los sistemas dependientes si dicha versión puede romper el funcionamiento del sistema. En su definición @Semver se trata el formato de la versión, que es `X.Y.Z`, formado por números enteros no negativos ni precedidos por ceros, y el incremento de versiones está definido de la siguiente forma:

- `X`, versión mayor: se han realizado cambios incompatibles. Cada incremento de `X` provoca establecer `Y` y `Z` a 0.
- `Y`, versión menor: se ha añadido funcionalidad compatible con versiones anteriores. Cada incremento de `Y` provoca establecer `Z` a 0.
- `Z`, versión parche: repara errores compatibles con versiones anteriores.

La primera versión lanzada al público se define como `1.0.0`, y es posible agregar identificadores y metadatos a versiones prelanzamiento. Por ejemplo, `1.0.0-alpha+001`.

Se ha preferido el versionado semántico sobre otros, como el versionado de calendario (usado por Ubuntu, cuya versión 24.04 muestra que salió en abril de 2024). Por ejemplo, ante el de calendario, es preferible este uso para que la versión no muestre una sensación de obsolescencia al utilizar una versión lanzada hace años ni una falta de madurez al utilizar una versión lanzada recientemente. De manera general, su uso se debe a la facilidad, la comprensión y a la previa experiencia del alumno.

### Criterios de calidad y estilo del código

A lo largo del desarrollo del código, se han seguido unos criterios de calidad establecidos por el autor con el fin de obtener un código comprensible tanto para desarrolladores como para usuarios, fácil de mantener y retomar en el futuro. Además, se ha procurado mantener un estilo homogéneo del código, también definido en este apartado. Los criterios son los siguientes:

- El código está escrito en inglés, incluyendo variables, funciones, comentarios y mensajes de registro. Al utilizar el idioma más hablado en el mundo @IdiomasHabladosMundo, la base de usuarios puede ser mucho más amplia que si se utilizara el idioma local.
- El código es autoexplicativo. En caso de ser complejo de comprender, hay comentarios que facilitan su entendimiento.
- Gran parte de las funciones están documentadas utilizando Doxygen, especificando una descripción, parámetros (en caso de existir) y valores de retorno (en caso de tenerlos). También se documentan otras partes del código, como las enumeraciones y los valores configurables.
- Las importaciones, enumeraciones, definiciones de valores, documentación y otros elementos considerados necesarios se muestran en archivos de cabecera (`.h`), evitando sobrecargar los archivos de código fuente (`.cpp`) con elementos no funcionales.
- El funcionamiento del código es eficiente, aprovechando las capacidades de la placa de desarrollo y del lenguaje de programación. Para ello, se realizan pruebas y consultas con los tutores y con herramientas de inteligencia artificial.
- Las líneas de comentarios no superan los 80 caracteres de longitud y las de código no superan los 120. En caso de necesitar más espacio, se introducen saltos de línea. Estos valores se originan a partir del primer almacenamiento digital de la historia de la informática, las tarjetas perforadas de 80x12 agujeros, y en la actualidad se limitan los caracteres por fila para mejorar la legibilidad del código sin necesidad de hacer scroll horizontal @80chars.
- El estilo de programación utilizado es el *Kernighan & Ritchie*, que evita líneas sin sentido y el consumo innecesario de espacio vertical en la sintaxis. Junto a este estilo, se emplea la indentación mediante tabulaciones y la convención de nombrado *lowerCamelCase*, útil para identificar distintas palabras al nombrar elementos del código sin necesidad de ampliar horizontalmente el código. El Listado \ref{metodologia:estiloKRlCC} muestra un ejemplo de este estilo.

```{.cpp #metodologia:estiloKRlCC .numberLines caption="Ejemplo de estilo del código Kernighan & Ritchie con lowerCamelCase" frame=single}
public int main(int argc, char *argv[]) {
	while (x == y) {
		doSomething();
		doSomethingElse();
		if (error)
			fixError();
		else
			continueAsNormal();
	}
}
```

- La ejecución muestra registros o *logs* si el usuario lo desea, los cuales se distribuyen por el código en puntos clave. Estos registros permiten realizar un seguimiento de lo que realiza la ejecución del código del proyecto e identificar fácilmente los fallos.

También, como parte de la calidad del código, se han establecido pruebas para comprobar el correcto funcionamiento del código, las cuales están detalladas en el Anexo [A](#pruebas).
