/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omniscience.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:06:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/24 21:39:10 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		apply_a_star(t_zombie *z)
{
	
}

void		omniscience(t_mlx *env)
{
	t_zombie		*tmp;
	static t_pos	player = {0, 0};

	if (player.x == env->player.x && player.y == env->player.y)
		return ;
	player.x = env->player.x;
	player.y = env->player.y;
	tmp = env->zombie;
	while (tmp)
	{
		apply_a_star(tmp);
		tmp = tmp->next;
	}
}
