/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/12 18:03:36 by droied           ###   ########.fr       */
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
