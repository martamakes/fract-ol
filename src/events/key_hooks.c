/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:56 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 10:31:04 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void handle_arrow_keys(mlx_t *mlx, t_fractol *fractol)
{
    double move_factor;
    
    move_factor = 0.1 * fractol->zoom;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        fractol->shift_x -= move_factor;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        fractol->shift_x += move_factor;
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        fractol->shift_y -= move_factor;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        fractol->shift_y += move_factor;
}

void handle_keys(mlx_key_data_t keydata, void *param)
{
    t_fractol *fractol;

    fractol = (t_fractol *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(fractol->mlx);
    if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
    {
        fractol->palette_index = (fractol->palette_index + 1) % fractol->palette_len;
        fractol->palette = &fractol->palettes[fractol->palette_index];
    }
}

void main_loop(void *param)
{
    t_fractol *fractol;
    
    fractol = (t_fractol *)param;
    if (!fractol || !fractol->img)
        return;    
    handle_arrow_keys(fractol->mlx, fractol);
    render_fractal(fractol);
}
