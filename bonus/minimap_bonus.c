/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 00:24:07 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 13:24:25 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	player(t_all *all, double x, double y)
{
	double size;
	double x_tmp;
	double y_tmp;
	double y_max;

	size = 1.0 * SCALE / 2.0;
	if (size < 1.0)
		size = 1.0;
	y_tmp = all->p->h - SCALE * all->map_h + y * SCALE - size / 2;
	y_max = y_tmp + size;
	while (y_tmp < y_max)
	{
		x_tmp = x * SCALE - size / 2;
		while (x_tmp < x * SCALE + size / 2)
		{
			pixel_put(all, x_tmp, y_tmp, 0xff4500);
			x_tmp += 1.0;
		}
		y_tmp += 1.0;
	}
}

void	labirint(t_all *all, int i, int j)
{
	int x;
	int y;
	int x_tmp;
	int y_tmp;

	x = i * SCALE;
	y = all->p->h - SCALE * all->map_h + SCALE * j;
	y_tmp = y - 1;
	while (++y_tmp < y + SCALE)
	{
		x_tmp = x - 1;
		while (++x_tmp < x + SCALE)
			pixel_put(all, x_tmp, y_tmp, 0xc8d8df);
	}
}

void	skip_empty_steps(double *x, double *y, double x_step, double y_step)
{
	int		x_int;
	int		y_int;
	int		x_scale_int;
	int		y_scale_int;

	x_int = (int)*x;
	y_int = (int)*y;
	x_scale_int = (int)(*x * SCALE);
	y_scale_int = (int)(*y * SCALE);
	while (x_scale_int == (int)(*x * SCALE) && y_scale_int == (int)(*y * SCALE)
		&& x_int == (int)*x && y_int == (int)*y)
	{
		*x += x_step;
		*y += y_step;
	}
}

void	viewcone(t_all *all)
{
	double	x;
	double	y;
	double	angle;
	double	x_step;
	double	y_step;

	angle = all->ray->dir - M_PI / 4;
	while (angle < all->ray->dir + M_PI / 4)
	{
		x = all->plr->x;
		y = all->plr->y;
		x_step = cos(angle) / 20.0;
		y_step = sin(angle) / 20.0;
		while (is_not_wall(all, y, x))
		{
			skip_empty_steps(&x, &y, x_step, y_step);
			pixel_put(all, x * SCALE, all->p->h -
					SCALE * all->map_h + y * SCALE, 0x666699);
		}
		angle += M_PI / 2.0 / all->p->w;
	}
}

void	minimap(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (all->p->map[i])
	{
		j = 0;
		while (all->p->map[i][j])
		{
			if (all->p->map[i][j] == '1')
				labirint(all, j, i);
			j++;
		}
		i++;
	}
	viewcone(all);
	player(all, all->plr->x, all->plr->y);
	sprites_on_minimap(all);
}
