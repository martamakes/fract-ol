#!/bin/bash

echo "Compilando y ejecutando el proyecto Fractol..."

# Compilar el proyecto
make re

# Verificar si la compilación fue exitosa
if [ $? -ne 0 ]; then
    echo "Error en la compilación. Por favor, verifica los errores arriba."
    exit 1
fi

# Ejecutar el programa con argumentos
if [ $# -eq 0 ]; then
    echo -e "\nEjecutando fractal Mandelbrot..."
    ./fractol M
else
    echo -e "\nEjecutando con los parámetros proporcionados: $@"
    ./fractol "$@"
fi
