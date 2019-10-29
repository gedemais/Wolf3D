/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:26 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/29 17:53:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	return (sqrtf(as + bs));
}
