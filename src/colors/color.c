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
 * con mejora específica para el Burning Ship
 */
static double	smooth_color(double iter, double max_iter, double zx, double zy, t_fractal_type type)
{
	double	log_zn;
	double	nu;

	if (iter < max_iter)
	{
		/* Cálculo mejorado para el Burning Ship */
		if (type == BURNINGSHIP)
		{
			/* El Burning Ship necesita un enfoque diferente debido a los valores absolutos */
			log_zn = log(zx * zx + zy * zy);
			nu = log(log_zn / log(2.0)) / log(2.0);
			
			/* Factor de ajuste optimizado para el Burning Ship */
			iter = iter + 1.0 - 0.6 * nu;
			
			/* Limitamos el factor de suavizado para reducir puntos aislados */
			if (nu > 0.5)
				iter = floor(iter) + 0.5;
		}
		else
		{
			/* Estándar para Mandelbrot y Julia */
			log_zn = log(zx * zx + zy * zy) / 2.0;
			nu = log(log_zn / log(2.0)) / log(2.0);
			iter = iter + 1.0 - nu;
		}
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
	double	smoothed_iter;

	/* Puntos dentro del conjunto (máximas iteraciones) */
	if (f->iter >= f->max_iter)
	{
		mlx_put_pixel(f->img, f->x, f->y, 0x000000FF); /* Negro */
		return;
	}
	
	/* Tratamiento especial para puntos cercanos al borde en Burning Ship */
	if (f->type == BURNINGSHIP && f->iter > f->max_iter * 0.99)
	{
		mlx_put_pixel(f->img, f->x, f->y, 0x000000FF); /* Negro */
		return;
	}

	/* Suavizado opcional para transiciones de color más naturales */
	if (f->smooth && f->iter < f->max_iter - 1)
		smoothed_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im, f->type);
	else
		smoothed_iter = f->iter;
	
	/* Aplicamos shift de color para efectos artísticos */
	smoothed_iter += f->color_shift;
	
	/* Normalización mejorada para mejor distribución de colores */
	normalized_iter = fmod(smoothed_iter * 0.05, 1.0);

	/* Selección de colores a interpolar */
	index = (int)(normalized_iter * (f->palette->count - 1));
	color1.value = f->palette->colors[index];
	color2.value = f->palette->colors[(index + 1) % f->palette->count];
	
	/* Factor de interpolación más preciso */
	normalized_iter = normalized_iter * (f->palette->count - 1) - index;
	
	/* Interpolación con transición mejorada */
	color1 = interpolate_colors(color1, color2, normalized_iter);
	
	/* Pintar el píxel con el color calculado */
	mlx_put_pixel(f->img, f->x, f->y, get_color(
		color1.rgba.r, color1.rgba.g, color1.rgba.b, 0xFF));
}
