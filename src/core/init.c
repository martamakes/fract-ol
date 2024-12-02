/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:53:55 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 14:20:11 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void set_predefined_julia(t_fractol *f, char set_type)
{
    char c;
    
    c = ft_tolower(set_type);
    if (c == 'd')
    {
        f->c.re = -0.4;
        f->c.im = 0.6;
    }
    else if (c == 'r')
    {
        f->c.re = -0.123;
        f->c.im = 0.745;
    }
    else if (c == 'g')
    {
        f->c.re = 0.36;
        f->c.im = 0.1;
    }
    else
        exit_error(f, "Invalid Julia set type");
}

static void validate_julia_params(t_fractol *f, char **argv)
{
    if (ft_strlen(argv[2]) == 1)
        set_predefined_julia(f, argv[2][0]);
    else if (argv[3])
    {
        f->c.re = ft_atof(argv[2]);
        f->c.im = ft_atof(argv[3]);
        if (isnan(f->c.re) || isnan(f->c.im))
            exit_error(f, "Invalid Julia parameters");
    }
    else
        exit_error(f, "Invalid Julia parameters");
}

void init_fractal_params(t_fractol *f)
{
    f->zoom = 4.0;
    f->max_iter = 1000;  // Aumentamos las iteraciones iniciales
    f->shift_x = -0.5;  // Para Mandelbrot
    f->shift_y = 0.0;
    f->palettes = init_palettes();
    f->palette_index = 0;
    f->palette = &f->palettes[0];
    f->palette_len = palette_len(f->palettes);
    f->smooth = true;  // Activamos el suavizado por defecto
    if (f->type == JULIA)
    {
        f->shift_x = 0.0;  // Reset para Julia
        validate_julia_params(f, f->params);
    }
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
    init_fractal_params(f);   
    if (mlx_image_to_window(f->mlx, f->img, (WIN_WIDTH - FRACT_SIZE) / 2, 0) < 0)
    {
        mlx_delete_image(f->mlx, f->img);
        mlx_terminate(f->mlx);
        exit_error(f, "Cannot put image to window");
    }   
    mlx_key_hook(f->mlx, &handle_keys, f);
    mlx_scroll_hook(f->mlx, &handle_scroll, f);
    mlx_loop_hook(f->mlx, &main_loop, f);
    render_fractal(f);
    mlx_loop(f->mlx);
}
