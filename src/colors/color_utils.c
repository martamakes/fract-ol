/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:57:27 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 13:36:27 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_rgb_values(t_color rgb, double *r, double *g, double *b)
{
	*r = rgb.rgba.r / 255.0;
	*g = rgb.rgba.g / 255.0;
	*b = rgb.rgba.b / 255.0;
}

t_hsv	rgb2hsv(t_color rgb)
{
	t_hsv	hsv;
	double	min;
	double	max;
	double	delta;
	double	r;
	double	g;
	double	b;

	init_rgb_values(rgb, &r, &g, &b);
	min = fmin(fmin(r, g), b);
	max = fmax(fmax(r, g), b);
	delta = max - min;
	hsv.v = max;
	hsv.s = (max != 0) ? delta / max : 0;
	if (delta == 0)
		hsv.h = 0;
	else if (max == r)
		hsv.h = 60 * fmod(((g - b) / delta), 6);
	else if (max == g)
		hsv.h = 60 * ((b - r) / delta + 2);
	else
		hsv.h = 60 * ((r - g) / delta + 4);
	if (hsv.h < 0)
		hsv.h += 360;
	return (hsv);
}
