/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/06/19 22:18:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_file_extension(const char *filename, const char *expected)
{
	const char	*ext = ft_strrchr(filename, '.');

	if (ext == 0 || ft_strncmp(ext, expected, ft_strlen(ext)) != 0
		|| ext[ft_strlen(expected)] != 0)
		fatal_error("file must have a %s extension: %s", expected, filename);
}

t_map	load_map(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		fatal_error("usage: %s <map_file>", *argv);
	check_file_extension(*(argv + 1), ".cub");
	map = (t_map){};
	return (map);
}
