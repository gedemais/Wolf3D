/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:26 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/16 05:26:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	fast_isr(float n)
{
	float	x2;
	float	threehalfs;
	t_isr	conv;

	x2 = n * 0.5f;
	threehalfs = 1.5f;
	conv = (t_isr){n};
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (x2 * conv.f * conv.f));
	return (1.0f / conv.f);
}

float	compute_dist(int ax, int ay, int bx, int by)
{
	int		a;
	float	as;
	int		b;
	float	bs;

	a = abs(bx - ax);
	b = abs(by - ay);
	as = a * a;
	bs = b * b;
	return (fast_isr(as + bs));
}

int		*color(void)
{
	static int	var = 0;

	return (&var);
}

bool	*blit_alpha(void)
{
	static bool		val = false;

	return (&val);
}

void	init_maths(t_mlx *env)
{
	env->nb_killed = 1;
	env->math.half_fov = env->player.cam.fov / 2.0f;
	env->math.half_wdt = WDT / 2.0f;
	env->math.half_hgt = HGT / 2.0f;
	env->math.wdt4 = WDT * 4;
	env->math.hgt4 = HGT * 4;
	env->math.img_bytes = WDT * HGT * 4;
}
