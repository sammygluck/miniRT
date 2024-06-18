/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:12:34 by wmarien           #+#    #+#             */
/*   Updated: 2024/06/04 12:40:44 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_line(t_world *world, char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\n')
		return (0);
	else if (*line == 'A')
		return (parse_ambient(world, line));
	else if (*line == 'C')
		return (parse_camera(world, line));
	else if (*line == 'L')
		return (parse_light(world, line));
	else if (*line == 's')
		return (parse_sphere(world, line));
	else if (*line == 'p')
		return (parse_plane(world, line));
	else if (*line == 'c')
		return (parse_cylinder(world, line));
	else
		return (err_msg("Parser: Invalid character on line"));
}

bool	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len-- > 3 && file[len - 2] == '.'
		&& file[len - 1] == 'r' && file[len] == 't')
		return (true);
	return (false);
}

int	parser(t_world *world, char *file)
{
	int		fd;
	char	*line;

	if (!check_filename(file))
		return (err_msg("Parser: Invalid file name"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perr_msg("Parser: ", file));
	line = get_next_line(fd, false);
	while (line)
	{
		if (parse_line(world, line))
			return (get_next_line(0, true), free(line), 1);
		free(line);
		line = get_next_line(fd, false);
	}
	if (!world->parsed[1])
		return (err_msg("Parser: No camera in file"));
	return (0);
}
