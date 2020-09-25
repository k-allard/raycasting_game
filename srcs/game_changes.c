/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_changes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 03:28:39 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 15:43:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	sort_sprite_array(t_all *all)
{
	t_sprite	*tmp;
	int			i;
	int			j;

	i = 0;
	while (i < all->sprite_count - 1)
	{
		j = 0;
		while (j < all->sprite_count - 1 - i)
		{
			if (all->sprites[j]->dist < all->sprites[j + 1]->dist)
			{
				tmp = all->sprites[j];
				all->sprites[j] = all->sprites[j + 1];
				all->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void		calc_sprite_distance(t_all *all)
{
	int i;

	i = 0;
	while (i < all->sprite_count)
	{
		all->sprites[i]->dist = sqrt(pow(all->plr->x - all->sprites[i]->x, 2)
								+ pow(all->plr->y - all->sprites[i]->y, 2));
		i++;
	}
	sort_sprite_array(all);
}

static void	glide(t_all *all, double y_step, double x_step)
{
	double y_new;
	double x_new;

	if (all->key_left == 0)
	{
		y_new = y_step + sin(all->ray->dir - M_PI / 2) * 0.4 * SPEED;
		x_new = x_step + cos(all->ray->dir - M_PI / 2) * 0.4 * SPEED;
		if (is_not_wall(all, all->plr->y + y_new * 3, all->plr->x + x_new * 3))
		{
			all->plr->y += y_new;
			all->plr->x += x_new;
			return ;
		}
	}
	if (all->key_rigth == 0)
	{
		y_new = y_step + sin(all->ray->dir + M_PI / 2) * 0.4 * SPEED;
		x_new = x_step + cos(all->ray->dir + M_PI / 2) * 0.4 * SPEED;
		if (is_not_wall(all, all->plr->y + y_new * 3, all->plr->x + x_new * 3))
		{
			all->plr->y += y_new;
			all->plr->x += x_new;
		}
	}
}

void		calc_new_position(t_all *all)
{
	double y_step;
	double x_step;

	all->ray->dir -= (SPEED * 0.55 * all->key_rotate_left);
	all->ray->dir += (SPEED * 0.55 * all->key_rotate_rigth);
	y_step = SPEED * (0.0
		+ sin(all->ray->dir - M_PI / 2) * 0.4 * all->key_left
		+ sin(all->ray->dir + M_PI / 2) * 0.4 * all->key_rigth
		- sin(all->ray->dir) * 0.4 * all->key_down
		+ sin(all->ray->dir) * 0.6 * all->key_forward);
	x_step = SPEED * (0.0
		+ cos(all->ray->dir - M_PI / 2) * 0.4 * all->key_left
		+ cos(all->ray->dir + M_PI / 2) * 0.4 * all->key_rigth
		- cos(all->ray->dir) * 0.4 * all->key_down
		+ cos(all->ray->dir) * 0.6 * all->key_forward);
	if (is_not_wall(all, all->plr->y + y_step * 3, all->plr->x + x_step * 3))
	{
		all->plr->y += y_step;
		all->plr->x += x_step;
	}
	else
		glide(all, y_step, x_step);
}
