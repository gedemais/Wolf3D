/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:50:23 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/16 05:24:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define HGT 600
# define WDT 800

# define MAX_MAP_SIZE 1048576

# define NB_SPRITES 21
# define PRECISION 10

# define WALL_NORTH 13
# define WALL_SOUTH 14
# define WALL_EST 15
# define WALL_WEST 16

# define MABOYE NB_SPRITES - 2
# define ZOMBIE NB_SPRITES - 3
# define GAME_OVER NB_SPRITES - 4

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)
# define BUFF_READ 8192

# define MAX_PATH 256
# define MAX_ZOMBIES 24

# define MINIMAP_SIZE 3
# define RETICLE_SIZE 20
# define NB_WEAPONS 4

# define RAY_STEP 0.0075f
# define ANGLE_DELTA 0.033f
# define INERTIE 0.1f

# define WAVE_1 7
# define WAVE_2 25
# define WAVE_3 50
# define SPAWN_LAPS 100

# define PI 3.14159f
# define PI_4 0.7853975
# define PI_34 2.3561925

# include "../libft/libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <limits.h>
# include <time.h>
# include "keys.h"

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
	W_GUN = 4,
	W_MP40 = 7,
	W_MINIGUN = 10,
	W_MAX = 12
};

typedef union			u_isr
{
	float				f;
	uint32_t			i;
}						t_isr;

typedef struct			s_draw
{
	int					dx;
	int					dy;
	int					j;
	int					xinc;
	int					yinc;
	int					cumul;
	int					x;
	int					y;
}						t_draw;

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
	float				hit_x;
	float				hit_y;
	float				bloc_mx;
	float				bloc_my;
	float				bloc_angle;
	float				sample_x;
	float				sample_y;
	int					sprite;
	int					test_x;
	int					test_y;
	int					hit;
}						t_ray;

typedef struct			s_bloc
{
	char				type;
}						t_bloc;

typedef struct			s_cam
{
	float				height;
	float				angle;
	float				fov;
}						t_cam;

typedef struct			s_z_render
{
	float				z_angle;
	float				cieling;
	float				floor;
	float				dist;
	float				height;
	float				ratio;
	float				width;
	float				middle;
}						t_z_render;

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

struct					s_zombie
{
	int					damages;
	int					dlaps;
	int					hp;
	int					refresh;
	float				x;
	float				y;
	float				mid;
	float				width;
	t_zombie			*next;
	t_zombie			*prev;
};

typedef struct			s_z_buff
{
	float				val;
	float				wall;
}						t_z_buff;

typedef struct s_node	t_node;

struct					s_node
{
	float				ggoal;
	float				lgoal;
	int					x;
	int					y;
	t_node				*n[4];
	t_node				*parent;
	int					index;
	bool				full;
	bool				visited;
	t_node				*next;
};

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_weapon
{
	int					damages;
	int					cadency;
	int					nb_frames;
	int					speed;
	bool				full_auto;
	char				type;
}						t_weapon;

typedef struct			s_math
{
	float				half_fov;
	int					half_wdt;
	int					half_hgt;
	int					wdt4;
	int					hgt4;
	int					img_bytes;
}						t_math;

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
	t_z_buff			z_buff[WDT];
	t_weapon			weapons[W_MAX];
	t_player			player;
	t_pos				*spawns;
	t_node				*start;
	t_node				*end;
	t_math				math;
	bool				keys[NB_KEYS];
	bool				night;
	float				min_dist;
	int					mm_size;
	int					nb_spawns;
	unsigned int		map_hgt;
	unsigned int		map_wdt;
	char				weapon;
	int					nb_killed;
	bool				war;
	int					bpp;
	int					s_l;
	int					endian;
}						t_mlx;

/*
** Ray casting
*/
char					*ray_casting(t_mlx *env);
void					set_background(t_mlx *env);

/*
** MLX functions
*/
void					ft_fill_pixel(char *img_str, int x, int y, int color);
char					*ft_clear_image(void *param, char *img_data);
int						ft_exit(int status);
void					ft_fill_texture(char *img_str, int x, int y, int color);

/*
** Events
*/
int						press_key(int key, void *param);
int						release_key(int key, void *param);
int						pos(int x, int y, void *param);
int						release(int button, int x, int y, void *param);
int						press(int button, int x, int y, void *param);
int						position(int x, int y, void *param);
int						base(void *param);
void					handle_enemys(t_mlx *env);
void					handle_weapon(t_mlx *env);
void					replace_pointer(int x, int y);

/*
** Weapons
*/
void					init_weapons(t_mlx *env);
int						load_sprites(t_mlx *env);
bool					do_copy(int color, char alph[4]);
void					blit_sprite(t_mlx *env, t_sprite sp, int x, int y);
bool					*blit_alpha(void);
bool					is_in_fov(t_mlx *e, float zx, float zy, t_z_render *r);

/*
** Parsing
*/
int						parse_map(t_mlx *env, char *file);
char					*read_file(int fd);
int						load_sprites(t_mlx *env);

/*
** Enemys
*/
int						z_lstlen(t_zombie *lst);
void					z_free_lst(t_zombie *lst);
void					z_snap_node(t_zombie **lst, t_zombie *node);
int						z_pushfront(t_zombie **lst, t_zombie *new);
t_zombie				*z_lstnew(t_mlx *env);
void					omniscience(t_mlx *env);
void					render_zombie(t_mlx *env, t_zombie *z);

/*
** A*
*/
int						a_star(t_mlx *e, t_node *n, t_node *s[2], float dir[2]);
float					compute_dist(int ax, int ay, int bx, int by);

t_node					*node_new(t_node *src);
int						node_pushback(t_node **lst, t_node *node);
void					node_pop(t_node **lst);
int						node_len(t_node *lst);

/*
** Hudding
*/
void					draw_minimap(t_mlx *env);
void					draw_square(t_mlx *env, int x, int y, int size);
void					draw_reticle(t_mlx *env);
void					ft_draw_line(void *param, int s[2], int e[2]);

void					barre_de_vie(t_mlx *env, int padx, int pady);
/*
** Sound
*/
void					weapon_sound(char type);
bool					game_over(t_mlx *env);
int						*color(void);

float					fast_isr(float n);
void					init_maths(t_mlx *env);

#endif
