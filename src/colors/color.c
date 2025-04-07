/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/04 12:52:15 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Convertir componentes RGBA a un solo valor uint32_t
 */
static uint32_t	get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
 * Suaviza el valor de iteración para colores más continuos
 */
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

/*
 * Interpola entre dos colores según un factor t entre 0 y 1
 */
static t_color	interpolate_colors(t_color c1, t_color c2, double t)
{
	t_color	result;
	double	t_smooth;

	t_smooth = t * t * (3 - 2 * t);
	result.rgba.r = (uint8_t)((1.0 - t_smooth) * c1.rgba.r + t_smooth * c2.rgba.r);
	result.rgba.g = (uint8_t)((1.0 - t_smooth) * c1.rgba.g + t_smooth * c2.rgba.g);
	result.rgba.b = (uint8_t)((1.0 - t_smooth) * c1.rgba.b + t_smooth * c2.rgba.b);
	result.rgba.a = 255;
	return (result);
}

/*
 * Asigna un color al píxel actual según el número de iteraciones
 */
void	put_pixel_color(t_fractol *f)
{
	t_color	color1;
	t_color	color2;
	double	normalized_iter;
	int		index;

	if (f->iter >= f->max_iter)
		mlx_put_pixel(f->img, f->x, f->y, 0x000000FF);
	else
	{
		/* Calcula iteración normalizada */
		normalized_iter = (double)f->iter / f->max_iter;
		normalized_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im)
			/ f->max_iter;
		
		/* Obtiene colores a interpolar */
		index = (int)(normalized_iter * (f->palette->count - 1));
		color1.value = f->palette->colors[index];
		color2.value = f->palette->colors[(index + 1) % f->palette->count];
		
		/* Calcula el factor de interpolación */
		normalized_iter = normalized_iter * (f->palette->count - 1) - index;
		
		/* Interpola los colores y dibuja el píxel */
		color1 = interpolate_colors(color1, color2, normalized_iter);
		mlx_put_pixel(f->img, f->x, f->y, get_color(
			color1.rgba.r, color1.rgba.g, color1.rgba.b, 0xFF));
	}
}
