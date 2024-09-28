/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:55:42 by droied            #+#    #+#             */
/*   Updated: 2024/09/28 18:49:14 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMALLOC_H
# define XMALLOC_H

void	*xmalloc(size_t bytes);
void	*xrealloc(void *pointer, size_t old_size, size_t new_size);
void	xfree(void *string);

#endif /* XMALLOC_H */
