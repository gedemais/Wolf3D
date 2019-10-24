/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:11:26 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/24 20:11:41 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	compute_dist(t_player p, unsigned int i, unsigned int j)
{
	int	a;
	int	as;
	int	b;
	int	bs;

	a = p.x - j;
	as = a * a;
	b = p.y - i;
	bs = b * b;
	return (sqrt(as + bs));
}
