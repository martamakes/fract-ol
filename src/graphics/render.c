/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:55:34 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 21:08:23 by mvigara-         ###   ########.fr       */
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
            calculate_mandelbrot(f);
            f->x++;
        }
        f->y++;
    }
}
