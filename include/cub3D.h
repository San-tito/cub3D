/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/20 13:06:41 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PROGRAM "cub3D"

# include "MLX42/MLX42.h"
# include "scene.h"

typedef struct s_core
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}				t_core;

# include "callback.h"
# include "dispose.h"
# include "error.h"
# include "ft_printf.h"
# include "limits.h"
# include "parse.h"
# include "render.h"
# include "xmalloc.h"
# include "raycast.h"
# include "print.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define PI 3.141592657
# define PI2 PI/2
# define PI3 3*PI/2

#endif /* CUB3D_H */
