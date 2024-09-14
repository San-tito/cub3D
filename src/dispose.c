/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/14 16:36:46 by santito          ###   ########.fr       */
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
	xfree(texture->pixels);
	xfree(texture);
}

void	dispose_core(t_core *core)
{
	if (core == 0)
		return ;
	dispose_texture(core->scene.textures.north);
	dispose_texture(core->scene.textures.south);
	dispose_texture(core->scene.textures.east);
	dispose_texture(core->scene.textures.west);
	dispose_map(&core->scene.map);
	if (core->mlx)
		mlx_terminate(core->mlx);
}
