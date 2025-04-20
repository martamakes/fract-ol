/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:58:15 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 09:58:18 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Switch to Mandelbrot fractal
 * 
 * @param f Fractal structure
 */
void	action_fractal_mandelbrot(t_fractol *f)
{
	switch_fractal(f, MANDELBROT);
}

/**
 * Switch to Julia fractal
 * 
 * @param f Fractal structure
 */
void	action_fractal_julia(t_fractol *f)
{
	switch_fractal(f, JULIA);
}

/**
 * Switch to Burning Ship fractal
 * 
 * @param f Fractal structure
 */
void	action_fractal_burningship(t_fractol *f)
{
	switch_fractal(f, BURNINGSHIP);
}

/**
 * Set Julia parameters to dendrite set
 * 
 * @param f Fractal structure
 */
void	action_julia_dendrite(t_fractol *f)
{
	if (f->type == JULIA)
		set_julia_param(f, 'd');
}

/**
 * Set Julia parameters to rabbit set
 * 
 * @param f Fractal structure
 */
void	action_julia_rabbit(t_fractol *f)
{
	if (f->type == JULIA)
		set_julia_param(f, 'r');
}
