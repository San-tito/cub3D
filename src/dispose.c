/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/10/11 15:41:24 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dispose_map(t_map *map)
{
	int	i;

	if (map)
	{
		i = 0;
		while (i < map->rows)
			xfree(map->cells[i++]);
		xfree(map->cells);
	}
}

void	dispose_texture(mlx_texture_t *texture)
{
	if (texture == 0)
		return ;
	mlx_delete_texture(texture);
}

void	dispose_mlx(mlx_t *mlx)
{
	if (mlx == 0)
		return ;
	mlx_terminate(mlx);
}

void	dispose_scene(t_scene *scene)
{
	if (scene == 0)
		return ;
	dispose_texture(scene->textures.north);
	dispose_texture(scene->textures.south);
	dispose_texture(scene->textures.east);
	dispose_texture(scene->textures.west);
	dispose_texture(scene->textures.door);
	dispose_texture(scene->a.tex);
	dispose_map(&scene->map);
}
