/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:30:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 14:30:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Process left and right arrow keys */
static bool	handle_horizontal_keys(mlx_t *mlx, t_fractol *fractol,
									double move_factor)
{
	bool	changed;

	changed = false;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		fractol->shift_x += move_factor;
		changed = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		fractol->shift_x -= move_factor;
		changed = true;
	}
	return (changed);
}

/* Process up and down arrow keys */
static bool	handle_vertical_keys(mlx_t *mlx, t_fractol *fractol,
								double move_factor)
{
	bool	changed;

	changed = false;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		fractol->shift_y += move_factor;
		changed = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		fractol->shift_y -= move_factor;
		changed = true;
	}
	return (changed);
}

/* Handle arrow key movement */
bool	handle_arrow_keys(mlx_t *mlx, t_fractol *fractol)
{
	double	move_factor;
	bool	h_changed;
	bool	v_changed;

	move_factor = 0.05 * fractol->zoom;
	h_changed = handle_horizontal_keys(mlx, fractol, move_factor);
	v_changed = handle_vertical_keys(mlx, fractol, move_factor);
	return (h_changed || v_changed);
}

/* Handle Julia set key commands */
void	handle_julia_keys(t_fractol *f, int key)
{
	if (f->type != JULIA)
		return ;
	if (key == MLX_KEY_D)
		set_julia_param(f, 'd');
	else if (key == MLX_KEY_R)
		set_julia_param(f, 'r');
	else if (key == MLX_KEY_G)
		set_julia_param(f, 'g');
}
