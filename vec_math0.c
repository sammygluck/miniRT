/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:04:47 by wmarien           #+#    #+#             */
/*   Updated: 2024/03/29 10:52:30 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_magnitude(t_vec3 vec)
{
	double	rtn;

	rtn = pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
	return (sqrt(rtn));
}

t_vec3	normalize(t_vec3 vec)
{
	t_vec3	rtn;
	double	norm;

	norm = vec_magnitude(vec);
	if (norm == 0)
		return (vec);
	rtn.x = vec.x / norm;
	rtn.y = vec.y / norm;
	rtn.z = vec.z / norm;
	return (rtn);
}

t_vec3	scalar_multiplication(t_vec3 vec, double scalar)
{
	t_vec3	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}

t_vec3	sum_vectors(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec3	diff_vectors(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}
