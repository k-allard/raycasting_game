/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:35:02 by kallard           #+#    #+#             */
/*   Updated: 2020/09/05 20:14:42 by kallard          ###   ########.fr       */
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
	t_win        *win;
	t_plr        *plr;
	char        **map;
}                  t_all;





#endif
