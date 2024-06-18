/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:27:43 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/16 15:32:19 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cam_in_cylinder(t_camera *cam, t_object *cylinder)
{
	t_vec3			cam_pos;
	t_quaternion	rot;

	rot = rotation_quaternion(cylinder->normal, (t_vec3){0, 1, 0});
	cam_pos = vector_rotation(cam->origin, rot);
	cam_pos = diff_vectors(cam_pos, cylinder->center);
	cam_pos.y += cylinder->h / 2.0;
	if (cam_pos.y > 0 && cam_pos.y < cylinder->h)
	{
		if (pow(cam_pos.x, 2) + pow(cam_pos.z, 2) < pow(cylinder->r, 2))
			return (1);
	}
	return (0);
}

int	in_shadow(t_mrt *mrt, t_ray ray)
{
	double		dist;
	double		light_dist;
	t_closest	closest_obj;
	t_list		*lst;

	closest_obj.t = DBL_MAX;
	closest_obj.object = NULL;
	light_dist = vec_magnitude(
			diff_vectors(ray.origin, mrt->world.light.origin));
	lst = mrt->world.objects;
	while (lst)
	{
		dist = intersect(ray, lst->content);
		if (dist > 1E-10 && dist < closest_obj.t && dist < light_dist)
		{
			closest_obj.t = dist;
			closest_obj.object = (t_object *)lst->content;
			break ;
		}
		lst = lst->next;
	}
	if (closest_obj.object)
		return (1);
	return (0);
}
