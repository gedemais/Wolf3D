/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omniscience.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:06:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 07:11:37 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		apply_a_star(t_mlx *env, t_node *nodes, t_node *s_e[2], t_zombie *z)
{
	float	tmp[4];
	float	speed;

	speed = 0.1;
	tmp[0] = 0.0f;
	tmp[1] = 0.0f;
	tmp[2] = z->x;
	tmp[3] = z->y;
	if (z->refresh == 0)
	{
		a_star(env, nodes, s_e, tmp);
		z->refresh = 10;
	}
	else
		z->refresh--;
	z->x += tmp[0] * speed;
	z->y += tmp[1] * speed;
}

void		fill_neighbours(t_mlx *env, t_node *n)
{
	unsigned int	x;
	unsigned int	y;
	int				pos;

	y = 0;
	while (y < env->map_hgt)
	{
		x = 0;
		while (x < env->map_wdt)
		{
			pos = y * env->map_wdt + x;
			n[pos].n[0] = (y > 0) ? &n[(y - 1) * env->map_wdt + x] : NULL;
			n[pos].n[1] = (y < env->map_hgt - 1) ? &n[(y + 1) * env->map_wdt +
				x] : NULL;
			n[pos].n[2] = (x > 0) ? &n[y * env->map_wdt + (x - 1)] : NULL;
			n[pos].n[3] = (x < env->map_wdt - 1) ? &n[y * env->map_wdt +
				(x + 1)] : NULL;
			x++;
		}
		y++;
	}
}

void		reset_values(t_mlx *env, t_node *nodes)
{
	int				pos;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < env->map_hgt)
	{
		x = 0;
		while (x < env->map_wdt)
		{
			pos = y * env->map_wdt + x;
			nodes[pos].visited = false;
			nodes[pos].ggoal = 10000000;
			nodes[pos].lgoal = 10000000;
			nodes[pos].parent = NULL;
			x++;
		}
		y++;
	}
}

t_node		*init_nodes(t_mlx *env)
{
	t_node			*dest;
	int				pos;
	unsigned int	x;
	unsigned int	y;

	y = -1;
	if (!(dest = (t_node*)malloc(sizeof(t_node) * env->map_hgt * env->map_wdt)))
		return (NULL);
	reset_values(env, dest);
	while (++y < env->map_hgt)
	{
		x = -1;
		while (++x < env->map_wdt)
		{
			pos = y * env->map_wdt + x;
			dest[pos].x = x;
			dest[pos].y = y;
			dest[pos].full = env->map[y][x].type == BLOC_FULL;
			dest[pos].index = pos;
		}
	}
	fill_neighbours(env, dest);
	return (dest);
}

void		omniscience(t_mlx *env)
{
	t_zombie		*tmp;
	t_node			*nodes;

	tmp = env->zombie;
	if (!(nodes = init_nodes(env)))
		return ;
	env->end = &nodes[(int)env->player.y * env->map_wdt + (int)env->player.x];
	env->end->x = (int)env->player.x;
	env->end->y = (int)env->player.y;
	while (tmp)
	{
		reset_values(env, nodes);
		env->start = &nodes[(int)tmp->y * env->map_wdt + (int)tmp->x];
		env->start->lgoal = 0.0f;
		env->start->ggoal = compute_dist(ES->x, ES->y, EE->x, EE->y);
		if (compute_dist(tmp->y, tmp->x, env->player.x, env->player.y) >= 1.5)
			apply_a_star(env, nodes, (t_node*[2]){env->start, env->end}, tmp);
		else if (tmp->dlaps <= 0 && (tmp->dlaps = SPAWN_LAPS))
			env->player.hp -= tmp->damages;
		tmp->dlaps--;
		render_zombie(env, tmp);
		tmp = tmp->next;
	}
	free(nodes);
}
