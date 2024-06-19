/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:45:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/20 00:09:59 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(const char *format, ...);
void	sys_error(const char *format, ...);
void	libx_error(void);

#endif /* ERROR_H */
