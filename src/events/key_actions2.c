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

/* Increase maximum iterations */
void	action_iter_up(t_fractol *f)
{
	if (f->max_iter < 1000)
		f->max_iter += 20;
	printf("Iterations: %d\n", f->max_iter);
}

/* Decrease maximum iterations */
void	action_iter_down(t_fractol *f)
{
	if (f->max_iter > 20)
		f->max_iter -= 20;
	printf("Iterations: %d\n", f->max_iter);
}

/* Print fractal type after switch */
static void	print_fractal_info(t_fractol *f)
{
	if (f->type == MANDELBROT)
		printf("Switched to Mandelbrot set\n");
	else if (f->type == JULIA)
		printf("Switched to Julia set (c: %.3f + %.3fi)\n", f->c.re, f->c.im);
	else if (f->type == BURNINGSHIP)
		printf("Switched to Burning Ship fractal\n");
}

/* Switch to a different fractal type */
void	switch_fractal(t_fractol *f, t_fractal_type new_type)
{
	if (f->type == new_type)
		return ;
	f->type = new_type;
	reset_view(f);
	if (f->type == JULIA)
		set_default_julia_params(f);
	print_fractal_info(f);
}
