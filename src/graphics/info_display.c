/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:45:34 by mvigara-          #+#    #+#             */
/*   Updated: 2025/04/19 18:57:23 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Convierte un double a string con notación científica
 */
static char	*ft_dtoa_scientific(double n, int precision)
{
	char	*str;
	int		exponent;
	double	mantissa;
	int		len;

	// Determinar signo
	int sign = (n < 0) ? -1 : 1;
	n = sign * n;
	
	// Encontrar el exponente
	exponent = 0;
	if (n > 0)
	{
		while (n >= 10.0)
		{
			n /= 10.0;
			exponent++;
		}
		while (n < 1.0)
		{
			n *= 10.0;
			exponent--;
		}
	}
	mantissa = sign * n;
	
	// Asignar buffer (tamaño aproximado)
	len = 20; // Suficiente para la mayoría de los casos
	str = (char *)malloc(len);
	if (!str)
		return (NULL);
	
	// Imprimir mantissa
	if (sign < 0)
		str[0] = '-';
	else
		str[0] = ' ';
	
	// Convertir el valor de mantissa a string con precisión dada
	char mantissa_str[10];
	int i = 0;
	int int_part = (int)mantissa;
	double frac_part = mantissa - int_part;
	
	mantissa_str[i++] = int_part + '0';
	mantissa_str[i++] = '.';
	
	// Agregar dígitos de precisión
	for (int j = 0; j < precision; j++)
	{
		frac_part *= 10;
		mantissa_str[i++] = (int)frac_part + '0';
		frac_part -= (int)frac_part;
	}
	mantissa_str[i] = '\0';
	
	// Formatear el string final con mantissa y exponente
	ft_strlcpy(str + (sign < 0 ? 1 : 1), mantissa_str, len - 1);
	
	// Añadir el exponente
	i = ft_strlen(str);
	str[i++] = 'e';
	if (exponent >= 0)
		str[i++] = '+';
	else
	{
		str[i++] = '-';
		exponent = -exponent;
	}
	
	// Convertir exponente a string
	if (exponent >= 10)
	{
		str[i++] = (exponent / 10) + '0';
		str[i++] = (exponent % 10) + '0';
	}
	else
	{
		str[i++] = '0';
		str[i++] = exponent + '0';
	}
	str[i] = '\0';
	
	return (str);
}

/*
 * Convierte el nombre del tipo de fractal a string
 */
static char	*get_fractal_name(t_fractal_type type)
{
	if (type == MANDELBROT)
		return ("Mandelbrot");
	else if (type == JULIA)
		return ("Julia");
	else if (type == BURNINGSHIP)
		return ("Burning Ship");
	else
		return ("Unknown");
}

/*
 * Crea o actualiza la imagen de información
 */
static void	create_info_image(t_fractol *f)
{
	// Si ya existe una imagen de información, eliminarla
	if (f->info_img)
		mlx_delete_image(f->mlx, f->info_img);
	
	// Crear nueva imagen para la información
	f->info_img = mlx_new_image(f->mlx, WIN_WIDTH, 80);
	if (!f->info_img)
		return;
	
	// Fondo semitransparente
	uint32_t bg_color = 0x10101080;
	for (uint32_t y = 0; y < f->info_img->height; y++)
	{
		for (uint32_t x = 0; x < f->info_img->width; x++)
			mlx_put_pixel(f->info_img, x, y, bg_color);
	}
	
	// Mostrar en la ventana
	mlx_image_to_window(f->mlx, f->info_img, 0, 0);
}

/*
 * Actualiza el texto de información 
 */
void	update_info_display(t_fractol *f)
{
	char *zoom_str;
	char iter_str[20];
	char palette_str[20];
	
	// No hacer nada si la info está desactivada
	if (!f->show_info)
		return;
	
	// Crear la imagen si no existe
	if (!f->info_img)
		create_info_image(f);
	
	// Limpiar la imagen anterior
	uint32_t bg_color = 0x10101080;
	for (uint32_t y = 0; y < f->info_img->height; y++)
	{
		for (uint32_t x = 0; x < f->info_img->width; x++)
			mlx_put_pixel(f->info_img, x, y, bg_color);
	}
	
	// Mostrar información del fractal
	mlx_put_string(f->mlx, "Fractal Type:", 10, 10);
	mlx_put_string(f->mlx, get_fractal_name(f->type), 130, 10);
	
	// Zoom con notación científica
	zoom_str = ft_dtoa_scientific(f->zoom, 2);
	if (zoom_str)
	{
		mlx_put_string(f->mlx, "Zoom:", 10, 25);
		mlx_put_string(f->mlx, zoom_str, 130, 25);
		free(zoom_str);
	}
	
	// Iteraciones
	ft_strlcpy(iter_str, "Max Iterations: ", 16);
	ft_strlcat(iter_str, ft_itoa(f->max_iter), 20);
	mlx_put_string(f->mlx, iter_str, 10, 40);
	
	// Posición
	char *x_str = ft_dtoa_scientific(f->shift_x, 4);
	char *y_str = ft_dtoa_scientific(f->shift_y, 4);
	if (x_str && y_str)
	{
		mlx_put_string(f->mlx, "Position: (", 10, 55);
		mlx_put_string(f->mlx, x_str, 100, 55);
		mlx_put_string(f->mlx, ", ", 210, 55);
		mlx_put_string(f->mlx, y_str, 225, 55);
		mlx_put_string(f->mlx, ")", 335, 55);
		free(x_str);
		free(y_str);
	}
	
	// Parámetros Julia
	if (f->type == JULIA)
	{
		char *c_re_str = ft_dtoa_scientific(f->c.re, 4);
		char *c_im_str = ft_dtoa_scientific(f->c.im, 4);
		if (c_re_str && c_im_str)
		{
			mlx_put_string(f->mlx, "Julia C: (", WIN_WIDTH - 250, 10);
			mlx_put_string(f->mlx, c_re_str, WIN_WIDTH - 180, 10);
			mlx_put_string(f->mlx, ", ", WIN_WIDTH - 110, 10);
			mlx_put_string(f->mlx, c_im_str, WIN_WIDTH - 95, 10);
			mlx_put_string(f->mlx, ")", WIN_WIDTH - 25, 10);
			free(c_re_str);
			free(c_im_str);
		}
	}
	
	// Paleta
	ft_strlcpy(palette_str, "Palette: ", 10);
	ft_strlcat(palette_str, ft_itoa(f->palette_index + 1), 15);
	ft_strlcat(palette_str, "/", 16);
	ft_strlcat(palette_str, ft_itoa(f->palette_len), 20);
	mlx_put_string(f->mlx, palette_str, WIN_WIDTH - 250, 25);
	
	// Suavizado
	mlx_put_string(f->mlx, "Smooth: ", WIN_WIDTH - 250, 40);
	mlx_put_string(f->mlx, f->smooth ? "On" : "Off", WIN_WIDTH - 180, 40);
	
	// Instrucciones
	mlx_put_string(f->mlx, "Press I to toggle info | ESC to exit", WIN_WIDTH - 300, 55);
}

/*
 * Activa o desactiva la visualización de información
 */
void	toggle_info_display(t_fractol *f)
{
	f->show_info = !f->show_info;
	
	if (f->show_info)
	{
		if (!f->info_img)
			create_info_image(f);
		update_info_display(f);
	}
	else if (f->info_img)
	{
		mlx_delete_image(f->mlx, f->info_img);
		f->info_img = NULL;
	}
}