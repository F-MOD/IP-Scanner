#!/bin/bash

# Instalar dependencias necesarias
sudo apt-get update
sudo apt-get install -y build-essential libssl-dev libpcap-dev

# Descargar y compilar el código de nmap
git clone https://github.com/usuario/nmap-tool.git
cd nmap-tool
make

# Agregar la herramienta al PATH del usuario actual
echo "export PATH=\$PATH:`pwd`" >> ~/.bashrc
source ~/.bashrc

# Mostrar un mensaje de finalización
echo "La herramienta de nmap ha sido instalada exitosamente. Para usarla, ejecute el comando nmap_tool."
