/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:40:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 15:40:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Update iteration count based on zoom level */
void	update_iterations(t_fractol *f)
{
	double	log_zoom;
	int		base_iter;

	if (f->type == BURNINGSHIP)
		base_iter = 50;
	else
		base_iter = 80;
	log_zoom = log10(4.0 / f->zoom);
	if (log_zoom < 0)
		log_zoom = 0;
	f->max_iter = (int)(base_iter + 50.0 * log_zoom * log_zoom);
	if (f->max_iter < base_iter)
		f->max_iter = base_iter;
	if (f->max_iter > 1000)
		f->max_iter = 1000;
	printf("Zoom: %.6f, New iterations: %d\n", f->zoom, f->max_iter);
}

/* Update zoom level based on scroll direction */
void	update_zoom(t_fractol *f, double ydelta)
{
	double	zoom_factor;

	if (ydelta > 0)
		zoom_factor = 0.90;
	else
		zoom_factor = 1.10;
	if (ydelta < 0 && f->zoom < 1e-10)
		return ;
	f->zoom *= zoom_factor;
	update_iterations(f);
}

/* Adjust mouse coordinates to fractal image dimensions */
void	adjust_mouse_coords(int *mx, int *my)
{
	int	offset_x;
	int	offset_y;

	offset_x = (WIN_WIDTH - FRACT_SIZE) / 2;
	offset_y = (WIN_HEIGHT - FRACT_SIZE) / 2;
	*mx -= offset_x;
	*my -= offset_y;
}

/* Print debug information for mouse position and zoom */
void	print_debug_info(t_fractol *f, double old_zoom)
{
	printf("Original mouse coords: %d,%d (in %dx%d image)\n",
		f->x, f->y, FRACT_SIZE, FRACT_SIZE);
	printf("Old zoom: %f, New zoom: %f\n", old_zoom, f->zoom);
	printf("Shift: %f,%f\n", f->shift_x, f->shift_y);
	print_fractal_params(f);
}
