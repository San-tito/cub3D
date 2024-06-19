/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/19 22:08:39 by sguzman          ###   ########.fr       */
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
# include "map.h"
# include "player.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/*____________________________*/

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_map		map;
	/* textures[4] textures for the four walls (N, S, E, W) */
	/* Floor color */
	/* Ceiling color */
}				t_game;

/*WINDOW*/

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

void			rendering_setup(t_game game);

#endif /* CUB3D_H */
