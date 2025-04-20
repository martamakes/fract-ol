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

/* Calculate the length of a palette array */
int	palette_len(t_palette *palettes)
{
	int	i;

	i = 0;
	while (i < 5 && palettes[i].count > 0)
		i++;
	return (i);
}

/* Initialize palette 4: Ocean theme */
static void	init_palette_ocean(t_palette *palette)
{
	*palette = (t_palette){7, 1, {
		0x000000FF,
		0x000080FF,
		0x0000CDFF,
		0x4169E1FF,
		0x87CEEBFF,
		0x00FFFFFF,
		0xE0FFFFFF
	}};
}

/* Initialize palette 5: Grayscale theme */
static void	init_palette_grayscale(t_palette *palette)
{
	*palette = (t_palette){7, 1, {
		0x000000FF,
		0x1A1A1AFF,
		0x333333FF,
		0x666666FF,
		0x999999FF,
		0xCCCCCCFF,
		0xFFFFFFFF
	}};
}

/* Initialize all predefined color palettes */
t_palette	*init_palettes(void)
{
	static t_palette	array[5];

	init_palette_blue_gold(&array[0]);
	init_palette_purple_green(&array[1]);
	init_palette_fire(&array[2]);
	init_palette_ocean(&array[3]);
	init_palette_grayscale(&array[4]);
	return (array);
}
