/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 02:58:41 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 13:48:26 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>

static int	sprite_init(t_all *all, t_sprite *sp)
{
	sp->dir = atan2(sp->y - all->plr->y, sp->x - all->plr->x);
	while (sp->dir - all->ray->dir > M_PI)
		sp->dir -= 2 * M_PI;
	while (sp->dir - all->ray->dir < -M_PI)
		sp->dir += 2 * M_PI;
	sp->h = (int)(all->p->h / sp->dist);
	sp->w = 1.0 * sp->h * all->text[S]->w / all->text[S]->h;
	sp->x_start = (sp->dir - all->ray->dir) * (all->p->w / 2) / (M_PI / 4)\
				+ (all->p->w / 2) - sp->w / 2;
	sp->y_start = all->p->h / 2 - sp->h / 2;
	return (1);
}

static void	draw_sprite(t_all *all, int index)
{
	t_sprite	sp;
	int			i;
	int			j;
	int			x;

	if (all->sprites[index]->dist < 0.4)
		return ;
	sp = *(all->sprites[index]);
	if (sprite_init(all, &sp))
	{
		i = -1;
		while (++i < sp.w)
			if ((sp.x_start + i >= 0 && sp.x_start + i < all->p->w) &&
				(all->depth_buf[sp.x_start + i] >= sp.dist))
			{
				j = -1;
				x = (i * all->text[S]->w / sp.w);
				while (++j < sp.h)
					if (sp.y_start + j >= 0 && sp.y_start + j < all->p->h)
						pixel_put(all, sp.x_start + i, sp.y_start + j,\
						pixel_get(all, S, x, (j * all->text[S]->h / sp.h)));
			}
	}
}

void		draw_sprites(t_all *all)
{
	int i;

	i = 0;
	while (i < all->sprite_count)
	{
		draw_sprite(all, i);
		i++;
	}
}
