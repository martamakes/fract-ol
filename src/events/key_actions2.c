/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:36:12 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 10:36:22 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Increase maximum iterations
 * 
 * @param f Fractal structure
 */
void	action_iter_up(t_fractol *f)
{
	if (f->max_iter < 1000)
		f->max_iter += 20;
	printf("Iterations: %d\n", f->max_iter);
}

/**
 * Decrease maximum iterations
 * 
 * @param f Fractal structure
 */
void	action_iter_down(t_fractol *f)
{
	if (f->max_iter > 20)
		f->max_iter -= 20;
	printf("Iterations: %d\n", f->max_iter);
}

/**
 * Set Julia parameters
 * 
 * @param f Fractal structure
 * @param set_type Type of Julia set to use
 */
void	set_julia_param(t_fractol *f, char set_type)
{
	char	c;

	if (f->type != JULIA)
		return;
		
	c = ft_tolower(set_type);
	if (c == 'd')
	{
		f->c.re = -0.4;
		f->c.im = 0.6;
		printf("Switched to Dendrite Julia set (c: %.3f + %.3fi)\n", f->c.re, f->c.im);
	}
	else if (c == 'r')
	{
		f->c.re = -0.123;
		f->c.im = 0.745;
		printf("Switched to Rabbit Julia set (c: %.3f + %.3fi)\n", f->c.re, f->c.im);
	}
	else if (c == 'g')
	{
		f->c.re = 0.36;
		f->c.im = 0.1;
		printf("Switched to Dragon Julia set (c: %.3f + %.3fi)\n", f->c.re, f->c.im);
	}
}

/**
 * Switch to a different fractal type
 * 
 * @param f Fractal structure
 * @param new_type New fractal type to switch to
 */
void	switch_fractal(t_fractol *f, t_fractal_type new_type)
{
	if (f->type == new_type)
		return;
		
	f->type = new_type;
	reset_view(f);
	
	/* Establecer parámetros adicionales para Julia */
	if (f->type == JULIA)
	{
		/* Si no hay parámetros de Julia ya establecidos, usar dendrita por defecto */
		if (f->c.re == 0.0 && f->c.im == 0.0)
			set_julia_param(f, 'd');
	}
	
	if (f->type == MANDELBROT)
		printf("Switched to Mandelbrot set\n");
	else if (f->type == JULIA)
		printf("Switched to Julia set (c: %.3f + %.3fi)\n", f->c.re, f->c.im);
	else if (f->type == BURNINGSHIP)
		printf("Switched to Burning Ship fractal\n");
}

/**
 * Display help information
 */
void	print_help(void)
{
	printf("\n------ FRACTOL CONTROLS ------\n");
	printf("Mouse wheel   : Zoom in/out at cursor position\n");
	printf("Arrow keys    : Move the view\n");
	printf("ESC           : Exit program\n");
	printf("\n--- Fractal Selection ---\n");
	printf("1              : Mandelbrot set\n");
	printf("2              : Julia set\n");
	printf("3              : Burning Ship fractal\n");
	printf("\n--- Julia Set Parameters ---\n");
	printf("D              : Dendrite Julia set\n");
	printf("R              : Rabbit Julia set\n");
	printf("G              : Dragon Julia set\n");
	printf("\n--- Visual Controls ---\n");
	printf("C              : Change color palette\n");
	printf("[              : Decrease color shift\n");
	printf("]              : Increase color shift\n");
	printf("S              : Toggle smooth coloring\n");
	printf("+              : Increase max iterations\n");
	printf("-              : Decrease max iterations\n");
	printf("R              : Reset view\n");
	printf("H              : Show this help\n");
	printf("--------------------------------\n\n");
}
