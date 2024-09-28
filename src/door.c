/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/28 14:15:35 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	place_doors(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->rows - 1)
	{
		col = 1;
		while (col < map->cols - 1)
		{
			if ((map->cells[row][col] == WALL && map->cells[row][col
					- 1] == SPACE && map->cells[row][col + 1] == SPACE
					&& map->cells[row + 1][col] == WALL && map->cells[row
					- 1][col] == WALL))
			{
				map->cells[row][col] = DOOR_CLOSED;
				break ;
			}
			col++;
		}
		row++;
	}
}

void	update_doors(t_map *map, int frame_count)
{
	int		row;
	int		col;
	t_cell	*cell;
	int		progress;

	row = 0;
	while (row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			cell = &map->cells[row][col];
			if (*cell == DOOR_OPENING)
			{
				progress = frame_count % DOOR_TIMER;
				if (progress >= DOOR_TIMER - 1)
					*cell = DOOR_OPEN;
			}
			else if (*cell == DOOR_CLOSING)
			{
				progress = frame_count % DOOR_TIMER;
				if (progress >= DOOR_TIMER - 1)
					*cell = DOOR_CLOSED;
			}
			col++;
		}
		row++;
	}
}

void	interact_with_door(t_map *map, t_fvec player_pos, t_fvec player_dir)
{
	t_cell	*cell;

	cell = &map->cells[(int)(player_pos.y + player_dir.y)][(int)(player_pos.x
			+ player_dir.x)];
	if (*cell == DOOR_CLOSED)
		*cell = DOOR_OPENING;
	else if (*cell == DOOR_OPEN)
		*cell = DOOR_CLOSING;
}
