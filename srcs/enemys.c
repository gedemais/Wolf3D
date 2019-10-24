#include "wolf3d.h"

float	compute_dist(t_player p, unsigned int i, unsigned int j)
{
	int	a;
	int	as;
	int	b;
	int	bs;

	a = p.x - j;
	as = a * a;
	b = p.y - i;
	bs = b * b;
	return (sqrt(as + bs));
}

void	find_closest_bloc(t_mlx *env, int closest[2], float *dist)
{
	unsigned int	i;
	unsigned int	j;
	float		best;
	float		tmp;

	i = 0;
	best = 10000000;
	closest[0] = 0;
	closest[1] = 0;
	while (i < env->map_hgt)
	{
		j = 1;
		while (j < env->map_wdt)
		{
			if (env->map[i][j].type != BLOC_VOID)
			{
				if ((tmp = compute_dist(env->player, i, j)) < best)
				{
					best = tmp;
					closest[0] = i;
					closest[1] = j;
				}

			}
			j++;
		}
		i++;
	}
	*dist = best;
}

void	handle_enemys(t_mlx *env)
{
	static int	laps = 1;
//	int		closest[2];

	(void)env;
//	if (env->nb_killed <= z_lstlen(env->zombie) || (laps < 100 && (laps++)))
//		return (0);
//	find_closest_spawn(env, closest);
	laps = 1;
}
