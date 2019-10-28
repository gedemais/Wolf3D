/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omniscience.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:06:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/28 21:03:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_as_lst	*get_lowest_cost(t_as_lst *lst)
{
	t_as_lst	*tmp;
	t_as_lst	*ret;
	float		low;

	tmp = lst;
	ret = NULL;
	low = 1000000.0f;
	while (tmp)
	{
		if (low > tmp->h)
		{
			ret = tmp;
			low = tmp->h;
		}
		tmp = tmp->next;
	}
	return (ret);
}

void	visit_neighbours(t_mlx *env, t_as_lst current, t_as_lst **closed, t_as_lst **opened)
{
	t_as_lst	n;
	t_as_lst	*tmp;
	int		x;
	int		y;

	x = -2;
	tmp = *opened;
	if (*opened)
	{
		as_free_lst(*opened);
		*opened = NULL;
	}
	while (++x < 2)
	{
		y = -2;
		while (++y < 2)
		{
			n.x = current.x + x;
			n.y = current.y + y;
			n.cost = current.cost + 1; // Computing new neighbour cost
			n.h = n.cost + compute_dist(n.x, n.y, env->player.x, env->player.y);
			if (n.x < 0 || n.x >= (float)env->map_wdt || n.y < 0 || n.y >= (float)env->map_hgt // Limiting tests to read only into the map
				|| as_find_node(*closed, &n) || ((tmp = as_find_node(*opened, &n)) && tmp->h < n.h))
				continue ;
			else if (env->map[n.y][n.x].type != BLOC_FULL)
			{
				as_push(opened, as_lstnew(n.x, n.y));
				(*opened)->cost = n.cost;
				(*opened)->h = n.h;
			}
		}
	}
}

void	print_map(t_mlx *env, t_as_lst current, t_zombie *z)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < env->map_hgt)
	{
		j = 0;
		while (j < env->map_wdt)
		{
			if (i == (unsigned int)current.y && j == (unsigned int)current.x)
				printf("o ");
			else if (i == (unsigned int)env->player.y && j == (unsigned int)env->player.x)
				printf("P ");
			else if (i == (unsigned int)z->y && j == (unsigned int)z->x)
				printf("Z ");
			else if (env->map[i][j].type == BLOC_VOID)
				printf(". ");
			else if (env->map[i][j].type == BLOC_FULL)
				printf("X ");
			else if (env->map[i][j].type == BLOC_SPAWN)
				printf("O");
			j++;
		}
		printf("\n");
		i++;
	}

}

int	find_path(t_mlx *env, t_zombie *z, float ret[2])
{
	t_as_lst	*opened;
	t_as_lst	*closed;
	t_as_lst	current;

	opened = NULL; // Set the lists pointers to NULL for as_push
	closed = NULL;
	if (as_push(&opened, as_lstnew(z->x, z->y)) == -1) // Push the first node in the opened list
		return (-1);

	opened->cost = 0.0f;
	opened->h = compute_dist((int)z->x, (int)z->y, (int)env->player.x, (int)env->player.y);

//	printf("Start : Z x = %f y = %f\nP x = %f y = %f\n", z->x, z->y, env->player.x, env->player.y);
	while (opened)
	{
		ft_memcpy(&current, get_lowest_cost(opened), sizeof(t_as_lst));
		print_map(env, current, z);
		usleep(50000);
//		printf("Current  x = %d y = %d\n", current.x, current.y);
		if (current.x - env->player.x < 1 && current.y - env->player.y < 1)
		{
			ret[0] = current.x - z->x;
			ret[1] = current.y - z->y;
//			printf("deltax = %f\ndelta_y = %f\n\n", ret[0], ret[1]);
			as_free_lst(opened);
			as_free_lst(closed);
			return (0);
		}
		as_snap_node(&opened, &current);
		visit_neighbours(env, current, &closed, &opened);
		as_push(&closed, as_lstnew(current.x, current.y));
		closed->cost = current.cost;
	}
	return (1);
}

void		apply_a_star(t_mlx *env, t_zombie *z)
{
	static float	tmp[2] = {0, 0};
	float		speed;

	(void)env;
	speed = 0.1;
	if (find_path(env, z, tmp) != 0)
	{
		exit (EXIT_SUCCESS);
		return ;
	}
	else
	{
		printf("Found\n");
		z->x += tmp[0] * speed;
		z->y += tmp[1] * speed;
	}
}

void		omniscience(t_mlx *env)
{
	t_zombie		*tmp;
	int			z;

	z = 0;
	tmp = env->zombie;
	while (tmp)
	{
//		apply_a_star(env, tmp);
		if (tmp->x > -1 && tmp->x < env->map_wdt && tmp->y > 0 && tmp->y < env->map_hgt)
		{
		}
		tmp = tmp->next;
		z++;
	}
}
