# Uso de la Plantilla

A continuación se presenta la estructura y utilización de esta plantilla.

## Configuración

La configuración de la plantilla se realiza a través del fichero *config.yaml*. Este es un fichero *yaml*, cuyos campos se describen en la Tabla \ref{anexo:valoresConfig}.

clave|valor
-|-----
Cite | Citas bibliográficas a incluir en la bibliografía no referenciadas en el texto
Cotutor | Nombre y apellidos del co-tutor académico
Csl | Fichero csl con el formato de las referencias
Department | Departamento del tutor académico
Language | Lenguaje de la plantilla [english\|spanish]
Month | Mes de defensa del TFG
Name | Nombre del autor del TFG
Technology | Tecnología específica
Title | Título del TFG
Tutor | Nombre del tutor académico
Year | Año de defensa del TFG

: Valores del fichero *config.yaml*\label{anexo:valoresConfig}

Un ejemplo de configuración de este fichero se muestra en el Listado \ref{anexo:valoresConfigEjemplo}.

```{.yaml #anexo:valoresConfigEjemplo .numberLines caption="Ejemplo de fichero de configuración config.yaml" frame=single}
Cite: @Gutwin2010GoneBut, @Rekimoto1997PickDrop
Cotutor: John Deere
Csl: input/resources/csl/acm-sig-proceedings.csl
Department: Ciencias de la Computación
Language: spanish
Month: Agosto
Name: Johny Anston
Technology: Sistemas de Información
Title: Una Aplicación para Resolver Problemas Genéricos
Tutor: Adam Smith
Year: 2023
```

## Estructura de Directorios

La plantilla tiene la estructura mostrada en la Figura \ref{estructuraDirectoriosTFG}.

```{.plantuml #estructuraDirectoriosTFG caption="Estructura de directorios de la plantilla del TFG" width=60%}
@startsalt
skinparam dpi 300
{
{T
+ Elemento Plantilla | Modificable por el usuario
+ templateAPP/
++ input/ | SI
+++ abstract.md
+++ acnowledgements.md
+++ acronyms.md
+++ appendices
++++ 01_ap1.md
++++ ...
+++ authorship.md
+++ chapters/
++++ 01_intro.md
++++ 02_objetivos.md
++++ ...
+++ dedication.md
+++ resources/
++++ bibliography/
+++++ bibliography.bib
++++ csl/
+++++ acm-sig-proceedings.csl
+++++ iso690-author-date-cs.csl
+++++ ...
++++ images/
+++++ image01.png
+++++ ...
++++ resumen.md
++ output/ | NO
+++ tfgii.pdf
++ plantuml-images/ | NO
++ static/ | NO
++ LICENSE | NO
++ config.yaml | SI
++ makefile | NO
++ run | NO
}
}
@endsalt
```

El documento generado por la plantilla es **output/tfgii.pdf**. Este documento se sobreescribe cada vez que se compila la plantilla. Es este documento, compilar se refiere a procesar los elementos de la plantilla para generar el documento *pdf*.

Las carpetas y ficheros modificables por el usuario y que contienen la información propia del TFG son las siguientes (marcadas como SI en la figura \ref{estructuraDirectoriosTFG}):

- input
- config.yaml

El resto de ficheros y directorios no deben de ser modificados por el usuario para el correcto funcionamiento de la plantilla.

### Carpeta input

La carpeta *input* contiene los ficheros que corresponden con las partes del TFG.

En primer lugar están los ficheros correspondientes al **abstract**, **acknowledgements**, **acronyms**, **authorship** y **dedication**. En estos, a excepción del **acronyms**, sólo hay que introducir el texto correspondiente.

El fichero **acronyms** tiene un formato yaml. En el, hay que introducir los pares *acrónimo* y *valor* separados por ":" y un espacio. Un ejemplo sería el del Listado \ref{anexo:ejemploAcronimoDefinicion}.


```{.yaml .numberLines #anexo:ejemploAcronimoDefinicion  caption="Ejemplo de definición de acrónimos" frame=single}
HTML: Lenguaje de marcas de hypertexto
HCI: Human Computer Interaction
```

También se encuentran en el directorio *input* los directorios **appendices** y **chapters**. Contienen, respectivamente, los apéndices y los capítulos del *TFG*, que corresponden con ficheros en *markdown*. En estos ficheros hay que tener en cuenta lo siguiente:

- El fichero debe comenzar con un encabezado de primer nivel
- Los ficheros se ordenan en el documento según su orden alfabético
- Sólo se tienen en cuenta los ficheros que comienzan con dos dígitos numéricos, p.ej. 01
- Si un fichero no comienza con dos dígitos numéricos, es ignorado y no se incluye a la hora de generar el documento

### Carpeta resources

El directorio *resources* contiene recursos de utilidad para la generación del documento, como imágenes o bibliografía.

La bibliografía se recoge en el fichero **bibliography/bibliography.bib**. Es un fichero en formato *bibtex* @bibtex que contiene los elementos bibliográficos. Por ejemplo, en el Listado \ref{anexo:ejemploBibliography} se encuentra definido el elementos bibliográfico *bibtex*.

```{.bibtex #anexo:ejemploBibliography .numberLines caption="Ejemplo de definición de elemento bibliográfico" frame=single}
@misc{bibtex,
  title = {BibTeX Format Description},
  howpublished = {\url{https://www.bibtex.org/Format/}},
  note = {Accessed: 2023-09-28}
}
```


El directorio **csl** contiene ficheros con diferentes formatos de bibliografía. Finalmente, el directorio **images** contiene las imágenes a utilizar en el documento.
 
## Elementos del Documento

Si bien la plantilla permite utilizar cualquier elemento de *Markdown* y *pandoc*, hay una serie de elementos que pueden ser de especial utilidad de cara a la realización de un TFG:

- Referencias bibliográficas
- Figuras
- Tablas
- Listados de código
- Notas al pie de página
- Acrónimos
- PlantUML
- Referencias dentro del Documento


### Citas Bibliográficas
\label{anchor:referencias}

La plantilla utiliza la bibliografía que se recoge en el fichero correspondiente. Para incluir una cita a un elemento bibliográfico, hay que añadir en el documento su referencia precedida del símbolo *\@*. Por ejemplo, para añadir la cita al elemento biliográfico *bibtex* se haría de la forma indicada en el Listado \ref{anexo:ejemploCita}.

```{.yaml #anexo:ejemploCita .numberLines caption="Ejemplo de cita de elemento bibliográfico" frame=single}
Es un fichero en formato *bibtex* @bibtex.
```

### Figuras

Para incluir figuras lo hacemos añadiendo una imagen en la cual especificamos el elemento *label*, que sirve para referenciarla. Por ejemplo, el código del Listaqdo \ref{anexo:ejemploFiguraCodigo} produce como resultado la Figura \ref{anexo:ejemploFiguraResultado}.

```{.markdown #anexo:ejemploFiguraCodigo .numberLines caption="Ejemplo de definición de una figura" frame=single}
![Logo de HTML5\label{anexo:ejemploFiguraResultado}](HTML5_sticker.png){width=50%}
```

![Logo de HTML5\label{anexo:ejemploFiguraResultado}](HTML5_sticker.png){width=50%}

### Tablas

Para definir una tabla se utiliza la sintaxis mostrada en el Listado de Código \ref{anexo:ejemploTablaCodigo}, cuyo resultado se muestra en la Tabla \ref{anexo:ejemploTablaResultado}.

```{.markdown #anexo:ejemploTablaCodigo .numberLines caption="Ejemplo de definición de una tabla" frame=single}
| Right | Left | Default | Center |
|------:|:-----|---------|:------:|
|   12  |  12  |    12   |    12  |
|  123  |  123 |   123   |   123  |
|    1  |    1 |     1   |     1  |
```


| Right | Left | Default | Center |
|------:|:-----|---------|:------:|
|   12  |  12  |    12   |    12  |
|  123  |  123 |   123   |   123  |
|    1  |    1 |     1   |     1  |

: Tabla de ejemplo\label{anexo:ejemploTablaResultado}

### Notas al Pie de Página

Para la definición de notas al pie de página se utiliza el código mostrado en el Listado \ref{anexo:ejemploPieCodigo}, cuyo resultado se muestra al pie de esta página[^anexo:ejemploNotaPie].

```{.markdown #anexo:ejemploPieCodigo .numberLines caption="Ejemplo de definición de una nota a pie de página" frame=single}
cuyo resultado se muestra al pie de esta página[^anexo:ejemploNotaPie].

[^anexo:ejemploNotaPie]: Ejemplo de nota al pie de página.
```

[^anexo:ejemploNotaPie]: Ejemplo de nota al pie de página.

### Acrónimos

Para hacer referencia a un acrónimo, por ejemplo [HTML](#HTML), hay que utilizar el código mostrado en el Listado \ref{anexo:ejemploAcronimo}. Previamente, el acrónimo debe de haber sido definido, tal y como se muestra en el Listado \ref{anexo:ejemploAcronimoDefinicion}.

```{.markdown #anexo:ejemploAcronimo .numberLines caption="Ejemplo de definición de referencia a un acrónimo" frame=single}
Para hacer referencia a un acrónimo, por ejemplo [HTML](#HTML), hay ...
```

### PlantUML

Esta plantilla permite la inserción de diagramas en *PlantUML* @plantuml. En el Listado \ref{anexo:ejemploPlantumlBasicoCodigo} se muestra un ejemplo básico de un diagrama de objetos en *PlantUML*, cuyo resultado se muestra en la Figura \ref{anexo:ejemploPlantumlBasicoResultado}.

```{#anexo:ejemploPlantumlBasicoCodigo .numberLines caption="Ejemplo de código plantuml básico" frame=single}
@startuml
skinparam dpi 300
object Object01
object Object02
object Object03
object Object04
object Object05
object Object06
object Object07
object Object08

Object01 <|-- Object02
Object03 *-- Object04
Object05 o-- "4" Object06
Object07 .. Object08 : some labels
@enduml
```

```{.plantuml #anexo:ejemploPlantumlBasicoResultado .numberLines caption="Ejemplo de plantuml básico" frame=single}
@startuml
skinparam dpi 300
object Object01
object Object02
object Object03
object Object04
object Object05
object Object06
object Object07
object Object08

Object01 <|-- Object02
Object03 *-- Object04
Object05 o-- "4" Object06
Object07 .. Object08 : some labels
@enduml
```

 También se puede dar formato, colores y formas, a los diagramas generados con PlantUML, tal y como se muestra en el Listado \ref{anexo:ejemploPlantumlFormatoCodigo}. El resultado se muestra en la Figura \ref{anexo:ejemploPlantumlFormatoResultado}.

```{#anexo:ejemploPlantumlFormatoCodigo .numberLines caption="Ejemplo de código plantuml con formato" frame=single}
@startmindmap
skinparam dpi 300
<style>
mindmapDiagram {
  node {
    BackgroundColor white
    FontColor #B30033
  }
  :depth(1) {
    BackgroundColor white
    FontColor #B30033
  }
  .uclm {
    BackgroundColor white 
    FontColor #B30033
  }
  .active {
    BackgroundColor #B30033
    FontColor white
  }
}
</style>
* Requisitos 
** Requisitos de usuario <<active>>
*** Requisitos de dominio <<active>>
*** Requisitos de negocio <<active>>
*** Requisitos de usuario final <<active>>
** Requisitos de sistema 
** Requisitos de SW/HW 

@endmindmap

```

```{.plantuml #anexo:ejemploPlantumlFormatoResultado .numberLines caption="Ejemplo de plantuml con formato" frame=single}
@startmindmap
skinparam dpi 300
<style>
mindmapDiagram {
  node {
    BackgroundColor white
    FontColor #B30033
  }
  :depth(1) {
    BackgroundColor white
    FontColor #B30033
  }
  .uclm {
    BackgroundColor white 
    FontColor #B30033
  }
  .active {
    BackgroundColor #B30033
    FontColor white
  }
}
</style>
* Requisitos 
** Requisitos de usuario <<active>>
*** Requisitos de dominio <<active>>
*** Requisitos de negocio <<active>>
*** Requisitos de usuario final <<active>>
** Requisitos de sistema 
** Requisitos de SW/HW 

@endmindmap
```

### Referencias Dentro del Documento

Para hacer una referencia a un capítulo dentro del documento se indica entre llaves el texto del enlace, seguido entre paréntesis del nombre del capítulo precedido del carácter *'#'*. El nombre del capítulo se indica en minúsculas y se sustituyen los espacios por el carácter *'-'*. Por ejemplo, si se quiere referenciar al capítulo *"Estructura de Directorios"* se utilizará el siguiente código mostrado en la Figura \ref{anexo:ejemploReferenciaInterna}.

```{#anexo:ejemploReferenciaInterna .numberLines caption="Referencia dentro del documento" frame=single}
Referencia a la [estructura de directorios](#estructura-de-directorios)
```

## Creación del Documento

La creación del documento se puede realizar utilizando un contenedor en *Docker* o de forma nativa en *Linux*[^creaLinux]. La Figura \ref{estructuraDirectoriosRaiz} muestra la estructura del directorio raíz de la plantilla.

```{.plantuml #estructuraDirectoriosRaiz caption="Estructura de directorios raíz de la plantilla" width=30%}
@startsalt
skinparam dpi 300
{
{T
+ template
++ templateAPP
++ util/
+++ fonts/
+++ sw/
++ Dockerfile
++ makefile
}
}
@endsalt
```

A continuación, se explica cómo funciona cada una de estas aproximaciones, así como sus requisitos.


[^creaLinux]: Se ha probado que funciona correctamente en la distribución *Ubuntu 22.04.1*.

### Ubuntu 

Ejecutar 'make' en el directorio raíz de la plantilla. 

Hay que tener instalado el siguiente software[^installSoftware]: 

- texlive-latex-base 
- texlive-lang-spanish 
- texlive-xetex 
- make 
- pandoc-plantuml-filter 

[^installSoftware]: Para instalar el software en Ubuntu hay que ejecutar *apt install nombre-paquete* 

También hay que instalar las fuentes adecuadas. Para ello crear el directorio (si no existe), copiar las fuentes y actualizarlas según el código de la Figura \ref{instalarFuentes}.

```{.bash #instalarFuentes caption="Instalación de las fuentes para el documento"}
$ sudo mkdir -p /usr/share/fonts/truetype/msttcorefonts/
$ sudo cp util/fonts/* /usr/share/fonts/truetype/msttcorefonts/
$ sudo fc-cache -f -v
$ sudo texhash
```

Finalmente, hay que instalar pandoc, pero en su versión 2.19.2-1. Para ello, ejecutar la orden de la Figura \ref{instalarPandoc} en el directorio raíz de la plantilla. Si se utiliza cualquier otra versión es muy probable que se tengan problemas, por ejemplo a la hora de generar imágenes con *plantuml*.

```{.bash #instalarPandoc caption="Instalación de Pandoc en su versión 2.19.2-1"}
$ sudo dpkg -i util/sw/pandoc-2.19.2-1-amd64.deb
```

### Docker

Ejecutar 'make docker' en el directorio raíz de la plantilla.

En el caso de utilizar Docker, el único prerequisito es tenerlo instalado[^instalarDockerUbuntu].

[^instalarDockerUbuntu]: [https://docs.docker.com/engine/install/ubuntu/](https://docs.docker.com/engine/install/ubuntu/)
