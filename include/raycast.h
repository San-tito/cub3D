/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:54:55 by deordone          #+#    #+#             */
/*   Updated: 2024/09/13 09:11:57 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3D.h"

typedef struct s_ray
{
	t_fvec	dir;
	t_fvec	sidedist;
	t_fvec	deltadist;
	t_ivec	pos;
	t_ivec	step;

	float	wall_dist;
	float	wall_start;
	float	wall_end;
	float	wall_height;
	int32_t	side;
}			t_ray;

typedef struct s_wall
{
	float	dist;
	int		height;
	int		start;
	int		end;
	int		color;
}			t_wall;

void		raycast(mlx_image_t *image, t_scene scene);

#endif /*  RAYCAST_H */
