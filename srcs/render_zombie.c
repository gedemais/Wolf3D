/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_zombie.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:02:57 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/03 23:48:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool	is_in_fov(t_mlx *env, float zx, float zy, t_z_render *r)
{
	float	vec_x;
	float	vec_y;
	float	eye_x;
	float	eye_y;

	vec_x = zx - env->player.x;
	vec_y = zy - env->player.y;

	r->dist = fast_isr(vec_x * vec_x + vec_y * vec_y);
	eye_x = sinf(env->player.cam.angle);
	eye_y = cosf(env->player.cam.angle);

//	printf("zombie at %f %f\nplayer at %f %f\ndist = %f\n", zx, zy, env->player.x, env->player.y, r->dist);
	r->z_angle = atan2f(eye_y, eye_x) - atan2f(vec_y, vec_x);
	if (r->z_angle < -PI)
		r->z_angle += PI * 2.0f;
	if (r->z_angle > PI)
		r->z_angle -= PI * 2.0f; return (fabs(r->z_angle) < env->player.cam.fov / 2.0f);
}

void	blit_zombie(t_mlx *env, t_sprite sp, t_z_render *r)
{
	unsigned int	x;
	unsigned int	y;
	float			sample_x;
	float			sample_y;
	int				column;
	int				color;

	x = 0;
	while (x < r->width)
	{
		y = 0;
		while (y < r->height)
		{
			sample_x = x / r->width;
			sample_y = y / r->height;
			color = *(int*)&sp.frame[(abs((int)(sample_y * 288) - 1) * 288 + (int)(sample_x * 288)) * 4];
			column = (int)(r->middle + x - (r->width / 2.0f));
			if (color != 0 && column >= 0 && column < WDT && env->z_buff[column] >= r->dist)
			{
				env->z_buff[column] = r->dist;
				ft_memcpy(&env->img_data[((int)(r->cieling + y - 1) * WDT * 4) + (column * 4)], &color, sizeof(int));
			}
			y++;
		}
		x++;
	}
}

void	render_zombie(t_mlx *env, t_zombie *z)
{
	t_z_render	r;

	if (!is_in_fov(env, z->y, z->x, &r) || r.dist <= 0.5)
		return ;
	r.cieling = (float)(HGT / 2.0f) - (float)HGT / r.dist;
	r.floor = HGT - (int)r.cieling;
	r.height = r.floor - r.cieling;
	r.ratio = 1.0f;
	r.width = r.height / r.ratio;
	r.middle = (0.5f * (r.z_angle / (env->player.cam.fov / 2.0f)) + 0.5f) * (float)WDT;

	z->mid = r.middle;
	z->width = r.width;
	blit_zombie(env, env->sprites[ZOMBIE], &r);
}
