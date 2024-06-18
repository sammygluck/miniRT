/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:19:23 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/18 15:31:58 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intersect_sphere(t_ray ray, t_object *sphere)
{
	t_vec3	par;
	double	dis;
	double	res1;
	double	res2;

	par.x = dot_product(ray.direction, ray.direction);
	par.y = 2 * dot_product(ray.direction,
			diff_vectors(ray.origin, sphere->center));
	par.z = dot_product(diff_vectors(ray.origin, sphere->center),
			diff_vectors(ray.origin, sphere->center));
	par.z -= pow(sphere->r, 2);
	dis = pow(par.y, 2) - (4 * par.x * par.z);
	if (dis <= 0)
		return (-1);
	res1 = (-par.y - sqrt(dis)) / (2 * par.x);
	res2 = (-par.y + sqrt(dis)) / (2 * par.x);
	if (res1 < res2 && res1 > 0)
		return (res1);
	else if (res2 > 0)
		return (res2);
	return (-1);
}

double	intersect_plane(t_ray ray, t_object *plane)
{
	double	denom;

	denom = dot_product(ray.direction, plane->normal);
	if (denom != 0)
		return ((dot_product(diff_vectors(plane->center, ray.origin),
					plane->normal) / denom));
	return (-1);
}

double	intersect_cylinder(t_ray ray, t_object *cylinder, t_vec3 *normal)
{
	double	which_cap;
	double	t_side;
	double	t_cap;

	ray = transform_ray(ray, cylinder);
	t_side = intersect_side(ray, cylinder) - 1E-10;
	t_cap = intersect_cap(ray, cylinder) - 1E-10;
	which_cap = ray.origin.y + (t_cap * ray.direction.y);
	if (t_side <= 0)
		return (normal_cap(which_cap, cylinder, normal), t_cap);
	if (t_cap == -1)
		return (t_side);
	if (t_side > 0 && t_cap > 0)
	{
		if (t_cap < t_side)
			normal_cap(which_cap, cylinder, normal);
		return (fmin(t_side, t_cap));
	}
	if (t_cap > 0)
		normal_cap(which_cap, cylinder, normal);
	return (fmax(t_side, t_cap));
}

double	intersect(t_ray ray, t_object *object)
{
	if (object->type == SPHERE)
		return (intersect_sphere(ray, object));
	else if (object->type == PLANE)
		return (intersect_plane(ray, object));
	else if (object->type == CYLINDER)
		return (intersect_cylinder(ray, object, NULL));
	else
		return (-1);
}

t_closest	iterate_obj(t_mrt *mrt, t_ray ray)
{
	double		t;
	t_list		*lst;
	t_object	*object;
	t_closest	closest_obj;

	lst = mrt->world.objects;
	closest_obj.t = DBL_MAX;
	closest_obj.object = NULL;
	while (lst)
	{
		object = (t_object *)lst->content;
		t = intersect(ray, object);
		if (t > 0 && t < closest_obj.t && t != -1)
		{
			closest_obj.t = t;
			closest_obj.object = (t_object *)lst->content;
		}
		lst = lst->next;
	}
	return (closest_obj);
}
