/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemys.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:02 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 07:08:12 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		manage_waves(t_mlx *env)
{
	if (env->nb_killed < WAVE_1)
		return (W_KNIFE);
	else if (env->nb_killed < WAVE_2)
		return (W_GUN);
	else if (env->nb_killed < WAVE_3)
		return (W_MP40);
	else
		return (W_MINIGUN);
}

void	death_priest(t_mlx *env)
{
	t_zombie	*tmp;

	tmp = env->zombie;
	while (tmp)
	{
		if (tmp->hp <= 0)
		{
			z_snap_node(&env->zombie, tmp);
			env->nb_killed++;
			tmp = env->zombie;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	handle_enemys(t_mlx *env)
{
	static int	laps = 0;

	env->weapon = manage_waves(env);
	death_priest(env);
	omniscience(env);
	if (MAX_ZOMBIES <= z_lstlen(env->zombie))
		return ;
	else if (laps > SPAWN_LAPS && !(laps = 0) && z_pushfront(&env->zombie,
		z_lstnew(env)) != 0)
		return ;
	laps++;
}
