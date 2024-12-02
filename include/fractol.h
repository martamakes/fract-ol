/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:40:28 by mvigara-          #+#    #+#             */
/*   Updated: 2024/12/02 14:13:53 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>
# include <pthread.h>

#define WIN_WIDTH   800
#define WIN_HEIGHT  600
#define FRACT_SIZE  800

typedef enum 		e_fractal_type
{
	NONE = 0,
	MANDELBROT = 1,
	JULIA = 2, 
	BURNINGSHIP = 3
} 					t_fractal_type;

typedef union 		u_color
{
    uint32_t 		value;
    struct 
	{
        			uint8_t a;
        			uint8_t b; 
        			uint8_t g;
        			uint8_t r;
    } 				rgba;
} 					t_color;

typedef struct s_palette 
{
    int     		count;
    int     		cycle;
    int32_t 		colors[9];
} 					t_palette;

typedef struct s_complex
{
   double  			re;
   double  			im;
}   				t_complex;

typedef struct s_fractol  
{  
    mlx_t           *mlx;  
    mlx_image_t     *img;  
    char            **params;   //**argv  
    t_fractal_type  type;  
    t_complex       c;          // Julia set parameter  
    t_complex       z;          // Current point
    int             x;          // Current pixel x coordinate
    int             y;          // Current pixel y coordinate
    int             iter;       // Current iteration count  
    double          zoom;       // Zoom level  
    double          shift_x;    // Pan position X  
    double          shift_y;    // Pan position Y  
    int             max_iter;   // Maximum iterations  
    int             color_shift;// Color palette rotation
	t_palette		*palette;	//palette actual
	t_palette   	*palettes;  // Array de paletas disponibles
	int         	palette_index;
	int         	palette_len;
	bool        	smooth;     // Suavizado de colores
}   				t_fractol;

// Core functions
bool    			check_args(int argc, char **argv, t_fractol *fractol);
int     			print_usage(void);
void   		 		init_fractol(t_fractol *fractol);
void    			exit_error(t_fractol *f, char *msg);
void				put_pixel_color(t_fractol *f);
void				calculate_mandelbrot(t_fractol *f);
t_palette			*init_palettes(void);
void				render_fractal(t_fractol *f);
void    			handle_keys(mlx_key_data_t keydata, void *param);
void    			handle_scroll(double xdelta, double ydelta, void *param);
void    			main_loop(void *param);
void				calculate_julia(t_fractol *f);
int					palette_len(t_palette *palettes);
t_palette 			*init_palettes(void);
void 				calculate_burning_ship(t_fractol *f);




#endif