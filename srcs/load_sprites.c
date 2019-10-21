#include "wolf3d.h"

static inline char	*read_bmp(char *filename)
{
	int 	i;
	int	fd;
	char	info[BMP_HEADER_SIZE];
	char	*data;
	int	sizes[3];

	i = 0;
	if ((fd = open(filename, O_RDONLY)) == -1
	|| read(fd, info, sizeof(char) * BMP_HEADER_SIZE) == -1)
		return (NULL);
	ft_memcpy(&sizes[1], &info[18], sizeof(int));
	ft_memcpy(&sizes[2], &info[22], sizeof(int));
	sizes[1] = ft_abs(sizes[1]);
	sizes[2] = ft_abs(sizes[2]);
	sizes[0] = 3 * sizes[1] * sizes[2];
	if (!(data = ft_strnew(sizes[0]))
		|| read(fd, data, sizeof(char) * sizes[0]) == -1)
		return (NULL);
	close(fd);
	while (i < sizes[0])
	{
		fd = (int)data[i];
		data[i] = data[i + 2];
		data[i + 2] = (char)fd;
		i += 3;
	}
	return data;
}

void	blit_weapon(t_mlx *env, char *sprite, int coords[2], int alpha)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	bytes;
	int		color;

	i = 0;
	j = 0;
	bytes = 128 * 3;
	while (i < 128)
	{
		while (j < bytes * (i + 1))
		{
			ft_memcpy(&color, &sprite[j], sizeof(char) * 3);
			if (color != alpha)
				ft_fill_pixel(env->img_data, coords[0] + (j / 3), coords[1] + i, color);
			j += 3;
		}
		i++;
	}
}

char	*sprite_names(int which)
{
	static char	*filenames[NB_SPRITES] = {
			"ressources/sprites/weapons/knife_floor.bmp",
			"ressources/sprites/weapons/knife_stand.bmp",
			"ressources/sprites/weapons/knife_1.bmp",
			"ressources/sprites/weapons/knife_2.bmp",
			"ressources/sprites/weapons/knife_3.bmp",
			"ressources/sprites/weapons/gun_floor.bmp"
			"ressources/sprites/weapons/gun_stand.bmp"
			"ressources/sprites/weapons/gun_1.bmp"
			"ressources/sprites/weapons/gun_2.bmp"
			"ressources/sprites/weapons/mp40_floor.bmp"
			"ressources/sprites/weapons/mp40_stand.bmp"
			"ressources/sprites/weapons/mp40_1.bmp"
			"ressources/sprites/weapons/mp40_2.bmp"
			"ressources/sprites/weapons/minigun_floor.bmp"
			"ressources/sprites/weapons/minigun_stand.bmp"
			"ressources/sprites/weapons/minigun_1.bmp"
			"ressources/sprites/weapons/minigun_2.bmp"};
	return (filenames[which]);
}

int	load_sprites(t_mlx *env)
{
	if (!(env->weapons[0].loot = read_bmp(sprite_names(0)))
		|| !(env->weapons[0].stand = read_bmp(sprite_names(1)))
		|| !(env->weapons[0].shot = (char**)malloc(sizeof(char*) * 3)))
		return (-1);
	if (!(env->weapons[0].shot[0] = read_bmp(sprite_names(2)))
		|| !(env->weapons[0].shot[1] = read_bmp(sprite_names(3)))
		|| !(env->weapons[0].shot[2] = read_bmp(sprite_names(4))))
		return (-1);
	printf("There\n");

	if (!(env->weapons[1].loot = read_bmp(sprite_names(5)))
		|| !(env->weapons[1].stand = read_bmp(sprite_names(6)))
		|| !(env->weapons[1].shot = (char**)malloc(sizeof(char*) * 2)))
		return (-1);
	if (!(env->weapons[1].shot[0] = read_bmp(sprite_names(7)))
		|| !(env->weapons[1].shot[1] = read_bmp(sprite_names(8))))
		return (-1);

	if (!(env->weapons[2].loot = read_bmp(sprite_names(9)))
		|| !(env->weapons[2].stand = read_bmp(sprite_names(10)))
		|| !(env->weapons[2].shot = (char**)malloc(sizeof(char*) * 2)))
		return (-1);
	if (!(env->weapons[2].shot[0] = read_bmp(sprite_names(11)))
		|| !(env->weapons[2].shot[1] = read_bmp(sprite_names(12))))
		return (-1);

	if (!(env->weapons[3].loot = read_bmp(sprite_names(13)))
		|| !(env->weapons[3].stand = read_bmp(sprite_names(14)))
		|| !(env->weapons[3].shot = (char**)malloc(sizeof(char*) * 2)))
		return (-1);
	if (!(env->weapons[3].shot[0] = read_bmp(sprite_names(15)))
		|| !(env->weapons[3].shot[1] = read_bmp(sprite_names(16))))
		return (-1);
	return (0);
}
