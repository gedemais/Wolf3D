/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barre.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 07:26:01 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/04 22:10:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	barre_bounds(t_mlx *e, int px, int py)
{
	unsigned int	y;

	y = 0;
	*color() = 0x0000ff;
	ft_draw_line(e, (int[2]){px, py}, (int[2]){px + 200, py});
	ft_draw_line(e, (int[2]){px, py + 1}, (int[2]){px + 200, py + 1});
	ft_draw_line(e, (int[2]){px, py + 2}, (int[2]){px + 200, py + 2});
	ft_draw_line(e, (int[2]){px, py + 31}, (int[2]){px + 202, py + 31});
	ft_draw_line(e, (int[2]){px, py + 32}, (int[2]){px + 202, py + 32});
	ft_draw_line(e, (int[2]){px, py + 33}, (int[2]){px + 202, py + 33});
	while (y < 32)
	{
		ft_draw_line(e, (int[2]){px, py + y}, (int[2]){px + 2, py + y});
		ft_draw_line(e, (int[2]){px + 200, py + y}, (int[2]){px + 202, py + y});
		y++;
	}
}

void	barre_de_vie(t_mlx *env, int px, int py)
{
	unsigned int	y;

	y = 3;
	barre_bounds(env, px, py);
	while (y < 31)
	{
		*color() = 0x00ff00;
		ft_draw_line(env, (int[2]){px + 3, py + y},
			(int[2]){px + env->player.hp * 2 - 2, py + y});
		*color() = 0xff0000;
		ft_draw_line(env, (int[2]){px + env->player.hp * 2 - 2, py + y},
			(int[2]){px + 200, py + y});
		y++;
	}
}
