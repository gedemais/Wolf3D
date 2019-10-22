#include "wolf3d.h"

int	position(int x, int y, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	if (env->mouse)
	{
		env->mouse_x = x;
		env->mouse_y = y;
	}
	return (0);
}

void	handle_keys(t_mlx *env)
{
	if (env->keys[UP_KEY] || env->keys[KEY_W])
	{
		env->player.x += sin(env->player.cam.angle) * Y_DELTA;
		env->player.y += cos(env->player.cam.angle) * Y_DELTA;
		if (env->map[(int)env->player.x][(int)env->player.y].type == 1)
		{
			env->player.x -= sin(env->player.cam.angle) * Y_DELTA;
			env->player.y -= cos(env->player.cam.angle) * Y_DELTA;
		}
	}
	else if (env->keys[DOWN_KEY] || env->keys[KEY_S])
	{
		env->player.x -= sin(env->player.cam.angle) * Y_DELTA;
		env->player.y -= cos(env->player.cam.angle) * Y_DELTA;
		if (env->map[(int)env->player.x][(int)env->player.y].type == 1)
		{
			env->player.x += sin(env->player.cam.angle) * Y_DELTA;
			env->player.y += cos(env->player.cam.angle) * Y_DELTA;
		}
	}
	else if (env->keys[KEY_D])
	{
		env->player.x += cos(env->player.cam.angle) * Y_DELTA;
		env->player.y -= sin(env->player.cam.angle) * Y_DELTA;
		if (env->map[(int)env->player.x][(int)env->player.y].type == 1)
		{
			env->player.x -= cos(env->player.cam.angle) * Y_DELTA;
			env->player.y += sin(env->player.cam.angle) * Y_DELTA;
		}
	}
	else if (env->keys[KEY_A])
	{
		env->player.x -= cos(env->player.cam.angle) * Y_DELTA;
		env->player.y += sin(env->player.cam.angle) * Y_DELTA;
		if (env->map[(int)env->player.x][(int)env->player.y].type == 1)
		{
			env->player.x += cos(env->player.cam.angle) * Y_DELTA;
			env->player.y -= sin(env->player.cam.angle) * Y_DELTA;
		}
	}
	else if (env->keys[RIGHT_KEY])
		env->player.cam.angle += ANGLE_DELTA;
	else if (env->keys[LEFT_KEY])
		env->player.cam.angle -= ANGLE_DELTA;
}

int	base(void *param)
{
	t_mlx	*env;
	float		rate;

	env = ((t_mlx*)param);

	handle_keys(env);

	if (env->mouse)
	{
		rate = (float)((float)env->mouse_x / (float)WDT);
		rate -= 0.5;
		env->player.cam.angle += ANGLE_DELTA * rate;
	}

	env->img_data = ray_casting(env);

	if (env->weapon != W_NONE)
		draw_reticle(env);

	draw_minimap(env);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
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
	if (key == KEY_M)
		env->mouse = env->mouse ? false : true;
	else if (key == ESC_KEY)
		exit(EXIT_SUCCESS);
	else
		env->keys[key] = true;
//	printf("Angle = %f\nx = %f\ny = %f\n", (double)env->player.cam.angle, (double)env->player.x, (double)env->player.y);
//	env->img_data = ray_casting(env);
//	draw_minimap(env);
//	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	return (0);
}
