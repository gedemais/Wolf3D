/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:17 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/04 03:09:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_fill_texture(char *img_str, int x, int y, int color)
{
	int		pos;

	if (x >= WDT || x < 0 || y >= HGT || y < 0)
		return ;
	pos = (abs(y - 1) * WDT + x) * sizeof(int);
	img_str[pos + 2] = color >> 16 & 255;
	img_str[pos + 1] = color >> 8 & 255;
	img_str[pos] = color & 255;
}

void	draw_col(t_mlx *env, unsigned int x, float updown[2], t_ray *ray)
{
	int				pos;
	unsigned int	y;

	y = 0;
	while (y < HGT)
	{
		if (y >= updown[0] && y < updown[1] - 1)
		{
			ray->sample_y = ((float)y - updown[0]) / (updown[1] - updown[0]);
			pos = (abs((int)(ray->sample_y * 288) - 1) * 288 + (int)(ray->sample_x * 288)) * sizeof(int);
			if (env->night)
				ft_fill_pixel(env->img_data, x, y, *(int*)&env->sprites[ray->sprite].frame[pos]);
			else
				ft_fill_texture(env->img_data, x, y, *(int*)&env->sprites[ray->sprite].frame[pos]);
		}
		y++;
	}
}

void	set_background(t_mlx *env)
{
	int		x;
	int		y;

	y = HGT / 2;
	*blit_alpha() = true;
	blit_sprite(env, env->sprites[NB_SPRITES - 1], 0, 0);
	blit_sprite(env, env->sprites[NB_SPRITES - 1], 288, 0);
	blit_sprite(env, env->sprites[NB_SPRITES - 1], 512, 0);
	while (y < HGT)
	{
		x = 0;
		while (x < WDT)
		{
			ft_fill_pixel(env->img_data, x, y, 0x333333);
			x++;
		}
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
	float			rectify;

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
			{
				ray.hit = env->map[ray.test_x][ray.test_y].type;
				
				ray.bloc_mx = (float)ray.test_x + 0.5f;
				ray.bloc_my = (float)ray.test_y + 0.5f;

				ray.hit_x = p->x + p->eye_x * ray.dist;
				ray.hit_y = p->y + p->eye_y * ray.dist;

				ray.bloc_angle = atan2f((ray.hit_y - ray.bloc_my), (ray.hit_x - ray.bloc_mx));

				if (ray.bloc_angle >= -3.14159f * 0.25f && ray.bloc_angle < 3.14159f * 0.25f)
				{
					ray.sprite = ray.hit == BLOC_SPAWN ? MABOYE : WALL_NORTH;
					ray.sample_x = ray.hit_y - (float)ray.test_y;
				}
				else if (ray.bloc_angle >= 3.14159f * 0.25f && ray.bloc_angle < 3.14159f * 0.75f)
				{
					ray.sprite = ray.hit == BLOC_SPAWN ? MABOYE : WALL_SOUTH;
					ray.sample_x = ray.hit_x - (float)ray.test_x;
				}
				else if (ray.bloc_angle < -3.14159f * 0.25f && ray.bloc_angle >= -3.14159f * 0.75f)
				{
					ray.sprite = ray.hit == BLOC_SPAWN ? MABOYE : WALL_EST;
					ray.sample_x = ray.hit_x - (float)ray.test_x;
				}
				else if (ray.bloc_angle >= 3.14159f * 0.75f || ray.bloc_angle < -3.14159f * 0.75f)
				{
					ray.sprite = ray.hit == BLOC_SPAWN ? MABOYE : WALL_WEST;
					ray.sample_x = ray.hit_y - (float)ray.test_y;
				}
			}
		}
		rectify = ((float)i * p->cam.fov / (float)WDT) - p->cam.fov / 2.0f;
//		ray.dist *= cosf(rectify) + 0.25;
		dcieling = (float)(HGT / 2.0f) - (float)(HGT / ray.dist);
		dfloor = (float)((float)HGT - dcieling);

		env->z_buff[i] = ray.dist;
		draw_col(env, i, (float[2]){dcieling, dfloor}, &ray);
		i++;
	}
	return (env->img_data);
}
