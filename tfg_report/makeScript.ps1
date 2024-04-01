param (
    [Parameter(Mandatory=$true)]
    [string]$command
)

switch ($command) {
    "docker" {
        .\makeScript.ps1 -command build
        .\makeScript.ps1 -command tfg
    }
    "build" {
        Write-Host "*******************"
        Write-Host "Construyendo imagen"
        Write-Host "*******************"
        docker build -t="felix.albertos/tfgii" .
    }
    "build_nocache" {
        Write-Host "*******************"
        Write-Host "Construyendo imagen"
        Write-Host "*******************"
        docker build --no-cache -t="felix.albertos/tfgii" .
    }
    "run" {
        Write-Host "*********************************"
        Write-Host "Corriendo imagen con directorio compartido"
        Write-Host "*********************************"
        docker run -i -t -v "$(Get-Location)/templateAPP:/home/tfgii/templateAPP" --name tfgii  felix.albertos/tfgii /bin/bash
    }
    "tfg" {
        .\makeScript.ps1 -command deleteContainer
        Write-Host "*********************************"
        Write-Host "Compilando Trabajo Final de Grado"
        Write-Host "*********************************"
        docker run -v "$(Get-Location)/templateAPP:/home/tfgii/templateAPP" --name tfgii  felix.albertos/tfgii
    }
    "deleteContainer" {
        Write-Host "*******************"
        Write-Host "Borrando contenedor"
        Write-Host "*******************"
        docker rm tfgii
    }
    "deleteImage" {
        Write-Host "***************"
        Write-Host "Borrando imagen"
        Write-Host "***************"
        docker rmi felix.albertos/tfgii
    }
    "help" {
        Write-Host "*******************"
        Write-Host "Utilidad para generar documento de TFG"
        Write-Host "Uso: "
        Write-Host "- Para compilar utilizando docker ejecutar 'makeScript.ps1 -command docker'"
        Write-Host "- Para mostrar la ayuda ejecutar 'makeScript.ps1 -command help'"
        Write-Host "*******************"
    }
    "clean" {
        .\makeScript.ps1 -command deleteContainer
        .\makeScript.ps1 -command deleteImage
    }
}
