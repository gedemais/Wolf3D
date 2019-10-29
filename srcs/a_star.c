/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:29:09 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/29 20:07:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	sort_lst(t_node **lst)
{
	t_node	*tmp;
	t_node	swap;
	int		len;
	int		i;

	i = 0;
	len = node_len(*lst);
	if (len <= 1)
		return ;
	tmp = *lst;
	while (i < len && tmp->next)
	{
		if (tmp->gdist > tmp->next->gdist)
		{
			swap = *tmp;
			*tmp = *(tmp->next);
			*(tmp->next) = swap;
		}
		i++;
		tmp = tmp->next;
	}
}

void	set_current(t_mlx *env, t_zombie *z, t_node *c)
{
	c->x = z->x;
	c->y = z->y;
	c->ldist = 0.0f;
	c->gdist = compute_dist(c->x, c->y, (int)env->player.y, (int)env->player.x);
}

int		a_star(t_mlx *env, t_node *grid, t_zombie *z, float dir[2])
{
	t_node	*opened;
	t_node	current;
//	float	goal;
	int		i;

	opened = NULL;
	(void)dir;
	(void)grid;
	i = 0;
	set_current(env, z, &current);
	if (node_pushback(&opened, node_new(&current)) != 0)
		return (-1);
	while (opened)
	{
		sort_lst(&opened);

		while (opened && opened->visited)
			node_pop(opened);

		if (!opened)
			break ;

		current = *opened;
		opened->visited = true;

/*		while (i < 4)
		{
			if (!grid[current.neighbours[i]].visited && !grid[current.neighbours[i]].full)
				node_pushback(&opened, node_new(&grid[current.neighbours[i]]));
			goal = current.ldist + compute_dist(current->x, current->y, grid[current->neighbours[i]].x, grid[current->neighbours[i]].y);
			if (goal < grid[current.neighbours[i]].ldist)
			{
				grid[current.neighbours[i]].parent = current->index;
				grid[current.neighbours[i]].ldist = goal;
	//			grid[current.neighbours[i]].gdist = goal + compute_dist();
			}
			i++;
		}*/
	}

	return (0);
}
