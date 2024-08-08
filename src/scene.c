/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/08/08 15:50:10 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_extension(const char *filename, const char *expected)
{
	const char	*ext = ft_strrchr(filename, '.');

	return (ext == 0 || ft_strncmp(ext, expected, ft_strlen(ext)) != 0
		|| ext[ft_strlen(expected)] != 0);
}

static void parse_player(t_scene *scene)
{
	scene->player.p.a = 0;
	/* luego hay que setear la posicion del player dependiendo del mapa
	 scene.player.p.x = core.img->width / 2;
	scene.player.p.y = core.img->height / 2;*/
	scene->player.p.x = 1000;
	scene->player.p.y = 1000;
	scene->player.p.dx = cos(scene->player.p.a) * 5;
	scene->player.p.dy = sin(scene->player.p.a) * 5;

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
	scene.refresh = 1;
	scene.map.rows = 0;
	scene.map.cols = 0;
	parse_scene(fd, &scene);
	parse_player(&scene);
	print_scene(&scene);
	if (validate_map(&scene) == 0)
		fatal_error("the map is not closed/surrounded by walls");
	close(fd);
	return (scene);
}
