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
    t_complex   z;
    t_complex   c;
    double      temp;
    
    c.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
    c.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
    z.re = 0;
    z.im = 0;
    f->iter = 0;
    while ((z.re * z.re + z.im * z.im) < 4.0 && f->iter < f->max_iter)
    {
        z.re = fabs(z.re);
        z.im = fabs(z.im);
        temp = z.re * z.re - z.im * z.im + c.re;
        z.im = 2.0 * z.re * z.im + c.im;
        z.re = temp;
        f->iter++;
    }
    f->z = z;
    put_pixel_color(f);
}
