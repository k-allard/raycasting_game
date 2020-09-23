/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 00:09:50 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 03:11:25 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	pixel_put(t_all *all, int x, int y, int color)
{
	char	*dest;

	dest = all->img->addr + (y * all->img->l_sz + x * (all->img->bpp / 8));
	*(unsigned int*)dest = color;
}

void	pixel_put_line(t_all *all, int width, int y, int color)
{
	char	*dest;
	int		x;
	int		pixel_size;

	pixel_size = all->img->bpp / 8;
	dest = all->img->addr + (y * all->img->l_sz);
	while (--width)
		*(unsigned int*)(dest + width * pixel_size) = color;
}

int		pixel_get(t_all *all, int text_id, int x, int y)
{
	char	*dest;
	t_img	t;

	t = *(all->text[text_id]);
	dest = t.addr + (y * t.l_sz + x * (t.bpp / 8));
	return (*(unsigned int*)dest);
}
