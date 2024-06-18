/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:23:23 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/16 14:34:39 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_world *world, char *line)
{
	if (world->parsed[0] == 1)
		return (err_msg("Parser: Multiple ambient lights in file"));
	if (line[0] != 'A' && !ft_isspace(line[1]))
		return (err_msg("Ambient: Invalid character on line"));
	line = skip_spaces(++line);
	if (parse_double(&world->amb.intensity, &line))
		return (1);
	if (world->amb.intensity < 0.0 || world->amb.intensity > 1.0)
		return (err_msg("Ambient: Invalid intensity for ambient light"));
	line = skip_spaces(++line);
	if (parse_rgb(&world->amb.color, &line))
		return (1);
	if (ft_strlen(line) != 1)
		return (err_msg("Ambient: Line too long"));
	world->parsed[0] = 1;
	return (0);
}

int	parse_camera(t_world *world, char *line)
{
	if (world->parsed[1] == 1)
		return (err_msg("Parser: Multiple camera's in file'"));
	if (line[0] != 'C' && !ft_isspace(line[1]))
		return (err_msg("Camera: Invalid character on line"));
	line = skip_spaces(++line);
	if (parse_cords(&world->cam.origin, &line))
		return (1);
	line = skip_spaces(line);
	if (parse_cords(&world->cam.normal, &line))
		return (1);
	if (!is_normalized(world->cam.normal))
		return (err_msg("Camera: Vector is not normalized"));
	line = skip_spaces(line);
	if (ft_isint(line) != 0)
		return (err_msg("Camera: Invalid format"));
	world->cam.fov = ft_atoi(line);
	if (world->cam.fov < 0 || world->cam.fov > 180)
		return (err_msg("Camera: Invalid FOV range"));
	while (!ft_iswspace(*line))
		line++;
	if (ft_strlen(line) != 1)
		return (err_msg("Camera: Line too long"));
	world->parsed[1] = 1;
	return (0);
}

int	parse_light(t_world *world, char *line)
{
	if (world->parsed[2] == 1)
		return (err_msg("Parser: Multiple light's in file"));
	if (line[0] != 'L' && !ft_isspace(line[1]))
		return (err_msg("Light: Invalid character on line"));
	line = skip_spaces(++line);
	if (parse_cords(&world->light.origin, &line))
		return (1);
	line = skip_spaces(line);
	if (ft_isdouble(++line) != 0)
		return (err_msg("Light: Invalid format"));
	if (parse_double(&world->light.intensity, &line))
		return (1);
	if (world->light.intensity < 0.0 || world->light.intensity > 1.0)
		return (err_msg("Light: Invalid intensity for light source"));
	line = skip_spaces(line);
	if (parse_rgb(&world->light.color, &line))
		return (1);
	if (ft_strlen(line) != 1)
		return (err_msg("Light: Line too long"));
	world->parsed[2] = 1;
	return (0);
}
