/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/13 09:14:42 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(const t_map *map)
{
	int	i;
	int	j;

	i = 0;
	printf("map:\n");
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			printf("%c", map->cells[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("column: %d\n", map->cols);
	printf("row: %d\n", map->rows);
}

void print_ray(const t_ray *ray)
{
	printf("\n[RAY]\n");
	printf("pos: (%i, %i)\n", ray->pos.x, ray->pos.y);
	printf("direction: (%f, %f)\n", ray->dir.x, ray->dir.y);
	printf("sidedist: (%f, %f)\n", ray->sidedist.x, ray->sidedist.y);
	printf("deltadist: (%f, %f)\n", ray->deltadist.x, ray->deltadist.y);
	printf("step: (%i, %i)\n", ray->step.x, ray->step.y);

	printf("wall distance: %f\n", ray->wall_dist);
	printf("wall start: %f\n", ray->wall_start);
	printf("wall end: %f\n", ray->wall_end);

	printf("side: %i\n", ray->side);
}

void	print_player(const t_player *player)
{
	printf("player:\n");
	printf("position: (%d, %d)\n", (int)player->pos.x, (int)player->pos.y);
	printf("orientation: %c\n", player->spawn_orient);
}

void	print_textures(const t_textures *textures)
{
	printf("textures:\n");
	printf("north: %s\n", textures->north);
	printf("south: %s\n", textures->south);
	printf("east: %s\n", textures->east);
	printf("west: %s\n", textures->west);
}

void	print_scene(const t_scene *scene)
{
	printf("scene:\n");
	print_map(&scene->map);
	print_player(&scene->player);
	print_textures(&scene->textures);
	printf("refresh: %d\n", scene->refresh);
	printf("floor color: %x\n", scene->floor_color);
	printf("ceiling color: %x\n", scene->ceiling_color);
}
