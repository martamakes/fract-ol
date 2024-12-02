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


t_color calculate_color(t_fractol *f)
{
   t_color color1;
   t_color color2;
   double  smooth_iter;
   double  normalized_iter;
   double  t;
   int     index;

   smooth_iter = smooth_color(f->iter, f->max_iter, f->z.re, f->z.im);
   normalized_iter = fmod(smooth_iter / 8.0, 1.0);
   t = normalized_iter * (f->palette->count - 1);
   index = (int)t;
   t -= index;
   t = t * t * (3 - 2 * t);
   color1.value = f->palette->colors[index];
   color2.value = f->palette->colors[(index + 1) % f->palette->count];
   return (interpolate_colors(color1, color2, t));
}

static void calculate_fractal_texture(t_fractol *f, mlx_texture_t *texture)
{
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
           put_pixel_to_texture(f, texture);
       }
   }
}

void    render_fractal(t_fractol *f)
{
   mlx_texture_t *texture;
   int32_t width;
   int32_t height;

   width = FRACT_SIZE;
   height = FRACT_SIZE;
   texture = mlx_texture_new(width, height);
   if (!texture)
       exit_error(f, "Failed to create texture");
   
   calculate_fractal_texture(f, texture);
   
   if (mlx_texture_to_image(f->mlx, texture) < 0)
   {
       mlx_delete_texture(texture);
       exit_error(f, "Failed to convert texture to image");
   }
   
   mlx_delete_texture(texture);
}
