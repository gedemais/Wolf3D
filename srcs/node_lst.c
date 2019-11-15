/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:25:47 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 06:39:22 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		node_len(t_node *lst)
{
	int	ret;

	ret = 0;
	while (lst)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}

void	node_pop(t_node **lst)
{
	t_node	*tmp;

	if (!(*lst))
		return ;
	if (!(*lst)->next)
	{
		free(*lst);
		*lst = NULL;
		return ;
	}
	tmp = (*lst)->next;
	free(*lst);
	(*lst) = tmp;
}

int		node_pushback(t_node **lst, t_node *node)
{
	t_node	*tmp;

	tmp = *lst;
	if (!node)
		return (-1);
	if (!(*lst))
	{
		*lst = node;
		(*lst)->next = NULL;
		return (0);
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
	return (0);
}

t_node	*node_new(t_node *src)
{
	t_node	*new;

	if (!(new = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	ft_memcpy(new, src, sizeof(t_node));
	return (new);
}
