/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reticle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 07:44:01 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 07:44:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_reticle(t_mlx *env)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	halfs[3];

	halfs[0] = RETICLE_SIZE / 2;
	halfs[1] = WDT / 2;
	halfs[2] = HGT / 2;
	i = halfs[1] - halfs[0] - 1;
	j = halfs[2] - halfs[0] - 1;
	x = halfs[1] + halfs[0];
	y = halfs[2] + halfs[0];
	while (++i < x)
	{
		ft_fill_pixel(env->img_data, i, halfs[2], 0xffffff);
		ft_fill_pixel(env->img_data, i, halfs[2] - 1, 0xffffff);
		ft_fill_pixel(env->img_data, i, halfs[2] + 1, 0xffffff);
	}
	while (++j < y)
	{
		ft_fill_pixel(env->img_data, halfs[1], j, 0xffffff);
		ft_fill_pixel(env->img_data, halfs[1] - 1, j, 0xffffff);
		ft_fill_pixel(env->img_data, halfs[1] + 1, j, 0xffffff);
	}
}
