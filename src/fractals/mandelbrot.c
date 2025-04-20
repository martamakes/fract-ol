/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:57:09 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 13:55:31 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_mandelbrot(t_fractol *f)
{
	t_complex	z;
	t_complex	c;
	double		temp;
	
	/* Calcular coordenada compleja desde píxel */
	c.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
	c.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
	
	/* Inicializar valores */
	z.re = 0;
	z.im = 0;
	f->iter = 0;
	
	/* Algoritmo principal de Mandelbrot */
	while ((z.re * z.re + z.im * z.im) < 4.0 && f->iter < f->max_iter)
	{
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = temp;
		f->iter++;
	}
	
	/* Guardar valor final para cálculo de color */
	f->z = z;
	put_pixel_color(f);
}