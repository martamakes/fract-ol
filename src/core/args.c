/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:55:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 13:55:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Shows usage information */
int	print_usage(void)
{
	ft_putstr_fd("\nUsage: ./fractol <type> [params]\n\n", 1);
	ft_putstr_fd("Types:\n", 1);
	ft_putstr_fd("  M or Mandelbrot  : Mandelbrot set\n", 1);
	ft_putstr_fd("  J or Julia [set/params] : Julia set variations\n", 1);
	ft_putstr_fd("    Sets:\n", 1);
	ft_putstr_fd("      d or dendrite : Dendrite set (-0.4 0.6)\n", 1);
	ft_putstr_fd("      r or rabbit   : Rabbit set (-0.123 0.745)\n", 1);
	ft_putstr_fd("      g or dragon   : Dragon set (0.36 0.1)\n", 1);
	ft_putstr_fd("    Custom: J <real> <imaginary>\n", 1);
	ft_putstr_fd("  B or Burningship : Burning ship fractal\n\n", 1);
	return (EXIT_FAILURE);
}

/* Validates short arguments (1 character) */
static bool	check_short_args(char **argv, int argc, t_fractol *fractol)
{
	if (argv[1][0] == 'M' || argv[1][0] == 'm')
		fractol->type = MANDELBROT;
	else if (argv[1][0] == 'B' || argv[1][0] == 'b')
		fractol->type = BURNINGSHIP;
	else if ((argv[1][0] == 'J' || argv[1][0] == 'j'))
	{
		if (argc == 3 || argc == 4)
		{
			fractol->type = JULIA;
			return (true);
		}
	}
	return (fractol->type != 0);
}

/* Validates long arguments (full word) */
static bool	check_long_args(char **argv, int argc, t_fractol *fractol)
{
	if (!ft_strncmp(argv[1], "Mandelbrot", 10))
		fractol->type = MANDELBROT;
	else if (!ft_strncmp(argv[1], "Julia", 5) && (argc == 3 || argc == 4))
		fractol->type = JULIA;
	else if (!ft_strncmp(argv[1], "Burningship", 11))
		fractol->type = BURNINGSHIP;
	return (fractol->type != 0);
}

/* Validates program arguments */
bool	check_args(int argc, char **argv, t_fractol *fractol)
{
	if (argc < 2)
		return (false);
	if (ft_strlen(argv[1]) == 1)
		return (check_short_args(argv, argc, fractol));
	else
		return (check_long_args(argv, argc, fractol));
}
