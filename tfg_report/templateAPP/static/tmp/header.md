---
csl: input/resources/csl/acm-sig-proceedings.csl
nocite: |
  @Gutwin2010GoneBut, @Rekimoto1997PickDrop
toc: false
documentclass: book
fontsize: 10.5pt
header-includes: |
  \usepackage{fontspec}
  \setmainfont{Arial}
  \usepackage[top=1in,bottom=1in,left=3.25cm,right=3.5cm]{geometry}
  \renewcommand{\baselinestretch}{1.5}
  \usepackage{lipsum}
  \usepackage{graphicx}
  \usepackage{fancyhdr}
  \usepackage{emptypage}
  \usepackage[titletoc]{appendix}
  \usepackage[strict]{changepage}
  \usepackage{lmodern} 
  \usepackage{amsmath}
  \usepackage{xcolor}
  \usepackage{titlesec}
  \usepackage{listings}
  \newcommand*{\justifyheading}{\raggedleft}
  \pagestyle{fancy}
  \fancyhf{}
  \fancyhead[LE]{\slshape \nouppercase{\rightmark}}
  \fancyhead[RO]{\slshape \nouppercase{\leftmark}}
  \fancyhead[LO,RE]{\thepage}
  \renewcommand{\headrulewidth}{0pt}

  \renewcommand{\sectionmark}[1]{\markright{\thesection.\ #1}}
  \makeatletter

  \usepackage[spanish]{babel}
  \usepackage{appendix}
  \addto\captionsspanish{%
  \renewcommand\appendixname{Anexo}
  \renewcommand\appendixpagename{Anexos}
  \renewcommand{\listtablename}{Índice de Tablas}
  \def\tablename{Tabla}
  \renewcommand{\lstlistingname}{Listado}
  \renewcommand{\lstlistlistingname}{Índice de Listados}
  }
  \lstset{
    basicstyle=\ttfamily,
    columns=fullflexible,
    frame=single,
    breaklines=true,
    postbreak=\mbox{\textcolor{red}{$\hookrightarrow$}\space},
  }
---

