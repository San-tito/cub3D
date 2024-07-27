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

static int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (ft_isspace(*line) == 0)
			return (0);
		line++;
	}
	return (1);
}

static int	is_valid_identifier(const char *str)
{
	return (ft_strnstr(str, "NO ", sizeof("NO ")) || ft_strnstr(str, "SO ",
			sizeof("SO ")) || ft_strnstr(str, "WE ", sizeof("WE "))
		|| ft_strnstr(str, "EA ", sizeof("EA ")) || *str == 'F' || *str == 'C');
}

static int	parse_color(int lineno, char *value, char *line)
{
	char	*comma;
	int		r;
	int		g;
	int		b;

	whitespace(&line);
	comma = ft_strchr(value, ',');
	if (comma == 0)
		parser_error(lineno, line, "invalid color format: %s", value);
	value[comma - value] = 0;
	if (legal_number(value, &r) == 0 || r < 0 || r > 255)
		parser_error(lineno, line, "invalid red color value: %s", value);
	value += comma - value + 1;
	comma = ft_strchr(value, ',');
	if (comma == 0)
		parser_error(lineno, line, "invalid color format: %s", value);
	value[comma - value] = 0;
	if (legal_number(value, &g) == 0 || g < 0 || g > 255)
		parser_error(lineno, line, "invalid green color value: %s", value);
	value += comma - value + 1;
	if (legal_number(value, &b) == 0 || b < 0 || b > 255)
		parser_error(lineno, line, "invalid blue color value: %s", value);
	return (r << 24 | g << 16 | b << 8 | 255);
}

static void	parse_config(t_scene *scene, int lineno, char *line)
{
	char	*key;
	char	*value;

	key = line;
	whitespace(&key);
	value = ft_strchr(key, ' ');
	if (!value)
		parser_error(lineno, line, "invalid configuration line: %s", line);
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
		scene->floor_color = parse_color(lineno, value, line);
	else if (ft_strncmp(key, "C", 1) == 0)
		scene->ceiling_color = parse_color(lineno, value, line);
}

void	parse_scene(int fd, t_scene *scene)
{
	char	*line;
	int		lineno;
	int		map_started;

	lineno = 0;
	map_started = 0;
	line = read_line(fd);
	while (line)
	{
		if (is_empty_line(line) == 0)
		{
			if (map_started == 0 && is_valid_identifier(line))
				parse_config(scene, lineno, line);
			else
			{
				if (map_started == 0)
					map_started++;
				// parse_map(scene, line, row++);
			}
		}
		lineno++;
		xfree(line);
		line = read_line(fd);
	}
}
