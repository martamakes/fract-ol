/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:20:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 14:20:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Print basic controls section */
static void	print_basic_controls(void)
{
	printf("\n------ FRACTOL CONTROLS ------\n");
	printf("Mouse wheel   : Zoom in/out at cursor position\n");
	printf("Arrow keys    : Move the view\n");
	printf("ESC           : Exit program\n");
}

/* Print fractal selection section */
static void	print_fractal_selection(void)
{
	printf("\n--- Fractal Selection ---\n");
	printf("1              : Mandelbrot set\n");
	printf("2              : Julia set\n");
	printf("3              : Burning Ship fractal\n");
}

/* Print Julia parameters section */
static void	print_julia_params(void)
{
	printf("\n--- Julia Set Parameters ---\n");
	printf("D              : Dendrite Julia set\n");
	printf("R              : Rabbit Julia set\n");
	printf("G              : Dragon Julia set\n");
}

/* Print visual controls section */
static void	print_visual_controls(void)
{
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

/* Display help information */
void	print_help(void)
{
	print_basic_controls();
	print_fractal_selection();
	print_julia_params();
	print_visual_controls();
}
