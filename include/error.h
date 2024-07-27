/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:45:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/25 15:18:44 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(const char *, ...);
void	sys_error(const char *, ...);
void	libx_error(const char *, ...);
void	parser_error(int, char *, const char *, ...);

#endif /* ERROR_H */
