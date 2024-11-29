/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:09:33 by marta             #+#    #+#             */
/*   Updated: 2024/09/20 09:19:29 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_digit(char c, int base)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (base > 10 && ft_isalpha(c))
		return (ft_tolower(c) - 'a' + 10);
	return (-1);
}

static int	check_base(const char **nptr, int base)
{
	if (base == 0)
	{
		if (**nptr == '0')
		{
			(*nptr)++;
			if (ft_tolower(**nptr) == 'x')
			{
				base = 16;
				(*nptr)++;
			}
			else
				base = 8;
		}
		else
			base = 10;
	}
	else if (base == 16 && **nptr == '0' && ft_tolower(*(*nptr + 1)) == 'x')
		*nptr += 2;
	return (base);
}

static int	convert_digits(const char **nptr, int base, long *result)
{
	int	digit;
	int	overflow;

	overflow = 0;
	while ((digit = char_to_digit(**nptr, base)) >= 0)
	{
		if (*result > (LONG_MAX - digit) / base)
		{
			overflow = 1;
			break ;
		}
		*result = *result * base + digit;
		(*nptr)++;
	}
	return (overflow);
}

static long	handle_overflow(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	return (LONG_MIN);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	int		sign;
	long	result;
	int		overflow;

	result = 0;
	while (ft_iswhitespace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	base = check_base(&nptr, base);
	overflow = convert_digits(&nptr, base, &result);
	if (endptr)
		*endptr = (char *)nptr;
	if (overflow)
		return (handle_overflow(sign));
	return (result * sign);
}
