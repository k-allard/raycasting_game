/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:34:05 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 14:12:14 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int text_x_int;
// double text_y;
// double text_y_step;
// int y;
// int y_max;
// int color;

void		draw_wall_line(t_all *all, int text_id, double column_h, int x, double hit)
{
	int text_x_int = ((int)(all->text[text_id]->w * hit)) % all->text[text_id]->w;
	double text_y = 0.0;

	double text_y_step = all->text[text_id]->h / column_h;
	int y = all->p->h/2.0 - column_h/2.0;
	int y_max = all->p->h/2.0 + column_h/2.0;
	if (y_max > all->p->h)
		y_max = all->p->h;
	int color = pixel_get(all, text_id, text_x_int, (int)text_y);
	while (y < y_max)
	{
		if(y >= 0)
		{
			pixel_put(all, x, y, color);
			if (((int)text_y) != (int)(text_y + text_y_step))
				color = pixel_get(all, text_id, text_x_int, (int)text_y);
		}
		y += 1;
		text_y += text_y_step;
	}
}

void		cast_rays(t_all *all)
{
	t_rc rc;

	rc = *(all->rc);	
	rc.angle = all->ray->dir - M_PI/4;
	rc.angle_max = all->ray->dir + M_PI/4;
	rc.pixel_index = 0;
	rc.step = 0;
	while (rc.angle < rc.angle_max && rc.pixel_index < all->p->w)
	{
		rc.x = all->plr->x;
		rc.y = all->plr->y;
		rc.x_step = cos(rc.angle) / 20.0;
		rc.y_step = sin(rc.angle) / 20.0;

		while (is_not_wall(all, rc.y, rc.x))
		{
			rc.x_int = (int)rc.x;
			rc.y_int = (int)rc.y;
			rc.x_scale_int = (int)(rc.x * SCALE);
			rc.y_scale_int = (int)(rc.y * SCALE);
			while (rc.x_scale_int == (int)(rc.x * SCALE) && rc.y_scale_int == (int)(rc.y * SCALE) && rc.x_int == (int)rc.x && rc.y_int == (int)rc.y)
			{
				rc.x += rc.x_step;
				rc.y += rc.y_step;
			}
		}
		if (is_wall(all, rc.y, rc.x))
		{
			rc.round_y = 1.0 * round(rc.y);
			rc.round_y_d = (rc.round_y - all->plr->y) / sinl(rc.angle);
			rc.round_y_x = cos(rc.angle) * rc.round_y_d + (all->plr->x);
			rc.round_x = 1.0 * round(rc.x);
			rc.round_x_d = (rc.round_x - all->plr->x) / cos(rc.angle);
			rc.round_x_y = sin(rc.angle) * rc.round_x_d + (all->plr->y);
			rc.distance = (rc.round_x_d < rc.round_y_d) ? rc.round_x_d : rc.round_y_d;
			rc.round_x_step = (rc.round_x > rc.x) ? -1 : 0;
			rc.round_y_step = (rc.round_y > rc.y) ? -1 : 0;
			if (rc.round_y_d < 0 || (rc.round_x_d >= 0 && ( \
				(rc.round_x_d < rc.round_y_d && is_wall(all, rc.round_x_y, (int)rc.round_x + rc.round_x_step)) || \
				(rc.round_y_d < rc.round_x_d && is_not_wall(all, (int)(rc.round_y) + rc.round_y_step, rc.round_y_x)))))
			{
				rc.distance = rc.round_x_d;
				rc.hit = rc.round_x_y - (int)rc.round_x_y;
				if (cos(rc.angle) > 0)
					rc.text_id = EA;
				else
					rc.text_id = WE;
			}
			else
			{
				rc.distance = rc.round_y_d;
				rc.hit = rc.round_y_x - (int)rc.round_y_x;
				if (sin(rc.angle) > 0)
					rc.text_id = SO;
				else
					rc.text_id = NO;
			}
			all->depth_buf[rc.pixel_index] = rc.distance;
			rc.column_h =  all->p->h / rc.distance / cos(rc.angle - all->ray->dir);
			draw_wall_line(all, rc.text_id, rc.column_h, rc.pixel_index, rc.hit);
		}
		rc.angle += M_PI/2.0/all->p->w;
		rc.pixel_index ++;
	}
}
