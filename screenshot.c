/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:35:41 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 00:08:00 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    ft_bmp(t_all *all)
{
	char		*bmp;
	int32_t		num;
	int			x;
	int			y;
	uint32_t	size;
	
	size = all->p->h * all->p->w * (all->img->bpp / 8) + 54;
	!(bmp = (char*)malloc(size)) ? error("Screenshot malloc error", all) : 0;

	//BITMAPFILEHEADER
	ft_bzero(bmp, size);
	ft_memcpy(&bmp[0x00], "BM", 2);
	ft_memcpy(&bmp[0x02], &size, 4);
	num = 0;
	ft_memcpy(&bmp[0x06], &num, 2);
	num = 14 + 40;
	ft_memcpy(&bmp[0x0A], &num, 4);

	//BITMAPINFO - v3
	num = 40;
	ft_memcpy(&bmp[0x0E], &num, 4);
	num = all->p->w;
	ft_memcpy(&bmp[0x12], &num, 4);
	num = -all->p->h;
	ft_memcpy(&bmp[0x16], &num, 4); //try -
	num = 1;
	ft_memcpy(&bmp[0x1A], &num, 2);
	num = 32;
	ft_memcpy(&bmp[0x1C], &num, 2);
	num = 0;
	ft_memcpy(&bmp[0x1E], &num, 4); /*способ хранения пикселей*/
	num = 0;
	ft_memcpy(&bmp[0x22], &num, 4); /*Размер пиксельных данных в байтах. Может быть обнулено если хранение осуществляется двумерным массивом.*/
	num = 2835;
	ft_memcpy(&bmp[0x26], &num, 4);
	ft_memcpy(&bmp[0x2A], &num, 4);
	num = 0;
	ft_memcpy(&bmp[0x2E], &num, 4); 
	ft_memcpy(&bmp[0x32], &num, 4); 

	x = 0;
	y = 0;
	while (y < all->p->h)
	{
		x = 0;
		while (x < all->p->w)
		{
			unsigned int color;
			uint32_t diff = y * all->img->l_sz + x * (all->img->bpp / 8);
			uint32_t diff_bmp = (y * all->p->w + x ) * (all->img->bpp / 8);
			color = *((unsigned int*)(all->img->addr + diff));
			//printf("%d %d [%d] = %u .. %u = %ld\n", y, x, all->img->width, diff_bmp, size, color);
			*(unsigned int*)(bmp + 54 + diff_bmp) = color;
			// ft_memcpy(&bmp[54 + diff], &color, 4);
			x++;
		}
		y ++;
	}
	
	//ft_memcpy(&bmp[54], (unsigned int*)(all->img->data_addr), (size - 54)/2);
	if (!(num = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		error("Couldn't create screenshot.bmp", all);
	(write(num, bmp, size)) < 0 ? error("Bad fd", all) : 0;
	free(bmp);
	close(num);
}

void	make_screenshot(t_all *all)
{
	write(1, "Saving screenshot...\n", 21);
	ft_bmp(all);
	write(1, "Screenshot saved!\n", 18);
	exit_game(all, EXIT_SUCCESS);
}
