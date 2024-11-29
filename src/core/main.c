/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:52:43 by mvigara-          #+#    #+#             */
/*   Updated: 2024/11/29 01:41:38 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	print_usage(void)
{
	ft_putstr_fd("\nUsage: ./fractol <type> [params]\n\n", 1);
	ft_putstr_fd("Types:\n", 1);
	ft_putstr_fd("  M or Mandelbrot  : Mandelbrot set\n", 1);
	ft_putstr_fd("  J or Julia [re im]: Julia set + optional parameters\n", 1); 
	ft_putstr_fd("  B or Burningship : Burning ship fractal\n\n", 1);
	return (EXIT_FAILURE);
}

bool	check_args(int argc, char **argv, t_fractol *fractol)
{
	if (argc < 2)
		return (false);
	if (ft_strlen(argv[1]) == 1)
	{
		if (argv[1][0] == 'M' || argv[1][0] == 'm')
			fractol->type = MANDELBROT;
		else if (argv[1][0] == 'B' || argv[1][0] == 'b')
			fractol->type = BURNINGSHIP;
		else if ((argv[1][0] == 'J' || argv[1][0] == 'j') && argc == 4)
		{
			fractol->type = JULIA;
			return (true);
		}
		return (fractol->type != 0);
	}
	else if (!ft_strncmp(argv[1], "Mandelbrot", 10))
		fractol->type = MANDELBROT;
	else if (!ft_strncmp(argv[1], "Julia", 5) && argc == 4)
		fractol->type = JULIA;
	else if (!ft_strncmp(argv[1], "Burningship", 11))
		fractol->type = BURNINGSHIP;
	return (fractol->type != 0);
}

int main(int argc, char **argv)
{
    t_fractol *fractol;

    if (!(fractol = malloc(sizeof(t_fractol))))
        return (EXIT_FAILURE);
    fractol->params = argv;
    if (!check_args(argc, argv, fractol))
    {
        free(fractol);
        return (print_usage());
    }
    init_fractol(fractol);
    return (0);
}
