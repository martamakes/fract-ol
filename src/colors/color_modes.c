/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:55:40 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 09:55:44 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Get color using linear interpolation in the palette
 * 
 * @param iter Iteration value
 * @param max_iter Maximum iteration count
 * @param palette Color palette to use
 * @param color_shift Color shift value
 * @return Interpolated color
 */
t_color	linear_color(double iter, int max_iter, t_palette *palette, 
					int color_shift)
{
	double	index;
	double	t;
	int		idx1;
	int		idx2;
	t_color	c1;
	t_color	c2;

	index = fmod(iter + color_shift, max_iter) / max_iter;
	index = fmod(index, 1.0);
	index = index * (palette->count - 1);
	idx1 = (int)index;
	idx2 = (idx1 + 1) % palette->count;
	t = index - idx1;
	c1.value = palette->colors[idx1];
	c2.value = palette->colors[idx2];
	return (clrlerp(c1, c2, t));
}

/**
 * Calculate color using smooth coloring method
 * Based on logarithmic distance estimation
 * 
 * @param f Fractal structure
 * @return Smoothed color
 */
t_color	smooth_color(t_fractol *f)
{
	double	smooth_iter;
	double	log_zn;
	double	nu;
	double	zn;

	zn = f->z.re * f->z.re + f->z.im * f->z.im;
	if (zn < 1e-10)
		return ((t_color){0xFF000000});
	log_zn = log(zn) / 2.0;
	nu = log(log_zn / log(2.0)) / log(2.0);
	smooth_iter = f->iter + 1.0 - nu;
	if (smooth_iter < 0)
		smooth_iter = 0;
	return (linear_color(smooth_iter, f->max_iter, f->palette, f->color_shift));
}

/**
 * Calculate color using banded coloring method
 * Creates visual bands with sinusoidal pattern
 * 
 * @param f Fractal structure
 * @return Banded color
 */
t_color	banded_color(t_fractol *f)
{
	double	scaled_iter;
	double	band_factor;

	scaled_iter = (double)(f->iter + f->color_shift) / f->max_iter;
	band_factor = sin(scaled_iter * M_PI * 10) * 0.5 + 0.5;
	return (linear_color(f->iter * band_factor, f->max_iter, 
						f->palette, f->color_shift));
}

/**
 * Main function to assign color to current pixel
 * 
 * @param f Fractal structure
 */
t_color	put_pixel_color(t_fractol *f)
{
	t_color	color_struct;

	if (f->iter >= f->max_iter)
	{
		mlx_put_pixel(f->img, f->x, f->y, 0xFF000000);
		return ((t_color){0});
	}
	if (f->smooth)
		color_struct = smooth_color(f);
	else if (f->type == BURNINGSHIP) /* Usar diferente coloración para el Burning Ship */
	{
		/* Calcular color con una fórmula especial para mejorar el contraste */
		double color_value = (double)f->iter / f->max_iter;
		int palette_idx = (f->palette_index + 1) % f->palette_len; /* Usar otra paleta */
		color_struct = linear_color(color_value * f->max_iter * 0.8, 
								f->max_iter, 
								&f->palettes[palette_idx], 
								f->color_shift);
	}
	else
		color_struct = banded_color(f);
	apply_pixel_color(f, color_struct);
	return (color_struct);
}
