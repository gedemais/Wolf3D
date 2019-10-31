#include "wolf3d.h"

void	barre_de_vie(t_mlx *env, int padx, int pady)
{
	unsigned int	x;
	unsigned int	i;

	x = 0;
	while (x < 200)
	{
		ft_fill_pixel(env->img_data, padx + x, pady, 0x0000ff);
		ft_fill_pixel(env->img_data, padx + x, pady + 1, 0x0000ff);
		i = 2;
		while (i < 20)
		{
			ft_fill_pixel(env->img_data, padx + x, pady + i, i < 2 || (int)i > env->player.hp ? 0x0000ff : 0x00ff00);
			i++;
		}
		ft_fill_pixel(env->img_data, padx + x, pady + i, 0x0000ff);
		ft_fill_pixel(env->img_data, padx + x, pady + i + 1, 0x0000ff);
		x++;
	}
}
