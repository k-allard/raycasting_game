/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:35:02 by kallard           #+#    #+#             */
/*   Updated: 2020/09/16 22:36:29 by kallard          ###   ########.fr       */
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

typedef struct s_checks
{
	//проверки 1 или 0. если 0 - error:
	int			r;				//разрешение картинки установлено?
	int			n;				//текстура для севера установлена?
	int			s;				//текстура для юга установлена?
	int			w;				//текстура для запада установлена?
	int			e;				//текстура для востока установлена?
	int			sp;				//текстура для спрайта установлена?
	int			f;				//установлен цвет пола?
	int			c;				//установлен цвет потолка?
	int			map;			//есть карта в файле?
	int			pos_player;		//нашли игрока на карте?


	int 		screen_w;		// ширина экрана
	int 		screen_h;		// высота экрана
}				t_checks;

typedef struct s_param
{
	int 		width;			//ширина окна игры и картинки
	int			hight;			//высота окна игры и картинки 
	
	//пути к текстурам:
	char		*n;				//текстура на севере и т.д...
	char		*s;
	char		*w;
	char		*e;
	char		*sp;

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


typedef struct		s_all 		// структура для остальных структур
{
	int				is_draw;
	t_checks		*ch;
	t_param			*p;
	t_img			**img;
	t_img			*texture_NO;
	t_plr			*plr;
	t_ray			*ray;
	void			*mlx;		//       	CONNECTION IDENTIFIER   all->mlx
	void			*win;		// 			WINDOW IDENTIFIER	
	// char			**map;
	int				map_width;
	int				map_hight;
}					t_all;


/*UTILS*/
void            my_pixel_put(t_all *all, int x, int y, int color);

/*CHECKS*/
int				check_filename(char *filename);
void			check_params(t_all *all);
void			check_line_map(char *line, t_all *all);


/*ERRORS*/
void			error(char *message);

/*INIT*/
void   			init_check_struct(t_all *all);
void			init_param_struct(t_all *all);
void			init_game_struct(t_all *all);

void			init_game(t_all *all);


/*PARSING*/
void			file_parsing(int fd, t_all *all);

/*GAME*/
void			game_start(t_all *all);
void			cast_rays(t_all *all);
void			cast_rays2(t_all *all);
void			cast_rays3(t_all *all);
void			three_dimensions(t_all *all);


#endif
