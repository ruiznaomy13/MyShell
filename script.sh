#!/bin/bash

# Obtener la ruta del directorio actual
directorio="$PWD"

# Verificar si la ruta es un directorio válido
if [ -d "$directorio" ]; then
    # Listar solo los directorios (carpetas)
    echo "Listado de carpetas en $directorio:"
    for carpeta in "$directorio"/*; do
        if [ -d "$carpeta" ]; then
            echo "$carpeta"
        fi
    done
else
    echo "El directorio actual no es válido."
fi

