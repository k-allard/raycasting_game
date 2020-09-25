/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 21:15:28 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 15:43:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	draw_wall_line_loop(t_all *all, int x, int y, int y_max)
{
	int	color;
	int	text_id;

	text_id = all->rc->text_id;
	color = pixel_get(all, text_id, all->rc->text_x_int, (int)all->rc->text_y);
	while (y < y_max)
	{
		if (y >= 0)
		{
			pixel_put(all, x, y, color);
			if (((int)all->rc->text_y) != (int)(all->rc->text_y
										+ all->rc->text_y_step))
				color = pixel_get(all, text_id, all->rc->text_x_int,\
						(int)all->rc->text_y);
		}
		y++;
		all->rc->text_y += all->rc->text_y_step;
	}
}

void		draw_wall_line(t_all *all, double column_h, int x, double hit)
{
	int	y;
	int	y_max;
	int text_id;

	text_id = all->rc->text_id;
	all->rc->text_x_int = ((int)(all->text[text_id]->w * hit))
						% all->text[text_id]->w;
	all->rc->text_y = 0.0;
	all->rc->text_y_step = all->text[text_id]->h / column_h;
	y = all->p->h / 2.0 - column_h / 2.0;
	y_max = all->p->h / 2.0 + column_h / 2.0;
	if (y_max > all->p->h)
		y_max = all->p->h;
	draw_wall_line_loop(all, x, y, y_max);
}
