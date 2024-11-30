/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:34:37 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/30 11:36:11 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calculate_julia(t_fractol *f)
{
    t_complex z;
    double temp;
    
    z.re = (f->x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
    z.im = (f->y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
    f->iter = 0;
    while ((z.re * z.re + z.im * z.im) < 4 && f->iter < f->max_iter)
    {
        temp = z.re * z.re - z.im * z.im + f->c.re;
        z.im = 2.0 * z.re * z.im + f->c.im;
        z.re = temp;
        f->iter++;
    }
    put_pixel_color(f);
}
