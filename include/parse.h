/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/09/28 18:51:07 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int		ft_isspace(int c);
int		legal_number(const char *string, int *result);
void	whitespace(char **str);
char	*read_line(int fd);
int		validate_map(t_scene *scene);
void	parse_scene(int fd, t_scene *scene);
int		is_valid_cells(char *line);
void	parse_map(int fd, t_scene *scene, char *line);

#endif /* PARSE_H */
