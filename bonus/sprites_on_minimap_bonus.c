/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_on_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:23:49 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 13:24:30 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	sprites_on_minimap(t_all *all)
{
	double	size;
	int		x_tmp;
	double	y_tmp;
	double	y_max;
	int		i;

	size = 1.3 * SCALE / 3.0;
	if (size < 1.0)
		size = 1.0;
	i = -1;
	while (++i < all->sprite_count)
		if (all->sprites[i]->is_found == 1)
		{
			y_tmp = all->p->h - SCALE * all->map_h
					+ all->sprites[i]->y * SCALE - size / 2;
			y_max = y_tmp + size;
			while (y_tmp < y_max)
			{
				x_tmp = all->sprites[i]->x * SCALE - size / 2 - 1;
				while (++x_tmp < all->sprites[i]->x * SCALE + size / 2)
					pixel_put(all, x_tmp, y_tmp, 0xffff00);
				y_tmp += 1.0;
			}
		}
}
