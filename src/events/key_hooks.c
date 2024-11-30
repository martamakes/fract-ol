/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:56 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/30 07:30:59 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void handle_keys(mlx_key_data_t keydata, void *param)
{
    t_fractol *fractol;

    fractol = (t_fractol *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(fractol->mlx);
}

void handle_scroll(double xdelta, double ydelta, void *param)
{
    t_fractol *fractol;
    
    fractol = (t_fractol *)param;
    (void)xdelta;
    
    if (ydelta > 0)
        fractol->zoom *= 0.9;
    else if (ydelta < 0)
        fractol->zoom *= 1.1;
}

void main_loop(void *param)
{
    t_fractol *fractol;
    
    fractol = (t_fractol *)param;
    if (!fractol || !fractol->img)
        return;
        
    ft_printf("Rendering frame...\n");  // Temporal, hasta que implementemos render_fractal
}