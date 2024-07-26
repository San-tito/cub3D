/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/30 14:20:19 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_color(int lineno, char *line)
{
	char	*comma;
	int		r;
	int		g;
	int		b;

	whitespace(&line);
	comma = ft_strchr(line, ',');
	if (comma == 0)
		parser_error(lineno, "invalid color format");
	line[comma - line] = 0;
	if (legal_number(line, &r) == 0 || r < 0 || r > 255)
		parser_error(lineno, "Invalid red color value: %s", line);
	line += comma - line + 1;
	comma = ft_strchr(line, ',');
	if (comma == 0)
		parser_error(lineno, "invalid color format");
	line[comma - line] = 0;
	if (legal_number(line, &g) == 0 || g < 0 || g > 255)
		parser_error(lineno, "Invalid green color value: %s", line);
	line += comma - line + 1;
	if (legal_number(line, &b) == 0 || b < 0 || b > 255)
		parser_error(lineno, "Invalid blue color value: %s", line);
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	parse_config(t_scene *scene, int lineno, char *line)
{
	char	*key;
	char	*value;

	key = line;
	whitespace(&key);
	value = ft_strchr(key, ' ');
	if (!value)
		parser_error(lineno, "invalid configuration line: %s", line);
	*value++ = '\0';
	whitespace(&value);
	if (ft_strncmp(key, "NO", 2) == 0)
		scene->textures.north = value;
	else if (ft_strncmp(key, "SO", 2) == 0)
		scene->textures.south = value;
	else if (ft_strncmp(key, "WE", 2) == 0)
		scene->textures.west = value;
	else if (ft_strncmp(key, "EA", 2) == 0)
		scene->textures.east = value;
	else if (ft_strncmp(key, "F", 1) == 0)
		scene->floor_color = parse_color(lineno, value);
	else if (ft_strncmp(key, "C", 1) == 0)
		scene->ceiling_color = parse_color(lineno, value);
}

void	parse_scene(int fd, t_scene *scene)
{
	char	*line;
	int		lineno;

	lineno = 0;
	line = read_line(fd);
	while (line)
	{
		if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
			|| ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3)
			|| *line == 'F' || *line == 'C')
			parse_config(scene, lineno, line);
		// else
		//	parse_map_line(scene, line, lineno);
		xfree(line);
		lineno++;
		line = read_line(fd);
	}
}
