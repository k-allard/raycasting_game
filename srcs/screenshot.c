/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:35:41 by kallard           #+#    #+#             */
/*   Updated: 2020/09/28 19:18:56 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	bmp_header(char *bmp, uint32_t size)
{
	int	num;

	ft_memcpy(&bmp[0x00], "BM", 2);
	ft_memcpy(&bmp[0x02], &size, 4);
	num = 0;
	ft_memcpy(&bmp[0x06], &num, 2);
	num = 14 + 40;
	ft_memcpy(&bmp[0x0A], &num, 4);
}

static void	bmp_info_v3(t_all *all, char *bmp)
{
	int	num;

	num = 40;
	ft_memcpy(&bmp[0x0E], &num, 4);
	num = all->p->w;
	ft_memcpy(&bmp[0x12], &num, 4);
	num = -all->p->h;
	ft_memcpy(&bmp[0x16], &num, 4);
	num = 1;
	ft_memcpy(&bmp[0x1A], &num, 2);
	num = 32;
	ft_memcpy(&bmp[0x1C], &num, 2);
	num = 0;
	ft_memcpy(&bmp[0x1E], &num, 4);
	num = 0;
	ft_memcpy(&bmp[0x22], &num, 4);
	num = 2835;
	ft_memcpy(&bmp[0x26], &num, 4);
	ft_memcpy(&bmp[0x2A], &num, 4);
	num = 0;
	ft_memcpy(&bmp[0x2E], &num, 4);
	ft_memcpy(&bmp[0x32], &num, 4);
}

static void	bmp_picture(t_all *all, char *bmp, uint32_t size)
{
	int			fd;
	int			x;
	int			y;
	uint32_t	diff;
	uint32_t	diff_bmp;

	y = 0;
	while (y < all->p->h)
	{
		x = 0;
		while (x < all->p->w)
		{
			diff = y * all->img->l_sz + x * (all->img->bpp / 8);
			diff_bmp = (y * all->p->w + x) * (all->img->bpp / 8);
			*(unsigned int*)(bmp + 54 + diff_bmp) =
				*((unsigned int*)(all->img->addr + diff));
			x++;
		}
		y++;
	}
	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		error("Couldn't create screenshot.bmp", all);
	(write(fd, bmp, size)) < 0 ? error("Bad fd", all) : 0;
	close(fd);
}

static void	bmp(t_all *all)
{
	char		*bmp;
	uint32_t	size;

	size = all->p->h * all->p->w * (all->img->bpp / 8) + 54;
	!(bmp = (char*)malloc(size)) ? error("Screenshot malloc error", all) : 0;
	ft_bzero(bmp, size);
	bmp_header(bmp, size);
	bmp_info_v3(all, bmp);
	bmp_picture(all, bmp, size);
	free(bmp);
}

void		make_screenshot(t_all *all)
{
	write(1, "Saving screenshot...\n", 21);
	bmp(all);
	write(1, "Screenshot saved!\n", 18);
	exit_game(all, EXIT_SUCCESS);
}
