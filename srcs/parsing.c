/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:07:34 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/22 23:40:01 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		start_check(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (env->file[i] && env->file[i] != '\n')
	{
		env->map_wdt += ft_isdigit(env->file[i]) ? 1 : 0;
		i++;
	}
	i = 0;
	while (env->file[i])
	{
		j = 0;
		while (env->file[i] && env->file[i] != '\n')
		{
			if (!ft_isdigit(env->file[i]) && !ft_is_whitespace(env->file[i]))
			{
				printf("unknown character\n");
				return (-1);
			}
			i++;
			j += ft_isdigit(env->file[i]) ? 1 : 0;
		}
		if (j != env->map_wdt - 1 || j == 0)
		{
				printf("invalid line length\n");
			return (-1);
		}
		env->map_hgt++;
		i++;
	}
	return (0);
}

int		fill_map(t_mlx *env)
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	y;

	i = 0;
	y = 0;
	while (env->file[i])
	{
		x = 0;
		while (env->file[i] && env->file[i] != '\n')
		{
			if (ft_isdigit(env->file[i]))
			{
				if ((env->map[y][x].type = (char)ft_atoi(&env->file[i])) >= BLOC_MAX)
					return (-1);
				if (env->map[y][x].type == BLOC_SPAWN)
					env->war = true;
				x++;
			}
			i++;
		}
		y++;
		i++;
	}
	return (0);
}

static inline void	map_bounds(t_mlx *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->map_wdt)
	{
		env->map[0][i].type = 1;
		env->map[env->map_hgt - 1][i].type = 1;
		i++;
	}
	i = 0;
	while (i < env->map_hgt)
	{
		env->map[i][0].type = 1;
		env->map[i][env->map_wdt - 1].type = 1;
		i++;
	}
}

int		parse_map(t_mlx *env, char *file)
{
	unsigned int	i;
	int				fd;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1
		|| !(env->file = read_file(fd)))
		return (-1);
	if (env->file[0] == '\0' || start_check(env) != 0
		|| !(env->map = (t_bloc**)malloc(sizeof(t_bloc*) * env->map_hgt)))
		return (-1);
	while (i < env->map_hgt)
	{
		if (!(env->map[i] = (t_bloc*)malloc(sizeof(t_bloc) * env->map_wdt)))
			return (-1);
		i++;
	}
	if (fill_map(env) != 0)
		return (-1);
	map_bounds(env);
	printf("height = %d\nwidth = %d\n", env->map_hgt, env->map_wdt);
/*	for (int i = 0; i < env->map_hgt; i++)
	{
		for (int j = 0; j < env->map_wdt; j++)
			printf("%d ", env->map[i][j].type);
		printf("\n");
	}*/
	free(env->file);
	return (0);
}
