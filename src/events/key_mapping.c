/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:30:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 15:30:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Fill actions array part 1 */
static void	init_actions_part1(t_key_action *actions)
{
	actions[0] = (t_key_action){MLX_KEY_C, action_next_palette};
	actions[1] = (t_key_action){MLX_KEY_RIGHT_BRACKET, action_color_shift_up};
	actions[2] = (t_key_action){MLX_KEY_LEFT_BRACKET, action_color_shift_down};
	actions[3] = (t_key_action){MLX_KEY_R, reset_view};
	actions[4] = (t_key_action){MLX_KEY_S, action_toggle_smooth};
	actions[5] = (t_key_action){MLX_KEY_EQUAL, action_iter_up};
}

/* Fill actions array part 2 */
static void	init_actions_part2(t_key_action *actions)
{
	actions[6] = (t_key_action){MLX_KEY_MINUS, action_iter_down};
	actions[7] = (t_key_action){MLX_KEY_1, action_fractal_mandelbrot};
	actions[8] = (t_key_action){MLX_KEY_2, action_fractal_julia};
	actions[9] = (t_key_action){MLX_KEY_3, action_fractal_burningship};
	actions[10] = (t_key_action){MLX_KEY_D, action_julia_dendrite};
	actions[11] = (t_key_action){MLX_KEY_T, action_julia_rabbit};
	actions[12] = (t_key_action){0, NULL};
}

/* Initialize key action map */
static void	init_actions(t_key_action *actions)
{
	init_actions_part1(actions);
	init_actions_part2(actions);
}

/* Process specific key press based on key action mapping */
void	process_key_action(t_fractol *f, int key)
{
	static t_key_action	actions[13];
	int					i;

	if (actions[0].action == NULL)
		init_actions(actions);
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
