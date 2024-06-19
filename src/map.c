/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:30:43 by droied            #+#    #+#             */
/*   Updated: 2024/06/19 20:13:53 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while (s1[++i] != '\0' && s2[i] != '\0' && n > i)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int check_map(int ac, char **av)
{
	int l_mapath;

	if (ac != 2)
	{
		printf(RED "cub3D: Invalid Number Of Arguments\n" RESET);
		exit(1);
	}
	l_mapath = ft_strlen(av[1]) - 4;
	if (ft_strncmp(&av[1][l_mapath], ".cub", 4) != 0)
	{
		printf(RED "cub3D: invalid map\n" RESET);
		exit(1);
	}
	return (0);
}
