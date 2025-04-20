/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 15:10:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Special coloring for Burning Ship fractal */
static t_color	burning_ship_color(t_fractol *f)
{
	double	color_value;
	int		palette_idx;

	color_value = (double)f->iter / f->max_iter;
	palette_idx = (f->palette_index + 1) % f->palette_len;
	return (linear_color(color_value * f->max_iter * 0.8,
			f->max_iter,
			&f->palettes[palette_idx],
			f->color_shift));
}

/* Main function to assign color to current pixel */
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
	else if (f->type == BURNINGSHIP)
		color_struct = burning_ship_color(f);
	else
		color_struct = banded_color(f);
	apply_pixel_color(f, color_struct);
	return (color_struct);
}
