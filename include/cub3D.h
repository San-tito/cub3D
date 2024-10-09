/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/10/09 10:12:47 by deordone         ###   ########.fr       */
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

# define DOOR_TEX "textures/42D.png"
# define SPRITE_MAGIC "textures/magic.png"
# define MAX_FRAMES_X 10
# define MAX_FRAMES_Y 5
# define DOOR_TIMER 30
# define ANIMATION_TIMER 24

typedef struct s_core
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}				t_core;

# define PI 3.141592657

#endif /* CUB3D_H */
