/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:31:17 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 17:43:38 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	update_iterations(t_fractol *f)
{
	double	log_zoom;
	int		base_iter;
	int		new_iter;

	// Iteraciones base ajustadas según tipo de fractal
	if (f->type == BURNINGSHIP)
		base_iter = 300;
	else if (f->type == JULIA)
		base_iter = 250;
	else
		base_iter = 200;
	
	// Usamos logaritmo base 2 para una escala más natural
	log_zoom = log(4.0 / f->zoom) / log(2.0);
	
	// Fórmula mejorada para zoom profundo con progresión más precisa
	if (log_zoom < 0)
	{
		// Ajustes específicos para cada tipo de fractal para mantener detalles
		if (f->type == MANDELBROT)
			new_iter = base_iter * (1 + pow(1.8, -log_zoom * 0.2));
		else if (f->type == JULIA)
			new_iter = base_iter * (1 + pow(1.6, -log_zoom * 0.25));
		else // BURNINGSHIP
			new_iter = base_iter * (1 + pow(1.7, -log_zoom * 0.22));
	}
	else
		new_iter = base_iter;
	
	// Mantener un mínimo razonable
	if (new_iter < base_iter)
		new_iter = base_iter;
	
	// Límite máximo para rendimiento, pero superior para permitir más detalle
	if (f->zoom < 1e-10) // Para zoom extremadamente profundo
		new_iter = 10000;
	else if (f->zoom < 1e-6) // Para zoom muy profundo
		new_iter = (new_iter > 8000) ? 8000 : new_iter;
	else // Para zoom normal
		new_iter = (new_iter > 5000) ? 5000 : new_iter;
	
	f->max_iter = new_iter;
}

static void	update_zoom(t_fractol *f, double ydelta)
{
	double	zoom_factor;

	// Zoom factor adaptativo basado en el nivel de zoom actual
	if (f->zoom < 1e-10) // Para zoom extremadamente profundo
		zoom_factor = (ydelta > 0) ? 0.97 : 1.03; // Más preciso
	else if (f->zoom < 1e-6) // Para zoom muy profundo
		zoom_factor = (ydelta > 0) ? 0.95 : 1.05; // Preciso
	else
		zoom_factor = (ydelta > 0) ? 0.9 : 1.1; // Normal
	
	// Aplicar zoom
	f->zoom *= zoom_factor;
	
	// Prevenir errores de precisión en zoom extremo
	if (f->zoom < 1e-13)
	{
		f->zoom = 1e-13; // Limitar zoom máximo para mantener precisión
	}
	
	// Actualizar iteraciones basadas en nuevo nivel de zoom
	update_iterations(f);
}

void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_fractol	*f;
	int32_t		mouse_x;
	int32_t		mouse_y;
	t_complex	mouse_pos;

	f = (t_fractol *)param;
	(void)xdelta;
	mlx_get_mouse_pos(f->mlx, &mouse_x, &mouse_y);
	mouse_x -= (WIN_WIDTH - FRACT_SIZE) / 2;
	mouse_pos.re = (mouse_x - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE
		+ f->shift_x;
	mouse_pos.im = (mouse_y - FRACT_SIZE / 2.0) * f->zoom / FRACT_SIZE
		+ f->shift_y;
	update_zoom(f, ydelta);
	f->shift_x = mouse_pos.re - (mouse_x - FRACT_SIZE / 2.0) * f->zoom
		/ FRACT_SIZE;
	f->shift_y = mouse_pos.im - (mouse_y - FRACT_SIZE / 2.0) * f->zoom
		/ FRACT_SIZE;
}
