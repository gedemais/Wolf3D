/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_zombie.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:02:57 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/16 04:24:30 by gedemais         ###   ########.fr       */
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
	r->z_angle = atan2f(eye_y, eye_x) - atan2f(vec_y, vec_x);
	if (r->z_angle < -PI)
		r->z_angle += PI * 2.0f;
	if (r->z_angle > PI)
		r->z_angle -= PI * 2.0f;
	return (fabs(r->z_angle) < env->player.cam.fov / 2.0f);
}

void	optimize_algebra(t_z_render *r, float divs[3], int *x, float *sx)
{
	divs[0] = r->width / 2.0f;
	divs[1] = 1 / r->width;
	divs[2] = 1 / r->height;
	*x = -1;
	*sx = 0.0f;
}

bool	do_pixel(t_mlx *env, t_z_render *r, int column, int color)
{
	if (color != 0 && column >= 0 && column < WDT
		&& env->z_buff[column].val >= r->dist)
	{
		env->z_buff[column].val = r->dist;
		env->z_buff[column].wall = false;
		return (true);
	}
	return (false);
}

void	blit_zombie(t_mlx *env, t_sprite sp, t_z_render *r)
{
	int				it[2];
	float			sample[2];
	float			divs[3];
	int				column;
	int				color;

	optimize_algebra(r, divs, &it[0], &sample[0]);
	while (++it[0] < r->width)
	{
		it[1] = -1;
		sample[1] = 0.0f;
		while (++it[1] < r->height)
		{
			color = *(int*)&sp.frame[(abs((int)(sample[1] * 288) - 1) *
				288 + (int)(sample[0] * 288)) * 4];
			column = (int)(r->middle + it[0] - divs[0]);
			if (do_pixel(env, r, column, color))
				ft_memcpy(&env->img_data[((int)(r->cieling + it[1] - 1) *
					env->math.wdt4) + (column * 4)], &color, 4);
			sample[1] += divs[2];
		}
		sample[0] += divs[1];
	}
}

void	render_zombie(t_mlx *env, t_zombie *z)
{
	t_z_render	r;

	if (!is_in_fov(env, z->y, z->x, &r) || r.dist <= 0.5)
		return ;
	r.cieling = env->math.half_hgt - (float)HGT / r.dist;
	r.floor = HGT - (int)r.cieling;
	r.height = r.floor - r.cieling;
	r.ratio = 1.0f;
	r.width = r.height / r.ratio;
	r.middle = (0.5f * (r.z_angle / env->math.half_fov) + 0.5f) * (float)WDT;
	z->mid = r.middle;
	z->width = r.width;
	blit_zombie(env, env->sprites[ZOMBIE], &r);
}
