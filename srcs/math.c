/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:26 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/03 22:32:38 by gedemais         ###   ########.fr       */
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
