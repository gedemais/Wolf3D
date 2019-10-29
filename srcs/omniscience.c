/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omniscience.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:06:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/29 19:59:46 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		apply_a_star(t_mlx *env, t_node *grid, t_zombie *z)
{
	float	tmp[2];
	float		speed;

	speed = 0.1;
	if (a_star(env, grid, z, tmp) != 0)
		return ;
//	z->x += tmp[0] * speed;
//	z->y += tmp[1] * speed;
}

void		fill_neighbours(t_mlx *env, t_node *node, int x, int y)
{
	ft_memset(&node->neighbours[0], 0, sizeof(int) * 4);
	if (y > 0)
		node->neighbours[3] = (y - 1) * env->map_wdt + x;
	if (x > 0)
		node->neighbours[2] = (y) * env->map_wdt + x - 1;
	if (x < (int)env->map_wdt)
		node->neighbours[1] = (y) * env->map_wdt + x + 1;
	if (y < (int)env->map_hgt)
		node->neighbours[0] = (y + 1) * env->map_wdt + x;
}

t_node	*init_grid(t_mlx *env)
{
	t_node			*grid;
	unsigned int	x;
	unsigned int	y;
	int				pos;

	if (!(grid = (t_node*)malloc(sizeof(t_node) * env->map_wdt * env->map_hgt)))
		return (NULL);
	y = 0;
	while (y < env->map_hgt)
	{
		x = 0;
		while (x < env->map_wdt)
		{
			pos = y * env->map_wdt + x;
			grid[pos].x = x;
			grid[pos].y = y;
			grid[pos].parent = 0;
			grid[pos].visited = false;
			grid[pos].gdist = 1000000;
			grid[pos].ldist = 1000000;
			grid[pos].parent = 0;
			grid[pos].full = env->map[y][x].type == BLOC_FULL ? true : false;
			grid[pos].index = pos;
			fill_neighbours(env, &grid[pos], x, y);
			x++;
		}
		y++;
	}
	return (grid);
}

void		omniscience(t_mlx *env)
{
	t_node			*grid;
	t_zombie		*tmp;

	tmp = env->zombie;
	if (!(grid = init_grid(env)))
		return ;
	while (tmp)
	{
//		apply_a_star(env, grid, tmp);
		if (tmp->x >= 0 && tmp->x < env->map_wdt && tmp->y >= 0 && tmp->y < env->map_hgt)
		{
		}
		tmp = tmp->next;
	}
	free(grid);
}
