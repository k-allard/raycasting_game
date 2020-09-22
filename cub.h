/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:35:02 by kallard           #+#    #+#             */
/*   Updated: 2020/09/21 22:08:31 by kallard          ###   ########.fr       */
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

#define SCALE	15         	   // условный размер каждого квадратика в карте
#define SPEED	0.08	   //0.1 is normal

typedef struct s_checks
{
	//проверки 1 или 0. если 0 - error:
	int			r;				//разрешение картинки установлено?
	int			no;				//текстура для севера установлена?
	int			so;				//текстура для юга установлена?
	int			we;				//текстура для запада установлена?
	int			ea;				//текстура для востока установлена?
	int			s;				//текстура для спрайта установлена?
	int			f;				//установлен цвет пола?
	int			c;				//установлен цвет потолка?
	int			map;			//есть карта в файле?
	int			pos_player;		//нашли игрока на карте?


	int 		screen_w;		// ширина экрана
	int 		screen_h;		// высота экрана
	int			screenshot;		//флаг, надо ли делать скриншот
}				t_checks;

enum COMPAS
{
	texture_NO = 0,
	texture_WE,
	texture_EA,
	texture_SO,
	texture_S
};

enum X11EVENTS
{
	X11_Event_KeyPress = 02,
	X11_Event_KeyRelease = 03,
	X11_Event_DestroyNotify = 17
	
};

typedef struct s_param
{
	int 		width;			//ширина окна игры и картинки
	int			hight;			//высота окна игры и картинки 
	
	//пути к текстурам:
	char		*no;				//текстура на севере и т.д...
	char		*so;
	char		*we;
	char		*ea;
	char		*s;

	int			f_rgb;			//цвет пола
	int			c_rgb;			//цвет потолка
	char		pl_dir;			//направление игрока - буква
	char		*line_map;		//спарсенная карта в виде 1 строки с межстроковым разделителем
	char		**split_map;	//карта в виде двумерного массива

}				t_param;

typedef struct		s_img 
{
	void			*img;		//       	IMAGE IDENTIFIER
	char			*data_addr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_point   	// структура для точки
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_ray        //структура для луча 
{
	double			x;
	double			y;
	double			dir;		//угол между направлением луча и осью x
	double			start;
	double			end;
}					t_ray;

typedef struct		s_plr        //структура для игрока 
{
	double			x;
	double			y;
	double			dir;		//угол между направлением взгляда и осью x
	
}					t_plr;


typedef struct		s_sprite        //структура для игрока 
{
	double			x;
	double			y;
	double			distance;
}					t_sprite;


typedef struct		s_all 		// структура для остальных структур
{
	int				is_draw;
	t_checks		*ch;
	t_param			*p;
	t_img			*img;
	t_img			*textures[5];
	t_plr			*plr;
	t_ray			*ray;
	void			*mlx;		//       	CONNECTION IDENTIFIER   all->mlx
	void			*win;		// 			WINDOW IDENTIFIER	
	// char			**map;
	int				map_width;
	int				map_hight;
	char			**map_protect;		
	t_sprite		**sprites;
	double			*depth_buffer;
	int				sprite_count;
	int				key_forward;
	int				key_down;
	int				key_rigth;
	int				key_left;
	int				key_rotate_rigth;
	int				key_rotate_left;
}					t_all;


/*UTILS*/
void            my_pixel_put(t_all *all, int x, int y, int color);
int            my_pixel_get(t_all *all, int text_id, int x, int y);
void             my_pixel_put_line(t_all *all, int width, int y, int color);

/*CHECKS*/
void			check_filename(char *filename, t_all *all);
void			check_params(t_all *all);
void			check_line_map(char *line, t_all *all);
void			checkmap(t_all *all, int x, int y);


/*ERRORS*/
void error(char *message, t_all *all);

/*INIT*/
void   			init_check_struct(t_all *all);
void			init_param_struct(t_all *all);
void			init_game_structs(t_all *all);
void			init_depth_buffer(t_all *all);
void			init_game(t_all *all);
void			init_sprite_struct(t_all *all);

/*PARSING*/
void			file_parsing(int fd, t_all *all);
 void			map_parsing(int fd, char *line, t_all *all);


/*GAME*/
void			game_start(t_all *all);
void			cast_rays(t_all *all);
void			cast_rays2(t_all *all);
void			cast_rays(t_all *all);
int 			is_not_wall(t_all* all, double y, double x);
int 			is_wall(t_all* all, double y, double x);
void 			draw_sprites(t_all *all);
void			three_dimensions(t_all *all);
int		exit_game(t_all *all, int exit_code);



void	make_screenshot(t_all *all);


#endif
