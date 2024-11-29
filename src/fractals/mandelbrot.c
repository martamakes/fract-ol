/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:57:09 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 02:14:24 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void ft_mandelbrot_set(t_fractol *fractol)
{
    double  x_scaled;
    double  y_scaled;
    double  temp;

    // Escalamos el punto actual usando la estructura definida
    x_scaled = (fractol->x - FRACT_SIZE / 2.0) * fractol->zoom / FRACT_SIZE + fractol->shift_x;
    y_scaled = (fractol->y - FRACT_SIZE / 2.0) * fractol->zoom / FRACT_SIZE + fractol->shift_y;
    
    // Inicializamos z (el punto actual)
    fractol->z.re = 0;
    fractol->z.im = 0;
    fractol->iter = 0;

    // La fórmula de Mandelbrot
    while ((fractol->z.re * fractol->z.re + fractol->z.im * fractol->z.im) < 4 
           && fractol->iter < fractol->max_iter)
    {
        temp = fractol->z.re * fractol->z.re - fractol->z.im * fractol->z.im + x_scaled;
        fractol->z.im = 2 * fractol->z.re * fractol->z.im + y_scaled;
        fractol->z.re = temp;
        fractol->iter++;
    }
}
