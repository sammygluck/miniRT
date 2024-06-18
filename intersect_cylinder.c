/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:36:01 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/18 15:36:03 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	transform_ray(t_ray old_ray, t_object *cylinder)
{
	double			dist;
	t_ray			result;
	t_quaternion	rot;

	dist = vec_magnitude(diff_vectors(old_ray.origin, cylinder->center));
	rot = rotation_quaternion(cylinder->normal, (t_vec3){0, 1, 0});
	result.origin = vector_rotation(normalize(
				diff_vectors(old_ray.origin, cylinder->center)), rot);
	result.origin = scalar_multiplication(result.origin, dist);
	result.direction = normalize(vector_rotation(old_ray.direction, rot));
	return (result);
}

double	intersect_cap(t_ray ray, t_object *cylinder)
{
	double	par1;
	double	par2;
	t_vec3	p;

	par1 = ((cylinder->h / 2) - ray.origin.y) / ray.direction.y;
	par2 = ((cylinder->h / -2) - ray.origin.y) / ray.direction.y;
	p.x = ray.origin.x + (par1 * ray.direction.x);
	p.z = ray.origin.z + (par1 * ray.direction.z);
	if (par1 > 0 && pow(p.x, 2) + pow(p.z, 2) <= pow(cylinder->r, 2))
	{
		p.x = ray.origin.x + (par2 * ray.direction.x);
		p.z = ray.origin.z + (par2 * ray.direction.z);
		if (par2 > 0 && pow(p.x, 2) + pow(p.z, 2) <= pow(cylinder->r, 2))
			return (fmin(par1, par2));
		else
			return (par1);
	}
	p.x = ray.origin.x + (par2 * ray.direction.x);
	p.z = ray.origin.z + (par2 * ray.direction.z);
	if (par2 > 0 && pow(p.x, 2) + pow(p.z, 2) <= pow(cylinder->r, 2))
		return (par2);
	return (-1);
}

double	intersect_side(t_ray ray, t_object *cylinder)
{
	double	t[2];
	double	h[2];
	double	dis;
	t_vec3	par;

	par.x = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	par.y = 2 * ((ray.origin.x * ray.direction.x)
			+ (ray.origin.z * ray.direction.z));
	par.z = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - pow(cylinder->r, 2);
	dis = pow(par.y, 2) - (4 * par.x * par.z);
	if (dis <= 0)
		return (-1);
	t[0] = (-par.y - sqrt(dis)) / (2 * par.x);
	t[1] = (-par.y + sqrt(dis)) / (2 * par.x);
	h[0] = ray.origin.y + (ray.direction.y * t[0]);
	h[1] = ray.origin.y + (ray.direction.y * t[1]);
	if ((h[0] >= -cylinder->h / 2 && h[0] <= cylinder->h / 2 && t[0] > 0)
		&& (h[1] >= -cylinder->h / 2 && h[1] <= cylinder->h / 2 && t[1] > 0))
		return (fmin(t[0], t[1]));
	if (h[0] >= -cylinder->h / 2 && h[0] <= cylinder->h / 2 && t[0] > 0)
		return (t[0]);
	if (h[1] >= -cylinder->h / 2 && h[1] <= cylinder->h / 2 && t[1] > 0)
		return (t[1]);
	return (-1);
}
