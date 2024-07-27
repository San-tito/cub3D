/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 18:52:37 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int		ft_isspace(int);
int		legal_number(const char *, int *);
void	whitespace(char **str);
char	*read_line(int);
int		validate_map(t_scene *);
void	parse_scene(int, t_scene *);
void	parse_map(t_scene *, int, char *);

#endif /* PARSE_H */
