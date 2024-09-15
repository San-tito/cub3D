/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:44:18 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/15 19:57:00 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fatal_error(t_scene *scene, const char *format, ...)
{
	va_list	args;

	ft_dprintf(2, "%s: ", PROGRAM);
	va_start(args, format);
	ft_vdprintf(2, format, args);
	ft_dprintf(2, "\n");
	va_end(args);
	dispose_scene(scene);
	exit(EXIT_FAILURE);
}

void	parser_error(int fd, t_scene *scene, const char *format, char *line)
{
	ft_dprintf(2, "%s: ", PROGRAM);
	ft_dprintf(2, format, line);
	ft_dprintf(2, "\n");
	xfree(line);
	close(fd);
	dispose_scene(scene);
	exit(EXIT_FAILURE);
}

void	sys_error(const char *format, ...)
{
	int		e;
	va_list	args;

	e = errno;
	ft_dprintf(2, "%s: ", PROGRAM);
	va_start(args, format);
	ft_vdprintf(2, format, args);
	ft_dprintf(2, ": %s", strerror(e));
	ft_dprintf(2, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}

void	libx_error(const char *format, ...)
{
	int		e;
	va_list	args;

	e = mlx_errno;
	ft_dprintf(2, "%s: ", PROGRAM);
	va_start(args, format);
	ft_vdprintf(2, format, args);
	ft_dprintf(2, ": %s", mlx_strerror(e));
	ft_dprintf(2, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}
