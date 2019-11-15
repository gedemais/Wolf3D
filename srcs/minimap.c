/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 05:57:01 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 06:38:39 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_color(char type)
{
	if (type == BLOC_VOID)
		*color() = 0xaaaaaa;
	else if (type == BLOC_FULL)
		*color() = 0xffffff;
	else if (type == BLOC_SPAWN)
		*color() = 0x000000;
}

void	draw_square(t_mlx *env, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_fill_pixel(env->img_data, x + j, y + i, *color());
			j++;
		}
		i++;
	}
}

void	point_zombies(t_mlx *env)
{
	t_zombie	*tmp;

	tmp = env->zombie;
	while (tmp)
	{
		draw_square(env, (int)tmp->x * MINIMAP_SIZE, (int)tmp->y * MINIMAP_SIZE,
			MINIMAP_SIZE);
		tmp = tmp->next;
	}
}

void	draw_fov(t_mlx *env, t_player *p)
{
	float			x;
	float			y;

	*color() = 0x00ff00;
	x = p->x + 3 * sinf(env->player.cam.angle - PI / 8);
	y = p->y + 3 * cosf(env->player.cam.angle - PI / 8);
	ft_draw_line(env, (int[2]){y * MINIMAP_SIZE, x * MINIMAP_SIZE},
		(int[2]){(int)p->y * MINIMAP_SIZE, (int)p->x * MINIMAP_SIZE});
	x = p->x + 3 * sinf(env->player.cam.angle + PI / 8);
	y = p->y + 3 * cosf(env->player.cam.angle + PI / 8);
	ft_draw_line(env, (int[2]){y * MINIMAP_SIZE, x * MINIMAP_SIZE},
		(int[2]){(int)p->y * MINIMAP_SIZE, (int)p->x * MINIMAP_SIZE});
	draw_square(env, (p->y - 0.5f) * MINIMAP_SIZE, (p->x - 0.5f) * MINIMAP_SIZE,
		MINIMAP_SIZE);
}

void	draw_minimap(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < env->map_hgt)
	{
		j = 0;
		while (j < env->map_wdt)
		{
			get_color(env->map[i][j].type);
			draw_square(env, j * MINIMAP_SIZE, i * MINIMAP_SIZE, MINIMAP_SIZE);
			j++;
		}
		i++;
	}
	draw_fov(env, &env->player);
	*color() = 0x0000ff;
	point_zombies(env);
}
