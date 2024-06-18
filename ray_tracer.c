/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:34:17 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/16 16:54:40 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	cast_ray(t_vec3 origin, t_vec3 point)
{
	t_ray	result;

	result.origin = origin;
	result.direction = normalize(diff_vectors(point, origin));
	return (result);
}

int	ray_tracer(t_mrt *mrt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_closest	closest;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = cast_ray(mrt->world.cam.origin, pix_to_cord(mrt->vp, x, y));
			closest = iterate_obj(mrt, ray);
			put_pixel(&mrt->mlx, x, y,
				shader(mrt, closest.object, closest.t, ray));
			x++;
		}
		y++;
	}
	return (0);
}
