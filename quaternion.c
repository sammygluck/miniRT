/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:39:23 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/18 15:32:44 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quaternion	normalize_quaternion(t_quaternion q)
{
	double	norm;

	norm = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= norm;
	q.x /= norm;
	q.y /= norm;
	q.z /= norm;
	return (q);
}

t_quaternion	multiply_quaternions(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	result;

	result.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	result.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	result.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	result.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
	return (result);
}

t_quaternion	rotation_quaternion(t_vec3 from, t_vec3 to)
{
	t_vec3			imag;
	t_quaternion	result;
	double			dot;

	dot = dot_product(from, to);
	imag = scalar_multiplication(cross_product(from, to), sqrt((1 - dot) / 2));
	result.x = imag.x;
	result.y = imag.y;
	result.z = imag.z;
	result.w = sqrt((1 + dot) / 2);
	return (normalize_quaternion(result));
}

t_vec3	vector_rotation(t_vec3 vec, t_quaternion rot)
{
	t_quaternion	result;

	result = multiply_quaternions(rot, (t_quaternion){0, vec.x, vec.y, vec.z});
	result = multiply_quaternions(result,
			(t_quaternion){rot.w, -rot.x, -rot.y, -rot.z});
	return ((t_vec3){result.x, result.y, result.z});
}
