/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:55:34 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 16:56:40 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Calculate and draw the fractal on the image */
void	render_fractal(t_fractol *f)
{
	ft_memset(f->img->pixels, 0, f->img->width * f->img->height
		* sizeof(int32_t));
	f->y = -1;
	while (++f->y < FRACT_SIZE)
	{
		f->x = -1;
		while (++f->x < FRACT_SIZE)
		{
			if (f->type == MANDELBROT)
				calculate_mandelbrot(f);
			else if (f->type == JULIA)
				calculate_julia(f);
			else if (f->type == BURNINGSHIP)
				calculate_burning_ship(f);
		}
	}
}
