# Fract-ol

Un proyecto gráfico para explorar y visualizar fractales.

## Descripción

Fract-ol es un programa de visualización de fractales desarrollado en C utilizando la biblioteca gráfica MLX42. Este proyecto permite visualizar y explorar tres tipos diferentes de fractales:

- **Mandelbrot**: El clásico conjunto de Mandelbrot
- **Julia**: Variante del conjunto de Julia con parámetros personalizables
- **Burning Ship**: Un fractal adicional con una estética única

## Características

- Zoom infinito con la rueda del ratón
- Navegación por el fractal usando las flechas del teclado
- Múltiples paletas de colores cambiables con la tecla 'C'
- Modo de suavizado para mejorar la calidad visual (alternado con la tecla 'S')
- Zoom centrado en la posición del ratón
- Ajuste de iteraciones máximas con las teclas '+' y '-'
- Restablecimiento de la vista con la tecla 'R'

## Uso

```bash
# Compilar el proyecto
make

# Ejecutar con diferentes fractales
./fractol M          # Mandelbrot
./fractol J d        # Julia (conjunto dendrita)
./fractol J r        # Julia (conjunto conejo)
./fractol J g        # Julia (conjunto dragón)
./fractol J 0.3 0.5  # Julia con parámetros personalizados
./fractol B          # Burning Ship
```

## Controles

- **ESC**: Cerrar el programa
- **Flechas**: Desplazarse por el fractal
- **Rueda del ratón**: Zoom in/out centrado en la posición del ratón
- **C**: Cambiar paleta de colores
- **S**: Alternar modo de suavizado
- **R**: Restablecer vista
- **+/-**: Aumentar/disminuir iteraciones máximas

## Requisitos

- macOS o Linux
- GLFW instalado para MLX42
- Compilador GCC o Clang con soporte para C99

## Instalación

```bash
# Clonar el repositorio con submódulos
git clone --recursive <URL-DEL-REPOSITORIO>
cd fract-ol

# Compilar
make
```

## Testing

```bash
# Ejecutar pruebas con Criterion
cd tests
make test

# Ejecutar con depurador
make test_debug

# Verificar fugas de memoria
make test_memory
```

## Implementación técnica

El proyecto está estructurado en módulos:

- **core/**: Inicialización y lógica principal
- **fractals/**: Implementación matemática de cada tipo de fractal
- **events/**: Manejo de eventos de teclado y ratón
- **graphics/**: Renderizado y gestión de imágenes
- **colors/**: Manejo de colores y paletas
- **utils/**: Utilidades y gestión de errores

La implementación utiliza números complejos para calcular los fractales y la potencia de MLX42 para una representación visual eficiente.

## Galería

Para ver ejemplos visuales, ejecuta el programa con diferentes parámetros y experimenta con el zoom y los cambios de color.

---

Desarrollado para el proyecto Fract-ol de la Escuela 42.