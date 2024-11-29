/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 19:11:26 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_palette *init_palettes(void) 
{
   static t_palette array[3];

   array[0] = (t_palette){5, 0, {
       0x000066,  // Azul oscuro
       0x0033CC,  // Azul medio
       0x3366FF,  // Azul claro  
       0x33CCFF,  // Azul celeste
       0x66FFFF   // Azul muy claro
   }};
   return (array);
}

static uint32_t get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
   return (r << 24 | g << 16 | b << 8 | a);
}

void put_pixel_color(t_fractol *f)
{
   t_color     color;
   uint32_t    rgba;

   if (f->iter >= f->max_iter)
       mlx_put_pixel(f->img, f->x, f->y, 0x000000FF);
   else
   {
       color.value = f->palette->colors[f->iter % f->palette->count];
       rgba = get_color(color.rgba.r, color.rgba.g, color.rgba.b, 255);
       mlx_put_pixel(f->img, f->x, f->y, rgba);
   }
}
