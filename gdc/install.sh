#!/bin/bash
APP_NAME="gdc"

INSTALL_DIR="/usr/local/bin"

CONFIG_DIR="$(eval echo ~${SUDO_USER:-$USER})/.config/Gestor_De_Costos"

SAVE_FILE="$CONFIG_DIR/save.txt"

if (( $EUID != 0 ))
then
    echo "Necesitas ejecutar con sudo."
    exit 1
fi

echo "Instalando Gestor De Costos..."

cp $APP_NAME $INSTALL_DIR/

chmod 777 $INSTALL_DIR/$APP_NAME

sudo -u ${SUDO_USER:-$USER} mkdir -p "$CONFIG_DIR"

if [ ! -f "$SAVE_FILE" ]
then
		sudo -u ${SUDO_USER:-$USER} bash -c "echo 0 > '$SAVE_FILE'"
fi

echo "Instalacion completada."

echo "Ahora puede ejecutar el Gestor De Costos con: $APP_NAME"
