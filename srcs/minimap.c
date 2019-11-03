#include "wolf3d.h"

static inline int	*color(void)
{
	static int	var = 0;

	return (&var);
}

void	get_color(char type)
{
	if (type == BLOC_VOID)
		*color() = 0xaaaaaa;
	else if (type == BLOC_FULL)
		*color() = 0xffffff;
	else if (type == BLOC_SPAWN)
		*color() = 0x000000;
}

void	draw_square(t_mlx *env, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_fill_pixel(env->img_data, x + j, y + i, *color());
			j++;
		}
		i++;
	}
}

void	point_zombies(t_mlx *env)
{
	t_zombie	*tmp;

	tmp = env->zombie;
	while (tmp)
	{
		draw_square(env, (int)tmp->x * MINIMAP_SIZE, (int)tmp->y * MINIMAP_SIZE, MINIMAP_SIZE);
		tmp = tmp->next;
	}
}

void	draw_minimap(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;
	float			x;
	float			y;

	i = 0;
	while (i < env->map_hgt)
	{
		j = 0;
		while (j < env->map_wdt)
		{
			get_color(env->map[i][j].type);
			draw_square(env, j * MINIMAP_SIZE, i * MINIMAP_SIZE, MINIMAP_SIZE);
			j++;
		}
		i++;
	}
	*color() = 0x00ff00;
	draw_square(env, env->player.y * MINIMAP_SIZE, env->player.x * MINIMAP_SIZE, MINIMAP_SIZE);

	x = env->player.x + 5 * sinf(env->player.cam.angle - PI / 8);
	y = env->player.y + 5 * cosf(env->player.cam.angle - PI / 8);

	ft_fill_pixel(env->img_data, y * MINIMAP_SIZE, x * MINIMAP_SIZE, *color());

	x = env->player.x + 5 * sinf(env->player.cam.angle + PI / 8);
	y = env->player.y + 5 * cosf(env->player.cam.angle + PI / 8);
	ft_fill_pixel(env->img_data, y * MINIMAP_SIZE, x * MINIMAP_SIZE, *color());


	*color() = 0x0000ff;
	point_zombies(env);
}
