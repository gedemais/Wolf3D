/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:26 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/26 16:02:27 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	compute_dist(int x, int y, int bx, int by)
{
	int	a;
	int	as;
	int	b;
	int	bs;

	a = bx - x;
	as = a * a;
	b = by - y;
	bs = b * b;
	return (sqrt(as + bs));
}
