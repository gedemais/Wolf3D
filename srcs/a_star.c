/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:29:09 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/30 21:15:59 by gedemais         ###   ########.fr       */
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
		if (tmp->ggoal > tmp->next->ggoal)
		{
			swap = *tmp;
			*tmp = *(tmp->next);
			*(tmp->next) = swap;
		}
		i++;
		tmp = tmp->next;
	}
}

int		a_star(t_mlx *env, t_node *nodes, t_node *s_e[2], float dir[2])
{
	t_node	*current;
	t_node	*set;
	t_node	*n;
	float	low_goal;
	int		i;
	(void)env;
	(void)nodes;

	set = NULL;
	current = s_e[0];
	if (node_pushback(&set, node_new(current)) != 0)
		return (-1);

	dir[0] = 0;
	dir[1] = 0;

	while (set)
	{
		sort_lst(&set);

		while (set && set->visited)
			node_pop(&set);

		if (!set)
			break;

		current = set;
		current->visited = true;

		if (current->x == (int)env->player.x && current->y == (int)env->player.y)
			break ;

		i = 0;
		while (i < 4)
		{
			if (current->neighbours[i])
			{
				n = ((t_node*)current->neighbours[i]);

				printf("There1 %d\n", set->index);
				if (!n->visited && !n->full)
					node_pushback(&set, node_new(n));
				printf("There2\n");

				low_goal = current->lgoal + compute_dist(current->x, current->y, n->x, n->y);
				if (low_goal < n->lgoal)
				{
					n->parent = current;
					n->lgoal = low_goal;
					n->ggoal = n->lgoal + compute_dist(current->x, current->y, n->x, n->y);
				}
			}
			i++;
		}
	}
//	printf("start : %d %d\nend : %d %d\n------------\n", s_e[0]->x, s_e[0]->y, s_e[1]->x, s_e[1]->y);

//	reconstruct_path(end);
	return (0);
}
