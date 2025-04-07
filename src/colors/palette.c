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
	while (i < 3 && palettes[i].count > 0)
		i++;
	return (i);
}

/*
 * Inicializa las paletas de colores predefinidas
 */
t_palette	*init_palettes(void)
{
	static t_palette	array[3];

	/* Paleta 1: Azul a amarillo */
	array[0] = (t_palette){9, 1, {0x000033FF, 0x000066FF, 0x000099FF, 
		0x0000CCFF, 0x0000FFFF, 0xFF6600FF, 0xFF9933FF, 0xFFCC00FF, 0xFFFF33FF}};
	/* Paleta 2: Púrpura a cyan */
	array[1] = (t_palette){7, 1, {0x000033FF, 0x4B0082FF, 0x800080FF, 
		0xDA70D6FF, 0xFFD700FF, 0x00CED1FF, 0xFFFFFFFF}};
	/* Paleta 3: Azul a rojo */
	array[2] = (t_palette){7, 1, {0x191970FF, 0x6A5ACDFF, 0x9370DBFF, 
		0xEE82EEFF, 0xFFA07AFF, 0xFFD700FF, 0xFFFFFFFF}};
	return (array);
}
