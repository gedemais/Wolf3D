#include "wolf3d.h"

void	barre_bounds(t_mlx *env, int padx, int pady)
{
	unsigned int	y;

	y =  0;
	*color() = 0x0000ff;
	ft_draw_line(env, (int[2]){padx, pady}, (int[2]){padx + 200,  pady});
	ft_draw_line(env, (int[2]){padx, pady + 1}, (int[2]){padx + 200,  pady + 1});
	ft_draw_line(env, (int[2]){padx, pady + 2}, (int[2]){padx + 200,  pady + 2});

	ft_draw_line(env, (int[2]){padx, pady + 31}, (int[2]){padx + 202,  pady + 31});
	ft_draw_line(env, (int[2]){padx, pady + 32}, (int[2]){padx + 202,  pady + 32});
	ft_draw_line(env, (int[2]){padx, pady + 33}, (int[2]){padx + 202,  pady + 33});

	while (y < 32)
	{
		ft_draw_line(env, (int[2]){padx, pady + y}, (int[2]){padx + 2, pady + y});
		ft_draw_line(env, (int[2]){padx + 200, pady + y}, (int[2]){padx + 202, pady + y});
		y++;
	}
}

void	barre_de_vie(t_mlx *env, int padx, int pady)
{
	unsigned int	y;

	y = 3;
	barre_bounds(env, padx, pady);
	while (y < 31)
	{
		*color() = 0x00ff00;
		ft_draw_line(env, (int[2]){padx + 3, pady + y}, (int[2]){padx + env->player.hp * 2 - 2, pady + y});
		*color() = 0xff0000;
		ft_draw_line(env, (int[2]){padx + env->player.hp * 2 - 2, pady + y}, (int[2]){padx + 200, pady + y});
		y++;
	}
}
