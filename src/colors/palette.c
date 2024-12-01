/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:03:04 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/30 13:14:27 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int palette_len(t_palette *palettes)
{
    int i;
    
    i = 0;
    while (i < 5 && palettes[i].count > 0)
        i++;
    return (i);
}

t_palette *init_palettes(void) 
{
    static t_palette array[6];
    
    array[0] = (t_palette){5, 0, {
        0xFF000066, 0xFF0033CC, 0xFF3366FF, 0xFF33CCFF, 0xFF66FFFF
    }};
    array[1] = (t_palette){5, 0, {
        0xFF000000, 0xFF440000, 0xFF880000, 0xFFBB0000, 0xFFFF0000
    }};
    array[2] = (t_palette){5, 0, {
        0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFF00FF, 0xFFFFFF00
    }};
    array[3] = (t_palette){5, 0, {
        0xFF004400, 0xFF006600, 0xFF008800, 0xFF00AA00, 0xFF00FF00
    }};
    array[4] = (t_palette){5, 0, {
        0xFFFFB732, 0xFFFF9300, 0xFFFF5500, 0xFFFF0000, 0xFF660000
    }};
        array[5] = (t_palette){5, 0, {
        0xFF1E90FF,  // Azul dodger
        0xFFFF69B4,  // Rosa hot pink
        0xFFFFD700,  // Dorado
        0xFF00CED1,  // Turquesa oscuro
        0xFFFF8C00   // Naranja oscuro
    }};
    return (array);
}

