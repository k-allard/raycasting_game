/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:34:05 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 15:43:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	wall_touch_init(t_all *all)
{
	t_rc *rc;

	rc = all->rc;
	rc->round_y = 1.0 * round(rc->y);
	rc->round_y_d = (rc->round_y - all->plr->y) / sinl(rc->angle);
	rc->round_y_x = cos(rc->angle) * rc->round_y_d + (all->plr->x);
	rc->round_x = 1.0 * round(rc->x);
	rc->round_x_d = (rc->round_x - all->plr->x) / cos(rc->angle);
	rc->round_x_y = sin(rc->angle) * rc->round_x_d + (all->plr->y);
	rc->dist = (rc->round_x_d < rc->round_y_d) ? rc->round_x_d :
													rc->round_y_d;
	rc->round_x_step = (rc->round_x > rc->x) ? -1 : 0;
	rc->round_y_step = (rc->round_y > rc->y) ? -1 : 0;
}

static void	wall_touch_point(t_all *all)
{
	t_rc *rc;

	rc = all->rc;
	if (rc->round_y_d < 0 || (rc->round_x_d >= 0 && \
		((rc->round_x_d < rc->round_y_d && \
		is_wall(all, rc->round_x_y, (int)rc->round_x + rc->round_x_step)) || \
		(rc->round_y_d < rc->round_x_d && is_not_wall(all, (int)(rc->round_y)
		+ rc->round_y_step, rc->round_y_x)))))
	{
		rc->dist = rc->round_x_d;
		rc->hit = rc->round_x_y - (int)rc->round_x_y;
		if (cos(rc->angle) > 0)
			rc->text_id = EA;
		else
			rc->text_id = WE;
	}
	else
	{
		rc->dist = rc->round_y_d;
		rc->hit = rc->round_y_x - (int)rc->round_y_x;
		if (sin(rc->angle) > 0)
			rc->text_id = SO;
		else
			rc->text_id = NO;
	}
}

static void	ray(t_all *all)
{
	t_rc *rc;

	rc = all->rc;
	rc->x_int = (int)rc->x;
	rc->y_int = (int)rc->y;
	rc->x_scale_int = (int)(rc->x * SCALE);
	rc->y_scale_int = (int)(rc->y * SCALE);
	while (rc->x_scale_int == (int)(rc->x * SCALE) && \
		rc->y_scale_int == (int)(rc->y * SCALE) && \
		rc->x_int == (int)rc->x && rc->y_int == (int)rc->y)
	{
		rc->x += rc->x_step;
		rc->y += rc->y_step;
	}
}

static void	cast_rays_init(t_all *all)
{
	t_rc *rc;

	rc = all->rc;
	rc->angle = all->ray->dir - M_PI / 4;
	rc->angle_max = all->ray->dir + M_PI / 4;
	rc->pixel_index = 0;
	rc->step = 0;
}

void		cast_rays(t_all *all)
{
	t_rc *rc;

	rc = all->rc;
	cast_rays_init(all);
	while (rc->angle < rc->angle_max && rc->pixel_index < all->p->w)
	{
		rc->x = all->plr->x;
		rc->y = all->plr->y;
		rc->x_step = cos(rc->angle) / 20.0;
		rc->y_step = sin(rc->angle) / 20.0;
		while (is_not_wall(all, rc->y, rc->x))
			ray(all);
		if (is_wall(all, rc->y, rc->x))
		{
			wall_touch_init(all);
			wall_touch_point(all);
			all->depth_buf[rc->pixel_index] = rc->dist;
			rc->col_h = all->p->h / rc->dist / cos(rc->angle - all->ray->dir);
			draw_wall_line(all, rc->col_h, rc->pixel_index, rc->hit);
		}
		rc->angle += M_PI / 2.0 / all->p->w;
		rc->pixel_index++;
	}
}
