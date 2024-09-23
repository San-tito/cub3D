/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/09/23 13:08:21 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "print.h"
#include <stdio.h>

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

void	init_scene(t_scene *scene, mlx_image_t *image)
{
	scene->refresh = 1;
	scene->player.dir.x = 1;
	scene->player.plane.y = tan(FOV_RAD / 2);
	if (scene->player.spawn_orient == WEST)
		rotate(scene, PI);
	if (scene->player.spawn_orient == SOUTH)
		rotate(scene, PI * 0.5);
	if (scene->player.spawn_orient == NORTH)
		rotate(scene, PI * 1.5);
	scene->minimap.pos.x = (image->width >> 4);
	scene->minimap.pos.y = (image->height >> 3);
	scene->minimap.radius = (scene->minimap.pos.x + scene->minimap.pos.y) >> 1;
	scene->minimap.player.x = scene->minimap.pos.x + scene->minimap.radius; 
	scene->minimap.player.y = scene->minimap.pos.y + scene->minimap.radius; 
	float zoom = 3.0;
	scene->minimap.scale.x = (float)(scene->map.cols) / (scene->minimap.radius << 1)/zoom;
    scene->minimap.scale.y = (float)(scene->map.rows) / (scene->minimap.radius << 1)/zoom;
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
	scene.player.pos.x = (float)(unsigned)~0;
	parse_scene(fd, &scene);
	close(fd);
	check_missing(&scene);
	if (validate_map(&scene) == 0)
		fatal_error(&scene, "the map is not closed/surrounded by walls");
	return (scene);
}
