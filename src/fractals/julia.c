/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:34:37 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 17:30:29 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_julia(t_fractol *f)
{
	t_complex	z;
	double		temp;
	double		zr_sq;
	double		zi_sq;

	// Calcular coordenadas complejas con alta precisión
	z.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
	z.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
	f->iter = 0;
	
	// Pre-computo para evitar cálculos repetidos
	zr_sq = z.re * z.re;
	zi_sq = z.im * z.im;
	
	// Optimización para zoom profundo
	if (f->zoom < 1e-8)
	{
		// Verificación por lotes para mayor eficiencia en zoom profundo
		int batch_size = 8;
		
		while (f->iter < f->max_iter)
		{
			// Realizar múltiples iteraciones antes de verificar escape
			for (int i = 0; i < batch_size && f->iter < f->max_iter; i++)
			{
				temp = zr_sq - zi_sq + f->c.re;
				z.im = 2.0 * z.re * z.im + f->c.im;
				z.re = temp;
				
				// Actualizar cuadrados para siguiente iteración
				zr_sq = z.re * z.re;
				zi_sq = z.im * z.im;
				f->iter++;
				
				// Verificar solo en última iteración del lote para optimizar
				if (i == batch_size - 1 && (zr_sq + zi_sq) > 4.0)
					break;
			}
			
			// Comprobación principal de escape
			if ((zr_sq + zi_sq) > 4.0)
				break;
			
			// Ajustar tamaño de lote basado en profundidad
			if (f->iter > f->max_iter / 2)
				batch_size = 16; // Lotes más grandes para puntos que tardan en escapar
		}
	}
	else
	{
		// Algoritmo estándar para niveles de zoom normales
		while ((zr_sq + zi_sq) < 4.0 && f->iter < f->max_iter)
		{
			temp = zr_sq - zi_sq + f->c.re;
			z.im = 2.0 * z.re * z.im + f->c.im;
			z.re = temp;
			
			// Actualizar cuadrados para siguiente iteración
			zr_sq = z.re * z.re;
			zi_sq = z.im * z.im;
			f->iter++;
		}
	}
	
	// Guardar resultado para coloreado
	f->z = z;
	put_pixel_color(f);
}
