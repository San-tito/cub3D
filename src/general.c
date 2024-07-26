/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 17:07:02 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static ssize_t	ft_strtoi(const char *nptr, char **endptr)
{
	ssize_t		acc;
	int			neg;
	const char	*s = nptr;

	acc = 0;
	whitespace((char **)&s);
	neg = (*s == '-');
	if (*s == '-' || *s == '+')
		s++;
	if (ft_isdigit(*s) == 0 && endptr != 0)
		return (*endptr = (char *)nptr, acc);
	while (ft_isdigit(*s))
	{
		if (neg && (acc < (INT_MIN + (*s - '0')) / 10))
			return (errno = ERANGE, acc = INT_MIN);
		if (neg == 0 && (acc > (INT_MAX - (*s - '0')) / 10))
			return (errno = ERANGE, acc = INT_MAX);
		if (neg)
			acc = acc * 10 - (*s++ - '0');
		else
			acc = acc * 10 + (*s++ - '0');
	}
	if (endptr != 0)
		*endptr = (char *)s;
	return (acc);
}

int	ft_isspace(int c)
{
	return (c == 0x20 || c == 0xD || c == 0xA || c == 0x9);
}

void	whitespace(char **str)
{
	if (str == 0 || *str == 0)
		return ;
	while (ft_isspace(**str))
		(*str)++;
}

int	legal_number(const char *string, int *result)
{
	ssize_t	value;
	char	*ep;

	if (result)
		*result = 0;
	if (string == 0)
		return (0);
	errno = 0;
	value = ft_strtoi(string, &ep);
	if (errno || ep == string)
		return (0);
	whitespace(&ep);
	if (*string && *ep == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}

char	*read_line(int fd)
{
	char	*buffer;
	char	character;
	int		bytes;
	int		index;

	index = 0;
	bytes = read(fd, &character, 1);
	buffer = xmalloc(sizeof(char) * 2);
	while (bytes > 0)
	{
		if (character == '\n')
			break ;
		buffer[index++] = character;
		buffer = xrealloc(buffer, ft_strlen(buffer) + 1, ft_strlen(buffer) + 2);
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (index == 0))
		return (xfree(buffer), NULL);
	buffer[index] = '\0';
	return (buffer);
}
