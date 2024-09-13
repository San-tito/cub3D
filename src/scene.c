/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/09/13 15:00:41 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "print.h"
#include <stdio.h>

int	check_file_extension(const char *filename, const char *expected)
{
	const char	*ext = ft_strrchr(filename, '.');

	return (ext == 0 || ft_strncmp(ext, expected, ft_strlen(ext)) != 0
		|| ext[ft_strlen(expected)] != 0);
}

t_scene	create_scene(int argc, char **argv)
{
	t_scene	scene;
	int		fd;

	scene = (t_scene){};
	if (argc != 2)
		fatal_error("usage: %s <map_file>", *argv);
	if (check_file_extension(*(argv + 1), ".cub"))
		fatal_error("file must have a .cub extension: %s", *(argv + 1));
	fd = open(*(argv + 1), O_RDONLY, 0666);
	if (fd < 0)
		sys_error("%s", *(argv + 1));
	scene.refresh = 1;
	parse_scene(fd, &scene);
	close(fd);
	print_scene(&scene);
	 if (validate_map(&scene) == 0)
		 fatal_error("the map is not closed/surrounded by walls");
	scene.player.dir.x = -1;//(scene.player.spawn_orient == EAST)
		//+ ((scene.player.spawn_orient == WEST) * -1);
	scene.player.dir.y = 0;//(scene.player.spawn_orient == SOUTH)
		//+ ((scene.player.spawn_orient == NORTH) * -1);
	scene.player.plane.x = 0;//scene.player.dir.x * tan(FOV_RAD / 2);
	scene.player.plane.y = 0.66;//scene.player.dir.y * tan(FOV_RAD / 2);
	return (scene);
}
