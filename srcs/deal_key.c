/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 23:08:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 05:15:41 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	handle_moves(t_mlx *env)
{
	env->player.speed = env->keys[SHIFT_KEY] ? 0.15 : 0.1;
	if (env->keys[UP_KEY] || env->keys[KEY_W])
	{
		env->player.x += sin(env->player.cam.angle) * env->player.speed;
		env->player.y += cos(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x -= sin(env->player.cam.angle) * env->player.speed;
			env->player.y -= cos(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[DOWN_KEY] || env->keys[KEY_S])
	{
		env->player.x -= sin(env->player.cam.angle) * env->player.speed;
		env->player.y -= cos(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x += sin(env->player.cam.angle) * env->player.speed;
			env->player.y += cos(env->player.cam.angle) * env->player.speed;
		}
	}
}

void	handle_keys(t_mlx *env)
{
	if (env->keys[KEY_D])
	{
		env->player.x += cos(env->player.cam.angle) * env->player.speed;
		env->player.y -= sin(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x -= cos(env->player.cam.angle) * env->player.speed;
			env->player.y += sin(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[KEY_A])
	{
		env->player.x -= cos(env->player.cam.angle) * env->player.speed;
		env->player.y += sin(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x += cos(env->player.cam.angle) * env->player.speed;
			env->player.y -= sin(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[RIGHT_KEY])
		env->player.cam.angle += (float)ANGLE_DELTA * env->player.speed * 10.0f;
	if (env->keys[LEFT_KEY])
		env->player.cam.angle -= (float)ANGLE_DELTA * env->player.speed * 10.0f;
}

int		base(void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	if (game_over(env))
		return (0);
	handle_moves(env);
	handle_keys(env);
	set_background(env);
	env->img_data = ray_casting(env);
	if (env->war)
		handle_enemys(env);
	if (env->weapon < W_MAX)
		handle_weapon(env);
	draw_minimap(env);
	barre_de_vie(env, WDT / 1.5, HGT - HGT / 8);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	return (0);
}

int		release_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	env->keys[key] = false;
	return (0);
}

int		press_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	if (key == ESC_KEY)
		exit(EXIT_SUCCESS);
	else if (key == KEY_N)
		env->night = env->night ? false : true;
	else
		env->keys[key] = true;
	return (0);
}
