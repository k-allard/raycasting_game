/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:41:14 by kallard           #+#    #+#             */
/*   Updated: 2020/10/04 01:33:13 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	undo_checkmap(t_all *all)
{
	int i;
	int j;

	i = -1;
	while (++i < all->map_h)
	{
		j = 0;
		while (all->p->map[i][j])
		{
			if (all->p->map[i][j] == '4')
				all->p->map[i][j] = '2';
			if (all->p->map[i][j] == '3')
				all->p->map[i][j] = '0';
			j++;
		}
	}
}

static void	after_pars(t_all *all)
{
	check_params(all);
	checkmap(all, all->plr->y, all->plr->x);
	undo_checkmap(all);
	map_protect(all);
	sprite_count(all);
	init_sprite_struct(all);
	get_sprite_position(all);
}

void		file_parsing(int fd, t_all *all)
{
	int		row_is_present;
	char	*line;
	int		i;

	row_is_present = 1;
	i = 0;
	while (row_is_present > 0)
	{
		if ((row_is_present = get_next_line(fd, &line)) == (-1))
			error("File reading error", all);
		while (line[i] == ' ')
			i++;
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		{
			all->ch->map++;
			map_parsing(fd, line, all);
			free(line);
			break ;
		}
		sort_param(&line[i], all);
		free(line);
	}
	after_pars(all);
}
