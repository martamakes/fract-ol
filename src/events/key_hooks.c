/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:56 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/30 11:22:54 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void handle_scroll(double xdelta, double ydelta, void *param)
{
    t_fractol *fractol;
    int32_t mouse_x;
    int32_t mouse_y;
    double mouse_re;
    double mouse_im;
    
    fractol = (t_fractol *)param;
    (void)xdelta;
    mlx_get_mouse_pos(fractol->mlx, &mouse_x, &mouse_y);
    mouse_x -= (WIN_WIDTH - FRACT_SIZE) / 2;
    mouse_re = (mouse_x - FRACT_SIZE/2.0) * fractol->zoom / FRACT_SIZE + fractol->shift_x;
    mouse_im = (mouse_y - FRACT_SIZE/2.0) * fractol->zoom / FRACT_SIZE + fractol->shift_y;
    if (ydelta > 0)
        fractol->zoom *= 0.9;
    else if (ydelta < 0)
        fractol->zoom *= 1.1;
    fractol->shift_x = mouse_re - (mouse_x - FRACT_SIZE/2.0) * fractol->zoom / FRACT_SIZE;
    fractol->shift_y = mouse_im - (mouse_y - FRACT_SIZE/2.0) * fractol->zoom / FRACT_SIZE;
}

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
