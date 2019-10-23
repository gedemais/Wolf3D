#include "wolf3d.h"

bool	do_copy(int color, char alph[4])
{
	int			diff;
	char		col[4];

	ft_memcpy(&col, &color, sizeof(int));
	ft_memcpy(&col, &color, sizeof(int));
	diff = 0;
	diff += ft_abs(col[0] - alph[0]);
	diff += ft_abs(col[1] - alph[1]);
	diff += ft_abs(col[2] - alph[2]);
	return (diff < PRECISION ? false : true);
}

void	blit_sprite(t_mlx *env, t_sprite sp, int x, int y)
{
	int		i;
	int		j;
	int		pos;
	int		s_l;
	char	alph[4];

	i = 0;
	ft_memcpy(&alph[0], &sp.alpha, sizeof(int));
	s_l = sp.width * 4;
	while (i < sp.height)
	{
		j = 0;
		pos = (abs(y + i - 1) * WDT + x) * sizeof(int);
		while (j < s_l)
		{
			if (do_copy(*(int*)&sp.frame[i * sp.width * 4 + j], alph))
				ft_memcpy(&env->img_data[pos + j], &sp.frame[i * sp.width * 4 + j], sizeof(int));
			j += 4;
		}
		i++;
	}
}

char	*sp_names(int which)
{
	static char	*filenames[NB_SPRITES] = {
			"ressources/sprites/weapons/knife_stand.XPM",
			"ressources/sprites/weapons/knife_floor.XPM",
			"ressources/sprites/weapons/knife_1.XPM",
			"ressources/sprites/weapons/knife_2.XPM",
			"ressources/sprites/weapons/knife_3.XPM",
			"ressources/sprites/weapons/gun_stand.XPM",
			"ressources/sprites/weapons/gun_floor.XPM",
			"ressources/sprites/weapons/gun_1.XPM",
			"ressources/sprites/weapons/gun_2.XPM",
			"ressources/sprites/weapons/mp40_stand.XPM",
			"ressources/sprites/weapons/mp40_floor.XPM",
			"ressources/sprites/weapons/mp40_1.XPM",
			"ressources/sprites/weapons/mp40_2.XPM",
			"ressources/sprites/weapons/minigun_stand.XPM",
			"ressources/sprites/weapons/minigun_floor.XPM",
			"ressources/sprites/weapons/minigun_1.XPM",
			"ressources/sprites/weapons/minigun_2.XPM"};
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
		if (!(env->sprites[i].frame = mlx_get_data_addr(env->sprites[i].ptr, &env->sprites[i].width, &env->sprites[i].height, &t)))
			return (-1);
		env->sprites[i].alpha = 9961608;
		env->sprites[i].width *= 9;
		env->sprites[i].height /= 4;
		i++;
	}
	return (0);
}
