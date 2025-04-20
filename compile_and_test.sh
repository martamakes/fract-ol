#!/bin/bash
cd /Users/marta/Documents/PROJECTS/fractol
make re

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "\n\033[0;32mCompilation successful! You can run the program with:\033[0m"
    echo -e "./fractol M    # for Mandelbrot set"
    echo -e "./fractol J d  # for Julia set (dendrite)"
    echo -e "./fractol B    # for Burning Ship fractal"
else
    echo -e "\n\033[0;31mCompilation failed. Please check the errors above.\033[0m"
fi
