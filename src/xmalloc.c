/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:09:36 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 13:23:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*xmalloc(size_t bytes)
{
	void	*temp;

	temp = malloc(bytes);
	if (temp == 0)
		fatal_error("xmalloc: cannot allocate %lu bytes", (unsigned long)bytes);
	return (temp);
}

void	*xrealloc(void *pointer, size_t old_size, size_t new_size)
{
	void	*temp;

	temp = xmalloc(new_size);
	ft_memcpy(temp, pointer, old_size);
	xfree(pointer);
	return (temp);
}

void	xfree(void *string)
{
	if (string)
		free(string);
}
