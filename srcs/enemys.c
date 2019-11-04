/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemys.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:02 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/04 07:44:59 by gedemais         ###   ########.fr       */
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
/*
void	print_lst(t_zombie *lst)
{
	t_zombie	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("---------\nhp = %d | damages = %d | x = %f | y = %f\n", tmp->hp, tmp->damages, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	printf("\n\n\n");
}
*/
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

void	render_zombies(t_mlx *env)
{
	t_zombie	*tmp;

	tmp = env->zombie;
	*blit_alpha() = false;
	while (tmp)
	{
//		blit_sprite(env, env->sprites[21], WDT / 2, HGT / 2);
		tmp = tmp->next;
	}
}

void	handle_enemys(t_mlx *env)
{
	static int	laps = 0;

	env->weapon = manage_waves(env);
	death_priest(env);
	omniscience(env);
	if (env->nb_killed <= z_lstlen(env->zombie))
		return ;
	else if (laps > 100 && !(laps = 0) && z_pushfront(&env->zombie, z_lstnew(env)) != 0)
		return ;
	laps++;
}
