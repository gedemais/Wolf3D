#include "wolf3d.h"

int		as_pop(t_as_lst **lst)
{
	t_as_lst	*tmp;

	tmp = (*lst)->next;
	free(*lst);
	(*lst) = tmp;
	return (0);
}

void	as_free_lst(t_as_lst *lst)
{
	if (lst && lst->next)
		as_free_lst(lst->next);
	free(lst);
}

void	as_snap_node(t_as_lst **lst, t_as_lst *node)
{
	t_as_lst		*tmp;
	t_as_lst		*tmp2;

	tmp = (*lst);
	if (node->x == tmp->x && node->y == tmp->y)
	{
		as_pop(lst);
		*lst = NULL;
		return ;
	}
	tmp2 = tmp->next;
	while (tmp && tmp2->next)
	{
		if (node->x == tmp2->x && node->y == tmp2->y)
		{
			tmp->next = tmp2->next;
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if (node->x == tmp2->x && node->y == tmp2->y)
	{
		free(tmp2);
		tmp->next = NULL;
	}
}

int	as_push(t_as_lst **lst, t_as_lst *new)
{
	if (!(*lst))
	{
		(*lst) = new;
		(*lst)->prev = NULL;
		(*lst)->next = NULL;
		return (0);
	}
	new->next = (*lst);
	(*lst) = new;
	return (0);
}


t_as_lst	*as_lstnew(float x, float y)
{
	t_as_lst	*new;

	if (!(new = (t_as_lst*)malloc(sizeof(t_as_lst))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->next = NULL;
	return (new);
}

t_as_lst	*as_find_node(t_as_lst *lst, t_as_lst *node)
{
	t_as_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if ((int)tmp->x == (int)node->x && (int)tmp->y == (int)node->y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
