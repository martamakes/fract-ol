/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:03:04 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/04 12:52:37 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* 
 * Calcula la longitud de un array de paletas
 */
int	palette_len(t_palette *palettes)
{
	int	i;

	i = 0;
	while (i < 5 && palettes[i].count > 0)
		i++;
	return (i);
}

/*
 * Inicializa las paletas de colores predefinidas
 */
t_palette	*init_palettes(void)
{
	static t_palette	array[5];

	/* Paleta 1: Fuego - tonos cálidos */
	array[0] = (t_palette){9, 1, {0x000000FF, 0x340700FF, 0x5C0A00FF, 
		0x9C2100FF, 0xE73B00FF, 0xFD6A02FF, 0xFCA204FF, 0xFDD017FF, 0xFFFF00FF}};
	/* Paleta 2: Oceano - azules y verdes */
	array[1] = (t_palette){9, 1, {0x020233FF, 0x0C0C5CFF, 0x13139DFF, 
		0x1919CCFF, 0x5050FFFF, 0x00FFFFFF, 0x00B7FFFF, 0x00D8A0FF, 0x00FFB9FF}};
	/* Paleta 3: Espectro - arcoiris completo */
	array[2] = (t_palette){7, 1, {0x9400D3FF, 0x4B0082FF, 0x0000FFFF, 
		0x00FF00FF, 0xFFFF00FF, 0xFF7F00FF, 0xFF0000FF}};
	/* Paleta 4: Eléctrico - negros y púrpuras con cyan */
	array[3] = (t_palette){8, 1, {0x000000FF, 0x16001EFF, 0x380440FF, 
		0x5F0770FF, 0x6F0990FF, 0x913CBFFF, 0xAD90D8FF, 0x00FFFFFF}};
	/* Paleta 5: Tierra - terrosos y dorados */
	array[4] = (t_palette){8, 1, {0x100C08FF, 0x2D231AFF, 0x5E4B34FF, 
		0x8F754EFF, 0xBEA46DFF, 0xE8C889FF, 0xF5E8C9FF, 0xFFFFFFFF}};
	return (array);
}
