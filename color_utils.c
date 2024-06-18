/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:31:35 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/11 16:31:37 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	add_colors(unsigned int color1, unsigned int color2)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ((color1 & 0xFF0000) >> 16) + ((color2 & 0xFF0000) >> 16);
	if (r > 0xFF)
		r = 0xFF;
	g = ((color1 & 0x00FF00) >> 8) + ((color2 & 0x00FF00) >> 8);
	if (g > 0xFF)
		g = 0xFF;
	b = (color1 & 0x0000FF) + (color2 & 0x0000FF);
	if (b > 0xFF)
		b = 0xFF;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	multiply_colors(unsigned int color1, unsigned int color2)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ((color1 & 0xFF0000) >> 16) * ((color2 & 0xFF0000) >> 16) / 255;
	g = ((color1 & 0x00FF00) >> 8) * ((color2 & 0x00FF00) >> 8) / 255;
	b = (color1 & 0x0000FF) * (color2 & 0x0000FF) / 255;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	scalar_color(unsigned int color, double scalar)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ((color & 0xFF0000) >> 16) * scalar;
	if (r > 0xFF)
		r = 0xFF;
	g = ((color & 0x00FF00) >> 8) * scalar;
	if (g > 0xFF)
		g = 0xFF;
	b = (color & 0x0000FF) * scalar;
	if (b > 0xFF)
		b = 0xFF;
	return ((r << 16) + (g << 8) + b);
}
