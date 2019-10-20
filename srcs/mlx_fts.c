/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:58:56 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/20 20:28:36 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_exit(int status)
{
	exit(status);
}

void	ft_fill_pixel(char *img_str, int x, int y, int color)
{
	int		pos;

	if (x >= WDT || x < 0 || y >= HGT || y < 0)
		return ;
	pos = (abs(y - 1) * WDT + x) * sizeof(int);
	img_str[pos] = color >> 16 & 255;
	img_str[pos + 1] = color >> 8 & 255;
	img_str[pos + 2] = color & 255;
}

char	*ft_clear_image(void *param, char *img_data)
{
	ft_memset(((t_mlx*)param)->img_data, 0, HGT * WDT * 4);
	mlx_put_image_to_window((t_mlx*)param, ((t_mlx*)param)->mlx_win,
			((t_mlx*)param)->img_ptr, 0, 0);
	return (img_data);
}
