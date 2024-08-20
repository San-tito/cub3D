/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:54:55 by deordone          #+#    #+#             */
/*   Updated: 2024/08/20 12:57:31 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3D.h"

typedef struct s_ray
{
	t_fvec	pos;
	t_fvec	dir;
	t_fvec	sidedist;
	t_fvec	deltadist;
	t_fvec	wall;
	t_ivec	step;
	t_ivec	map;

	float	cam_x;
	float	wall_dist;
	float	wall_start;
	float	wall_end;
	int32_t	side;
} t_ray ;

void	raycast(mlx_image_t *image, t_scene scene);

#endif /*  RAYCAST_H */
