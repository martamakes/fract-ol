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

/* Process color components for interpolation */
static void	process_colors(t_color *c1, t_color *c2, int *idx, t_palette *pal)
{
	c1->value = pal->colors[idx[0]];
	c2->value = pal->colors[idx[1]];
}

/* Get color using linear interpolation in the palette */
t_color	linear_color(double iter, int max_iter, t_palette *palette,
			int color_shift)
{
	double	index;
	double	t;
	int		indices[2];
	t_color	colors[2];

	index = fmod(iter + color_shift, max_iter) / max_iter;
	index = fmod(index, 1.0);
	index = index * (palette->count - 1);
	indices[0] = (int)index;
	indices[1] = (indices[0] + 1) % palette->count;
	t = index - indices[0];
	process_colors(&colors[0], &colors[1], indices, palette);
	return (clrlerp(colors[0], colors[1], t));
}

/* Calculate color using smooth coloring method */
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

/* Calculate color using banded coloring method */
t_color	banded_color(t_fractol *f)
{
	double	scaled_iter;
	double	band_factor;

	scaled_iter = (double)(f->iter + f->color_shift) / f->max_iter;
	band_factor = sin(scaled_iter * M_PI * 10) * 0.5 + 0.5;
	return (linear_color(f->iter * band_factor, f->max_iter,
			f->palette, f->color_shift));
}
