/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:41:14 by kallard           #+#    #+#             */
/*   Updated: 2020/09/29 21:23:23 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	file_parsing(int fd, t_all *all)
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
	check_params(all);
	checkmap(all, all->plr->y, all->plr->x);
	map_outerspace_clear(all);
}
