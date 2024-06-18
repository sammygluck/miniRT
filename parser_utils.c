/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:30:22 by wmarien           #+#    #+#             */
/*   Updated: 2024/03/14 15:36:29 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*skip_spaces(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}

int	parse_rgb(unsigned int *color, char **line)
{
	int	rgb[3];
	int	ctr;

	ctr = ft_isint(*line);
	if ((*line)[ctr] != ',')
		return (err_msg("Parser: Invalid format"));
	rgb[0] = ft_atoi(*line);
	*line += ctr;
	ctr = ft_isint(++(*line));
	if ((*line)[ctr] != ',')
		return (err_msg("Parser: Invalid format"));
	rgb[1] = ft_atoi(*line);
	*line += ctr;
	ctr = ft_isint(++(*line));
	if (!ft_isdigit((*line)[ctr]) && (*line)[ctr] != '+' && (*line)[ctr] != '-')
		return (err_msg("Parser: Invalid format"));
	rgb[2] = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (err_msg("Parser: Invalid RGB values"));
	else
		*color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	return (0);
}

int	parse_cords(t_vec3 *cords, char **line)
{
	int	ctr;

	ctr = ft_isdouble(*line);
	if ((*line)[ctr] != ',')
		return (err_msg("0Parser: Invalid format"));
	cords->x = ft_atof(*line);
	*line += ctr;
	ctr = ft_isdouble(++(*line));
	if ((*line)[ctr] != ',')
		return (err_msg("1Parser: Invalid format"));
	cords->y = ft_atof(*line);
	*line += ctr;
	ctr = ft_isdouble(++(*line));
	if (!ft_isdigit((*line)[ctr]) && (*line)[ctr] != '+' && (*line)[ctr] != '-')
		return (err_msg("2Parser: Invalid format"));
	cords->z = ft_atof(*line);
	while (**line && !ft_isspace(**line))
		(*line)++;
	return (0);
}

int	is_normalized(t_vec3 vec)
{
	double	mag;

	mag = vec_magnitude(vec);
	if (mag < 0.99999 || mag > 1.00001)
		return (0);
	else
		return (1);
}

int	parse_double(float *val, char **line)
{
	if (ft_isdouble(*line) != 0)
		return (err_msg("Parser: Invalid format"));
	*val = ft_atof(*line);
	while (**line && !ft_iswspace(**line))
		(*line)++;
	return (0);
}
