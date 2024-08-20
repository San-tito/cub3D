/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/20 13:20:44 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(const t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("map:\n");
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_printf("%c", map->cells[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void print_ray(const t_ray *ray)
{
	ft_printf("\n[RAY]\n");
	ft_printf("position: (%d, %d)\n", ray->pos.x, ray->pos.y);
	ft_printf("direction: (%d, %d)\n", ray->dir.x, ray->dir.y);
	ft_printf("sidedist: (%d, %d)\n", ray->sidedist.x, ray->sidedist.y);
	ft_printf("deltadist: (%d, %d)\n", ray->deltadist.x, ray->deltadist.y);
	ft_printf("wall: (%d, %d)\n", ray->wall.x, ray->wall.y);
	ft_printf("step: (%i, %i)\n", ray->step.x, ray->step.y);
	ft_printf("map: (%i, %i)\n", ray->map.x, ray->map.y);

	ft_printf("wall distance: %d\n", ray->wall_dist);
	ft_printf("wall start: %d\n", ray->wall_start);
	ft_printf("wall end: (%d, %d)\n", ray->wall_end);

	ft_printf("camera x: %d\n", ray->cam_x);
	ft_printf("side: %i\n", ray->side);
}

void	print_player(const t_player *player)
{
	ft_printf("player:\n");
	ft_printf("position: (%d, %d)\n", player->pos.x, player->pos.y);
	ft_printf("orientation: %c\n", player->spawn_orient);
}

void	print_textures(const t_textures *textures)
{
	ft_printf("textures:\n");
	ft_printf("north: %s\n", textures->north);
	ft_printf("south: %s\n", textures->south);
	ft_printf("east: %s\n", textures->east);
	ft_printf("west: %s\n", textures->west);
}

void	print_scene(const t_scene *scene)
{
	ft_printf("scene:\n");
	print_map(&scene->map);
	print_player(&scene->player);
	print_textures(&scene->textures);
	ft_printf("refresh: %d\n", scene->refresh);
	ft_printf("floor color: %x\n", scene->floor_color);
	ft_printf("ceiling color: %x\n", scene->ceiling_color);
}
