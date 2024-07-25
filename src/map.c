/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 02:42:37 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_extension(const char *filename, const char *expected)
{
	const char	*ext = ft_strrchr(filename, '.');

	return (ext == 0 || ft_strncmp(ext, expected, ft_strlen(ext)) != 0
		|| ext[ft_strlen(expected)] != 0);
}

int	parse_color(char *line, int lineno)
{
	char	**components;
	int		r;
	int		g;
	int		b;

	components = ft_split(line, ',');
	if (*components == 0 || *(components + 1) == 0 || *(components + 2) == 0)
		parser_error(lineno, "invalid color format");
	if (legal_number(*components, &r) == 0 || r < 0 || r > 255)
		parser_error(lineno, "invalid red component");
	if (legal_number(*(components + 1), &g) == 0 || g < 0 || g > 255)
		parser_error(lineno, "invalid green component");
	if (legal_number(*(components + 2), &b) == 0 || b < 0 || b > 255)
		parser_error(lineno, "invalid blue component");
	xfree(components);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

void	parse_config(t_scene *scene, char *line, int lineno)
{
	char	**parts;
	char	*key;
	char	*value;

	parts = ft_split(line, ' ');
	if (*parts == 0 || *(parts + 1) == 0)
		parser_error(lineno, "invalid configuration");
	key = *parts;
	value = *(parts + 1);
	if (ft_strncmp(key, "NO", sizeof("NO")) == 0)
		scene->textures.north = value;
	else if (strcmp(key, "SO") == 0)
		scene->textures.south = value;
	else if (strcmp(key, "WE") == 0)
		scene->textures.west = value;
	else if (strcmp(key, "EA") == 0)
		scene->textures.east = value;
	else if (strcmp(key, "F") == 0)
		scene->floor_color = parse_color(value, lineno);
	else if (strcmp(key, "C") == 0)
		scene->roof_color = parse_color(value, lineno);
	else
		parser_error(lineno, "unknown configuration key: %s", key);
	xfree(parts);
}

void	parse_cub(t_scene *scene, int fd)
{
	char	*line;
	int		lineno;

	lineno = 0;
	line = read_line(fd);
	while (line)
	{
		if (ft_strnstr(line, "NO ", sizeof("NO ")) || ft_strnstr(line, "SO ",
				sizeof("SO ")) || ft_strnstr(line, "WE ", sizeof("WE "))
			|| ft_strnstr(line, "EA ", sizeof("EA ")) || *line == 'F'
			|| *line == 'C')
			parse_config(scene, line, lineno);
		// else
		//	parse_map_line(scene, line, lineno);
		lineno++;
		xfree(line);
		line = read_line(fd);
	}
}

t_scene	create_scene(int argc, char **argv)
{
	t_scene	scene;
	int		fd;

	if (argc != 2)
		fatal_error("usage: %s <map_file>", *argv);
	if (check_file_extension(*(argv + 1), ".cub"))
		fatal_error("file must have a .cub extension: %s", *(argv + 1));
	fd = open(*(argv + 1), O_RDONLY, 0666);
	if (fd < 0)
		sys_error("%s", *(argv + 1));
	parse_cub(&scene, fd);
	close(fd);
	scene.refresh = 1;
	return (scene);
}
