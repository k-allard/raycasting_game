/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:35:02 by kallard           #+#    #+#             */
/*   Updated: 2020/09/06 14:14:28 by kallard          ###   ########.fr       */
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

#define SCALE 16            // условный размер каждого квадратика в карте

typedef struct s_checks
{
	int	r;		//resolution
	int	n;		//path north
	int	s;		//path south
	int	w;		//path west
	int	e;		//path east
	int	sp;		//path sprite
	int	f;		//установлен цвет пола?
	int	c;		//установлен цвет потолка?
	int	map;	//есть карта в файле?
	int	pos_player;	//нашли месторасположение игрока?
}				t_checks;

typedef struct s_param
{
	int 		width;	//ширина картинки
	int			hight;	//высота картинки 
	//пути к текстурам:
	char		*n;		//текстура на севере и т.д...
	char		*s;
	char		*w;
	char		*e;
	char		*sp;
	int			f_rgb;		//цвет пола
	int			c_rgb;		//цвет потолка
	char		pl_dir;		//направление игрока
	char		*line_map;	//спарсенная карта в виде 1 строки с межстроковым разделителем |
	char		**split_map;	//карта в виде двумерного массива

}				t_param;

typedef struct    s_win     //структура для окна
{
	void        *mlx;
	void        *win;
	void        *img;
	void        *addr;		//img address from mlx_get_data_addr()
	int            line_l;  //line_length
	int            bpp;     //bits_per_pixel
	int            en;		//endian
}                  t_win;

typedef struct    s_point   // структура для точки
{
	int            x;
	int            y;
}                  t_point;

typedef struct    s_plr        //структура для игрока и луча
{
	float        x;
	float        y;
	float        dir;
	float        start;
	float        end;
}                  t_plr;

typedef struct    s_all // структура для всего вместе
{
	t_checks	*ch;
	t_param		*p;
	t_win        *win;
	t_plr        *plr;
	char        **map;
}                  t_all;


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

/*PARSING*/
void			file_parsing(int fd, t_all *all);


#endif
