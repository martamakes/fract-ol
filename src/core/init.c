/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:53:55 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 21:09:51 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void validate_julia_params(t_fractol *f, char **argv)
{
    f->c.re = ft_atof(argv[2]);
    f->c.im = ft_atof(argv[3]);
    if (isnan(f->c.re) || isnan(f->c.im))
        exit_error(f, "Invalid Julia parameters");
}

static void	init_fractal_params(t_fractol *f)
{
    f->zoom = 4.0;
    f->max_iter = 50;
    f->shift_x = -0.5;
    f->shift_y = 0.0;
    if (f->type == JULIA)
        validate_julia_params(f, f->params);
}

void init_fractol(t_fractol *f)
{
    f->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "42 Fractol", true);
    if (!f->mlx)
        exit_error(f, "MLX initialization failed");
        
    f->img = mlx_new_image(f->mlx, FRACT_SIZE, FRACT_SIZE);
    if (!f->img)
    {
        mlx_terminate(f->mlx);
        exit_error(f, "Image creation failed");
    }
    f->palettes = init_palettes();
    f->palette = &f->palettes[0];
    init_fractal_params(f);
    if (mlx_image_to_window(f->mlx, f->img, (WIN_WIDTH - FRACT_SIZE) / 2, 0) < 0)
    {
        mlx_delete_image(f->mlx, f->img);
        mlx_terminate(f->mlx);
        exit_error(f, "Cannot put image to window");
    }
    calculate_mandelbrot(f);
    render_fractal(f);
    mlx_image_to_window(f->mlx, f->img, (WIN_WIDTH - FRACT_SIZE) / 2, 0);
    mlx_loop(f->mlx);
    mlx_loop(f->mlx);
}

