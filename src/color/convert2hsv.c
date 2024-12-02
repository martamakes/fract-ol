/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert2hsv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:37:22 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 13:37:55 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_rgb_values(t_color *rgb, double r, double g, double b)
{
	rgb->rgba.r = (uint8_t)(r * 255);
	rgb->rgba.g = (uint8_t)(g * 255);
	rgb->rgba.b = (uint8_t)(b * 255);
	rgb->rgba.a = 255;
}

static void	calculate_hsv_components(t_hsv hsv, double *c, double *x, double *m)
{
	*c = hsv.v * hsv.s;
	*x = *c * (1 - fabs(fmod(hsv.h / 60, 2) - 1));
	*m = hsv.v - *c;
}

t_color	hsv2rgb(t_hsv hsv)
{
	t_color	rgb;
	double	c;
	double	x;
	double	m;

	calculate_hsv_components(hsv, &c, &x, &m);
	if (hsv.h >= 0 && hsv.h < 60)
		set_rgb_values(&rgb, c + m, x + m, m);
	else if (hsv.h >= 60 && hsv.h < 120)
		set_rgb_values(&rgb, x + m, c + m, m);
	else if (hsv.h >= 120 && hsv.h < 180)
		set_rgb_values(&rgb, m, c + m, x + m);
	else if (hsv.h >= 180 && hsv.h < 240)
		set_rgb_values(&rgb, m, x + m, c + m);
	else if (hsv.h >= 240 && hsv.h < 300)
		set_rgb_values(&rgb, x + m, m, c + m);
	else
		set_rgb_values(&rgb, c + m, m, x + m);
	return (rgb);
}

static double	adjust_hue_diff(double h_diff)
{
	if (h_diff > 180)
		h_diff -= 360;
	else if (h_diff < -180)
		h_diff += 360;
	return (h_diff);
}

t_hsv	interpolate_hsv(t_hsv color1, t_hsv color2, double t)
{
	t_hsv	result;
	double	h_diff;

	h_diff = color2.h - color1.h;
	h_diff = adjust_hue_diff(h_diff);
	result.h = color1.h + t * h_diff;
	if (result.h < 0)
		result.h += 360;
	else if (result.h >= 360)
		result.h -= 360;
	result.s = color1.s + t * (color2.s - color1.s);
	result.v = color1.v + t * (color2.v - color1.v);
	return (result);
}
