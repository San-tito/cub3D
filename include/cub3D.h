/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:25 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/06 18:36:08 by droied           ###   ########.fr       */
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
# include "print.h"
# include "render.h"
# include "xmalloc.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define PI 3.141592657

#endif /* CUB3D_H */
