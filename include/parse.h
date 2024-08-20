/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/08/20 15:20:00 by deordone         ###   ########.fr       */
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
void	set_player(mlx_image_t*, t_player *);


#endif /* PARSE_H */
