/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 00:24:07 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 03:53:34 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	player(t_all *all, double x, double y)
{
	double size = 1.0 * SCALE / 2.0;
	if (size < 1.0) 
		size = 1.0;
	double x_tmp;
	double y_tmp = all->p->h - SCALE * all->map_h + y * SCALE - size/2;
	double y_max = y_tmp + size;

	while (y_tmp < y_max)
	{
		x_tmp = x * SCALE - size/2;
		while (x_tmp < x * SCALE + size/2) 
		{
			pixel_put(all, x_tmp, y_tmp, 0xff4500);
			x_tmp += 1.0;
		}
		y_tmp += 1.0;
	}
}

void	sprites_on_minimap(t_all *all)
{
	double size = 1.0 * SCALE / 3.0;
	double x_tmp;
	double y_tmp;
	double y_max;
	int i = -1;

	if (size < 1.0) 
		size = 1.0;
	while (++i < all->sprite_count)
	{
		y_tmp = all->p->h - SCALE * all->map_h + all->sprites[i]->y * SCALE - size/2;
		y_max = y_tmp + size;

		while (y_tmp < y_max)
		{
			x_tmp = all->sprites[i]->x * SCALE - size/2;
			while (x_tmp < all->sprites[i]->x * SCALE + size/2) 
			{
				pixel_put(all, x_tmp, y_tmp, 0xff4500);
				x_tmp += 1.0;
			}
			y_tmp += 1.0;
		}
	}
}

void	minimap_background(t_all *all)
{
	int x;
	int y;
	
	y = -1;
	y = all->p->h - SCALE * all->map_h;
	while (++y < all->p->h)
	{
		x = -1;
		while(++x < SCALE * all->map_w)
			pixel_put(all, x, y, 0x2e3628);
	}
}

void	labirint(t_all *all, int i, int j)
{
	int x = i * SCALE;
	int y = all->p->h - SCALE * all->map_h + SCALE * j;
	int x_tmp;
	int y_tmp = y-1;

	while (++y_tmp < y + SCALE)
	{
		x_tmp = x-1;
		while(++x_tmp < x + SCALE)
			pixel_put(all, x_tmp, y_tmp, 0xffb6c1);
	}
}

void	viewcone(t_all *all)
{
	int x_scale_int;
	int y_scale_int;
	int x_int;
	int y_int;
	double x = all->plr->x;
	double y = all->plr->y;
	
	double angle = all->ray->dir - M_PI/4;
	double angle_max  = all->ray->dir + M_PI/4;

	int pixel_index = 0;
	int step = 0;
	while(angle < angle_max && pixel_index < all->p->w)
	{
		x = all->plr->x;
		y = all->plr->y;
		double x_step = cos(angle) / 20.0;
		double y_step = sin(angle) / 20.0;

		while (is_not_wall(all, y, x))
		{
			x_int = (int)x;
			y_int = (int)y;
			x_scale_int = (int)(x*SCALE);
			y_scale_int = (int)(y*SCALE);
			while (x_scale_int == (int)(x*SCALE) && y_scale_int == (int)(y*SCALE) && x_int == (int)x && y_int == (int)y)
			{
				x += x_step; 
				y += y_step;
			}
			pixel_put(all, x * SCALE, all->p->h - SCALE * all->map_h + y * SCALE, 0x666699);
		}
		angle += M_PI/2.0/all->p->w;
		pixel_index ++;
	}
}

void	minimap(t_all *all)
{
	int i = 0;
	
	// minimap_background(all);
	while (all->p->map[i])
	{
		int j = 0;
		while(all->p->map[i][j])
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
