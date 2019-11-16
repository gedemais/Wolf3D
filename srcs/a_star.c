/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:29:09 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/16 04:23:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	swap_nodes(t_node *a, t_node *b)
{
	t_node	swap;

	ft_memcpy(&swap, a, sizeof(t_node) - sizeof(t_node*));
	ft_memcpy(a, b, sizeof(t_node) - sizeof(t_node*));
	ft_memcpy(b, &swap, sizeof(t_node) - sizeof(t_node*));
}

void	sort_lst(t_node **lst)
{
	t_node	*start;
	t_node	*tmp;
	t_node	*i;

	start = *lst;
	while (start->next)
	{
		i = start->next;
		tmp = start->next;
		while (i)
		{
			if (i->ggoal < tmp->ggoal)
				tmp = i;
			i = i->next;
		}
		swap_nodes(start, tmp);
		start = start->next;
	}
}

int		reconstruct_path(t_node *end, float dir[4])
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
	return (0);
}

void	explore_neighbours(t_node *set, t_node *nodes, t_node *current)
{
	t_node	*n;
	float	low_goal;
	int		i;

	i = -1;
	while (++i < 4)
		if (current->n[i])
		{
			n = ((t_node*)current->n[i]);
			low_goal = current->lgoal + 1.0f;
			if (!n->visited && !n->full && low_goal < n->lgoal)
			{
				n->parent = &nodes[current->index];
				n->lgoal = low_goal;
				n->ggoal = n->lgoal + 1.0f;
				node_pushback(&set, node_new(n));
			}
		}
}

int		a_star(t_mlx *env, t_node *nodes, t_node *s_e[2], float dir[4])
{
	t_node	*current;
	t_node	*set;

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
			break ;
		current = set;
		current->visited = true;
		if (current->x == (int)env->player.y && current->y == (int)env->player.x
			&& reconstruct_path(current, dir) == 0)
			return (0);
		explore_neighbours(set, nodes, current);
	}
	return (0);
}
