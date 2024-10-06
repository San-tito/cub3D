/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/10/06 01:43:41 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_alpha(int color)
{
	return (color & 0xFF);
}

int	get_red(int color)
{
	return ((color >> 24) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_blue(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
