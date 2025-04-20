/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:10:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 16:10:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Calculate complex coordinates from mouse position */
void	calculate_complex_coords(t_fractol *f, int mx, int my,
		t_complex *mouse_pos)
{
	mouse_pos->re = (mx - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_x;
	mouse_pos->im = (my - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE + f->shift_y;
}

/* Update fractal shift values based on new zoom and mouse position */
void	update_fractal_shift(t_fractol *f, int mx, int my,
		t_complex mouse_pos)
{
	f->shift_x = mouse_pos.re - (mx - FRACT_SIZE / 2.0) 
		* f->zoom / FRACT_SIZE;
	f->shift_y = mouse_pos.im - (my - FRACT_SIZE / 2.0) 
		* f->zoom / FRACT_SIZE;
}

/* Check if mouse is in fractal image area */
int	is_mouse_in_image(int x, int y)
{
	if (x < 0 || x >= FRACT_SIZE || y < 0 || y >= FRACT_SIZE)
		return (0);
	return (1);
}
