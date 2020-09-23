/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:35:02 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 03:45:25 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "mlx/mlx.h"

# define SCALE		15
# define SPEED		0.08

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
	double 			dir;
	int 			h;
	int 			w;
	int 			x_start;
	int 			y_start;
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
}					t_all;

/*
** DRAW
*/

void				pixel_put(t_all *all, int x, int y, int color);
int					pixel_get(t_all *all, int text_id, int x, int y);
void				pixel_put_line(t_all *all, int width, int y, int color);

/*
** CHECKS
*/

void				check_filename(char *filename, t_all *all);
void				check_params(t_all *all);
void				check_line_map(char *line, t_all *all);
void				checkmap(t_all *all, int x, int y);

/*
** ERRORS
*/

void				error(char *message, t_all *all);

/*
** INIT
*/

void				init_check_struct(t_all *all);
void				init_param_struct(t_all *all);
void				init_game_structs(t_all *all);
void				init_game(t_all *all);
void				init_sprite_struct(t_all *all);

/*
** PARSING
*/

void				file_parsing(int fd, t_all *all);
void				map_parsing(int fd, char *line, t_all *all);
void				sort_param(char *line, t_all *all);
void				texture_pars(char *line, t_all *all, char *id, int i);
void				resolution_pars(char *line, t_all *all);
void				floor_n_c(char *line, int *rgb, char flag, t_all *all);

/*
** GAME
*/

void				game_start(t_all *all);
void				cast_rays(t_all *all);
int					is_not_wall(t_all *all, double y, double x);
int					is_wall(t_all *all, double y, double x);
void				draw_sprites(t_all *all);
void				three_dimensions(t_all *all);
int					exit_game(t_all *all, int exit_code);
int					close_win(t_all *all);

void				make_screenshot(t_all *all);

/*
** PIXEL DRAW
*/

void        background(t_all *all);

/*
** GAME CHANGES
*/

void		calc_new_position(t_all* all);
void	calc_sprite_distance(t_all *all);
void	sort_sprite_array(t_all *all);




/*
** BONUS
*/

void				minimap(t_all *all);

#endif
