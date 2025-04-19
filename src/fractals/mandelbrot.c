/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:57:09 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 17:42:51 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_in_main_bulb(t_complex c)
{
	double	q;

	q = (c.re - 0.25) * (c.re - 0.25) + c.im * c.im;
	if (q * (q + (c.re - 0.25)) < 0.25 * c.im * c.im)
		return (1);
	if ((c.re + 1.0) * (c.re + 1.0) + c.im * c.im < 0.0625)
		return (1);
	return (0);
}

void	calculate_mandelbrot(t_fractol *f)
{
	t_complex	c;
	t_complex	z;
	double		zr_sq;
	double		zi_sq;
	double		temp;

	// Calcular las coordenadas complejas con alta precisión
	c.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
	c.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;

	// Optimización: detectar puntos dentro del cardiode principal y período 2 bulbo
	if (is_in_main_bulb(c))
	{
		f->iter = f->max_iter;
		f->z.re = 0;
		f->z.im = 0;
		put_pixel_color(f);
		return ;
	}

	// Inicialización 
	z.re = 0;
	z.im = 0;
	zr_sq = 0;
	zi_sq = 0;
	f->iter = 0;

	// Nivel de zoom muy profundo: usar técnicas de optimización
	if (f->zoom < 1e-8)
	{
		// Periodos fijos para muestreo rápido
		int fastCycle = 8;
		
		// Iterar rápidamente en periodos
		while (f->iter < f->max_iter)
		{
			// Verificar escape cada 8 iteraciones inicialmente
			for (int i = 0; i < fastCycle && f->iter < f->max_iter; i++)
			{
				temp = zr_sq - zi_sq + c.re;
				z.im = 2.0 * z.re * z.im + c.im;
				z.re = temp;
				zr_sq = z.re * z.re;
				zi_sq = z.im * z.im;
				f->iter++;

				// Reducir verificaciones para velocidad en bucle interno
				if (i == fastCycle - 1 && zr_sq + zi_sq > 4.0)
					break;
			}

			// Verificar escape después del ciclo rápido
			if (zr_sq + zi_sq > 4.0)
				break;

			// Adaptar fastCycle según iteraciones
			if (f->iter > f->max_iter / 2)
				fastCycle = 16; // Más iteraciones por ciclo para puntos que tardan en escapar
		}
	}
	else
	{
		// Algoritmo estándar para niveles de zoom normales
		while (zr_sq + zi_sq < 4.0 && f->iter < f->max_iter)
		{
			temp = zr_sq - zi_sq + c.re;
			z.im = 2.0 * z.re * z.im + c.im;
			z.re = temp;
			zr_sq = z.re * z.re;
			zi_sq = z.im * z.im;
			f->iter++;
		}
	}

	// Guardar resultado para coloreado
	f->z = z;
	put_pixel_color(f);
}
