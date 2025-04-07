/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 16:46:15 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
       iter += 0.25 * sin(iter * 0.05);
   }
   return (iter);
}

static t_color interpolate_colors(t_color c1, t_color c2, double t)
{
   t_color result;
   double t_smooth;
   double gamma;

   t_smooth = t * t * (3 - 2 * t);
   gamma = 2.2;
   result.rgba.r = (uint8_t)(pow((1.0 - t_smooth) * pow(c1.rgba.r / 255.0,
                   gamma) + t_smooth * pow(c2.rgba.r / 255.0, gamma), gamma) * 255.0);
   result.rgba.g = (uint8_t)(pow((1.0 - t_smooth) * pow(c1.rgba.g / 255.0,
                   gamma) + t_smooth * pow(c2.rgba.g / 255.0, gamma), gamma) * 255.0);
   result.rgba.b = (uint8_t)(pow((1.0 - t_smooth) * pow(c1.rgba.b / 255.0,
                   gamma) + t_smooth * pow(c2.rgba.b / 255.0, gamma), gamma) * 255.0);
   result.rgba.a = 255;
   return (result);
}

static uint32_t get_basic_color(t_fractol *f)
{
    int color_index;
    
    color_index = f->iter % f->palette->count;
    return (f->palette->colors[color_index]);
}

void put_pixel_color(t_fractol *f)
{
   t_color final_color;
   t_color color1;
   t_color color2;
   double smooth_iter;
   double normalized_iter;
   double t;
   int index;

   if (f->iter >= f->max_iter)
       mlx_put_pixel(f->img, f->x, f->y, 0x000000FF);
   else if (!f->smooth) // Modo simple (sin suavizado)
   {
       mlx_put_pixel(f->img, f->x, f->y, get_basic_color(f));
   }
   else // Modo suavizado
   {
       smooth_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im);
       normalized_iter = fmod(smooth_iter / 8.0, 1.0);
       t = normalized_iter * (f->palette->count - 1);
       index = (int)t;
       t -= index;
       t = t * t * (3 - 2 * t);
       color1.value = f->palette->colors[index];
       color2.value = f->palette->colors[(index + 1) % f->palette->count];
       final_color = interpolate_colors(color1, color2, t);
       mlx_put_pixel(f->img, f->x, f->y, get_color(
           final_color.rgba.r,
           final_color.rgba.g,
           final_color.rgba.b,
           0xFF));
   }
}
