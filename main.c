/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:54:30 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/03 13:47:45 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_exit(t_mrt *mrt)
{
	ft_lstclear(&mrt->world.objects, &free);
	if (mrt->mlx.mlx && mrt->mlx.window)
		mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.window);
	if (mrt->mlx.mlx && mrt->mlx.image)
		mlx_destroy_image(mrt->mlx.mlx, mrt->mlx.image);
	if (mrt->mlx.mlx)
		mlx_destroy_display(mrt->mlx.mlx);
	if (mrt->mlx.mlx)
		free(mrt->mlx.mlx);
	exit (0);
}

int	main(int ac, char **av)
{
	t_mrt	mrt;
	int		rtn;

	rtn = 1;
	if (ac != 2)
		return (err_msg("Program: Wrong use"));
	ft_bzero(&mrt, sizeof(t_mrt));
	if (!parser(&mrt.world, av[1]))
	{
		init_viewport(&mrt);
		if (display_win(&mrt) == 0)
			rtn = 0;
	}
	else
		ft_lstclear(&mrt.world.objects, &free);
	return (rtn);
}
