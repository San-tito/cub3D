/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:44:18 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/19 22:12:08 by sguzman          ###   ########.fr       */
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

void	sys_error(void)
{
	int			e;
	const char	*ename = PROGRAM;

	e = mlx_errno;
	ft_dprintf(2, "%s: ", ename);
	ft_dprintf(2, ": %s\n", mlx_strerror(e));
	exit(EXIT_FAILURE);
}
