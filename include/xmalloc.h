/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:55:42 by droied            #+#    #+#             */
/*   Updated: 2024/06/25 15:11:20 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMALLOC_H
# define XMALLOC_H

void	*xmalloc(size_t);
void	*xrealloc(void *, size_t, size_t);
void	xfree(void *);

#endif /* XMALLOC_H */
