/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/30 18:28:06 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "callback.h"
# include "color.h"
# include "dispose.h"
# include "error.h"
# include "ft_printf.h"
# include "limits.h"
# include "parse.h"
# include "raycast.h"
# include "render.h"
# include "scene.h"
# include "xmalloc.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define FOV 60
# define PROGRAM "cub3D"
# define SPEED 0.1f
# define SENSITIVITY 0.0005f

# define DOOR_TEX "textures/mossy.png"
# define DOOR_TIMER 30

typedef struct s_core
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}				t_core;

# define PI 3.141592657

#endif /* CUB3D_H */
