/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:44:18 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/20 00:09:23 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fatal_error(const char *format, ...)
{
	va_list		args;
	const char	*ename = PROGRAM;

	ft_dprintf(2, "%s: ", ename);
	va_start(args, format);
	ft_vdprintf(2, format, args);
	ft_dprintf(2, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}

void	sys_error(const char *format, ...)
{
	int			e;
	va_list		args;
	const char	*ename = PROGRAM;

	e = errno;
	ft_dprintf(2, "%s: ", ename);
	va_start(args, format);
	ft_vdprintf(2, format, args);
	ft_dprintf(2, ": %s", strerror(e));
	ft_dprintf(2, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}

void	libx_error(void)
{
	int			e;
	const char	*ename = PROGRAM;

	e = mlx_errno;
	ft_dprintf(2, "%s: ", ename);
	ft_dprintf(2, "%s", mlx_strerror(e));
	ft_dprintf(2, "\n");
	exit(EXIT_FAILURE);
}
