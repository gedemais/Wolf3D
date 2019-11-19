/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:07:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/19 13:12:27 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int					check_spawn(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < env->map_hgt)
	{
		j = 0;
		while (j < env->map_wdt)
		{
			if (env->map[i][j].type == BLOC_VOID)
			{
				env->player.x = (float)i + 1.41f;
				env->player.y = (float)j + 1.41f;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static inline char	*strrealloc(char *s, unsigned int size)
{
	char	*new;

	if (!(new = ft_strnew(size)))
	{
		free(s);
		return (NULL);
	}
	new = ft_strcpy(new, s);
	free(s);
	return (new);
}

static inline char	*buffer_join(char *dst, const char *src, unsigned int start)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i + start] = src[i];
		i++;
	}
	dst[i + start] = '\0';
	return (dst);
}

char				*read_file(int fd)
{
	char			buff[BUFF_READ + 1];
	char			*dest;
	int				ret;
	unsigned int	size[2];

	size[0] = BUFF_READ;
	size[1] = 0;
	if (fd == -1 || !(dest = ft_strnew(BUFF_READ)))
		return (NULL);
	while ((ret = (int)read(fd, buff, BUFF_READ)) > 0 && size[1] < MAX_MAP_SIZE)
	{
		size[1] += (unsigned int)ret;
		buff[ret] = '\0';
		if (size[1] >= size[0] && (size[0] *= 2) > 0
			&& !(dest = strrealloc(dest, size[0])))
			return (NULL);
		dest = buffer_join(dest, buff, size[1] - (unsigned int)ret);
	}
	if (ret == -1 || size[1] >= MAX_MAP_SIZE)
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}
