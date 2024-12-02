/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 13:35:30 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static uint32_t	get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static double	smooth_color(double iter, double max_iter, double zx, double zy)
{
	double	log_zn;
	double	nu;

	if (iter < max_iter)
	{
		log_zn = log(zx * zx + zy * zy) / 2.0;
		nu = log(log_zn / log(2.0)) / log(2.0);
		iter = iter + 1.0 - nu;
	}
	return (iter);
}

static t_color	int_to_color(int32_t value)
{
	t_color	color;

	color.value = value;
	return (color);
}

static void	get_colors_for_pixel(t_fractol *f, double t, t_color *c1, t_color *c2)
{
	int	index;

	index = (int)(t * (f->palette->count - 1));
	*c1 = int_to_color(f->palette->colors[index]);
	*c2 = int_to_color(f->palette->colors[(index + 1) % f->palette->count]);
}

void	put_pixel_color(t_fractol *f)
{
	t_color	color1;
	t_color	color2;
	t_hsv	hsv1;
	t_hsv	hsv2;
	t_color	final_color;
	double	t;

	if (f->iter >= f->max_iter)
		mlx_put_pixel(f->img, f->x, f->y, 0x000000FF);
	else
	{
		t = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im);
		t = t / f->max_iter;
		t = log(t * 0.95 + 0.05) / log(2.0);
		t = fmod(t * f->palette->count, 1.0);
		get_colors_for_pixel(f, t, &color1, &color2);
		hsv1 = rgb2hsv(color1);
		hsv2 = rgb2hsv(color2);
		final_color = hsv2rgb(interpolate_hsv(hsv1, hsv2, t));
		mlx_put_pixel(f->img, f->x, f->y, get_color(
				final_color.rgba.r, final_color.rgba.g,
				final_color.rgba.b, final_color.rgba.a));
	}
}
