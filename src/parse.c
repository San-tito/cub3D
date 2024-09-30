/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/30 18:29:03 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_identifier(char *str)
{
	whitespace(&str);
	return (*str == '\0' || ft_strnstr(str, "NO ", sizeof("NO "))
		|| ft_strnstr(str, "SO ", sizeof("SO ")) || ft_strnstr(str, "WE ",
			sizeof("WE ")) || ft_strnstr(str, "EA ", sizeof("EA "))
		|| ft_strnstr(str, "F ", sizeof("F ")) || ft_strnstr(str, "C ",
			sizeof("C ")));
}

static int	parse_color(int fd, t_scene *scene, char *value, char *line)
{
	int		color[3];
	char	*comma;
	int		i;

	i = 0;
	whitespace(&line);
	while (i < 3)
	{
		if (i < 2)
		{
			comma = ft_strchr(value, ',');
			if (comma == 0)
				parser_error(fd, scene, "invalid color format: %s", line);
			*comma = '\0';
		}
		if (legal_number(value, color + i) == 0 || color[i] < 0
			|| color[i] > 255)
			parser_error(fd, scene, "invalid color value: %s", line);
		if (i < 2)
			value = comma + 1;
		i++;
	}
	return (get_color(color[0], color[1], color[2], 0xFF));
}

static mlx_texture_t	*parse_texture(int fd, t_scene *scene, char *value,
		char *line)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(value);
	if (texture == 0)
		parser_error(fd, scene, "invalid texture: %s", line);
	return (texture);
}

static void	parse_config(int fd, t_scene *scene, char *line)
{
	char	*key;
	char	*value;

	key = line;
	whitespace(&key);
	value = ft_strchr(key, ' ');
	if (value == 0)
		return ;
	*value++ = '\0';
	whitespace(&value);
	if (ft_strncmp(key, "NO", 2) == 0)
		scene->textures.north = parse_texture(fd, scene, value, line);
	else if (ft_strncmp(key, "SO", 2) == 0)
		scene->textures.south = parse_texture(fd, scene, value, line);
	else if (ft_strncmp(key, "WE", 2) == 0)
		scene->textures.west = parse_texture(fd, scene, value, line);
	else if (ft_strncmp(key, "EA", 2) == 0)
		scene->textures.east = parse_texture(fd, scene, value, line);
	else if (ft_strncmp(key, "F", 1) == 0)
		scene->floor_color = parse_color(fd, scene, value, line);
	else if (ft_strncmp(key, "C", 1) == 0)
		scene->ceiling_color = parse_color(fd, scene, value, line);
}

void	parse_scene(int fd, t_scene *scene)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = read_line(fd);
	while (line)
	{
		if (map_started == 0 && is_valid_identifier(line))
			parse_config(fd, scene, line);
		else
		{
			if (map_started == 0)
				map_started++;
			if (is_valid_cells(line) == 0)
				parser_error(fd, scene, "invalid map format: %s", line);
			parse_map(fd, scene, line);
		}
		xfree(line);
		line = read_line(fd);
	}
}
