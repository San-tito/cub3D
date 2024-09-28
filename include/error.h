/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:45:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/28 18:49:49 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(t_scene *scene, const char *format, ...);
void	sys_error(const char *format, ...);
void	libx_error(const char *format, ...);
void	parser_error(int fd, t_scene *scene, const char *format, char *line);

#endif /* ERROR_H */
