/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:03:04 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 12:09:40 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int palette_len(t_palette *palettes)
{
    int i;
    
    i = 0;
    while (i < 6 && palettes[i].count > 0)
        i++;
    return (i);
}


t_palette *init_palettes(void) 
{
    static t_palette array[6];
    
    array[0] = (t_palette){9, 0, {0x000033FF, 0x000066FF, 0x000099FF, 
        0x0000CCFF, 0x0000FFFF, 0xFF6600FF, 0xFF9933FF, 0xFFCC00FF, 0xFFFF33FF}};
    array[1] = (t_palette){7, 0, {0x000033FF, 0x4B0082FF, 0x800080FF, 
        0xDA70D6FF, 0xFFD700FF, 0x00CED1FF, 0xFFFFFFFF}};
    array[2] = (t_palette){7, 0, {0x191970FF, 0x6A5ACDFF, 0x9370DBFF, 
        0xEE82EEFF, 0xFFA07AFF, 0xFFD700FF, 0xFFFFFFFF}};
    array[3] = (t_palette){7, 0, {0x000080FF, 0x4B0082FF, 0x800080FF, 
        0xDB7093FF, 0xADD8E6FF, 0xFFD700FF, 0xFFFFFFFF}};
    array[4] = (t_palette){7, 0, {0x000066FF, 0x4169E1FF, 0xB8860BFF, 
        0xFF8C00FF, 0xE6E6FAFF, 0xFFD700FF, 0xFFFFFFFF}};
    array[5] = (t_palette){7, 0, {0x000033FF, 0x003366FF, 0x0099CCFF, 
        0x00CCFFFF, 0xFFD700FF, 0xFFCC00FF, 0xFFFFFFFF}};
    return (array);
}
