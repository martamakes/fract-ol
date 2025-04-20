/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:59:15 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 11:35:57 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Reset view to default position for current fractal type */
void	reset_view(t_fractol *f)
{
	f->zoom = 4.0;
	f->max_iter = 100;
	f->color_shift = 0;
	if (f->type == MANDELBROT)
	{
		f->shift_x = -0.5;
		f->shift_y = 0.0;
	}
	else if (f->type == JULIA)
	{
		f->shift_x = 0.0;
		f->shift_y = 0.0;
		f->zoom = 2.0;
		if (f->c.re == 0.0 && f->c.im == 0.0)
			set_julia_param(f, 'd');
	}
	else if (f->type == BURNINGSHIP)
	{
		f->shift_x = -0.25;
		f->shift_y = -0.65;
		f->max_iter = 200;
		f->zoom = 4.7;
	}
}

/* Switch to next color palette */
void	action_next_palette(t_fractol *f)
{
	f->palette_index = (f->palette_index + 1) % f->palette_len;
	f->palette = &f->palettes[f->palette_index];
}

/* Increase color shift value */
void	action_color_shift_up(t_fractol *f)
{
	f->color_shift += 5.0;
}

/* Decrease color shift value */
void	action_color_shift_down(t_fractol *f)
{
	f->color_shift -= 5.0;
}

/* Toggle smooth coloring mode */
void	action_toggle_smooth(t_fractol *f)
{
	f->smooth = !f->smooth;
}
