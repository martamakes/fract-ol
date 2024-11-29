/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:57:06 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 01:57:36 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int handle_whitespace_sign(const char *str, int *sign)
{
    int i;

    i = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            *sign = -1;
        i++;
    }
    return (i);
}

double  ft_atof(const char *str)
{
    int     i;
    int     sign;
    double  result;
    double  decimal;
    
    sign = 1;
    result = 0.0;
    i = handle_whitespace_sign(str, &sign);
    while (str[i] >= '0' && str[i] <= '9')
        result = result * 10.0 + (str[i++] - '0');
    if (str[i] == '.')
    {
        decimal = 1.0;
        i++;
        while (str[i] >= '0' && str[i] <= '9')
        {
            decimal *= 0.1;
            result += (str[i++] - '0') * decimal;
        }
    }
    return (result * sign);
}
