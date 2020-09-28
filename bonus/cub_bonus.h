/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:35:02 by kallard           #+#    #+#             */
/*   Updated: 2020/09/28 15:08:12 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "../mlx/mlx.h"

# define SCALE		12
# define SPEED		0.08

typedef struct		s_rc
{
	int				x_scale_int;
	int				y_scale_int;
	int				x_int;
	int				y_int;
	double			x;
	double			y;
	double			angle;
	double			angle_max;
	int				pixel_index;
	int				step;
	double			x_step;
	double			y_step;
	double			round_y;
	double			round_y_d;
	double			round_y_x;
	double			round_x;
	double			round_x_d;
	double			round_x_y;
	double			dist;
	double			hit;
	int				text_id;
	int				color;
	int				round_x_step;
	int				round_y_step;
	double			col_h;
	int				text_x_int;
	double			text_y;
	double			text_y_step;
}					t_rc;

typedef struct		s_checks
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
	int				map;
	int				pos_player;
	int				screen_w;
	int				screen_h;
	int				screenshot;
}					t_checks;

enum				e_compas
{
	NO = 0,
	WE,
	EA,
	SO,
	S
};

enum				e_events
{
	KeyPress = 02,
	KeyRelease = 03,
	DestroyNotify = 17
};

typedef struct		s_param
{
	int				w;
	int				h;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				f_rgb;
	int				c_rgb;
	char			pl_dir;
	char			*line_map;
	char			**map;
}					t_param;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				w;
	int				h;
	int				bpp;
	int				l_sz;
	int				en;
}					t_img;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_ray
{
	double			x;
	double			y;
	double			dir;
	double			start;
	double			end;
}					t_ray;

typedef struct		s_plr
{
	double			x;
	double			y;
	double			dir;
}					t_plr;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	double			dir;
	int				h;
	int				w;
	int				x_start;
	int				y_start;
	int				is_found;
}					t_sprite;

typedef struct		s_all
{
	int				is_draw;
	t_checks		*ch;
	t_param			*p;
	t_img			*img;
	t_img			*text[5];
	t_plr			*plr;
	t_ray			*ray;
	t_sprite		**sprites;
	t_rc			*rc;
	void			*mlx;
	void			*win;
	int				map_w;
	int				map_h;
	double			*depth_buf;
	int				sprite_count;
	int				key_forward;
	int				key_down;
	int				key_rigth;
	int				key_left;
	int				key_rotate_rigth;
	int				key_rotate_left;
	int				sprites_found;
}					t_all;

/*
** INIT
*/

void				init_check_struct(t_all *all);
void				init_game(t_all *all);
void				init_game_structs(t_all *all);
void				init_sprite_struct(t_all *all);

/*
** FILE PARSING
*/

void				file_parsing(int fd, t_all *all);
void				sort_param(char *line, t_all *all);
void				texture_pars(char *line, t_all *all, char *id, int i);
void				resolution_pars(char *line, t_all *all);
void				floor_n_c(char *line, int *rgb, char flag, t_all *all);
void				map_parsing(int fd, char *line, t_all *all);

/*
** CHECKS
*/

void				check_filename(char *filename, t_all *all);
void				check_params(t_all *all);
void				check_line_map(char *line, t_all *all);
void				checkmap(t_all *all, int x, int y);

/*
** GAME
*/

void				game_start(t_all *all);
void				calc_new_position(t_all *all);
void				calc_sprite_distance(t_all *all);

/*
** RAYCASTING
*/

void				background(t_all *all);
void				cast_rays(t_all *all);
void				draw_wall_line(t_all *all, double column_h, int x,
					double hit);
void				draw_sprites(t_all *all);

/*
** UTILS
*/

int					is_wall(t_all *all, double y, double x);
int					is_not_wall(t_all *all, double y, double x);
int					pixel_get(t_all *all, int text_id, int x, int y);
void				pixel_put(t_all *all, int x, int y, int color);
void				pixel_put_line(t_all *all, int width, int y, int color);
void				make_screenshot(t_all *all);
char				*safe_str_join(char *str1, const char *str2);
int					num_pars(char *str);
void				zeroing(t_all *all);

/*
** EXIT
*/

void				error(char *message, t_all *all);
int					exit_game(t_all *all, int exit_code);
int					close_win(t_all *all);
void				safe_free(void *ptr);
void				safe_free_str(char **ptr);

/*
** BONUS
*/

void				minimap(t_all *all);
void				sprites_on_minimap(t_all *all);
void				coin_counter(t_all *all);

#endif
