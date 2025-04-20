/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:40:28 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 11:18:47 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define FRACT_SIZE  600
# define WIN_WIDTH   600
# define WIN_HEIGHT  600

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
	t_palette     *palette;       /* Paleta actual */
	t_palette     *palettes;      /* Array de paletas */
	int           palette_index;  /* Índice de paleta actual */
	int           palette_len;    /* Número de paletas */
	bool          smooth;         /* Suavizado de colores */
} t_fractol;

/* Nueva estructura para presets de Julia (después de definir t_fractol) */
typedef struct s_julia_preset
{
	char		key;
	double		re;
	double		im;
} t_julia_preset;

/* Nueva estructura para mapeo de teclas a acciones */
typedef struct s_key_action
{
	int		key;  /* Usamos int en lugar de mlx_key_t */
	void	(*action)(t_fractol *f);
} t_key_action;

/* Inicialización de paletas y colores */
t_palette	*init_palettes(void);
int			palette_len(t_palette *palettes);

/* Funciones principales */
bool		check_args(int argc, char **argv, t_fractol *fractol);
int			print_usage(void);
void		init_fractal_params(t_fractol *fractol);
void		exit_error(t_fractol *f, char *msg);

/* Funciones de renderizado */
t_color		put_pixel_color(t_fractol *f);
void		render_fractal(t_fractol *f);

/* Cálculo de fractales */
void		calculate_mandelbrot(t_fractol *f);
void		calculate_julia(t_fractol *f);
void		calculate_burning_ship(t_fractol *f);

/* Function prototypes for color_utils.c */
uint32_t	get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int			ft_lerpi(int first, int second, double p);
double		smooth_step(double t);
t_color		clrlerp(t_color c1, t_color c2, double p);
void		apply_pixel_color(t_fractol *f, t_color color_struct);

/* Function prototypes for color_modes.c */
t_color		linear_color(double iter, int max_iter, t_palette *palette, 
			int color_shift);
t_color		smooth_color(t_fractol *f);
t_color		banded_color(t_fractol *f);

/* Function prototypes for key_actions.c */
void		reset_view(t_fractol *f);
void		action_next_palette(t_fractol *f);
void		action_color_shift_up(t_fractol *f);
void		action_color_shift_down(t_fractol *f);
void		action_toggle_smooth(t_fractol *f);

/* Function prototypes for key_actions2.c */
void		action_iter_up(t_fractol *f);
void		action_iter_down(t_fractol *f);
void		set_julia_param(t_fractol *f, char set_type);
void		switch_fractal(t_fractol *f, t_fractal_type new_type);
void		print_help(void);

/* Function prototypes for fractal_actions.c */
void		action_fractal_mandelbrot(t_fractol *f);
void		action_fractal_julia(t_fractol *f);
void		action_fractal_burningship(t_fractol *f);
void		action_julia_dendrite(t_fractol *f);
void		action_julia_rabbit(t_fractol *f);
void		action_julia_dragon(t_fractol *f);

/* Function prototypes for key_hooks.c */
bool		handle_arrow_keys(mlx_t *mlx, t_fractol *fractol);
void		process_key_action(t_fractol *f, int key);
void		handle_keys(mlx_key_data_t keydata, void *param);
void		main_loop(void *param);

/* Function prototypes for scroll_events.c */
void		handle_scroll(double xdelta, double ydelta, void *param);

/* Debug Functions */
void		print_fractal_params(t_fractol *f);

#endif
