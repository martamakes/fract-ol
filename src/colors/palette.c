/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:03:04 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 11:34:47 by mvigara-         ###   ########.fr       */
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
        0xFF1B1464, 0xFF0652DD, 0xFF9980FA, 0xFFFFD32A, 0xFFEA8685
    }};
    array[1] = (t_palette){5, 0, {
        0xFF000033, 0xFF4B0082, 0xFFDA70D6, 0xFFFFD700, 0xFF00CED1
    }};
    array[2] = (t_palette){5, 0, {
        0xFF191970, 0xFF6A5ACD, 0xFF9370DB, 0xFFEE82EE, 0xFFFFA07A
    }};
    array[3] = (t_palette){5, 0, {
        0xFF000080, 0xFF4B0082, 0xFF800080, 0xFFDB7093, 0xFFADD8E6
    }};
    array[4] = (t_palette){5, 0, {
        0xFF000066, 0xFF4169E1, 0xFFB8860B, 0xFFFF8C00, 0xFFE6E6FA
    }};
    array[5] = (t_palette){5, 0, {
        0xFF000033, 0xFF003366, 0xFF0099CC, 0xFF00CCFF, 0xFFFFFFFF
    }};
    return (array);
}
