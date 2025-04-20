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

/**
 * Handle arrow key movement
 * 
 * @param mlx MLX instance
 * @param fractol Fractal structure
 * @return true if any movement occurred
 */
bool	handle_arrow_keys(mlx_t *mlx, t_fractol *fractol)
{
	double	move_factor;
	bool	changed;

	changed = false;
	move_factor = 0.05 * fractol->zoom;
	
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		fractol->shift_x += move_factor; /* Invertido: izquierda mueve a la derecha */
		changed = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		fractol->shift_x -= move_factor; /* Invertido: derecha mueve a la izquierda */
		changed = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		fractol->shift_y += move_factor; /* Invertido: arriba mueve hacia abajo */
		changed = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		fractol->shift_y -= move_factor; /* Invertido: abajo mueve hacia arriba */
		changed = true;
	}
	return (changed);
}

/**
 * Process specific key press based on key action mapping
 * 
 * @param f Fractal structure
 * @param key Key that was pressed
 */
/**
 * Process specific key press based on key action mapping
 * 
 * @param f Fractal structure
 * @param key Key that was pressed
 */
void	process_key_action(t_fractol *f, int key)
{
	static t_key_action	actions[13];
	int					i;

	if (actions[0].action == NULL)
	{
		actions[0] = (t_key_action){MLX_KEY_C, action_next_palette};
		actions[1] = (t_key_action){MLX_KEY_RIGHT_BRACKET, action_color_shift_up};
		actions[2] = (t_key_action){MLX_KEY_LEFT_BRACKET, action_color_shift_down};
		actions[3] = (t_key_action){MLX_KEY_R, reset_view};
		actions[4] = (t_key_action){MLX_KEY_S, action_toggle_smooth};
		actions[5] = (t_key_action){MLX_KEY_EQUAL, action_iter_up};
		actions[6] = (t_key_action){MLX_KEY_MINUS, action_iter_down};
		actions[7] = (t_key_action){MLX_KEY_1, action_fractal_mandelbrot};
		actions[8] = (t_key_action){MLX_KEY_2, action_fractal_julia};
		actions[9] = (t_key_action){MLX_KEY_3, action_fractal_burningship};
		actions[10] = (t_key_action){MLX_KEY_D, action_julia_dendrite};
		actions[11] = (t_key_action){MLX_KEY_T, action_julia_rabbit};
		actions[12] = (t_key_action){0, NULL};
	}
	i = 0;
	while (actions[i].action != NULL)
	{
		if (actions[i].key == key)
		{
			actions[i].action(f);
			break ;
		}
		i++;
	}
}

/**
 * Main keyboard event handler
 * 
 * @param keydata Key event data from MLX
 * @param param Pointer to fractal structure
 */
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
	
	if (f->type == JULIA)
	{
		if (keydata.key == MLX_KEY_D)
			set_julia_param(f, 'd');
		else if (keydata.key == MLX_KEY_R)
			set_julia_param(f, 'r');
		else if (keydata.key == MLX_KEY_G)
			set_julia_param(f, 'g');
	}
}

/**
 * Set Julia parameters to dragon set
 * 
 * @param f Fractal structure
 */
void	action_julia_dragon(t_fractol *f)
{
	if (f->type == JULIA)
		set_julia_param(f, 'g');
}

/**
 * Main rendering loop
 * 
 * @param param Pointer to fractal structure
 */
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
