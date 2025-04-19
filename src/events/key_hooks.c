/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:56 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 10:31:04 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static void	print_help(void)
{
	printf("\n===== PROGRAM CONTROLS =====\n");
	printf("ESC: Exit program\n");
	printf("Arrow keys: Move view\n");
	printf("Mouse wheel: Zoom in/out\n");
	printf("C: Change color palette\n");
	printf("[/]: Adjust color shift\n");
	printf("S: Toggle color smoothing\n");
	printf("R: Reset view\n");
	printf("+/-: Increase/decrease maximum iterations\n");
	printf("1/2/3: Switch between fractals\n");
	printf("D/G/R: Change Julia set parameters\n");
	printf("I: Toggle info display\n");
	printf("H: Show this help\n\n");
}

static void	handle_arrow_keys(mlx_t *mlx, t_fractol *fractol)
{
	double	move_factor;
	
	move_factor = 0.1 * fractol->zoom;
	/* Corregido para que las direcciones sean intuitivas */
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		fractol->shift_x += move_factor; /* Movemos hacia la izquierda */
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		fractol->shift_x -= move_factor; /* Movemos hacia la derecha */
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		fractol->shift_y += move_factor; /* Movemos hacia arriba */
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		fractol->shift_y -= move_factor; /* Movemos hacia abajo */
}

static void	reset_view(t_fractol *f)
{
	f->zoom = 4.0;
	f->max_iter = 100;
	f->color_shift = 0.0; /* Resetea también el shift de color */
	
	if (f->type == MANDELBROT)
	{
		f->shift_x = -0.5;
		f->shift_y = 0.0;
	}
	else if (f->type == JULIA)
	{
		f->shift_x = 0.0;
		f->shift_y = 0.0;
	}
	else if (f->type == BURNINGSHIP)
	{
		f->shift_x = -0.4;
		f->shift_y = -0.5;
	}
}

/* Set Julia parameters for different set types */
static void	set_julia_param(t_fractol *f, char set_type)
{
	char	c;
	
	c = ft_tolower(set_type);
	if (c == 'd')
	{
		f->c.re = -0.4;
		f->c.im = 0.6;
	}
	else if (c == 'r')
	{
		f->c.re = -0.123;
		f->c.im = 0.745;
	}
	else if (c == 'g')
	{
		f->c.re = 0.36;
		f->c.im = 0.1;
	}
}

/* Switch fractal type */
static void	switch_fractal(t_fractol *f, t_fractal_type new_type)
{
	if (f->type == new_type)
		return;
	f->type = new_type;
	
	/* Set appropriate parameters for the new fractal */
	if (new_type == JULIA)
		set_julia_param(f, 'd');
	
	/* Reset view for the new fractal */
	reset_view(f);
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractol->mlx);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		fractol->palette_index = (fractol->palette_index + 1) % fractol->palette_len;
		fractol->palette = &fractol->palettes[fractol->palette_index];
	}
	/* Color shift con corchetes */
	if (keydata.key == MLX_KEY_RIGHT_BRACKET && keydata.action == MLX_PRESS)
		fractol->color_shift += 5.0; /* Avanza en la paleta */
	if (keydata.key == MLX_KEY_LEFT_BRACKET && keydata.action == MLX_PRESS)
		fractol->color_shift -= 5.0; /* Retrocede en la paleta */
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		reset_view(fractol); /* Resetea la vista */
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		fractol->smooth = !fractol->smooth; /* Alterna el suavizado */
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		fractol->max_iter += 50; /* Aumenta las iteraciones */
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS && 
		fractol->max_iter > 50)
		fractol->max_iter -= 50; /* Disminuye las iteraciones */
	/* Toggle info display */
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		toggle_info_display(fractol);
	/* Help key */
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
		print_help();
	
	/* Fractal switching keys */
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		switch_fractal(fractol, MANDELBROT);
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		switch_fractal(fractol, JULIA);
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		switch_fractal(fractol, BURNINGSHIP);
	
	/* Julia set variations (when in Julia mode) */
	if (fractol->type == JULIA && keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_D)
			set_julia_param(fractol, 'd');
		else if (keydata.key == MLX_KEY_R)
			set_julia_param(fractol, 'r');
		else if (keydata.key == MLX_KEY_G)
			set_julia_param(fractol, 'g');
	}
}

void	main_loop(void *param)
{
	t_fractol	*fractol;
	
	fractol = (t_fractol *)param;
	if (!fractol || !fractol->img)
		return;
	handle_arrow_keys(fractol->mlx, fractol);
	render_fractal(fractol);
	
	// Actualizar la información en pantalla si está activada
	if (fractol->show_info)
		update_info_display(fractol);
}