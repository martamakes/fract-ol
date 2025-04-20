#!/bin/bash

# Limpiamos y compilamos el proyecto
echo "Compilando el proyecto..."
make re

# Verificamos si la compilación fue exitosa
if [ $? -ne 0 ]; then
    echo "Error en la compilación. Abortando."
    exit 1
fi

echo "Compilación exitosa!"

# Ejecutamos el programa con los argumentos deseados
if [ $# -eq 0 ]; then
    echo "Ejecutando fractal Mandelbrot..."
    ./fractol M
else
    echo "Ejecutando con los argumentos proporcionados..."
    ./fractol "$@"
fi
