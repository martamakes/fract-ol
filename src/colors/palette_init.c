/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:10:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 15:16:11 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Initialize palette 1: Blue and gold theme */
void	init_palette_blue_gold(t_palette *palette)
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

/* Initialize palette 2: Purple and green theme */
void	init_palette_purple_green(t_palette *palette)
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

/* Initialize palette 3: Fire theme */
void	init_palette_fire(t_palette *palette)
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
