/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:35:43 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 01:36:21 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    exit_error(t_fractol *f, char *msg)
{
   if (f)
       free(f);
   ft_putendl_fd("Error:", 2);
   ft_putendl_fd(msg, 2);
   exit(EXIT_FAILURE);
}
