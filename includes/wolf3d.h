/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:50:23 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/24 21:16:13 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define HGT 600
# define WDT 900

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)
# define BUFF_READ 8192

# define BMP_HEADER_SIZE 54

# define NB_THREADS 8

# define NB_SPRITES 22
# define NB_WEAPONS 4
# define BMP_HEADER_SIZE 54

# define MINIMAP_SIZE 4

# define RAY_STEP 0.01f

# define ANGLE_DELTA 0.025f
# define INERTIE 0.1f

# define RETICLE_SIZE 20

# define NB_KEYS 260

# define PRECISION 110

# define ESC_KEY 53
# define SPACE_KEY 49
# define SHIFT_KEY 257
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_M 46

# define WAVE_1 10
# define WAVE_2 33
# define WAVE_3 100

# include "../libft/libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

enum					e_bloc_type
{
						BLOC_VOID,
						BLOC_FULL,
						BLOC_SPAWN,
						BLOC_MAX
};

enum					e_weapon_type
{
					W_KNIFE,
					W_GUN = 5,
					W_MP40 = 9,
					W_MINIGUN = 13,
					W_MAX = 14
};

typedef struct			s_sprite
{
	void				*frame;
	void				*ptr;
	int					height;
	int					width;
	int					alpha;
}						t_sprite;

typedef struct			s_ray
{
	float				angle;
	float				dist;
	int					test_x;
	int					test_y;
	int				hit;
}						t_ray;

typedef struct			s_bloc
{
	char				type;
//	union pr contenir les params
}						t_bloc;

typedef struct			s_cam
{
	float				height;
	float				angle;
	float				fov;
}						t_cam;

typedef struct			s_player
{
	int					hp;
	float				speed;
	float				x;
	float				y;
	float				eye_x;
	float				eye_y;
	t_cam				cam;
}						t_player;

typedef struct s_zombie	t_zombie;

struct			s_zombie
{
	int		damages;
	int		hp;
	float	x;
	float	y;
	float	dx;
	float	dy;
	t_zombie	*next;
	t_zombie	*prev;
};

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_weapon
{
	int				damages;
	int				cadency;
	int				nb_frames;
	int				speed;
	bool			full_auto;
	char			type;
}				t_weapon;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img_ptr;
	char				*img_data;
	char				*file;
	t_bloc				**map;
	t_sprite			*sprites;
	t_zombie			*zombie;
	t_weapon			weapons[W_MAX];
	t_player			player;
	t_pos				*spawns;
	bool				keys[NB_KEYS];
	float				min_dist;
	int					mm_size;
	int					nb_spawns;
	unsigned int		map_hgt;
	unsigned int		map_wdt;
	char				weapon;
	int				nb_killed;
	bool				war;
	int				bpp;
	int				s_l;
	int				endian;
}						t_mlx;

/*
** Ray casting
*/
char					*ray_casting(t_mlx *env);

/*
** MLX functions
*/
void					ft_fill_pixel(char *img_str, int x, int y, int color);
char					*ft_clear_image(void *param, char *img_data);
int						ft_exit(int status);

/*
** Events
*/
int					press_key(int key, void *param);
int					release_key(int key, void *param);
int					position(int x, int y, void *param);
int					base(void *param);
void				handle_enemys(t_mlx *env);
void				handle_weapon(t_mlx *env);

/*
** Weapons 
*/
void				init_weapons(t_mlx *env);
int					load_sprites(t_mlx *env);
void				blit_sprite(t_mlx *env, t_sprite sp, int x, int y);

/*
** Parsing
*/
int						parse_map(t_mlx *env, char *file);
char					*read_file(int fd);
int					load_sprites(t_mlx *env);

/*
** Enemys
*/
int						z_lstlen(t_zombie *lst);
void					z_free_lst(t_zombie *lst);
void					z_snap_node(t_zombie **lst, t_zombie *node);
int						z_pushfront(t_zombie **lst, t_zombie *new);
t_zombie				*z_lstnew(t_mlx *env);
void					omniscience(t_mlx *env);

/*
** Hudding
*/
void					draw_minimap(t_mlx *env);
void					draw_square(t_mlx *env, int x, int y, int size);
void					draw_reticle(t_mlx *env);

/*
** Utils
*/
double					ft_sq(double nb);

#endif
