/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:55:34 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 17:31:49 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_pixel(t_fractol *f)
{
	if (f->type == MANDELBROT)
		calculate_mandelbrot(f);
	else if (f->type == JULIA)
		calculate_julia(f);
	else if (f->type == BURNINGSHIP)
		calculate_burning_ship(f);
}

static void	render_step(t_fractol *f, int step)
{
	int			y;
	int			x;
	uint32_t	color;
	int			dx;
	int			dy;
	int			detail_level;

	// Ajustar nivel de detalle basado en el zoom
	if (f->zoom < 1e-8)
		detail_level = 3; // Detalle máximo para zoom profundo
	else if (f->zoom < 1e-5)
		detail_level = 2; // Detalle alto
	else
		detail_level = 1; // Normal

	y = 0;
	while (y < FRACT_SIZE)
	{
		x = 0;
		while (x < FRACT_SIZE)
		{
			f->x = x;
			f->y = y;

			// Para paso grande, siempre calcular
			if (step >= 4 || detail_level == 3)
				render_pixel(f);
			// Para pasos intermedios, ser selectivo basado en zoom
			else if (step == 2 && (detail_level >= 2 || 
					(x % 4 == 0 && y % 4 == 0))) // Muestreo para equilibrar rendimiento
				render_pixel(f);
			// Para paso pequeño, priorizar bordes y zonas complejas
			else if (step == 1)
			{
				// Siempre calcular bordes de ventana
				if (x < 2 || y < 2 || x >= FRACT_SIZE - 2 || y >= FRACT_SIZE - 2)
					render_pixel(f);
				// Examinar píxeles vecinos para detectar bordes del fractal
				else if (x > 0 && y > 0)
				{
					uint32_t col_left = *(uint32_t *)(f->img->pixels + 
						((y) * f->img->width + (x-1)) * sizeof(int32_t));
					uint32_t col_up = *(uint32_t *)(f->img->pixels + 
						((y-1) * f->img->width + (x)) * sizeof(int32_t));
					
					// Si hay diferencia de color, estamos en un borde
					if (col_left != col_up)
						render_pixel(f);
					else
					{
						// Calcular algunos puntos de forma aleatoria para detalles finos
						if ((x + y) % 3 == 0)
							render_pixel(f);
						else
							// Usar color del vecino para puntos no calculados
							mlx_put_pixel(f->img, x, y, col_left);
					}
				}
				else
					render_pixel(f);
			}

			// Rellenar píxeles adyacentes para pasos mayores que 1
			if (step > 1)
			{
				color = *(uint32_t *)(f->img->pixels + (y * f->img->width + x)
						* sizeof(int32_t));
				dy = 0;
				while (dy < step && (y + dy) < FRACT_SIZE)
				{
					dx = 0;
					while (dx < step && (x + dx) < FRACT_SIZE)
					{
						if (!(dx == 0 && dy == 0))
							mlx_put_pixel(f->img, x + dx, y + dy, color);
						dx++;
					}
					dy++;
				}
			}
			x += step;
		}
		y += step;
	}
}

/* 
 * Calcula los puntos del fractal y los dibuja en la imagen
 */
void	render_fractal(t_fractol *f)
{
	// Limpiar la imagen
	ft_memset(f->img->pixels, 0, f->img->width * f->img->height
		* sizeof(int32_t));
	
	// Ajustar la estrategia de renderizado según el nivel de zoom
	if (f->zoom < 1e-10)
	{
		// Para zoom extremo, usar máximo detalle
		render_step(f, 4);
		render_step(f, 2);
		render_step(f, 1);
	}
	else if (f->zoom < 1e-6)
	{
		// Para zoom profundo, usar alta precisión
		render_step(f, 8);
		render_step(f, 4);
		render_step(f, 2);
		render_step(f, 1);
	}
	else
	{
		// Para zoom normal, usar enfoque progresivo estándar
		render_step(f, 16); // Paso inicial más grande para mejor rendimiento
		render_step(f, 8);
		render_step(f, 4);
		render_step(f, 2);
		render_step(f, 1);
	}
}
