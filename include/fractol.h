/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:40:28 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 14:13:53 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>

# define WIN_WIDTH   800
# define WIN_HEIGHT  600
# define FRACT_SIZE  800

/* Tipos de fractales */
typedef enum e_fractal_type
{
	NONE = 0,
	MANDELBROT = 1,
	JULIA = 2, 
	BURNINGSHIP = 3
} t_fractal_type;

/* Estructura para manejo de colores */
typedef union u_color
{
    uint32_t value;
    struct 
	{
        uint8_t a;
        uint8_t b; 
        uint8_t g;
        uint8_t r;
    } rgba;
} t_color;

/* Estructura para paletas de colores */
typedef struct s_palette 
{
    int     count;
    int     cycle;
    int32_t colors[9];
} t_palette;

/* Estructura para números complejos */
typedef struct s_complex
{
   double re;
   double im;
} t_complex;

/* Estructura principal del fractal */
typedef struct s_fractol  
{  
    mlx_t         *mlx;           /* Instancia MLX */
    mlx_image_t   *img;           /* Imagen del fractal */
    mlx_image_t   *info_img;      /* Imagen para mostrar información */
    char          **params;       /* Parámetros (argv) */
    t_fractal_type type;          /* Tipo de fractal */
    t_complex     c;              /* Parámetro para conjunto de Julia */
    t_complex     z;              /* Punto actual */
    int           x;              /* Coordenada x actual */
    int           y;              /* Coordenada y actual */
    int           iter;           /* Contador de iteraciones actual */
    double        zoom;           /* Nivel de zoom */
    double        shift_x;        /* Desplazamiento X */
    double        shift_y;        /* Desplazamiento Y */
    int           max_iter;       /* Iteraciones máximas */
    int           color_shift;    /* Rotación de paleta */
	t_palette       *palette;       /* Paleta actual */
	t_palette       *palettes;      /* Array de paletas */
	int             palette_index;  /* Índice de paleta actual */
	int             palette_len;    /* Número de paletas */
	bool            smooth;         /* Suavizado de colores */
	bool            show_info;      /* Mostrar información en pantalla */
} t_fractol;

/* Funciones principales */
bool    check_args(int argc, char **argv, t_fractol *fractol);
int     print_usage(void);
void    init_fractol(t_fractol *fractol);
void    exit_error(t_fractol *f, char *msg);

/* Funciones de renderizado */
void	put_pixel_color(t_fractol *f);
void	render_fractal(t_fractol *f);

/* Cálculo de fractales */
void	calculate_mandelbrot(t_fractol *f);
void	calculate_julia(t_fractol *f);
void	calculate_burning_ship(t_fractol *f);

/* Manejo de eventos */
void    handle_keys(mlx_key_data_t keydata, void *param);
void    handle_scroll(double xdelta, double ydelta, void *param);
void    main_loop(void *param);

/* Gestión de colores */
t_palette *init_palettes(void);
int	palette_len(t_palette *palettes);

/* Gestión de información en pantalla */
void	update_info_display(t_fractol *f);
void	toggle_info_display(t_fractol *f);

#endif