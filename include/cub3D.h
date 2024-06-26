/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/26 02:21:00 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/************PROGRAM***********/

# define PROGRAM "cub3D"

/*____________________________*/

/***********INCLUDES***********/

# include "MLX42/MLX42.h"
# include "color.h"
# include "error.h"
# include "ft_printf.h"
# include "scene.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_core
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}				t_core;

/*WINDOW*/
# define PT_PRUEBA "./assets/circle.png"
# define WIDTH 1280
# define HEIGHT 720

/*ANGLES*/

# define ANGLES 360 /* must be divisable by 4*/
# define ANGLEQUAD 90
# define FINEANGLES 3600
# define ANG90 900
# define ANG180 1800
# define ANG270 2700
# define ANG360 3600
# define VANG90 90
# define VANG180 180
# define VANG270 270
# define VANG360 360

/*____________________________*/

# define PI 3.141592657

void			rendering_setup(t_core core);
void			draw_minimap(t_core core);
void			ft_hook(void *param);
void			draw_character(t_core core, t_vec3 c, int base);

#endif /* CUB3D_H */
