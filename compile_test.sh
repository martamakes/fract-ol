#!/bin/bash
cd /Users/marta/Documents/PROJECTS/fractol
make re

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "\n\033[0;32mCompilation successful! Testing the changes:\033[0m"
    echo -e "Running Mandelbrot set with improved colors..."
    ./fractol M
else
    echo -e "\n\033[0;31mCompilation failed. Please check the errors above.\033[0m"
fi
