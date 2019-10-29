/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_lst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:12:13 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/29 18:12:13 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		z_lstlen(t_zombie *lst)
{
	t_zombie	*tmp;
	int			ret;

	ret = 0;
	tmp = lst;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

void	z_free_lst(t_zombie *lst)
{
	if (lst->next)
		z_free_lst(lst->next);
	free(lst);
}

void	z_snap_node(t_zombie **lst, t_zombie *node)
{
	t_zombie		*tmp;

	tmp = (*lst);
	if (node == *lst)
	{
		node = node->next;
		free(*lst);
		*lst = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	if (node == tmp)
	{
		tmp->prev->next = NULL;
		free(tmp);
		return ;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}

int	z_pushfront(t_zombie **lst, t_zombie *new)
{
	t_zombie	*tmp;

	if (!(*lst))
	{
		(*lst) = new;
		(*lst)->prev = NULL;
		(*lst)->next = NULL;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
	return (0);
}

t_zombie	*z_lstnew(t_mlx *env)
{
	t_zombie	*new;
	int			spawn;

	if (!(new = (t_zombie*)malloc(sizeof(t_zombie))))
		return (NULL);
	new->hp = 1 + (env->nb_killed * 3);
	new->damages = 1 + (env->nb_killed / 3);
	spawn = rand() % env->nb_spawns;
	new->x = (float)env->spawns[spawn].x;
	new->y = (float)env->spawns[spawn].y;
	return (new);
}
