/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/30 18:49:16 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_door_position(t_cell **cells, int row, int col)
{
	int	is_corner_door;
	int	is_horizontal_door;
	int	is_vertical_door;

	is_corner_door = (cells[row - 1][col - 1] == DOOR_CLOSED || cells[row
			- 1][col + 1] == DOOR_CLOSED || cells[row + 1][col
			- 1] == DOOR_CLOSED || cells[row + 1][col + 1] == DOOR_CLOSED);
	is_horizontal_door = (cells[row][col + 1] == SPACE && cells[row][col
			- 1] == SPACE && cells[row + 1][col] == WALL && cells[row
			- 1][col] == WALL);
	is_vertical_door = (cells[row][col + 1] == WALL && cells[row][col
			- 1] == WALL && cells[row + 1][col] == SPACE && cells[row
			- 1][col] == SPACE);
	return ((is_horizontal_door || is_vertical_door) && is_corner_door == 0);
}

void	place_doors(t_map *map)
{
	int	row;
	int	col;
	int	valid;

	row = 1;
	while (row < map->rows - 1)
	{
		col = 1;
		while (col < map->cols - 1)
		{
			if (map->cells[row][col] == WALL)
			{
				map->cells[row][col] = DOOR_CLOSED;
				valid = validate_map(map, col, row);
				map->cells[row][col] = WALL;
				if (valid && is_valid_door_position(map->cells, row, col))
					map->cells[row][col] = DOOR_CLOSED;
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

	row = 1;
	while (row < map->rows - 1)
	{
		col = 1;
		while (col < map->cols - 1)
		{
			cell = &map->cells[row][col];
			progress = frame_count % DOOR_TIMER;
			if (*cell == DOOR_OPENING && progress >= DOOR_TIMER - 1)
				*cell = DOOR_OPEN;
			else if (*cell == DOOR_CLOSING && progress >= DOOR_TIMER - 1)
				*cell = DOOR_CLOSED;
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
