/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/09/14 16:01:39 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_extension(const char *filename, const char *expected)
{
	const char	*ext = ft_strrchr(filename, '.');

	return (ext == 0 || ft_strncmp(ext, expected, ft_strlen(ext)) != 0
		|| ext[ft_strlen(expected)] != 0);
}

static void	init_player(t_scene *scene)
{
	scene->player.dir.x = 1;
	scene->player.plane.y = tan(FOV_RAD / 2);
	if (scene->player.spawn_orient == NORTH)
		rotate(scene, 3 * PI / 2);
	if (scene->player.spawn_orient == SOUTH)
		rotate(scene, PI / 2);
	if (scene->player.spawn_orient == WEST)
		rotate(scene, PI);
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
	if (validate_map(&scene) == 0)
		fatal_error("the map is not closed/surrounded by walls");
	init_player(&scene);
	return (scene);
}
