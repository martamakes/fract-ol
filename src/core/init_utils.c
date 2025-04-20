/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:45:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 13:45:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Get fractal type name for display */
char	*get_fractal_name(t_fractal_type type)
{
	if (type == MANDELBROT)
		return ("Mandelbrot");
	else if (type == JULIA)
		return ("Julia");
	else if (type == BURNINGSHIP)
		return ("Burning Ship");
	else
		return ("Unknown");
}

/* Displays the current fractal parameters */
void	print_fractal_params(t_fractol *f)
{
	printf("\n--- Fractal Parameters ---\n");
	printf("Type: %d (%s)\n", f->type, get_fractal_name(f->type));
	printf("Position: shift_x=%.6f, shift_y=%.6f\n", f->shift_x, f->shift_y);
	printf("Zoom: %.6f\n", f->zoom);
	printf("Max iterations: %d\n", f->max_iter);
	printf("Color shift: %d\n", f->color_shift);
	printf("Palette index: %d\n", f->palette_index);
	if (f->smooth)
		printf("Smooth coloring: On\n");
	else
		printf("Smooth coloring: Off\n");
	if (f->type == JULIA)
		printf("Julia params: c_re=%.6f, c_im=%.6f\n", f->c.re, f->c.im);
	printf("-------------------------\n");
}

/* Sets predefined Julia set parameters based on type */
void	set_predefined_julia(t_fractol *f, char set_type)
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

/* Validates and sets Julia parameters from command line arguments */
void	validate_julia_params(t_fractol *f, char **argv)
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
