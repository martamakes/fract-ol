/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:13:31 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 09:54:57 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Convert RGBA components to a single 32-bit value
 * 
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @param a Alpha component (0-255)
 * @return uint32_t color value in format suitable for mlx
 */
uint32_t	get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * Linearly interpolate between two integer values
 * 
 * @param first First value
 * @param second Second value
 * @param p Interpolation factor (0.0 to 1.0)
 * @return Interpolated value
 */
int	ft_lerpi(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

/**
 * Apply a smoothing function to improve transitions
 * Uses cubic smoothstep function
 * 
 * @param t Value to smooth (0.0 to 1.0)
 * @return Smoothed value
 */
double	smooth_step(double t)
{
	return (t * t * (3.0 - 2.0 * t));
}

/**
 * Interpolate between two colors with a smoothed transition
 * 
 * @param c1 First color
 * @param c2 Second color
 * @param p Interpolation factor (0.0 to 1.0)
 * @return Interpolated color
 */
t_color	clrlerp(t_color c1, t_color c2, double p)
{
	t_color	c;
	double	p_smooth;

	if (c1.value == c2.value)
		return (c1);
	p_smooth = smooth_step(p);
	c.rgba.r = (uint8_t)ft_lerpi((int)c1.rgba.r, (int)c2.rgba.r, p_smooth);
	c.rgba.g = (uint8_t)ft_lerpi((int)c1.rgba.g, (int)c2.rgba.g, p_smooth);
	c.rgba.b = (uint8_t)ft_lerpi((int)c1.rgba.b, (int)c2.rgba.b, p_smooth);
	c.rgba.a = 255;
	return (c);
}

/**
 * Apply pixel color to the image
 * 
 * @param f Fractal structure
 * @param color_struct Color to apply
 */
void	apply_pixel_color(t_fractol *f, t_color color_struct)
{
	uint32_t	color_value;

	color_value = get_color(
		color_struct.rgba.r,
		color_struct.rgba.g,
		color_struct.rgba.b,
		color_struct.rgba.a
	);
	mlx_put_pixel(f->img, f->x, f->y, color_value);
}
