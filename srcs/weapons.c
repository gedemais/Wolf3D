/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:44:33 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 07:57:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_weapons(t_mlx *env)
{
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

	tmp = env->zombie;
	while (tmp)
	{
		if (fabs(env->math.half_wdt - tmp->mid) < (tmp->width / 2 -
			(60 * tmp->width / 288)) && !env->z_buff[env->math.half_wdt].wall)
		{
			if (env->weapon == W_KNIFE && compute_dist(env->player.y,
				env->player.x, tmp->x, tmp->y) > 3.0f)
			{
				tmp = tmp->next;
				continue ;
			}
			tmp->hp -= env->weapons[(int)env->weapon].damages;
			break ;
		}
		tmp = tmp->next;
	}
}

void	shot(t_mlx *env, bool *done, bool *in)
{
	static int	step = 0;
	int			speed;
	int			sp;

	speed = env->weapons[(int)env->weapon].speed;
	if (step / speed < env->weapons[(int)env->weapon].nb_frames)
	{
		sp = (int)env->weapon + step / speed + 1;
		blit_sprite(env, env->sprites[sp], (env->math.half_wdt -
			env->sprites[sp].width / 2), HGT - env->sprites[sp].height);
		step++;
	}
	else
	{
		apply_damages(env);
		blit_sprite(env, env->sprites[(int)env->weapon], (env->math.half_wdt -
			env->sprites[(int)env->weapon].width / 2), HGT -
			env->sprites[(int)env->weapon].height);
		step = 0;
		*done = env->weapons[(int)env->weapon].full_auto ? false : true;
	}
	*in = *done ? false : true;
}

void	handle_weapon(t_mlx *env)
{
	static bool		stop = false;
	static bool		in = false;
	int				i;

	i = 0;
	draw_reticle(env);
	*blit_alpha() = false;
	if ((env->keys[SPACE_KEY] && !stop)
		|| (!env->weapons[(int)env->weapon].full_auto && in))
		shot(env, &stop, &in);
	else
	{
		in = false;
		blit_sprite(env, env->sprites[(int)env->weapon],
			(WDT / 2 - env->sprites[(int)env->weapon].width / 2),
			HGT - env->sprites[(int)env->weapon].height);
	}
	if (!env->keys[SPACE_KEY])
		stop = false;
}
