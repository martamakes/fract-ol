/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:53:55 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 11:31:50 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Initialize fractal-specific parameters */
static void	init_fractal_specific(t_fractol *f)
{
	if (f->type == MANDELBROT)
		f->shift_x = -0.5;
	else if (f->type == JULIA)
	{
		validate_julia_params(f, f->params);
		f->zoom = 1.3;
	}
	else if (f->type == BURNINGSHIP)
	{
		f->shift_x = -0.5062;
		f->shift_y = -0.5355;
		f->max_iter = 50;
		f->zoom = 4.79;
		f->color_shift = 1;
		f->palette_index = 2;
	}
}

/* Initializes fractal parameters based on the fractal type */
void	init_fractal_params(t_fractol *f)
{
	f->zoom = 4.0;
	f->max_iter = 20;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->palettes = init_palettes();
	f->palette_index = 0;
	f->palette = &f->palettes[0];
	f->palette_len = palette_len(f->palettes);
	f->smooth = true;
	f->color_shift = 0.0;
	init_fractal_specific(f);
}
