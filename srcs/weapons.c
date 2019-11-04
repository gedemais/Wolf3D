/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:44:33 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/04 00:20:00 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_weapons(t_mlx *env)
{
	env->weapon = W_MP40;
	env->weapons[W_KNIFE].cadency = 10;
	env->weapons[W_KNIFE].damages = 20;
	env->weapons[W_KNIFE].full_auto = false;
	env->weapons[W_KNIFE].speed = 2;
	env->weapons[W_KNIFE].nb_frames = 3;
	env->weapons[W_GUN].cadency = 5;
	env->weapons[W_GUN].damages = 30;
	env->weapons[W_GUN].full_auto = false;
	env->weapons[W_GUN].speed = 1;
	env->weapons[W_GUN].nb_frames = 3;
	env->weapons[W_MP40].cadency = 2;
	env->weapons[W_MP40].damages = 20;
	env->weapons[W_MP40].full_auto = true;
	env->weapons[W_MP40].speed = 1;
	env->weapons[W_MP40].nb_frames = 2;
	env->weapons[W_MINIGUN].cadency = 1;
	env->weapons[W_MINIGUN].damages = 40;
	env->weapons[W_MINIGUN].full_auto = true;
	env->weapons[W_MINIGUN].speed = 1;
	env->weapons[W_MINIGUN].nb_frames = 2;
}



void	apply_damages(t_mlx *env)
{
	t_zombie	*tmp;
	int			half_wdt;

	tmp = env->zombie;
	half_wdt = WDT / 2;
	while (tmp)
	{
		if (fabs(half_wdt - tmp->mid) < tmp->width / 2)
		{
			printf("%d\n", tmp->hp);
			tmp->hp -= env->weapons[(int)env->weapon].damages;
			break ;
		}
		tmp = tmp->next;
	}
}

void	shot(t_mlx *env, bool *done)
{
	static int	step = 0;
	int		speed;

	speed = env->weapons[(int)env->weapon].speed;
	if (step / speed < env->weapons[(int)env->weapon].nb_frames)
	{
		blit_sprite(env, env->sprites[(int)env->weapon + step / speed + 2], (WDT / 2 - env->sprites[(int)env->weapon + step / speed + 2].width / 2), HGT - env->sprites[(int)env->weapon + step / speed + 2].height);
		step++;
	}
	else
	{
		apply_damages(env);
		blit_sprite(env, env->sprites[(int)env->weapon], (WDT / 2 - env->sprites[(int)env->weapon].width / 2), HGT - env->sprites[(int)env->weapon].height);
		step = 0;
		*done = env->weapons[(int)env->weapon].full_auto ? false : true;
	}
}

void	handle_weapon(t_mlx *env)
{
	static bool		stop = false;
	int				i;

	i = 0;
	draw_reticle(env);
	*blit_alpha() = false;
	if (env->keys[SPACE_KEY] && !stop)
		shot(env, &stop);
	else
		blit_sprite(env, env->sprites[(int)env->weapon], (WDT / 2 - env->sprites[(int)env->weapon].width / 2), HGT - env->sprites[(int)env->weapon].height);
	if (!env->keys[SPACE_KEY])
		stop = false;
}
