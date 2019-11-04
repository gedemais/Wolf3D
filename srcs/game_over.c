/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:25:34 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/04 05:41:43 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool	game_over(t_mlx *env)
{
	static int	i = 0;
	static bool	dead = false;
	t_sprite	*sprite;

	sprite = NULL;
	if (env->player.hp <= 0)
		dead = true;
	if (!dead)
		return (false);
	if (i >= 3)
	{
		sprite = (rand() % 10 < 2) ? &env->sprites[MABOYE] : &env->sprites[GAME_OVER];
		i = 0;
	}
	if (sprite)
	{
		ft_memset(env->img_data, 30, sizeof(int) * WDT * HGT);
		blit_sprite(env, *sprite, WDT / 2 - 144, HGT / 2 - 144);
	}
	i++;
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	return (dead);
}
