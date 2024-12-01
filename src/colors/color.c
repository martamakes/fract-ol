/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/30 13:17:11 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static uint32_t get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
   return (r << 24 | g << 16 | b << 8 | a);
}

static double smooth_color(double iter, double max_iter, double zx, double zy)
{
    if (iter < max_iter)
    {
        // Logaritmo del módulo al cuadrado
        double log_zn = log(zx * zx + zy * zy) / 2.0;
        double nu = log(log_zn / log(2.0)) / log(2.0);
        // Suavizado de la iteración
        iter = iter + 1.0 - nu;
    }
    return iter;
}

static t_color interpolate_colors(t_color c1, t_color c2, double t)
{
    t_color result;
    // Interpolación con corrección gamma
    double gamma = 2.2;
    double t_corrected = pow(t, 1.0 / gamma);

    result.rgba.r = (uint8_t)(pow((1.0 - t_corrected) * pow(c1.rgba.r / 255.0, gamma) + 
                    t_corrected * pow(c2.rgba.r / 255.0, gamma), gamma) * 255.0);
    result.rgba.g = (uint8_t)(pow((1.0 - t_corrected) * pow(c1.rgba.g / 255.0, gamma) + 
                    t_corrected * pow(c2.rgba.g / 255.0, gamma), gamma) * 255.0);
    result.rgba.b = (uint8_t)(pow((1.0 - t_corrected) * pow(c1.rgba.b / 255.0, gamma) + 
                    t_corrected * pow(c2.rgba.b / 255.0, gamma), gamma) * 255.0);
    result.rgba.a = 255;
    
    return result;
}

void put_pixel_color(t_fractol *f)
{
    t_color     color1;
    t_color     color2;
    t_color     final_color;
    double      smooth_iter;
    uint32_t    rgba;

    if (f->iter >= f->max_iter)
        mlx_put_pixel(f->img, f->x, f->y, 0x000000FF);
    else
    {
        // Aplicar suavizado
        smooth_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im);
        
        // Calcular índices de color
        int index1 = ((int)smooth_iter) % f->palette->count;
        int index2 = (index1 + 1) % f->palette->count;
        
        // Obtener fracción para interpolación
        double fract = smooth_iter - floor(smooth_iter);
        
        color1.value = f->palette->colors[index1];
        color2.value = f->palette->colors[index2];
        
        final_color = interpolate_colors(color1, color2, fract);
        rgba = get_color(final_color.rgba.r, final_color.rgba.g, 
                        final_color.rgba.b, final_color.rgba.a);
        
        mlx_put_pixel(f->img, f->x, f->y, rgba);
    }
}
