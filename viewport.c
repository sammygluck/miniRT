/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:13:38 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/03 13:28:05 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
void	init_viewport(t_mrt *mrt)
{
	double	aspect_ratio;
	double	fovr;

	fovr = mrt->world.cam.fov * M_PI / 180;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	mrt->vp.width = 2 * tan(fovr / 2);
	mrt->vp.height = mrt->vp.width / aspect_ratio;
	mrt->vp.front = mrt->world.cam.normal;
	mrt->vp.right = cross_product((t_vec3){0, 1, 0}, mrt->vp.front);
	mrt->vp.up = cross_product(mrt->vp.front, mrt->vp.right);
}

t_vec3	pix_to_cord(t_viewport vp, int x, int y)
{
	double	vx;
	double	vy;
	t_vec3	result;

	vx = (x / (double)WIDTH) * vp.width - (vp.width / 2);
	vy = ((y / (double)HEIGHT) * vp.height - (vp.height / 2)) * -1;
	result = sum_vectors(vp.front, sum_vectors(scalar_multiplication(
					vp.right, vx), scalar_multiplication(vp.up, vy)));
	return (result);
}
*/

t_vec3	top_left_pixel(t_mrt *mrt, t_quaternion rot)
{
	t_vec3	result;

	result.x = mrt->vp.width / -2.0;
	result.y = mrt->vp.height / 2.0;
	result.z = 1;
	result = vector_rotation(result, rot);
	return (sum_vectors(result, mrt->world.cam.origin));
}

void	init_viewport(t_mrt *mrt)
{
	double			aspect_ratio;
	double			fovr;
	t_quaternion	rot;

	fovr = mrt->world.cam.fov * M_PI / 180;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	rot = rotation_quaternion((t_vec3){0, 0, 1}, mrt->world.cam.normal);
	mrt->vp.width = 2 * tan(fovr / 2);
	mrt->vp.height = mrt->vp.width / aspect_ratio;
	mrt->vp.tlp = top_left_pixel(mrt, rot);
	mrt->vp.right = normalize(vector_rotation((t_vec3){1, 0, 0}, rot));
	mrt->vp.down = normalize(vector_rotation((t_vec3){0, -1, 0}, rot));
	mrt->vp.x_step = mrt->vp.width / (double)WIDTH;
	mrt->vp.y_step = mrt->vp.height / (double)HEIGHT;
}

t_vec3	pix_to_cord(t_viewport vp, int x, int y)
{
	t_vec3	result;

	result = vp.tlp;
	result = sum_vectors(result,
			scalar_multiplication(vp.right, (double)x * vp.x_step));
	result = sum_vectors(result,
			scalar_multiplication(vp.down, (double)y * vp.y_step));
	return (result);
}
