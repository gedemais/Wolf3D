#include "wolf3d.h"
/*
void	barre_bounds(t_mlx *env, int padx, int pady)
{
	
}*/

void	barre_de_vie(t_mlx *env, int padx, int pady)
{
	unsigned int	y;

	y =  0;
	while (y < 200)
	{
		*color() = 0xff0000;
		ft_draw_line(env, (int[2]){padx, pady}, (int[2]){padx + 200,  pady});
		y++;
	}
}
