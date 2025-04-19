/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 17:44:16 by mvigara-         ###   ########.fr       */
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
 * con mejora específica para cada tipo de fractal y nivel de zoom
 */
static double	smooth_color(double iter, double max_iter, double zx, double zy, t_fractal_type type, double zoom)
{
	double	log_zn;
	double	nu;
	double	smoothed;

	// Verificar si es punto de escape (no está dentro del conjunto)
	if (iter < max_iter)
	{
		// Ajustes específicos por tipo de fractal
		if (type == BURNINGSHIP)
		{
			// Fórmula mejorada para Burning Ship
			log_zn = log(zx * zx + zy * zy);
			nu = log(log_zn / log(2.0)) / log(2.0);
			
			// Ajustar suavizado basado en nivel de zoom
			if (zoom < 1e-8)
				smoothed = iter + 1.0 - 0.4 * nu; // Más suave en zoom profundo
			else
				smoothed = iter + 1.0 - 0.6 * nu;
			
			// En bordes muy detallados, aplicar discretización parcial para realzar patrones
			if (nu > 0.5 && iter > max_iter * 0.8)
				smoothed = floor(smoothed) + 0.5;
		}
		else if (type == JULIA)
		{
			// Fórmula mejorada para Julia con más detalles
			log_zn = log(zx * zx + zy * zy) / 2.0;
			nu = log(log_zn / log(2.0)) / log(2.0);
			
			// Factor de corrección basado en zoom para mantener detalles finos
			double correction = (zoom < 1e-6) ? 0.85 : 1.0;
			smoothed = iter + 1.0 - nu * correction;
			
			// Ajuste para mantener detalles en bordes sin perder la autosimilitud
			if (iter > max_iter * 0.9)
			{
				// Limitar valor para evitar saltos bruscos de color
				smoothed = max_iter * (0.85 + (iter/max_iter - 0.9) * 1.0);
			}
		}
		else // MANDELBROT
		{
			log_zn = log(zx * zx + zy * zy) / 2.0;
			nu = log(log_zn / log(2.0)) / log(2.0);
			
			// Suavizado adaptativo basado en nivel de zoom
			if (zoom < 1e-10) // Zoom extremadamente profundo
			{
				// Aplicar función de suavizado especial para preservar la autosimilitud
				double phase = fmod(iter / 10.0, 1.0);
				smoothed = iter + 1.0 - nu * (0.8 + sin(phase * M_PI * 2) * 0.1);
			}
			else if (zoom < 1e-6) // Zoom muy profundo
			{
				// Suavizado adaptado para capturar detalles sutiles
				smoothed = iter + 1.0 - nu * 0.9;
			}
			else // Zoom normal
			{
				smoothed = iter + 1.0 - nu;
			}
			
			// Ajustes para mantener patrones reconocibles en estructuras mini-brot
			if (iter > max_iter * 0.97 && iter < max_iter)
			{
				// Enfatizar sutilmente los bordes del conjunto sin romper la autosimilitud
				double edge_factor = (max_iter - iter) / (max_iter * 0.03);
				smoothed = max_iter * 0.97 + edge_factor * 0.02 * max_iter;
			}
		}
		
		return smoothed;
	}
	
	return max_iter; // Puntos dentro del conjunto
}

/*
 * Interpola entre dos colores según un factor t entre 0 y 1
 * Usando una interpolación mejorada para transiciones más suaves
 */
static t_color	interpolate_colors(t_color c1, t_color c2, double t)
{
	t_color	result;
	double	t_smooth;

	// Función de suavizado mejorada (Smoothstep cúbico)
	t_smooth = t * t * (3.0 - 2.0 * t);
	
	// Aplicar una curva de distribución perceptual para colores más naturales
	double perceptual_factor = pow(t_smooth, 0.8);
	
	// Mezclar componentes de color con peso perceptual
	result.rgba.r = (uint8_t)((1.0 - perceptual_factor) * c1.rgba.r + perceptual_factor * c2.rgba.r);
	result.rgba.g = (uint8_t)((1.0 - perceptual_factor) * c1.rgba.g + perceptual_factor * c2.rgba.g);
	result.rgba.b = (uint8_t)((1.0 - perceptual_factor) * c1.rgba.b + perceptual_factor * c2.rgba.b);
	result.rgba.a = 255;
	
	return (result);
}

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
		/* Aplicar colores especializados para el interior del conjunto */
		if (f->type == MANDELBROT)
			mlx_put_pixel(f->img, f->x, f->y, 0x000000FF); /* Negro clásico para Mandelbrot */
		else if (f->type == JULIA)
			mlx_put_pixel(f->img, f->x, f->y, 0x101010FF); /* Negro con sutil diferencia para Julia */
		else if (f->type == BURNINGSHIP)
			mlx_put_pixel(f->img, f->x, f->y, 0x080808FF); /* Negro con tono propio para Burning Ship */
		return;
	}
	
	/* Manejo especial para puntos muy cercanos al conjunto */
	if (f->iter > f->max_iter * 0.99)
	{
		/* Colores especiales para bordes muy cercanos con sutil variación por profundidad */
		uint32_t border_color;
		double edge_factor = (f->max_iter - f->iter) / (f->max_iter * 0.01); // 0.0 a 1.0
		
		if (f->type == JULIA)
		{
			/* Blanco para Julia con sutiles variaciones de tono */
			uint8_t intensity = 255 - (uint8_t)(edge_factor * 20);
			border_color = get_color(intensity, intensity, intensity, 0xFF);
		}
		else if (f->type == MANDELBROT)
		{
			/* Degradado de rojo a negro para Mandelbrot */
			uint8_t red_val = 255 - (uint8_t)(edge_factor * 100);
			border_color = get_color(red_val, 0, 0, 0xFF);
		}
		else // BURNINGSHIP
		{
			/* Azul para Burning Ship con variaciones de intensidad */
			uint8_t blue_val = 255 - (uint8_t)(edge_factor * 50);
			border_color = get_color(0, blue_val / 2, blue_val, 0xFF);
		}
		
		mlx_put_pixel(f->img, f->x, f->y, border_color);
		return;
	}

	/* Aplicar suavizado adaptativo basado en el nivel de zoom */
	if (f->smooth && f->iter < f->max_iter - 1)
		smoothed_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im, f->type, f->zoom);
	else
		smoothed_iter = f->iter;
	
	/* Shift de color con patrón cíclico mejorado */
	double cyclic_shift = f->color_shift;
	
	/* En niveles profundos de zoom, aplicar patrón de repetición para mantener autosimilitud */
	if (f->zoom < 1e-8)
		cyclic_shift += log(1.0 / f->zoom) * 2.0;
	
	smoothed_iter += cyclic_shift;
	
	/* Factor de escala adaptativo para colores */
	double scale_factor;
	if (f->zoom < 1e-10) // Zoom extremo
		scale_factor = 0.007; // Detalle muy fino
	else if (f->zoom < 1e-6) // Zoom profundo
		scale_factor = 0.01;  // Detalle fino
	else if (f->zoom < 0.01) // Zoom medio
		scale_factor = 0.02;  // Detalle medio
	else if (f->zoom < 1.0) // Zoom cercano
		scale_factor = 0.03;  // Detalle normal
	else // Zoom lejano
		scale_factor = 0.05;  // Vista amplia
	
	/* Aplicar ciclo de color adaptativo */
	int cycle_length = f->palette->cycle;
	if (f->zoom < 1e-8)
		cycle_length = (int)(cycle_length * 1.5); // Ciclos más largos en zoom profundo
	
	normalized_iter = fmod(smoothed_iter * scale_factor * cycle_length, 1.0);

	/* Selección de colores a interpolar */
	index = (int)(normalized_iter * (f->palette->count - 1));
	color1.value = f->palette->colors[index];
	color2.value = f->palette->colors[(index + 1) % f->palette->count];
	
	/* Factor de interpolación con precisión mejorada */
	normalized_iter = normalized_iter * (f->palette->count - 1) - index;
	
	/* Interpolación de colores con transición natural */
	color1 = interpolate_colors(color1, color2, normalized_iter);
	
	/* Ajuste final para preservar detalles en zoom profundo */
	if (f->zoom < 1e-10 && f->type == MANDELBROT)
	{
		// Sutilmente aumentar el contraste en zonas de detalle fino
		double contrast = 1.1;
		color1.rgba.r = (uint8_t)fmin(255, color1.rgba.r * contrast);
		color1.rgba.g = (uint8_t)fmin(255, color1.rgba.g * contrast);
		color1.rgba.b = (uint8_t)fmin(255, color1.rgba.b * contrast);
	}
	
	/* Pintar el píxel con el color calculado */
	mlx_put_pixel(f->img, f->x, f->y, get_color(
		color1.rgba.r, color1.rgba.g, color1.rgba.b, 0xFF));
}
