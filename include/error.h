/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:45:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/15 19:56:39 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(t_scene *, const char *, ...);
void	sys_error(const char *, ...);
void	libx_error(const char *, ...);
void	parser_error(int, t_scene *, const char *, char *);

#endif /* ERROR_H */
