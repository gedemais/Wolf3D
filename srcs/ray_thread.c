#include "wolf3d.h"

void	init_thread(t_mlx *env, t_raythread *thread, unsigned int index)
{
	static int	partition = (WDT / NB_THREADS);

	thread->start = index * partition;
	thread->stop = thread->start + partition;
	thread->index = index;
	thread->env = env;
	ft_memcpy(&thread->p, &env->player, sizeof(t_player));
}

static inline void	ft_fill_texture(char *img_str, int x, int y, int color)
{
	int		pos;

	if (x >= WDT || x < 0 || y >= HGT || y < 0)
		return ;
	pos = (abs(y - 1) * WDT + x) * sizeof(int);
	img_str[pos + 2] = color >> 16 & 255;
	img_str[pos + 1] = color >> 8 & 255;
	img_str[pos] = color & 255;
}

static inline void	draw_col(t_mlx *env, unsigned int x, float updown[2], t_ray *ray)
{
	int				pos;
	unsigned int	y;

	y = 0;
	while (y < HGT)
	{
		if (y >= updown[0] && y < updown[1] - 1)
		{
			ray->sample_y = ((float)y - updown[0]) / (updown[1] - updown[0]);
			pos = (abs((int)(ray->sample_y * 288) - 1) * 288 + (int)(ray->sample_x * 288)) * sizeof(int);
			if (env->night)
				ft_fill_pixel(env->img_data, x, y, *(int*)&env->sprites[ray->sprite].frame[pos]);
			else
				ft_fill_texture(env->img_data, x, y, *(int*)&env->sprites[ray->sprite].frame[pos]);
		}
		y++;
	}
}

void	*ray_threading(void *thread)
{
	t_raythread	*t;
	float		half_hgt;

	half_hgt = HGT / 2.0f;
	t = ((t_raythread*)thread);
	while (t->start < t->stop)
	{
		t->ray.angle = (float)(t->p.cam.angle - t->p.cam.fov / 2) + (float)t->start / (float)WDT * t->p.cam.fov;
		t->ray.hit = 0;

		t->p.eye_x = sin(t->ray.angle);
		t->p.eye_y = cos(t->ray.angle);
		t->ray.dist = 0;
		while (!t->ray.hit)
		{
			t->ray.dist += RAY_STEP;
			t->ray.test_x = (int)(t->p.x + t->p.eye_x * t->ray.dist);
			t->ray.test_y = (int)(t->p.y + t->p.eye_y * t->ray.dist);
//			printf("%d %d\n", t->ray.test_x, t->ray.test_y);
			if (t->env->map[t->ray.test_x][t->ray.test_y].type > 0)
			{
				t->ray.hit = t->env->map[t->ray.test_x][t->ray.test_y].type;
				
				t->ray.bloc_mx = (float)t->ray.test_x + 0.5f;
				t->ray.bloc_my = (float)t->ray.test_y + 0.5f;

				t->ray.hit_x = t->p.x + t->p.eye_x * t->ray.dist;
				t->ray.hit_y = t->p.y + t->p.eye_y * t->ray.dist;

				t->ray.bloc_angle = atan2f((t->ray.hit_y - t->ray.bloc_my), (t->ray.hit_x - t->ray.bloc_mx));

				if (t->ray.bloc_angle >= -3.14159f * 0.25f && t->ray.bloc_angle < 3.14159f * 0.25f)
				{
					t->ray.sprite = t->ray.hit == BLOC_SPAWN ? MABOYE : WALL_NORTH;
					t->ray.sample_x = t->ray.hit_y - (float)t->ray.test_y;
				}
				else if (t->ray.bloc_angle >= 3.14159f * 0.25f && t->ray.bloc_angle < 3.14159f * 0.75f)
				{
					t->ray.sprite = t->ray.hit == BLOC_SPAWN ? MABOYE : WALL_SOUTH;
					t->ray.sample_x = t->ray.hit_x - (float)t->ray.test_x;
				}
				else if (t->ray.bloc_angle < -3.14159f * 0.25f && t->ray.bloc_angle >= -3.14159f * 0.75f)
				{
					t->ray.sprite = t->ray.hit == BLOC_SPAWN ? MABOYE : WALL_EST;
					t->ray.sample_x = t->ray.hit_x - (float)t->ray.test_x;
				}
				else if (t->ray.bloc_angle >= 3.14159f * 0.75f || t->ray.bloc_angle < -3.14159f * 0.75f)
				{
					t->ray.sprite = t->ray.hit == BLOC_SPAWN ? MABOYE : WALL_WEST;
					t->ray.sample_x = t->ray.hit_y - (float)t->ray.test_y;
				}
			}
		}
		t->rectify = ((float)t->start * t->p.cam.fov / (float)WDT) - t->p.cam.fov / 2.0f;
//		ray.dist *= cosf(rectify) + 0.25;
		t->dcieling = (float)(HGT / 2.0f) - (float)(HGT / t->ray.dist);
		t->dfloor = (float)((float)HGT - t->dcieling);

		t->env->z_buff[t->start] = t->ray.dist;
		draw_col(t->env, t->start, (float[2]){t->dcieling, t->dfloor}, &t->ray);
		t->start++;
	}
	pthread_exit(NULL);
}
/*
static inline int	relaunch(t_mlx *env, t_raythread[NB_THREADS])
{
		
}
*/
char	*ray_thread(t_mlx *env)
{
	t_raythread	cores[NB_THREADS];
	unsigned int		i;

	i = 0;
	while (i < NB_THREADS)
	{
		init_thread(env, &cores[i], i);
		if (pthread_create(&cores[i].thread, NULL, &ray_threading, &cores[i]))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		if (pthread_join(cores[i].thread, NULL))
			return (NULL);
//		if (relaunch(env, cores))
//			return (NULL);
		i++;
	}
	return (env->img_data);
}
