/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/09/30 17:37:14 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_file_extension(const char *filename, const char *expected)
{
	const char	*ext = ft_strrchr(filename, '.');

	return (ext == 0 || ft_strncmp(ext, expected, ft_strlen(ext)) != 0
		|| ext[ft_strlen(expected)] != 0);
}

void	check_missing(t_scene *scene)
{
	if (scene->textures.north == 0)
		fatal_error(scene, "missing north texture");
	else if (scene->textures.south == 0)
		fatal_error(scene, "missing south texture");
	else if (scene->textures.east == 0)
		fatal_error(scene, "missing east texture");
	else if (scene->textures.west == 0)
		fatal_error(scene, "missing west texture");
	else if (scene->floor_color == 0)
		fatal_error(scene, "missing floor color");
	else if (scene->ceiling_color == 0)
		fatal_error(scene, "missing ceiling color");
	else if ((int)scene->player.pos.x < 0)
		fatal_error(scene, "missing player");
}

void	init_scene(t_scene *scene)
{
	scene->refresh = 1;
	scene->player.dir.x = 1;
	scene->player.plane.y = tan((FOV * (PI / 180.0)) / 2);
	if (scene->player.spawn_orient == WEST)
		rotate(scene, PI);
	if (scene->player.spawn_orient == SOUTH)
		rotate(scene, PI * 0.5);
	if (scene->player.spawn_orient == NORTH)
		rotate(scene, PI * 1.5);
	scene->textures.door = mlx_load_png(DOOR_TEX);
	place_doors(&scene->map);
}

t_scene	create_scene(int argc, char **argv)
{
	t_scene	scene;
	int		fd;

	scene = (t_scene){};
	if (argc != 2)
		fatal_error(&scene, "usage: %s <map_file>", *argv);
	if (check_file_extension(*(argv + 1), ".cub"))
		fatal_error(&scene, "file must have a .cub extension: %s", *(argv + 1));
	fd = open(*(argv + 1), O_RDONLY, 0666);
	if (fd < 0)
		sys_error("%s", *(argv + 1));
	scene.player.pos.x = (float)(-1);
	parse_scene(fd, &scene);
	close(fd);
	check_missing(&scene);
	if (validate_map(&scene.map, scene.player.pos.x, scene.player.pos.y) == 0)
		fatal_error(&scene, "the map is not closed/surrounded by walls");
	init_scene(&scene);
	return (scene);
}
