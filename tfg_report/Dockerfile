# Version: 1.0
FROM ubuntu:22.04
LABEL maintainer="felix.albertos@uclm.es"
RUN apt update && \
    apt install -yq tzdata && \
    ln -fs /usr/share/zoneinfo/Europe/Madrid /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata
RUN apt install sudo -y
RUN adduser --uid 1000 tfgii
RUN echo "tfgii:tfgii" | chpasswd
RUN usermod -aG sudo tfgii
RUN apt install texlive-latex-base -y
RUN apt install texlive-lang-spanish -y
RUN apt install texlive-xetex -y
RUN mkdir -p /usr/share/fonts/truetype/msttcorefonts/
COPY util/fonts/* /usr/share/fonts/truetype/msttcorefonts/
RUN fc-cache -f -v
RUN texhash
RUN apt -y install make
COPY util/sw/pandoc-2.19.2-1-amd64.deb /tmp/
RUN dpkg -i /tmp/pandoc-2.19.2-1-amd64.deb
RUN apt install pandoc-plantuml-filter -y
USER tfgii
WORKDIR /home/tfgii/templateAPP
CMD make
