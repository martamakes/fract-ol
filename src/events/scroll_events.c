/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:31:17 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 09:33:42 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Process mouse coordinates and zoom */
static void	process_mouse_zoom(t_fractol *f, double ydelta)
{
	int			mouse_x;
	int			mouse_y;
	t_complex	mouse_pos;
	double		old_zoom;

	old_zoom = f->zoom;
	mlx_get_mouse_pos(f->mlx, &mouse_x, &mouse_y);
	adjust_mouse_coords(&mouse_x, &mouse_y);
	if (!is_mouse_in_image(mouse_x, mouse_y))
		return ;
	f->x = mouse_x;
	f->y = mouse_y;
	calculate_complex_coords(f, mouse_x, mouse_y, &mouse_pos);
	update_zoom(f, ydelta);
	update_fractal_shift(f, mouse_x, mouse_y, mouse_pos);
	print_debug_info(f, old_zoom);
}

/* Handle mouse scroll events */
void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	(void)xdelta;
	process_mouse_zoom(f, ydelta);
}
