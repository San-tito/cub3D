/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:18:44 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/21 19:44:00 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef void	(*t_funori)(t_player *, int32_t);

static void north_south( t_player *player, int32_t i)
{
	if (i == 0)
	{	
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (i == 1)
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
}


static void west_east( t_player *player, int32_t i)
{
	if (i == 2)
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else if (i == 3)
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
}

void set_player(mlx_image_t *img, t_scene *scene)
{
	t_funori	orientation[] = { &north_south, &west_east};
	t_orient	ori[4] = { NORTH, SOUTH, WEST, EAST};
	int32_t i;

	i = 0;
	scene->scale.x = img->width / scene->map.cols; 
	scene->scale.y = img->height / scene->map.rows; 
	while (i < 4 && ori[i] != scene->player.spawn_orient)
		i++;
	if (i < 2)
		(orientation[0])(&scene->player, i);
	else if (i < 4)
		(orientation[1])(&scene->player, i);
	scene->player.rotate = 0;
	scene->player.move.x = 0;
	scene->player.move.y = 0;
	scene->player.pos.x = (int)scene->player.pos.x * scene->scale.x;
	scene->player.pos.y = (int)scene->player.pos.y * scene->scale.y;
}
