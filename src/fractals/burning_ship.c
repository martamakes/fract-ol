/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:18:03 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 17:30:52 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_burning_ship(t_fractol *f)
{
	t_complex	c;
	t_complex	z;
	double		zr_abs;
	double		zi_abs;
	double		zr_abs_sq;
	double		zi_abs_sq;
	double		z_mag_sq;
	double		temp;

	// Calcular coordenadas complejas con alta precisión
	c.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
	c.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
	
	// Inicialización
	z.re = 0.0;
	z.im = 0.0;
	f->iter = 0;
	z_mag_sq = 0.0;
	
	// Optimización para zoom profundo
	if (f->zoom < 1e-8)
	{
		// Procesamiento por lotes para mejor rendimiento
		int batch_size = 6; // Menor que otros fractales porque Burning Ship es más complejo
		
		while (f->iter < f->max_iter)
		{
			// Procesar múltiples iteraciones antes de verificar escape
			for (int i = 0; i < batch_size && f->iter < f->max_iter; i++)
			{
				// Optimización: Calcular valor absoluto y su cuadrado
				zr_abs = fabs(z.re);
				zi_abs = fabs(z.im);
				zr_abs_sq = zr_abs * zr_abs;
				zi_abs_sq = zi_abs * zi_abs;
				
				// Fórmula del Burning Ship
				temp = zr_abs_sq - zi_abs_sq + c.re;
				z.im = 2.0 * zr_abs * zi_abs + c.im;
				z.re = temp;
				
				// Actualizar magnitud al cuadrado para próxima iteración
				z_mag_sq = z.re * z.re + z.im * z.im;
				f->iter++;
				
				// Verificación de escape sólo en la última iteración del lote
				if (i == batch_size - 1 && z_mag_sq > 4.0)
					break;
			}
			
			// Verificación principal de escape
			if (z_mag_sq > 4.0)
				break;
			
			// Ajustar tamaño de lote según progreso
			if (f->iter > f->max_iter * 0.7)
				batch_size = 10; // Incrementar para puntos de escape lento
		}
	}
	else
	{
		// Algoritmo estándar con optimizaciones menores
		while (z_mag_sq < 4.0 && f->iter < f->max_iter)
		{
			// Calcular valores absolutos una sola vez
			zr_abs = fabs(z.re);
			zi_abs = fabs(z.im);
			
			// Fórmula optimizada
			temp = zr_abs * zr_abs - zi_abs * zi_abs + c.re;
			z.im = 2.0 * zr_abs * zi_abs + c.im;
			z.re = temp;
			
			// Actualizar magnitud al cuadrado
			z_mag_sq = z.re * z.re + z.im * z.im;
			f->iter++;
		}
	}
	
	// Guardar resultado para coloración
	f->z = z;
	put_pixel_color(f);
}
