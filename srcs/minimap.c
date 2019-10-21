#include "wolf3d.h"

static inline bool	*player_pos(void)
{
	static bool	var = false;

	return (&var);
}

void	draw_square(t_mlx *env, int x, int y, int size)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	color = env->map[y / MINIMAP_SIZE][x / MINIMAP_SIZE].type == 1 ? 0xffffff : 0x888888;
	if (*player_pos())
		color = 0xff0000;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_fill_pixel(env->img_data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	*player_pos() = false;
	while (i < env->map_hgt)
	{
		j = 0;
		while (j < env->map_wdt)
		{
			draw_square(env, j * MINIMAP_SIZE, i * MINIMAP_SIZE, MINIMAP_SIZE);
			j++;
		}
		i++;
	}
	*player_pos() = true;
	draw_square(env, env->player.y * MINIMAP_SIZE, env->player.x * MINIMAP_SIZE, MINIMAP_SIZE);
}
