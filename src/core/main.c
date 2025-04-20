/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:52:43 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 11:34:25 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Main program entry */
int	main(int argc, char **argv)
{
	t_fractol	*fractol;

	fractol = malloc(sizeof(t_fractol));
	if (!fractol)
		return (EXIT_FAILURE);
	fractol->params = argv;
	if (!check_args(argc, argv, fractol))
	{
		free(fractol);
		return (print_usage());
	}
	init_fractal_params(fractol);
	setup_mlx(fractol);
	setup_hooks(fractol);
	mlx_loop(fractol->mlx);
	mlx_terminate(fractol->mlx);
	free(fractol);
	return (EXIT_SUCCESS);
}
