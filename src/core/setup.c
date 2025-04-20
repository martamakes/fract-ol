/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:00:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/21 14:00:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Setup MLX window and image */
void	setup_mlx(t_fractol *fractol)
{
	int	offset_x;
	int	offset_y;

	fractol->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Fractol", true);
	if (!fractol->mlx)
		exit_error(fractol, "Failed to initialize MLX42");
	fractol->img = mlx_new_image(fractol->mlx, FRACT_SIZE, FRACT_SIZE);
	if (!fractol->img)
		exit_error(fractol, "Failed to create image");
	render_fractal(fractol);
	offset_x = (WIN_WIDTH - FRACT_SIZE) / 2;
	offset_y = (WIN_HEIGHT - FRACT_SIZE) / 2;
	if (mlx_image_to_window(fractol->mlx, fractol->img, offset_x, offset_y) < 0)
		exit_error(fractol, "Failed to add image to window");
	printf("Image placed at offset: %d,%d\n", offset_x, offset_y);
}

/* Setup event hooks */
void	setup_hooks(t_fractol *fractol)
{
	mlx_key_hook(fractol->mlx, handle_keys, fractol);
	mlx_scroll_hook(fractol->mlx, handle_scroll, fractol);
	mlx_loop_hook(fractol->mlx, main_loop, fractol);
	printf("\nFractal initialized. Press H for help.\n");
	print_fractal_params(fractol);
}
