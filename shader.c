/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:53:00 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/16 14:56:46 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	normal_sphere(t_object *object, t_vec3 hitpoint, t_mrt *mrt)
{
	double	dist;
	t_vec3	normal;

	normal = normalize(diff_vectors(hitpoint, object->center));
	dist = vec_magnitude(diff_vectors(object->center, mrt->world.cam.origin));
	if (dist < object->r)
		return (scalar_multiplication(normal, -1));
	else
		return (normal);
}

t_vec3	normal_plane(t_object *object, t_ray ray)
{
	t_vec3	inv_normal;

	inv_normal = normalize(scalar_multiplication(object->normal, -1.0));
	if (dot_product(object->normal, ray.direction) < 0)
		return (inv_normal);
	return (object->normal);
}

void	normal_cap(double cap, t_object *cylinder, t_vec3 *normal)
{
	t_vec3	result;

	if (!normal)
		return ;
	result = cylinder->normal;
	if (cap < 0)
	{
		*normal = scalar_multiplication(result, -1.0);
		return ;
	}
	*normal = result;
}	

t_vec3	normal_cylinder(t_mrt *mrt, t_object *cylinder,
						t_vec3 hitpoint, t_vec3 normal)
{
	t_vec3			transf_p;
	t_vec3			transf_c;
	t_vec3			new_normal;
	t_quaternion	rot;

	new_normal = normal;
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
	{
		rot = rotation_quaternion(cylinder->normal, (t_vec3){0, 1, 0});
		transf_p = vector_rotation(hitpoint, rot);
		transf_c = vector_rotation(cylinder->center, rot);
		new_normal = diff_vectors(transf_p,
				(t_vec3){transf_c.x, transf_p.y, transf_c.z});
		rot = (t_quaternion){rot.w, -rot.x, -rot.y, -rot.z};
		new_normal = normalize(vector_rotation(new_normal, rot));
	}
	if (cam_in_cylinder(&mrt->world.cam, cylinder))
		new_normal = scalar_multiplication(new_normal, -1);
	return (new_normal);
}

unsigned int	shader(t_mrt *mrt, t_object *object, double t, t_ray ray)
{
	t_vec3			hitpoint;
	t_vec3			normal;
	unsigned int	colors[2];

	colors[0] = scalar_color(mrt->world.amb.color, mrt->world.amb.intensity);
	if (t == DBL_MAX)
		return (0x000000);
	normal = (t_vec3){0, 0, 0};
	if (object->type == CYLINDER)
		intersect_cylinder(ray, object, &normal);
	hitpoint = sum_vectors(ray.origin, scalar_multiplication(ray.direction, t));
	ray = cast_ray(hitpoint, mrt->world.light.origin);
	if (in_shadow(mrt, ray))
		return (multiply_colors(colors[0], object->color));
	if (object->type == SPHERE)
		normal = normal_sphere(object, hitpoint, mrt);
	else if (object->type == PLANE)
		normal = normal_plane(object, ray);
	else if (object->type == CYLINDER)
		normal = normal_cylinder(mrt, object, hitpoint, normal);
	if (dot_product(normal, ray.direction) < 0)
		return (multiply_colors(colors[0], object->color));
	colors[1] = scalar_color(mrt->world.light.color,
			dot_product(normal, ray.direction) * mrt->world.light.intensity);
	return (multiply_colors(add_colors(colors[1], colors[0]), object->color));
}
