/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:31:17 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/20 09:33:42 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void update_iterations(t_fractol *f)
{
    double log_zoom;
    int base_iter;
    
    /* Base de iteraciones según el tipo de fractal */
    if (f->type == BURNINGSHIP)
        base_iter = 50;
    else
        base_iter = 80;
    
    /* Incrementar iteraciones logarítmicamente con el zoom */
    log_zoom = log10(4.0/f->zoom);
    if (log_zoom < 0)
        log_zoom = 0;
    
    /* Fórmula mejorada para calcular iteraciones necesarias */
    f->max_iter = (int)(base_iter + 50.0 * log_zoom * log_zoom);
    
    /* Límites para evitar valores extremos */
    if (f->max_iter < base_iter)
        f->max_iter = base_iter;
    if (f->max_iter > 1000)
        f->max_iter = 1000;
    
    printf("Zoom: %.6f, New iterations: %d\n", f->zoom, f->max_iter);
}

static void update_zoom(t_fractol *f, double ydelta)
{
    double zoom_factor;
    
    /* Factor de zoom más gradual */
    zoom_factor = (ydelta > 0) ? 0.90 : 1.10;
    
    /* Limitar el zoom máximo para evitar problemas de precisión */
    if (ydelta < 0 && f->zoom < 1e-10)
        return;
    
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
    double      old_zoom;
    
    f = (t_fractol *)param;
    (void)xdelta;
    
    /* Guardar el zoom actual antes de actualizarlo */
    old_zoom = f->zoom;
    
    /* Obtener posición del ratón */
    mlx_get_mouse_pos(f->mlx, &mouse_x, &mouse_y);
    
    /* Ajustar la posición del ratón al tamaño de la imagen */
    int offset_x = (WIN_WIDTH - FRACT_SIZE) / 2;
    int offset_y = (WIN_HEIGHT - FRACT_SIZE) / 2;
    
    /* Ajustar coordenadas a la imagen */
    mouse_x -= offset_x;
    mouse_y -= offset_y;
    
    /* Verificar si el ratón está sobre la imagen */
    if (mouse_x < 0 || mouse_x >= FRACT_SIZE || mouse_y < 0 || mouse_y >= FRACT_SIZE)
        return;
    
    /* Debug original de coordenadas */
    printf("Original mouse coords: %d,%d (in %dx%d image)\n", mouse_x, mouse_y, FRACT_SIZE, FRACT_SIZE);
    
    /* Convertir coordenadas de ventana a coordenadas del plano complejo ANTES del zoom */
    mouse_re = (mouse_x - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE + f->shift_x;
    mouse_im = (mouse_y - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE + f->shift_y;
    
    /* Actualizar zoom */
    update_zoom(f, ydelta);
    
    /* Recalcular desplazamiento para mantener el punto bajo el cursor */
    f->shift_x = mouse_re - (mouse_x - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE;
    f->shift_y = mouse_im - (mouse_y - FRACT_SIZE/2.0) * f->zoom / FRACT_SIZE;
    
    /* Mostrar información útil de debug */
    printf("Mouse pos: %d,%d -> %f,%f\n", mouse_x, mouse_y, mouse_re, mouse_im);
    printf("Old zoom: %f, New zoom: %f\n", old_zoom, f->zoom);
    printf("Shift: %f,%f\n", f->shift_x, f->shift_y);
    print_fractal_params(f);
}
