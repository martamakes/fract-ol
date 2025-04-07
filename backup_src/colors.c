/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 16:46:15 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Funciones de paleta de colores */
int palette_len(t_palette *palettes)
{
    int i;
    
    i = 0;
    while (i < 6 && palettes[i].count > 0)
        i++;
    return (i);
}

t_palette *init_palettes(void) 
{
    static t_palette array[3];
    
    /* Reducimos a 3 paletas para simplificar */
    array[0] = (t_palette){9, 1, {0x000033FF, 0x000066FF, 0x000099FF, 
        0x0000CCFF, 0x0000FFFF, 0xFF6600FF, 0xFF9933FF, 0xFFCC00FF, 0xFFFF33FF}};
    array[1] = (t_palette){7, 1, {0x000033FF, 0x4B0082FF, 0x800080FF, 
        0xDA70D6FF, 0xFFD700FF, 0x00CED1FF, 0xFFFFFFFF}};
    array[2] = (t_palette){7, 1, {0x191970FF, 0x6A5ACDFF, 0x9370DBFF, 
        0xEE82EEFF, 0xFFA07AFF, 0xFFD700FF, 0xFFFFFFFF}};
    return (array);
}

/* Funciones de color */
static uint32_t get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
   return (r << 24 | g << 16 | b << 8 | a);
}

static double smooth_color(double iter, double max_iter, double zx, double zy)
{
   double log_zn;
   double nu;

   if (iter < max_iter)
   {
       log_zn = log(zx * zx + zy * zy) / 2.0;
       nu = log(log_zn / log(2.0)) / log(2.0);
       iter = iter + 1.0 - nu;
   }
   return (iter);
}

static t_color interpolate_colors(t_color c1, t_color c2, double t)
{
   t_color result;
   double t_smooth;

   t_smooth = t * t * (3 - 2 * t);
   result.rgba.r = (uint8_t)((1.0 - t_smooth) * c1.rgba.r + t_smooth * c2.rgba.r);
   result.rgba.g = (uint8_t)((1.0 - t_smooth) * c1.rgba.g + t_smooth * c2.rgba.g);
   result.rgba.b = (uint8_t)((1.0 - t_smooth) * c1.rgba.b + t_smooth * c2.rgba.b);
   result.rgba.a = 255;
   return (result);
}

/* Asigna color basado en el número de iteraciones */
void put_pixel_color(t_fractol *f)
{
   t_color color1;
   t_color color2;
   double normalized_iter;
   int index;

   if (f->iter >= f->max_iter)
       mlx_put_pixel(f->img, f->x, f->y, 0x000000FF);
   else
   {
       /* Versión simplificada de coloreado */
       normalized_iter = (double)f->iter / f->max_iter;
       normalized_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im) / f->max_iter;
       index = (int)(normalized_iter * (f->palette->count - 1));
       color1.value = f->palette->colors[index];
       color2.value = f->palette->colors[(index + 1) % f->palette->count];
       normalized_iter = normalized_iter * (f->palette->count - 1) - index;
       color1 = interpolate_colors(color1, color2, normalized_iter);
       mlx_put_pixel(f->img, f->x, f->y, get_color(
           color1.rgba.r, color1.rgba.g, color1.rgba.b, 0xFF));
   }
}