/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:20:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 15:20:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Set dendrite julia parameters */
static void	set_julia_dendrite(t_fractol *f)
{
	f->c.re = -0.4;
	f->c.im = 0.6;
	printf("Switched to Dendrite Julia set (c: %.3f + %.3fi)\n",
		f->c.re, f->c.im);
}

/* Set rabbit julia parameters */
static void	set_julia_rabbit(t_fractol *f)
{
	f->c.re = -0.123;
	f->c.im = 0.745;
	printf("Switched to Rabbit Julia set (c: %.3f + %.3fi)\n",
		f->c.re, f->c.im);
}

/* Set dragon julia parameters */
static void	set_julia_dragon(t_fractol *f)
{
	f->c.re = 0.36;
	f->c.im = 0.1;
	printf("Switched to Dragon Julia set (c: %.3f + %.3fi)\n",
		f->c.re, f->c.im);
}

/* Set Julia parameters */
void	set_julia_param(t_fractol *f, char set_type)
{
	char	c;

	if (f->type != JULIA)
		return ;
	c = ft_tolower(set_type);
	if (c == 'd')
		set_julia_dendrite(f);
	else if (c == 'r')
		set_julia_rabbit(f);
	else if (c == 'g')
		set_julia_dragon(f);
}

/* Set default Julia parameters if needed */
void	set_default_julia_params(t_fractol *f)
{
	if (f->c.re == 0.0 && f->c.im == 0.0)
		set_julia_param(f, 'd');
}
