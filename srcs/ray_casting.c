/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:17 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/20 20:44:22 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_col(t_mlx *env, unsigned int x, float dcieling, float dfloor)
{
	unsigned int	y;

	y = 0;
	while (y < HGT)
	{
	//	printf("x = %d\ny = %d\n\n", x, y);
		if (y < dcieling)
			ft_fill_pixel(env->img_data, x, y, 0x555555);
		else if (y >= dcieling && y < dfloor)
			ft_fill_pixel(env->img_data, x, y, 0x00ff00);
		else
			ft_fill_pixel(env->img_data, x, y, 0x555555);
		y++;
	}
}

char	*ray_casting(t_mlx *env)
{
	t_ray			ray;
	float			ray_angle;
	float			dist;
	t_player		*p;
	unsigned int	i;
	float			dcieling;
	float			dfloor;

	i = 0;
	p = ((t_player*)&env->player);
	ray.sq_hgt = env->map_hgt * env->map_hgt;
	ray.sq_wdt = env->map_wdt * env->map_wdt;
	while (i < WDT)
	{
		ray_angle = (float)(p->cam.angle - p->cam.fov / 2) + (float)i / (float)WDT * p->cam.fov;
		ray.hit = false;

		p->eye_x = sin(ray_angle);
		p->eye_y = cos(ray_angle);

		dist = 0;
		while (!ray.hit)
		{
			dist += RAY_STEP;
			ray.test_x = (int)(p->x + p->eye_x * dist);
			ray.test_y = (int)(p->y + p->eye_y * dist);

			if (ray.test_x < 0 || ray.test_x > (int)env->map_wdt
				|| ray.test_y < 0 || ray.test_y > (int)env->map_hgt)
			{
				ray.hit = true;
				dist = sqrt(ray.sq_hgt + ray.sq_wdt);
			}
			else if (env->map[ray.test_x][ray.test_y].type == 1)
				ray.hit = true;
		}
		dcieling = (float)(HGT / 2.0f) - (float)(HGT / dist);
		dfloor = (float)((float)HGT - dcieling);
		draw_col(env, i, dcieling, dfloor);
		i++;
	}
	return (env->img_data);
}
