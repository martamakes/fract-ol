# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    debug_tests.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 15:04:24 by mvigara-          #+#    #+#              #
#    Updated: 2024/12/01 15:10:32 by mvigara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Detectar sistema operativo
OS=$(uname)

# Asegurar que estamos en el directorio correcto
if [[ ! -f "test_fractol.c" ]]; then
    echo -e "${RED}Error: Debes ejecutar este script desde el directorio tests/${NC}"
    exit 1
fi

# Función para verificar/instalar Criterion
check_criterion() {
    echo -e "${BLUE}Verificando Criterion...${NC}"
    
    if [ "$OS" = "Darwin" ]; then
        # macOS - usar Homebrew
        if ! brew list criterion &>/dev/null; then
            echo -e "${YELLOW}Criterion no está instalado. Instalando...${NC}"
            brew install criterion
        fi
    else
        # Ubuntu - usar apt
        if ! dpkg -l | grep -q libcriterion-dev; then
            echo -e "${YELLOW}Criterion no está instalado. Instalando...${NC}"
            sudo apt-get update
            sudo apt-get install -y libcriterion-dev
        fi
    fi
    
    echo -e "${GREEN}Criterion está instalado correctamente${NC}"
}

# Función para verificar/instalar herramientas de depuración
check_debug_tools() {
    if [ "$OS" = "Darwin" ]; then
        # Verificar LLDB en macOS
        if ! command -v lldb &> /dev/null; then
            echo -e "${YELLOW}LLDB no está instalado. Instalando Xcode Command Line Tools...${NC}"
            xcode-select --install
        fi
    else
        # Verificar GDB y Valgrind en Linux
        if ! command -v gdb &> /dev/null; then
            echo -e "${YELLOW}GDB no está instalado. Instalando...${NC}"
            sudo apt-get update && sudo apt-get install -y gdb
        fi
        
        if ! command -v valgrind &> /dev/null; then
            echo -e "${YELLOW}Valgrind no está instalado. Instalando...${NC}"
            sudo apt-get update && sudo apt-get install -y valgrind
        fi
    fi
    
    echo -e "${GREEN}Herramientas de depuración instaladas correctamente${NC}"
}

# Función para ejecutar tests con depurador
run_debug_tests() {
    if [ "$OS" = "Darwin" ]; then
        echo -e "${BLUE}Ejecutando tests con LLDB...${NC}"
        lldb ./test_fractol -o run
    else
        echo -e "${BLUE}Ejecutando tests con GDB...${NC}"
        gdb -ex run --args ./test_fractol
    fi
}

# Función para ejecutar tests con Valgrind/leaks
run_memory_tests() {
    if [ "$OS" = "Linux" ]; then
        echo -e "${BLUE}Ejecutando tests con Valgrind...${NC}"
        valgrind --leak-check=full \
                 --show-leak-kinds=all \
                 --track-origins=yes \
                 --verbose \
                 --log-file=valgrind-out.txt \
                 ./test_fractol
        
        echo -e "${GREEN}Resultados de Valgrind guardados en valgrind-out.txt${NC}"
        echo -e "${BLUE}Resumen de fugas de memoria:${NC}"
        grep -A 5 "LEAK SUMMARY" valgrind-out.txt
    else
        echo -e "${BLUE}Usando leaks en macOS...${NC}"
        MallocStackLogging=1 leaks --atExit -- ./test_fractol
    fi
}

# Verificar instalaciones necesarias
check_criterion
check_debug_tools

# Compilar los tests
echo -e "${BLUE}Compilando tests...${NC}"
make test

if [ $? -ne 0 ]; then
    echo -e "${RED}Error en la compilación${NC}"
    exit 1
fi

# Ejecutar las pruebas según los argumentos recibidos
case "$1" in
    "debug")
        run_debug_tests
        ;;
    "memory")
        run_memory_tests
        ;;
    "all"|"")
        run_debug_tests
        run_memory_tests
        ;;
    *)
        echo -e "${RED}Opción inválida. Uso: $0 [debug|memory|all]${NC}"
        exit 1
        ;;
esac