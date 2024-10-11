/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/10/11 12:30:51 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(const t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("┌──────────────────────MAP──────────────────────┐\n");
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
	ft_printf("column: %d\n", map->cols);
	ft_printf("row: %d\n", map->rows);
	ft_printf("└───────────────────────────────────────────────┘\n");
}

void	print_ray(const t_ray *ray)
{
	ft_printf("\n[RAY]\n");
	ft_printf("pos: (%i, %i)\n", ray->pos.x, ray->pos.y);
	ft_printf("direction: (%f, %f)\n", ray->dir.x, ray->dir.y);
	ft_printf("sidedist: (%f, %f)\n", ray->sidedist.x, ray->sidedist.y);
	ft_printf("deltadist: (%f, %f)\n", ray->deltadist.x, ray->deltadist.y);
	ft_printf("step: (%i, %i)\n", ray->step.x, ray->step.y);
	ft_printf("side: %i\n", ray->side);
}

void	print_player(const t_player *player)
{
	ft_printf("┌─────PLAYER─────┐\n");
	ft_printf("position: (%d, %d)\n", (int)player->pos.x, (int)player->pos.y);
	ft_printf("direction: (%d, %d)\n", (int)player->dir.x, (int)player->dir.y);
	ft_printf("orientation: %c\n", player->spawn_orient);
	ft_printf("└────────────────┘\n");
}

void	print_textures(const t_textures *textures)
{
	ft_printf("┌─────TEXTURES─────┐\n");
	ft_printf("north: %p\n", textures->north->pixels);
	ft_printf("south: %p\n", textures->south->pixels);
	ft_printf("east: %p\n", textures->east->pixels);
	ft_printf("west: %p\n", textures->west->pixels);
	ft_printf("└──────────────────┘\n");
}

void	print_scene(const t_scene *scene)
{
	print_map(&scene->map);
	print_player(&scene->player);
	print_textures(&scene->textures);
	ft_printf("┌─────COLORS─────┐\n");
	ft_printf("floor color: %X\n", scene->floor_color);
	ft_printf("ceiling color: %X\n", scene->ceiling_color);
	ft_printf("└────────────────┘\n");
}
