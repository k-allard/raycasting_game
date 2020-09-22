/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:34:05 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 01:54:00 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		draw_wall_line(t_all *all, int text_id, double column_h, int x, double hit)
{
	int text_x_int = ((int)(all->text[text_id]->w * hit)) % all->text[text_id]->w;
	double text_y = 0.0;

	double text_y_step = all->text[text_id]->h / column_h;
	int y = all->p->h/2.0 - column_h/2.0;
	int y_max = all->p->h/2.0 + column_h/2.0;
	if (y_max > all->p->h)
		y_max = all->p->h;
	int color = my_pixel_get(all, text_id, text_x_int, (int)text_y);
	while (y < y_max)
	{
		if(y >= 0)
		{
			my_pixel_put(all, x, y, color);
			if (((int)text_y) != (int)(text_y + text_y_step))
				color = my_pixel_get(all, text_id, text_x_int, (int)text_y);
		}
		y += 1;
		text_y += text_y_step;
	}
}

int inline	is_not_wall(t_all* all, double y, double x)
{
	return ((all->p->map[(int)y][(int)x] != '1') &&
	 (all->p->map[(int)y][(int)x] != '\0') && 
	 (all->p->map[(int)y][(int)x] != ' '));
}

int inline	is_wall(t_all* all, double y, double x)
{
	return ((all->p->map[(int)y][(int)x] == '1') || 
		(all->p->map[(int)y][(int)x] == '\0') ||
		(all->p->map[(int)y][(int)x] == ' '));
}

void		cast_rays(t_all *all)
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
		}
		if (is_wall(all, y, x))
		{
			double round_y = 1.0 * round(y);
			double round_y_d = (round_y - all->plr->y) / sinl(angle);
			double round_y_x = cos(angle) * round_y_d + (all->plr->x);
			double round_x = 1.0 * round(x);
			double round_x_d = (round_x - all->plr->x) / cos(angle);
			double round_x_y = sin(angle) * round_x_d + (all->plr->y);	
			double distance = (round_x_d < round_y_d) ? round_x_d : round_y_d;
			double hit;
			int text_id;
			int color;
			int round_x_step = (round_x > x) ? -1 : 0;
			int round_y_step = (round_y > y) ? -1 : 0;

			if (round_y_d < 0 || (round_x_d >= 0 && ( \
				(round_x_d < round_y_d && is_wall(all, round_x_y, (int)round_x + round_x_step)) || \
				(round_y_d < round_x_d && is_not_wall(all, (int)(round_y) + round_y_step, round_y_x)))))
			{	
				distance = round_x_d;
				hit = round_x_y - (int)round_x_y;
				if (cos(angle) > 0)
					text_id = EA;
				else
					text_id = WE;
			}
			else
			{
				distance = round_y_d;
				hit = round_y_x - (int)round_y_x;
				if (sin(angle) > 0)
					text_id = SO;
				else 
					text_id = NO;
			}
			all->depth_buf[pixel_index] = distance;
			double column_h =  all->p->h / distance / cos(angle - all->ray->dir);			
			draw_wall_line(all, text_id, column_h, pixel_index, hit);
		}
		angle += M_PI/2.0/all->p->w;
		pixel_index ++;
	}
}
