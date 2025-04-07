/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:31:17 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/01 11:50:53 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void update_iterations(t_fractol *f)
{
    double log_zoom;
    int base_iter;
    int new_iter;
    
    base_iter = 100;
    log_zoom = log10(4.0/f->zoom);
    if (log_zoom < 0)
        log_zoom = 0;
    new_iter = (int)(base_iter * (1 + log_zoom * 1.5));
    if (new_iter > 1000)
        new_iter = 1000;
    if (new_iter < base_iter)
        new_iter = base_iter;
    f->max_iter = new_iter;
}

static void update_zoom(t_fractol *f, double ydelta)
{
    double zoom_factor;
    
    zoom_factor = (ydelta > 0) ? 0.95 : 1.05;
    f->zoom *= zoom_factor;
    update_iterations(f);
}

void handle_scroll(double xdelta, double ydelta, void *param)
{
    t_fractol   *f;
    int32_t     mouse_x;
    int32_t     mouse_y;
    double      mouse_re;
    double      mouse_im;
    
    f = (t_fractol *)param;
    (void)xdelta;
    mlx_get_mouse_pos(f->mlx, &mouse_x, &mouse_y);
    mouse_x -= (WIN_WIDTH - FRACT_SIZE) / 2;
    mouse_re = (mouse_x - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE + f->shift_x;
    mouse_im = (mouse_y - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE + f->shift_y;
    update_zoom(f, ydelta);
    if (f->zoom < 0.1)
        f->max_iter = (int)(100 * (1 / f->zoom) * 0.2);
    else
        f->max_iter = 100;    
    f->max_iter = fmin(f->max_iter, 1000);
    f->shift_x = mouse_re - (mouse_x - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE;
    f->shift_y = mouse_im - (mouse_y - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE;
}
