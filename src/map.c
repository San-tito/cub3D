/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:21:05 by droied            #+#    #+#             */
/*   Updated: 2024/09/22 20:13:32 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_cells(char *line)
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

static int	flood_fill(t_map *map, int **visited, int x, int y)
{
	if ((x >= 0 && x < map->cols && y >= 0 && y < map->rows) == 0
		|| visited[y][x])
		return (1);
	if (map->cells[y][x] == WALL)
		return (1);
	if (x == 0 || x == map->cols - 1 || y == 0 || y == map->rows - 1)
		return (0);
	visited[y][x] = 1;
	if (flood_fill(map, visited, x + 1, y) == 0)
		return (0);
	if (flood_fill(map, visited, x - 1, y) == 0)
		return (0);
	if (flood_fill(map, visited, x, y + 1) == 0)
		return (0);
	if (flood_fill(map, visited, x, y - 1) == 0)
		return (0);
	return (1);
}

int	validate_map(t_scene *scene)
{
	int	**visited;
	int	is_closed;
	int	i;
	int	j;

	visited = xmalloc(scene->map.rows * sizeof(int *));
	i = 0;
	while (i < scene->map.rows)
	{
		visited[i] = xmalloc(scene->map.cols * sizeof(int));
		j = 0;
		while (j < scene->map.cols)
			visited[i][j++] = 0;
		i++;
	}
	is_closed = flood_fill(&scene->map, visited, scene->player.pos.x,
			scene->player.pos.y);
	i = 0;
	while (i < scene->map.rows)
		xfree(visited[i++]);
	xfree(visited);
	return (is_closed);
}

static void	resize_map(t_scene *scene, int new_cols)
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
			ft_memset(scene->map.cells[row] + scene->map.cols, SPACE, (new_cols
					- scene->map.cols) * sizeof(t_cell));
			row++;
		}
		scene->map.cols = new_cols;
	}
	scene->map.cells = xrealloc(scene->map.cells, scene->map.rows
			* sizeof(t_cell *), (scene->map.rows + 1) * sizeof(t_cell *));
	scene->map.cells[scene->map.rows] = xmalloc(scene->map.cols
			* sizeof(t_cell));
	ft_memset(scene->map.cells[scene->map.rows], SPACE, scene->map.cols
		* sizeof(t_cell));
	scene->map.rows++;
}

void	parse_map(int fd, t_scene *scene, char *line)
{
	char		c;
	int			i;
	const int	len = ft_strlen(line);

	resize_map(scene, len);
	i = 0;
	while (i < len)
	{
		c = line[i];
		if (c == SPACE || c == WALL)
			scene->map.cells[scene->map.rows - 1][i] = c;
		else if (ft_isspace(c))
			scene->map.cells[scene->map.rows - 1][i] = SPACE;
		else if (c == NORTH || c == SOUTH || c == EAST || c == WEST)
		{
			if ((int)scene->player.pos.x >= 0)
				parser_error(fd, scene, "multiple players detected", line);
			scene->player.pos.x = i + 0.5;
			scene->player.pos.y = scene->map.rows - 0.5;
			scene->player.spawn_orient = c;
			scene->map.cells[scene->map.rows - 1][i] = SPACE;
		}
		i++;
	}
}
