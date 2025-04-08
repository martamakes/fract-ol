/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:18:03 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 13:56:10 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calculate_burning_ship(t_fractol *f)
{
    t_complex   c;
    double      zx;
    double      zy;
    double      xtemp;
    
    /* Mapear coordenadas de píxel a coordenadas complejas */
    c.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
    c.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
    
    /* Valores iniciales para la iteración */
    zx = 0.0;
    zy = 0.0;
    f->iter = 0;
    
    /* Algoritmo principal del Burning Ship (Implementación óptima) */
    while (zx * zx + zy * zy < 4.0 && f->iter < f->max_iter)
    {
        /* Tomamos el valor absoluto antes del cálculo del cuadrado */
        zx = fabs(zx);
        zy = fabs(zy);
        
        /* Algoritmo de Mandelbrot con los valores absolutos */
        xtemp = zx * zx - zy * zy + c.re;
        zy = 2.0 * zx * zy + c.im;
        zx = xtemp;
        
        f->iter++;
    }
    
    /* Guardamos los valores para el cálculo de color */
    f->z.re = zx;
    f->z.im = zy;
    put_pixel_color(f);
}
