/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/23 11:02:44 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	place_doors(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->rows)
	{
		col = 1;
		while (col < map->cols - 1)
		{
			if (map->cells[row][col] == WALL && map->cells[row][col
				- 1] == SPACE && map->cells[row][col + 1] == SPACE)
			{
				map->cells[row][col] = DOOR_CLOSED;
				break ;
			}
			col++;
		}
		row++;
	}
}
