/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:55:34 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/30 11:34:11 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void render_fractal(t_fractol *f)
{
    f->y = 0;
    while (f->y < FRACT_SIZE)
    {
        f->x = 0;
        while (f->x < FRACT_SIZE)
        {
            if (f->type == MANDELBROT)
                calculate_mandelbrot(f);
            else if (f->type == JULIA)
                calculate_julia(f);
            f->x++;
        }
        f->y++;
    }
}
