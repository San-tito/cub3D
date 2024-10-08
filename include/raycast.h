/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:54:55 by deordone          #+#    #+#             */
/*   Updated: 2024/09/28 19:26:04 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3D.h"

typedef struct s_ray
{
	t_fvec			dir;
	t_fvec			sidedist;
	t_fvec			deltadist;
	t_ivec			pos;
	t_ivec			step;
	int32_t			side;
}					t_ray;

typedef struct s_wall
{
	double			dist;
	int				height;
	int				start;
	int				end;
	t_ivec			tex;
	mlx_texture_t	*texture;
}					t_wall;

void				raycast(mlx_image_t *image, t_scene scene);

#endif /*  RAYCAST_H */
