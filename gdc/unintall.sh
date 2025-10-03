#!/bin/bash

APP_NAME="gdc"

INSTALL_DIR="/usr/local/bin"

CONFIG_DIR="$(eval echo ~${SUDO_USER:-$USER})/.config/Gestor_De_Costos"

echo "Desinstalando Gestor De Costos..."

if (( $EUID != 0 ))
then
		echo "Necesitas ejecutar con sudo."
		exit 1
fi

rm -f -r $CONFIG_DIR

rm -f $INSTALL_DIR/$APP_NAME

echo "Gestor De Costos eliminado correctamente"
