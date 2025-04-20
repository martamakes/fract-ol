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

# define FRACT_SIZE	600
# define WIN_WIDTH	600
# define WIN_HEIGHT	600

/* Fractal types */
typedef enum e_fractal_type
{
	NONE = 0,
	MANDELBROT = 1,
	JULIA = 2,
	BURNINGSHIP = 3
}	t_fractal_type;

/* Color handling structure */
typedef union u_color
{
	uint32_t	value;
	struct s_rgba
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	}	rgba;
}	t_color;

/* Color palette structure */
typedef struct s_palette
{
	int		count;
	int		cycle;
	int32_t	colors[9];
}	t_palette;

/* Complex number structure */
typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

/* Main fractal structure */
typedef struct s_fractol
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**params;
	t_fractal_type	type;
	t_complex		c;
	t_complex		z;
	int				x;
	int				y;
	int				iter;
	double			zoom;
	double			shift_x;
	double			shift_y;
	int				max_iter;
	int				color_shift;
	t_palette		*palette;
	t_palette		*palettes;
	int				palette_index;
	int				palette_len;
	bool			smooth;
}	t_fractol;

/* Julia preset structure */
typedef struct s_julia_preset
{
	char	key;
	double	re;
	double	im;
}	t_julia_preset;

/* Key to action mapping structure */
typedef struct s_key_action
{
	int		key;
	void	(*action)(t_fractol *f);
}	t_key_action;

/* Palette and color initialization */
t_palette	*init_palettes(void);
int			palette_len(t_palette *palettes);
void		init_palette_blue_gold(t_palette *palette);
void		init_palette_purple_green(t_palette *palette);
void		init_palette_fire(t_palette *palette);

/* Main functions and arguments */
bool		check_args(int argc, char **argv, t_fractol *fractol);
int			print_usage(void);
void		init_fractal_params(t_fractol *fractol);
void		exit_error(t_fractol *f, char *msg);
void		setup_mlx(t_fractol *fractol);
void		setup_hooks(t_fractol *fractol);

/* Helper functions */
char		*get_fractal_name(t_fractal_type type);
void		print_fractal_params(t_fractol *f);
void		set_predefined_julia(t_fractol *f, char set_type);
void		validate_julia_params(t_fractol *f, char **argv);

/* Rendering functions */
t_color		put_pixel_color(t_fractol *f);
void		render_fractal(t_fractol *f);

/* Fractal calculation */
void		calculate_mandelbrot(t_fractol *f);
void		calculate_julia(t_fractol *f);
void		calculate_burning_ship(t_fractol *f);

/* Color utilities functions */
uint32_t	get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int			ft_lerpi(int first, int second, double p);
double		smooth_step(double t);
t_color		clrlerp(t_color c1, t_color c2, double p);
void		apply_pixel_color(t_fractol *f, t_color color_struct);

/* Color modes functions */
t_color		linear_color(double iter, int max_iter, t_palette *palette,
				int color_shift);
t_color		smooth_color(t_fractol *f);
t_color		banded_color(t_fractol *f);

/* Key action handlers */
void		reset_view(t_fractol *f);
void		action_next_palette(t_fractol *f);
void		action_color_shift_up(t_fractol *f);
void		action_color_shift_down(t_fractol *f);
void		action_toggle_smooth(t_fractol *f);

/* Additional key action handlers */
void		action_iter_up(t_fractol *f);
void		action_iter_down(t_fractol *f);
void		set_julia_param(t_fractol *f, char set_type);
void		switch_fractal(t_fractol *f, t_fractal_type new_type);
void		print_help(void);
void		set_default_julia_params(t_fractol *f);

/* Fractal action handlers */
void		action_fractal_mandelbrot(t_fractol *f);
void		action_fractal_julia(t_fractol *f);
void		action_fractal_burningship(t_fractol *f);
void		action_julia_dendrite(t_fractol *f);
void		action_julia_rabbit(t_fractol *f);
void		action_julia_dragon(t_fractol *f);

/* Key hook functions */
bool		handle_arrow_keys(mlx_t *mlx, t_fractol *fractol);
void		process_key_action(t_fractol *f, int key);
void		handle_keys(mlx_key_data_t keydata, void *param);
void		handle_julia_keys(t_fractol *f, int key);
void		main_loop(void *param);

/* Zoom and scroll functions */
void		update_iterations(t_fractol *f);
void		update_zoom(t_fractol *f, double ydelta);
void		adjust_mouse_coords(int *mx, int *my);
void		print_debug_info(t_fractol *f, double old_zoom);
int			is_mouse_in_image(int x, int y);
void		calculate_complex_coords(t_fractol *f, int mx, int my,
				t_complex *mouse_pos);
void		update_fractal_shift(t_fractol *f, int mx, int my,
				t_complex mouse_pos);
void		handle_scroll(double xdelta, double ydelta, void *param);

#endif
