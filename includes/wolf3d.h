/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:50:23 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/20 20:42:04 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define HGT 720
# define WDT 1080
# define KEY_PRESS 2
# define KEY_PRESS_MASK (1L<<0)
# define ITER_BASE 30
# define BUFF_READ 8192

# define NB_THREADS 8

# define RAY_STEP 0.01f

# define ANGLE_DELTA 0.05f

# define Y_DELTA 0.1f

# define ESC_KEY 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126

# include "../libft/libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>

enum					e_bloc_type
{
						BLOC_VOID,
						BLOC_FULL,
						BLOC_MAX
};

typedef struct			s_ray
{
	float				angle;
	float				dist;
	int					test_x;
	int					test_y;
	float				sq_hgt;
	float				sq_wdt;
	bool				hit;
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
	float				x;
	float				y;
	float				dirx;
	float				diry;
	float				eye_x;
	float				eye_y;
	t_cam				cam;
}						t_player;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img_ptr;
	char				*img_data;
	char				*file;
	t_bloc				**map;
	t_player			player;
	unsigned int		map_hgt;
	unsigned int		map_wdt;
	int					bpp;
	int					s_l;
	int					endian;
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
** Parsing
*/
int						parse_map(t_mlx *env, char *file);
char					*read_file(int fd);

/*
** Utils
*/
double					ft_sq(double nb);

#endif
