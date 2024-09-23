/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/09/23 10:58:04 by santito          ###   ########.fr       */
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
int		is_valid_cells(char *);
void	place_doors(t_map *);
void	parse_map(int, t_scene *, char *);

#endif /* PARSE_H */
