/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/19 21:13:54 by sguzman          ###   ########.fr       */
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
# include "ft_printf.h"
# include "map.h"
# include "player.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/*____________________________*/

/************MAP***************/

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

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

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	ft_hook(void *param);

int		check_map(int ac, char **av);

#endif /* CUB3D_H */
