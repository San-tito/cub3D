/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:21:05 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 18:55:06 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_cells(char *line)
{
	whitespace(&line);
	if (*line == 0)
		return (0);
	while (*line)
	{
		if ((*line == '0' || *line == '1' || *line == 'N' || *line == 'S'
				|| *line == 'E' || *line == 'W' || *line == ' ') == 0)
			return (0);
		line++;
	}
	return (1);
}

void	resize_map(t_scene *scene, int new_cols)
{
	int	row;

	if (new_cols > scene->map.cols)
	{
		row = 0;
		while (row < scene->map.rows)
		{
			scene->map.cells[row] = xrealloc(scene->map.cells[row],
					scene->map.cols * sizeof(t_cell), new_cols
					* sizeof(t_cell));
			memset(scene->map.cells[row] + scene->map.cols, SPACE, (new_cols
					- scene->map.cols) * sizeof(t_cell));
			row++;
		}
		scene->map.cols = new_cols;
	}
	if (scene->map.rows == 0)
	{
		scene->map.cells = (t_cell **)xmalloc(sizeof(t_cell *));
		scene->map.cells[0] = (t_cell *)xmalloc(new_cols * sizeof(t_cell));
		memset(scene->map.cells[0], SPACE, new_cols * sizeof(t_cell));
		scene->map.rows = 1;
	}
	else
	{
		scene->map.cells = xrealloc(scene->map.cells, scene->map.rows
				* sizeof(t_cell *), (scene->map.rows + 1) * sizeof(t_cell *));
		scene->map.cells[scene->map.rows] = (t_cell *)xmalloc(new_cols
				* sizeof(t_cell));
		memset(scene->map.cells[scene->map.rows], SPACE, new_cols
			* sizeof(t_cell));
		scene->map.rows++;
	}
}

void	parse_map(t_scene *scene, int lineno, char *line)
{
	char		c;
	int			i;
	const int	len = ft_strlen(line);

	if (is_valid_cells(line) == 0)
		parser_error(lineno, line, "invalid map format: %s", line);
	resize_map(scene, len);
	i = 0;
	while (i < len)
	{
		c = line[i];
		if (c == SPACE || c == WALL)
			scene->map.cells[scene->map.rows - 1][i] = c;
		else if (c == ' ')
			scene->map.cells[scene->map.rows - 1][i] = SPACE;
		else if (c == NORTH || c == SOUTH || c == EAST || c == WEST)
		{
			scene->player.pos.x = i;
			scene->player.pos.y = scene->map.rows - 1;
			scene->player.spawn_orient = c;
		}
		i++;
	}
}
