/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:43:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/04 01:36:51 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void	init_player(t_mlx *env)
{
	env->player.hp = 100;
	env->player.cam.fov = 3.141 / 2;
	env->player.speed = 0.1;
	env->player.x = 37;
	env->player.y = 38;
}

static inline int		ft_set_env(t_mlx *env, char *map)
{
	if (parse_map(env, map) != 0
		|| load_sprites(env) != 0)
		return (-1);
	if (!(env->mlx_ptr = mlx_init())
		|| !(env->mlx_win = mlx_new_window(env->mlx_ptr, WDT, HGT, "Wolf3D")))
		return (-1);
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, WDT, HGT))
		|| !(env->img_data = mlx_get_data_addr(env->img_ptr, &env->bpp, 
		&env->s_l, &env->endian)))
		return (-1);
	ft_memset(&env->keys[0], false, sizeof(bool) * NB_KEYS);
	init_player(env);
	init_weapons(env);
	env->nb_killed = 1;
	return (0);
}

static inline void	set_hooks(t_mlx *env)
{
	mlx_hook(env->mlx_win, KEY_PRESS, KEY_PRESS_MASK, press_key, env);
	mlx_hook(env->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, release_key, env);
	mlx_loop_hook(env->mlx_ptr, base, env);
	mlx_hook(env->mlx_win, 17, (1L << 17), ft_exit, env);
}

static inline int		wolf_3d(char *map)
{
	t_mlx	env;

	ft_memset(&env, 0, sizeof(t_mlx));
	if (ft_set_env(&env, map) == -1)
		return (-1);
	mlx_put_image_to_window(&env, env.mlx_win, env.img_ptr, 0, 0);

	set_hooks(&env);
	mlx_loop(env.mlx_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	srand(time(0));
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
