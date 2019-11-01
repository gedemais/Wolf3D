/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_zombie.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:02:57 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/01 21:51:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool	is_in_fov(t_mlx *env, float zx, float zy, t_z_render *r)
{
	float	vec_x;
	float	vec_y;

	vec_x = zx - env->player.x;
	vec_y = zy - env->player.y;

	env->player.eye_x = cosf(ft_to_radians(env->player.cam.angle));
	env->player.eye_y = sinf(ft_to_radians(env->player.cam.angle));

	r->dist = sqrtf(vec_x * vec_x + vec_y * vec_y);

	r->z_angle = atan2f(env->player.eye_y, env->player.eye_x) - atan2f(vec_y, vec_x);
	if (r->z_angle < PI)
		r->z_angle += PI + PI;
	if (r->z_angle > PI)
		r->z_angle -= PI + PI;
	return (fabs(r->z_angle) < env->player.cam.fov / 2.0f);
}

void	blit_zombie(t_mlx *env, t_sprite sp, t_z_render r)
{
	unsigned int	x;
	unsigned int	y;
	float			sx;
	float			sy;
	int				color;
	int				column;
	char			alph[4];

	ft_memcpy(&alph[0], &sp.alpha, sizeof(int));
	x = 0;
	while (x < r.width)
	{
		y = 0;
		while (y < r.height)
		{
			sx = (float)x / (float)r.width;
			sy = (float)y / (float)r.height;
			color = *(int*)&sp.frame[(int)(sy * 288 * 288 * 4) + (int)(sx * 288 * 4)];
			column = (int)(r.middle + x - (r.width / 2.0f));
			printf("column = %d\n", column);
			if (column > 0 || column < WDT)
				ft_fill_pixel(env->img_data, column, r.cieling + y, color);
			y++;
		}
		x++;
	}
}

void	render_zombie(t_mlx *env, t_zombie *z)
{
	t_z_render	r;

	if (!is_in_fov(env, z->x, z->y, &r) && r.dist >= 1)
		return ;

	r.cieling = (float)HGT / 2.0f - (float)HGT / r.dist;
	r.floor = (float)HGT - r.cieling;
	r.height = r.floor - r.cieling;
	r.ratio = (float)env->sprites[ZOMBIE].height / (float)env->sprites[ZOMBIE].width;
	r.width = r.height / r.ratio;

	r.middle = (0.5f * (r.z_angle / (env->player.cam.fov / 2.0f)) + 0.5f) * (float)WDT;
//	ft_fill_pixel(env->img_data, 0xffffff, (int)r.middle, 590);
	if (r.dist > 2)
		blit_zombie(env, env->sprites[ZOMBIE], r);
}
