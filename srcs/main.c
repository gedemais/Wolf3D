/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:43:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/21 02:48:53 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline int		ft_set_env(t_mlx *env, char *map)
{
	if (parse_map(env, map) != 0)
		return (-1);
	if (!(env->mlx_ptr = mlx_init())
		|| !(env->mlx_win = mlx_new_window(env->mlx_ptr, WDT, HGT, "Wolfd3D")))
		return (-1);
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, WDT, HGT))
		|| !(env->img_data = mlx_get_data_addr(env->img_ptr, &env->bpp, 
		&env->s_l, &env->endian)))
		return (-1);
	env->player.x = 5;
	env->player.y = 5;
	env->player.dirx = 0;
	env->player.diry = 1;
	env->player.cam.fov = 3.141 / 3;
	return (0);
}


static inline int		wolf_3d(char *map)
{
	t_mlx	env;

	ft_memset(&env, 0, sizeof(t_mlx));
	if (ft_set_env(&env, map) == -1)
		return (-1);
	mlx_put_image_to_window(&env, env.mlx_win, env.img_ptr, 0, 0);
	mlx_hook(env.mlx_win, KEY_PRESS, KEY_PRESS_MASK, deal_key, &env);
//	mlx_hook(env.mlx_win, 4, (1L << 2), ft_press, &env);
	mlx_hook(env.mlx_win, 6, 0, position, &env);
	mlx_hook(env.mlx_win, 7, 0, base, &env);
	mlx_hook(env.mlx_win, 17, (1L << 17), ft_exit, &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage : ./wolfd3d [map]\n", 2);
		return (1);
	}
	else if (wolf_3d(argv[1]) == -1)
	{
		ft_putstr_fd("Map Error\n", 2);
		return (1);
	}
	return (0);
}
