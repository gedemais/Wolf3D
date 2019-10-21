#include "wolf3d.h"

void	draw_reticle(t_mlx *env)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	halfs[3];

	halfs[0] = RETICLE_SIZE / 2;
	halfs[1] = WDT / 2;
	halfs[2] = HGT / 2;
	i = halfs[1] - halfs[0] - 1;
	j = halfs[2] - halfs[0] - 1;
	x = halfs[1] + halfs[0];
	y = halfs[2] + halfs[0];
	while (++i < x)
	{
		ft_fill_pixel(env->img_data, i, halfs[2], 0xff0000);
		ft_fill_pixel(env->img_data, i, halfs[2] - 1, 0xff0000);
		ft_fill_pixel(env->img_data, i, halfs[2] + 1, 0xff0000);
	}
	while (++j < y)
	{
		ft_fill_pixel(env->img_data, halfs[1], j, 0xff0000);
		ft_fill_pixel(env->img_data, halfs[1] - 1, j, 0xff0000);
		ft_fill_pixel(env->img_data, halfs[1] + 1, j, 0xff0000);
	}
}
