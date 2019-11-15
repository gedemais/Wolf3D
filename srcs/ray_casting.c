/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:17 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 07:39:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_col(t_mlx *env, unsigned int x, float updown[2], t_ray *ray)
{
	int				pos;
	float			sub;
	int				xscale;
	unsigned int	y;

	y = 0;
	sub = updown[1] - updown[0];
	xscale = (ray->sample_x * 288);
	while (y < HGT)
	{
		if (y >= updown[0] && y < updown[1] - 1)
		{
			ray->sample_y = ((float)y - updown[0]) / sub;
			pos = (abs((int)(ray->sample_y * 288) - 1) * 288 + xscale) * 4;
			if (env->night)
				ft_fill_pixel(env->img_data, x, y,
					*(int*)&env->sprites[ray->sprite].frame[pos]);
			else
				ft_fill_texture(env->img_data, x, y,
					*(int*)&env->sprites[ray->sprite].frame[pos]);
		}
		y++;
	}
}

void	set_background(t_mlx *env)
{
	int		y;
	int		half;

	y = env->math.half_hgt;
	half = y * WDT * 4;
	*blit_alpha() = true;
	blit_sprite(env, env->sprites[NB_SPRITES - 1], 0, 0);
	blit_sprite(env, env->sprites[NB_SPRITES - 1], 288, 0);
	blit_sprite(env, env->sprites[NB_SPRITES - 1], 512, 0);
	ft_memset(&env->img_data[half], 0x33, half);
}

void	collision(t_ray *r, t_player *p)
{
	r->bloc_mx = (float)r->test_x + 0.5f;
	r->bloc_my = (float)r->test_y + 0.5f;
	r->hit_x = p->x + p->eye_x * r->dist;
	r->hit_y = p->y + p->eye_y * r->dist;
	r->bloc_angle = atan2f((r->hit_y - r->bloc_my), (r->hit_x - r->bloc_mx));
	if (r->bloc_angle >= -PI_4 && r->bloc_angle < PI_4)
	{
		r->sprite = r->hit == BLOC_SPAWN ? MABOYE : WALL_NORTH;
		r->sample_x = r->hit_y - (float)r->test_y;
	}
	else if (r->bloc_angle >= PI_4 && r->bloc_angle < PI_34)
	{
		r->sprite = r->hit == BLOC_SPAWN ? MABOYE : WALL_SOUTH;
		r->sample_x = r->hit_x - (float)r->test_x;
	}
	else if (r->bloc_angle < -PI_4 && r->bloc_angle >= -PI_34)
	{
		r->sprite = r->hit == BLOC_SPAWN ? MABOYE : WALL_EST;
		r->sample_x = r->hit_x - (float)r->test_x;
	}
	else if (r->bloc_angle >= PI_34 || r->bloc_angle < -PI_34)
	{
		r->sprite = r->hit == BLOC_SPAWN ? MABOYE : WALL_WEST;
		r->sample_x = r->hit_y - (float)r->test_y;
	}
}

void	shoot_ray(t_mlx *env, t_ray *ray, t_player *p)
{
	p->eye_x = sin(ray->angle);
	p->eye_y = cos(ray->angle);
	ray->dist = 0;
	while (!ray->hit)
	{
		ray->dist += RAY_STEP;
		ray->test_x = (int)(p->x + p->eye_x * ray->dist);
		ray->test_y = (int)(p->y + p->eye_y * ray->dist);
		if (env->map[ray->test_x][ray->test_y].type != BLOC_VOID)
		{
			ray->hit = env->map[ray->test_x][ray->test_y].type;
			collision(ray, p);
		}
	}
}

char	*ray_casting(t_mlx *env)
{
	t_ray			ray;
	t_player		*p;
	unsigned int	i;
	float			rectify;
	float			bounds[2];

	i = 0;
	p = ((t_player*)&env->player);
	while (i < WDT)
	{
		ray.angle = (float)(p->cam.angle - env->math.half_fov) +
			(float)i / (float)WDT * p->cam.fov;
		ray.hit = 0;
		shoot_ray(env, &ray, p);
		rectify = ((float)i * p->cam.fov / (float)WDT) - env->math.half_fov;
		ray.dist *= cosf(rectify) + 0.33f;
		bounds[0] = env->math.half_hgt - (float)(HGT / ray.dist);
		bounds[1] = (float)HGT - bounds[0];
		env->z_buff[i].val = ray.dist;
		env->z_buff[i].wall = true;
		draw_col(env, i, bounds, &ray);
		i++;
	}
	return (env->img_data);
}
