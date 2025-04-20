/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:53:55 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 11:31:50 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void print_fractal_params(t_fractol *f)
{
    printf("\n--- Fractal Parameters ---\n");
    printf("Type: %d (%s)\n", f->type, 
           f->type == MANDELBROT ? "Mandelbrot" : 
           f->type == JULIA ? "Julia" : 
           f->type == BURNINGSHIP ? "Burning Ship" : "Unknown");
    printf("Position: shift_x=%.6f, shift_y=%.6f\n", f->shift_x, f->shift_y);
    printf("Zoom: %.6f\n", f->zoom);
    printf("Max iterations: %d\n", f->max_iter);
    printf("Color shift: %d\n", f->color_shift);
    printf("Palette index: %d\n", f->palette_index);
    printf("Smooth coloring: %s\n", f->smooth ? "On" : "Off");
    
    if (f->type == JULIA)
        printf("Julia params: c_re=%.6f, c_im=%.6f\n", f->c.re, f->c.im);
    printf("-------------------------\n");
}

static void	set_predefined_julia(t_fractol *f, char set_type)
{
	char	c;

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

static void	validate_julia_params(t_fractol *f, char **argv)
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
    f->max_iter = 20;
    f->shift_x = 0.0;
    f->shift_y = 0.0;
    f->palettes = init_palettes();
    f->palette_index = 0;
    f->palette = &f->palettes[0];
    f->palette_len = palette_len(f->palettes);
    f->smooth = true;
    f->color_shift = 0.0;
    
    if (f->type == MANDELBROT)
    {
        f->shift_x = -0.5;  /* Centra Mandelbrot horizontalmente */
    }
    else if (f->type == JULIA)
    {
        validate_julia_params(f, f->params);
        /* Julia no necesita un desplazamiento por defecto */
        f->zoom = 1.3;     /* Un zoom más cercano para mejor visualización */
    }
    else if (f->type == BURNINGSHIP)
    {
        f->shift_x = -0.5062;  /* Mejor centrado horizontal */
        f->shift_y = -0.5355;  /* Mejor centrado vertical para ver la "base" del barco */
        f->max_iter = 50;  /* Aumentar significativamente las iteraciones para eliminar puntitos */
        f->zoom = 4.79;
		f->color_shift = 1;
		f->palette_index = 2;     /* Ajustar zoom para ver mejor estructura */
    }
}
