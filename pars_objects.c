/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:09:26 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/16 14:35:48 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(t_world *world, char *line)
{
	t_object	*new;

	if (line[0] != 's' && line[1] != 'p' && !ft_isspace(line[2]))
		return (err_msg("Sphere: Invalid character on line"));
	new = malloc(sizeof(t_object));
	if (!new)
		return (perr_msg("Parser: ", "Malloc"));
	new->type = SPHERE;
	line = skip_spaces(line + 2);
	if (parse_cords(&new->center, &line))
		return (free(new), 1);
	line = skip_spaces(line);
	if (parse_double(&new->r, &line))
		return (free(new), 1);
	new->r /= 2;
	if (new->r <= 0.0)
		return (free(new), err_msg("Sphere: Invalid diameter value"));
	line = skip_spaces(line);
	if (parse_rgb(&new->color, &line))
		return (free(new), 1);
	if (ft_strlen(line) != 1)
		return (free(new), err_msg("Sphere: Line too long"));
	ft_lstadd_back(&world->objects, ft_lstnew(new));
	world->obj_parsed++;
	return (0);
}

int	parse_plane(t_world *world, char *line)
{
	t_object	*new;

	if (line[0] != 'p' && line[1] != 'l' && !ft_isspace(line[2]))
		return (err_msg("Plane: Invalid character on line"));
	new = malloc(sizeof(t_object));
	if (!new)
		return (perr_msg("Parser: ", "Malloc"));
	new->type = PLANE;
	line = skip_spaces(line + 2);
	if (parse_cords(&new->center, &line))
		return (free(new), 1);
	line = skip_spaces(line);
	if (parse_cords(&new->normal, &line))
		return (free(new), 1);
	if (!is_normalized(new->normal))
		return (free (new), err_msg("Plane: Vector is not normalized"));
	line = skip_spaces(line);
	if (parse_rgb(&new->color, &line))
		return (free(new), 1);
	if (ft_strlen(line) != 1)
		return (free(new), err_msg("Plane: Line too long"));
	ft_lstadd_back(&world->objects, ft_lstnew(new));
	world->obj_parsed++;
	return (0);
}

int	parse_cylinder2(t_object *new, char **line)
{
	if (parse_double(&new->r, &*line))
		return (free(new), 1);
	new->r /= 2;
	if (new->r <= 0.0)
		return (free(new), err_msg("Cylinder: Invalid diameter value"));
	*line = skip_spaces(*line);
	if (parse_double(&new->h, &*line))
		return (free(new), 1);
	if (new->h <= 0.0)
		return (free(new), err_msg("Cylinder: Invalid height value"));
	*line = skip_spaces(*line);
	if (parse_rgb(&new->color, &*line))
		return (free(new), 1);
	return (0);
}

int	parse_cylinder(t_world *world, char *line)
{
	t_object	*new;

	if (line[0] != 'c' && line[1] != 'y' && !ft_isspace(line[2]))
		return (err_msg("Cylinder: Invalid character on line"));
	new = malloc(sizeof(t_object));
	if (!new)
		return (perr_msg("Parser: ", "Malloc"));
	new->type = CYLINDER;
	line = skip_spaces(line + 2);
	if (parse_cords(&new->center, &line))
		return (free(new), 1);
	line = skip_spaces(line);
	if (parse_cords(&new->normal, &line))
		return (free(new), 1);
	if (!is_normalized(new->normal))
		return (free (new), err_msg("Cylinder: Vector is not normalized"));
	line = skip_spaces(line);
	if (parse_cylinder2(new, &line))
		return (1);
	if (ft_strlen(line) != 1)
		return (free(new), err_msg("Cylinder: Line too long"));
	ft_lstadd_back(&world->objects, ft_lstnew(new));
	world->obj_parsed++;
	return (0);
}
