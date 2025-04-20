/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:56 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 10:11:24 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Main keyboard event handler */
void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(f->mlx);
		return ;
	}
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
	{
		print_help();
		return ;
	}
	if (keydata.action != MLX_PRESS)
		return ;
	process_key_action(f, keydata.key);
	handle_julia_keys(f, keydata.key);
}

/* Set Julia parameters to dragon set */
void	action_julia_dragon(t_fractol *f)
{
	if (f->type == JULIA)
		set_julia_param(f, 'g');
}

/* Main rendering loop */
void	main_loop(void *param)
{
	t_fractol	*f;
	static int	frame_count = 0;
	static bool	params_changed = true;

	f = (t_fractol *)param;
	if (!f || !f->img)
		return ;
	if (handle_arrow_keys(f->mlx, f))
		params_changed = true;
	if (params_changed || frame_count % 30 == 0)
	{
		print_fractal_params(f);
		params_changed = false;
	}
	render_fractal(f);
	frame_count++;
}
