/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/22 19:13:15 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(const t_map *map)
{
	int	i;
	int	j;

	i = 0;
	printf("┌──────────────────────MAP──────────────────────┐\n");
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
	printf("└───────────────────────────────────────────────┘\n");
}

void	print_ray(const t_ray *ray)
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
	printf("┌─────PLAYER─────┐\n");
	printf("position: (%d, %d)\n", (int)player->pos.x, (int)player->pos.y);
	printf("direction: (%d, %d)\n", (int)player->dir.x, (int)player->dir.y);
	printf("orientation: %c\n", player->spawn_orient);
	printf("└────────────────┘\n");
}

void	print_textures(const t_textures *textures)
{
	printf("┌─────TEXTURES─────┐\n");
	printf("north: %p\n", textures->north->pixels);
	printf("south: %p\n", textures->south->pixels);
	printf("east: %p\n", textures->east->pixels);
	printf("west: %p\n", textures->west->pixels);
	printf("└──────────────────┘\n");
}

void	print_scene(const t_scene *scene)
{
	print_map(&scene->map);
	print_player(&scene->player);
	print_textures(&scene->textures);
	printf("┌─────COLORS─────┐\n");
	printf("floor color: %X\n", scene->floor_color);
	printf("ceiling color: %X\n", scene->ceiling_color);
	printf("└────────────────┘\n");
}
