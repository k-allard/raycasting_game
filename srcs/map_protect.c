/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_protect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 01:02:31 by kallard           #+#    #+#             */
/*   Updated: 2020/10/04 01:36:50 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	map_super_protect(t_all *all, int y, int x)
{
	char **map_pr;

	map_pr = all->p->map_protect;
	if (x >= 0 && x < all->map_w + 2 && y >= 0 && y < all->map_h + 2)
	{
		if (map_pr[y][x] == '1' || map_pr[y][x] == '*')
			return ;
		if (map_pr[y][x] == ' ')
			map_pr[y][x] = '*';
		else
		{
			map_pr[y][x] = '*';
			all->p->map[y - 1][x - 1] = ' ';
		}
		map_super_protect(all, y - 1, x);
		map_super_protect(all, y + 1, x);
		map_super_protect(all, y, x - 1);
		map_super_protect(all, y, x + 1);
	}
}

void		map_protect(t_all *all)
{
	int		i;
	size_t	j;
	char	**map_pr;

	if (!(all->p->map_protect = (char **)malloc(sizeof(char*) \
								* (all->map_h + 2))))
		error("MapProtect MALLOC ERROR", all);
	map_pr = all->p->map_protect;
	if (!(map_pr[0] = (char *)malloc(sizeof(char) * (all->map_w + 3))))
		error("MapProtect[0] MALLOC ERROR", all);
	i = -1;
	while (++i < all->map_w + 3)
		map_pr[0][i] = ' ';
	map_pr[0][all->map_w + 2] = '\0';
	i = 0;
	while (++i < all->map_h + 2)
		if (!(map_pr[i] = ft_strdup(map_pr[0])))
			error("MapProtect[i] MALLOC ERROR", all);
	i = -1;
	while (++i < all->map_h)
	{
		j = ft_strlcpy(&(map_pr[i + 1][1]), all->p->map[i], all->map_w + 1);
		map_pr[i + 1][j + 1] = ' ';
	}
	map_super_protect(all, 0, 0);
}
