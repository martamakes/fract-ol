/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:03:04 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 09:56:02 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Calculate the length of a palette array
 * 
 * @param palettes Array of color palettes
 * @return Number of valid palettes in the array
 */
int	palette_len(t_palette *palettes)
{
	int	i;

	i = 0;
	while (i < 5 && palettes[i].count > 0)
		i++;
	return (i);
}

/**
 * Initialize palette 1: Blue and gold theme
 * 
 * @param palette Palette to initialize
 */
static void	init_palette_blue_gold(t_palette *palette)
{
	*palette = (t_palette){7, 1, {
		0x000000FF,
		0x0A1172FF,
		0x0000FFFF,
		0x00FFFFFF,
		0x7DF9FFFF,
		0xFFD700FF,
		0xFFFFFFFF
	}};
}

/**
 * Initialize palette 2: Purple and green theme
 * 
 * @param palette Palette to initialize
 */
static void	init_palette_purple_green(t_palette *palette)
{
	*palette = (t_palette){7, 1, {
		0x000000FF,
		0x4B0082FF,
		0x800080FF,
		0xDA70D6FF,
		0x00FF00FF,
		0x32CD32FF,
		0xADFF2FFF
	}};
}

/**
 * Initialize palette 3: Fire theme
 * 
 * @param palette Palette to initialize
 */
static void	init_palette_fire(t_palette *palette)
{
	*palette = (t_palette){7, 1, {
		0x000000FF,
		0x8B0000FF,
		0xFF0000FF,
		0xFF4500FF,
		0xFFA500FF,
		0xFFD700FF,
		0xFFFF00FF
	}};
}

/**
 * Initialize all predefined color palettes
 * 
 * @return Array of initialized palettes
 */
t_palette	*init_palettes(void)
{
	static t_palette	array[5];

	init_palette_blue_gold(&array[0]);
	init_palette_purple_green(&array[1]);
	init_palette_fire(&array[2]);
	
	array[3] = (t_palette){7, 1, {
		0x000000FF,
		0x000080FF,
		0x0000CDFF,
		0x4169E1FF,
		0x87CEEBFF,
		0x00FFFFFF,
		0xE0FFFFFF
	}};
	
	array[4] = (t_palette){7, 1, {
		0x000000FF,
		0x1A1A1AFF,
		0x333333FF,
		0x666666FF,
		0x999999FF,
		0xCCCCCCFF,
		0xFFFFFFFF
	}};
	
	return (array);
}
