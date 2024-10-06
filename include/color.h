/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:23:37 by droied            #+#    #+#             */
/*   Updated: 2024/10/06 01:43:53 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int	get_alpha(int rgba);
int	get_red(int rgba);
int	get_green(int rgba);
int	get_blue(int rgba);
int	get_color(int r, int g, int b, int a);

#endif /* CALLBACK_H */
