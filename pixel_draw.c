/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 03:16:03 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 03:20:22 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	background(t_all *all)
{
	int y_tmp;

	y_tmp = -1;
	while (++y_tmp < all->p->h / 2)
		pixel_put_line(all, all->p->w, y_tmp, all->p->c_rgb);
	while (++y_tmp < all->p->h)
		pixel_put_line(all, all->p->w, y_tmp, all->p->f_rgb);
}
