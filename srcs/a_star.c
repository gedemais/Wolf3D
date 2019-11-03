/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:29:09 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/03 19:17:04 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_lst(t_node *lst)
{
	t_node	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		printf("node %d, x = %d | y = %d | ggoal = %f\n", tmp->index, tmp->x, tmp->y, tmp->ggoal);
		tmp = tmp->next;
	}
	printf("---------------------\n");
	fflush(stdout);
}

void	swap_nodes(t_node *a, t_node *b)
{
	t_node	swap;

	ft_memcpy(&swap, a, sizeof(t_node) - sizeof(t_node*));
	ft_memcpy(a, b, sizeof(t_node) - sizeof(t_node*));
	ft_memcpy(b, &swap, sizeof(t_node) - sizeof(t_node*));
}

void	sort_lst(t_node **lst)
{
	t_node	*tmp;
	bool	sort;

	if (!*lst || !(*lst)->next)
		return ;
	sort = false;
	while (!sort)
	{
		sort = true;
		tmp = *lst;
		while (tmp->next)
		{
			if (tmp->ggoal > tmp->next->ggoal && !(sort = false))
				swap_nodes(tmp, tmp->next);
			tmp = tmp->next;
		}
	}

}

void	reconstruct_path(t_node *end, float dir[4])
{
	t_node	*tmp;
	t_node	*last;

	tmp = end->parent;
	last = end;
	while (tmp && tmp->parent)
	{
		last = tmp;
		tmp = tmp->parent;
	}
	dir[0] = (float)last->x + 0.5f - dir[2];
	dir[1] = (float)last->y + 0.5f - dir[3];
}

int		a_star(t_mlx *env, t_node *nodes, t_node *s_e[2], float dir[4])
{
	t_node	*current;
	t_node	*set;
	t_node	*n;
	float	low_goal;
	int		i;

	set = NULL;
	current = s_e[0];
	if (node_pushback(&set, node_new(current)) != 0)
		return (-1);

	while (set)
	{
		sort_lst(&set);

		while (set && set->visited)
			node_pop(&set);

		if (!set)
			break;

		current = set;
		current->visited = true;

		if (current->x == (int)env->player.y && current->y == (int)env->player.x)
		{
			reconstruct_path(current, dir);
			return (0);
		}

		i = 0;
		while (i < 4)
		{
			if (current->neighbours[i])
			{
				n = ((t_node*)current->neighbours[i]);

				low_goal = current->lgoal + 1.0f;
				if (!n->visited && !n->full && low_goal < n->lgoal)
				{
					n->parent = &nodes[current->index];
					n->lgoal = low_goal;
					n->ggoal = n->lgoal + compute_dist(current->x, current->y, n->x, n->y);
					node_pushback(&set, node_new(n));
				}
			}
			i++;
		}
	}
	return (0);
}
