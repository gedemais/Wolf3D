/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:17 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/24 19:07:39 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_col(t_mlx *env, unsigned int x, float updown[2], int type)
{
	unsigned int	y;

	y = 0;
	while (y < HGT)
	{
		if (y < updown[0])
			ft_fill_pixel(env->img_data, x, y, 0xaa2020);
		else if (y >= updown[0] && y < updown[1])
		{
			if (type == 1)
				ft_fill_pixel(env->img_data, x, y, 0xffff00);
			else if (type == 2)
				ft_fill_pixel(env->img_data, x, y, 0x000000);
		}
		else
			ft_fill_pixel(env->img_data, x, y, 0x555555);
		y++;
	}
}

char	*ray_casting(t_mlx *env)
{
	t_ray			ray;
	t_player		*p;
	unsigned int	i;
	float			dcieling;
	float			dfloor;

	i = 0;
	p = ((t_player*)&env->player);
	while (i < WDT)
	{
		ray.angle = (float)(p->cam.angle - p->cam.fov / 2) + (float)i / (float)WDT * p->cam.fov;
		ray.hit = 0;

		p->eye_x = sin(ray.angle);
		p->eye_y = cos(ray.angle);
		ray.dist = 0;
		while (!ray.hit)
		{
			ray.dist += RAY_STEP;
			ray.test_x = (int)(p->x + p->eye_x * ray.dist);
			ray.test_y = (int)(p->y + p->eye_y * ray.dist);
			if (env->map[ray.test_x][ray.test_y].type > 0)
				ray.hit = env->map[ray.test_x][ray.test_y].type;
		}
		dcieling = (float)(HGT / 2.0f) - (float)(HGT / ray.dist);
		dfloor = (float)((float)HGT - dcieling);
		dcieling *= cosf(ft_to_radians(ray.angle));
		draw_col(env, i, (float[2]){dcieling, dfloor}, ray.hit);
		i++;
	}
	return (env->img_data);
}
