/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:14:53 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/03 18:12:40 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_horizontal(void *param, t_draw var)
{
	var.cumul = var.dx / 2;
	while (var.j <= var.dx)
	{
		var.x += var.xinc;
		var.cumul += var.dy;
		if (var.cumul >= var.dx)
		{
			var.cumul -= var.dx;
			var.y += var.yinc;
		}
		ft_fill_pixel(MPA->IMGD, var.x, var.y, *color());
		var.j++;
	}
}

void	ft_vertical(void *param, t_draw var)
{
	var.cumul = var.dy / 2;
	while (var.j <= var.dy)
	{
		var.y += var.yinc;
		var.cumul += var.dx;
		if (var.cumul >= var.dy)
		{
			var.cumul -= var.dy;
			var.x += var.xinc;
		}
		var.j++;
		ft_fill_pixel(MPA->IMGD, var.x, var.y, *color());
	}
}

void	ft_draw_line(void *param, int s[2], int e[2])
{
	t_draw	var;

	var.j = 1;
	var.x = s[0];
	var.y = s[1];
	var.dx = e[0] - s[0];
	var.dy = e[1] - s[1];
	var.xinc = (var.dx > 0) ? 1 : -1;
	var.yinc = (var.dy > 0) ? 1 : -1;
	var.dx = abs(var.dx);
	var.dy = abs(var.dy);
	ft_fill_pixel(MPA->IMGD, var.x, var.y, *color());
	if (var.dx > var.dy)
		ft_horizontal(MPA, var);
	else
		ft_vertical(MPA, var);
}
