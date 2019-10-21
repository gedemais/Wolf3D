#include "wolf3d.h"

int	position(int x, int y, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	env->mouse_x = x;
	env->mouse_y = y;
	base(param);
	return (0);
}

int	base(void *param)
{
	t_mlx	*env;
	float	rate;

	env = ((t_mlx*)param);
	rate = (float)((float)env->mouse_x / (float)WDT);
	rate -= 0.5;
	env->player.cam.angle += ANGLE_DELTA * rate;
	env->img_data = ray_casting(env);
	draw_minimap(env);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	return (0);
}

void	handle_keys(t_mlx *env, int key)
{
	if (key == ESC_KEY)
		exit(EXIT_SUCCESS);
	else if (key == UP_KEY)
	{
		env->player.x += sin(env->player.cam.angle) * Y_DELTA;
		env->player.y += cos(env->player.cam.angle) * Y_DELTA;
		if (env->map[(int)env->player.x][(int)env->player.y].type == 1)
		{
			env->player.x -= sin(env->player.cam.angle) * Y_DELTA;
			env->player.y -= cos(env->player.cam.angle) * Y_DELTA;
		}
	}
	else if (key == DOWN_KEY)
	{
		env->player.x -= sin(env->player.cam.angle) * Y_DELTA;
		env->player.y -= cos(env->player.cam.angle) * Y_DELTA;
		if (env->map[(int)env->player.x][(int)env->player.y].type == 1)
		{
			env->player.x += sin(env->player.cam.angle) * Y_DELTA;
			env->player.y += cos(env->player.cam.angle) * Y_DELTA;
		}
	}
	else if (key == RIGHT_KEY)
		env->player.cam.angle += ANGLE_DELTA;
	else if (key == LEFT_KEY)
		env->player.cam.angle -= ANGLE_DELTA;
}

int		deal_key(int key, void *param)
{
	t_mlx	*env;

	env = ((t_mlx*)param);
	if (key == ESC_KEY || (key >= 123 && key <= 126))
		handle_keys(env, key);
	printf("Angle = %f\nx = %f\ny = %f\n", (double)env->player.cam.angle, (double)env->player.x, (double)env->player.y);
	env->img_data = ray_casting(env);
	draw_minimap(env);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	return (0);
}
