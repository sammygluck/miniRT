/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:24:13 by wmarien           #+#    #+#             */
/*   Updated: 2024/03/28 15:25:08 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*tmp;

	tmp = mlx->buff + (y * mlx->size_line) + (x * (mlx->bpp / 8));
	*(unsigned int *)tmp = color;
}

int	key_hook(int keycode, t_mrt *mrt)
{
	if (keycode == ESC_KEY)
		mrt_exit(mrt);
	return (0);
}

void	add_mlx_hook(t_mrt *mrt)
{
	mlx_key_hook(mrt->mlx.window, key_hook, mrt);
	mlx_hook(mrt->mlx.window, DESTROYNOTIFY, 0, mrt_exit, mrt);
}

int	display_win(t_mrt *mrt)
{
	mrt->mlx.mlx = mlx_init();
	if (mrt->mlx.mlx != NULL)
	{
		mrt->mlx.window = mlx_new_window(mrt->mlx.mlx, WIDTH, HEIGHT, "MiniRT");
		if (mrt->mlx.window != NULL)
		{
			mrt->mlx.image = mlx_new_image(mrt->mlx.mlx, WIDTH, HEIGHT);
			if (mrt->mlx.image != NULL)
			{
				mrt->mlx.buff = mlx_get_data_addr(mrt->mlx.image, &mrt->mlx.bpp,
						&mrt->mlx.size_line, &mrt->mlx.endian);
				mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.window,
					mrt->mlx.image, 0, 0);
				add_mlx_hook(mrt);
				prep_win(mrt);
				mlx_loop(mrt->mlx.mlx);
				return (0);
			}
		}
	}
	return (1);
}
