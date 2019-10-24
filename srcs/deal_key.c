#include "wolf3d.h"

void	handle_keys(t_mlx *env)
{
	env->player.speed = env->keys[SHIFT_KEY] ? 0.2 : 0.1;
	if (env->keys[UP_KEY] || env->keys[KEY_W])
	{
		env->player.x += sin(env->player.cam.angle) * env->player.speed;
		env->player.y += cos(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x -= sin(env->player.cam.angle) * env->player.speed;
			env->player.y -= cos(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[DOWN_KEY] || env->keys[KEY_S])
	{
		env->player.x -= sin(env->player.cam.angle) * env->player.speed;
		env->player.y -= cos(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x += sin(env->player.cam.angle) * env->player.speed;
			env->player.y += cos(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[KEY_D])
	{
		env->player.x += cos(env->player.cam.angle) * env->player.speed;
		env->player.y -= sin(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x -= cos(env->player.cam.angle) * env->player.speed;
			env->player.y += sin(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[KEY_A])
	{
		env->player.x -= cos(env->player.cam.angle) * env->player.speed;
		env->player.y += sin(env->player.cam.angle) * env->player.speed;
		if (env->map[(int)env->player.x][(int)env->player.y].type > 0)
		{
			env->player.x += cos(env->player.cam.angle) * env->player.speed;
			env->player.y -= sin(env->player.cam.angle) * env->player.speed;
		}
	}
	if (env->keys[RIGHT_KEY])
		env->player.cam.angle += (float)ANGLE_DELTA * (float)env->player.speed * 10.0f;
	if (env->keys[LEFT_KEY])
		env->player.cam.angle -= (float)ANGLE_DELTA * (float)env->player.speed * 10.0f;
}

int		base(void *param)
{
	t_mlx	*env;
	clock_t	t;
	clock_t	e;

	t = clock();
	env = ((t_mlx*)param);

	handle_keys(env);
	if (env->war)
		handle_enemys(env);
	env->img_data = ray_casting(env);
	if (env->weapon < W_MAX)
		handle_weapon(env);
	draw_minimap(env);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	e = clock();
//	printf("%f\n", 1 / (float)((float)((float)e - (float)t) / 1000000));
	return (0);
}

int		release_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	env->keys[key] = false;
	return (0);
}

int		press_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	if (key == ESC_KEY)
		exit(EXIT_SUCCESS);
	else
		env->keys[key] = true;
	return (0);
}
