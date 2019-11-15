/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:54:20 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/15 02:57:08 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool	do_copy(int color, char alph[4])
{
	int			diff;
	char		col[4];

	ft_memcpy(&col, &color, sizeof(int));
	diff = 0;
	diff += ft_abs(col[1] - alph[1]);
	diff += ft_abs(col[2] - alph[2]);
	diff += ft_abs(col[3] - alph[3]);
	if (diff < PRECISION)
		return (false);
	return (true);
}

void	alpha_filter(t_sprite *sp)
{
	int				x;
	int				y;
	int				color;
	int				pos;
	char			alph[4];

	y = 0;
	ft_memcpy(&alph[0], &sp->alpha, sizeof(int));
	while (y < sp->height)
	{
		x = 0;
		while (x < sp->width)
		{
			pos = (abs(y - 1) * 288 + x) * sizeof(int);
			color = *(int*)&sp->frame[pos];
			if (!do_copy(color, alph))
				ft_memset(&sp->frame[pos], 0, sizeof(int));
			x++;
		}
		y++;
	}
}

void	blit_sprite(t_mlx *env, t_sprite sp, int x, int y)
{
	int		i;
	int		j;
	int		pos;
	int		s_l;
	char	alph[4];

	i = 0;
	s_l = sp.width * 4;
	ft_memcpy(&alph[0], &sp.alpha, sizeof(int));
	while (i < sp.height)
	{
		j = 0;
		pos = (abs(y + i - 1) * WDT + x) * sizeof(int);
		while (j < s_l)
		{
			if (*blit_alpha()
				|| do_copy(*(int*)&sp.frame[i * sp.width * 4 + j], alph))
				ft_memcpy(&env->img_data[pos + j],
					&sp.frame[i * sp.width * 4 + j], sizeof(int));
			j += 4;
		}
		i++;
	}
}

char	*sp_names(int which)
{
	static char	*filenames[NB_SPRITES] = {
			"ressources/sprites/weapons/knife_stand.XPM",
			"ressources/sprites/weapons/knife_1.XPM",
			"ressources/sprites/weapons/knife_3.XPM",
			"ressources/sprites/weapons/knife_2.XPM",
			"ressources/sprites/weapons/gun_stand.XPM",
			"ressources/sprites/weapons/gun_1.XPM",
			"ressources/sprites/weapons/gun_2.XPM",
			"ressources/sprites/weapons/mp40_stand.XPM",
			"ressources/sprites/weapons/mp40_1.XPM",
			"ressources/sprites/weapons/mp40_2.XPM",
			"ressources/sprites/weapons/minigun_stand.XPM",
			"ressources/sprites/weapons/minigun_1.XPM",
			"ressources/sprites/weapons/minigun_2.XPM",
			"ressources/sprites/walls/wall_north.XPM",
			"ressources/sprites/walls/wall_south.XPM",
			"ressources/sprites/walls/wall_est.XPM",
			"ressources/sprites/walls/wall_west.XPM",
			"ressources/sprites/game_over.XPM",
			"ressources/sprites/zombie.XPM",
			"ressources/sprites/maboye.XPM",
			"ressources/sprites/skybox.XPM"};

	return (filenames[which]);
}

int		load_sprites(t_mlx *env)
{
	unsigned int	i;
	int				t;

	i = 0;
	if (!(env->sprites = (t_sprite*)malloc(sizeof(t_sprite) * NB_SPRITES)))
		return (-1);
	while (i < NB_SPRITES)
	{
		if (!(env->sprites[i].ptr = mlx_xpm_file_to_image(env->img_ptr,
			sp_names(i), &env->sprites[i].width, &env->sprites[i].height)))
			return (-1);
		if (!(env->sprites[i].frame = mlx_get_data_addr(env->sprites[i].ptr,
			&env->sprites[i].width, &env->sprites[i].height, &t)))
			return (-1);
		env->sprites[i].alpha = 9961608;
		env->sprites[i].width *= 9;
		env->sprites[i].height /= 4;
		i++;
	}
	alpha_filter(&env->sprites[ZOMBIE]);
	return (0);
}
