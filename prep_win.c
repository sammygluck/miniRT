/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:30:58 by wmarien           #+#    #+#             */
/*   Updated: 2024/03/28 15:31:33 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_image(t_mlx *mlx, unsigned int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			put_pixel(mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	prep_win(t_mrt *mrt)
{
	mlx_clear_window(mrt->mlx.mlx, mrt->mlx.window);
	clear_image(&mrt->mlx, 0x000000);
	ray_tracer(mrt);
	mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.window,
		mrt->mlx.image, 0, 0);
}
