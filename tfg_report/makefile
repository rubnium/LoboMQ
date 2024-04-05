.PHONY: nativo docker build build_nocache docker run deleteContainer deleteImage clean tfg help
nativo: 
	@ (cd templateAPP/ ; ./run)
docker: build tfg
build:
	@echo "*******************"
	@echo "Construyendo imagen"
	@echo "*******************"
	docker build -t="felix.albertos/tfgii" .
build_nocache:
	@echo "*******************"
	@echo "Construyendo imagen"
	@echo "*******************"
	docker build --no-cache -t="felix.albertos/tfgii" .
run:
	@echo "*********************************"
	@echo "Corriendo imagen con directorio compartido"
	@echo "*********************************"
	-docker run -i -t -v "$(PWD)/templateAPP":/home/tfgii/templateAPP --name tfgii  felix.albertos/tfgii /bin/bash
tfg: deleteContainer
	@echo "*********************************"
	@echo "Compilando Trabajo Final de Grado"
	@echo "*********************************"
	-docker run -v "$(PWD)/templateAPP":/home/tfgii/templateAPP --name tfgii  felix.albertos/tfgii
deleteContainer:
	@echo "*******************"
	@echo "Borrando contenedor"
	@echo "*******************"
	-docker rm tfgii
deleteImage:
	@echo "***************"
	@echo "Borrando imagen"
	@echo "***************"
	-docker rmi felix.albertos/tfgii
help:
	@echo "*******************"
	@echo "Utilidad para generar documento de TFG"
	@echo "Uso: "
	@echo "- Para compilar de forma nativa ejecutar 'make'"
	@echo "- Para compilar utilizando docker ejecutar 'make docker'"
	@echo "- Para mostrar la ayuda ejecutar 'make help'"
	@echo "*******************"
clean: deleteContainer deleteImage
