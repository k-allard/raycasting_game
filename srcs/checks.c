/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 13:16:58 by kallard           #+#    #+#             */
/*   Updated: 2020/10/05 19:43:08 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	checkmap(t_all *all, int x, int y)
{
	char	**map;

	map = all->p->map;
	if (x == all->map_h)
		error("Map not closed around spawn", all);
	if (map[x][y] == '1' || map[x][y] == '3' || map[x][y] == '4')
		return ;
	if (x == 0 || y == 0)
		error("Map not closed around spawn", all);
	if (map[x][y] == ' ')
		error("Map not closed around spawn", all);
	if (map[x][y] == '0')
		map[x][y] = '3';
	if (map[x][y] == '2')
		map[x][y] = '4';
	checkmap(all, x + 1, y);
	checkmap(all, x, y + 1);
	checkmap(all, x - 1, y);
	checkmap(all, x, y - 1);
}

void	check_below_map(int fd, t_all *all)
{
	int		row_is_present;
	char	*line;

	row_is_present = 1;
	while (row_is_present > 0)
	{
		if ((row_is_present = get_next_line(fd, &line)) == (-1))
			error("File reading error!", all);
		if (*line != '\0')
			error("There should be nothing below the map", all);
		free(line);
	}
}

void	check_line_map(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !(line[i] >= '0' && line[i] <= '2') &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W')
			error("Unknown symbol on the map", all);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
			line[i] == 'W')
		{
			all->p->pl_dir = line[i];
			all->ch->pos_player++;
		}
		i++;
	}
}

void	check_params(t_all *all)
{
	if (all->ch->r == 0)
		error("Resolution is not set", all);
	if (all->ch->no == 0 || all->ch->so == 0 || all->ch->we == 0 ||
		all->ch->ea == 0)
		error("Path to the wall texture is not set", all);
	if (all->ch->s == 0)
		error("Path to the sprite texture is not set", all);
	if (all->ch->f == 0)
		error("Floor color is not set", all);
	if (all->ch->c == 0)
		error("Ceiling color is not set", all);
	if (all->ch->map != 1)
		error("Is there a map in your file?", all);
	if (all->ch->pos_player == 0)
		error("Player position is not set", all);
	if (all->ch->r != 1)
		error("Resolution must be set once", all);
	if (all->ch->no != 1 || all->ch->so != 1 || all->ch->we != 1 ||
		all->ch->ea != 1 || all->ch->s != 1)
		error("The path to each texture must be set once", all);
	if (all->ch->f != 1 || all->ch->c != 1)
		error("The floor and ceiling colors must be set once", all);
	if (all->ch->pos_player != 1)
		error("There must be only one player on the map", all);
}

void	check_filename(char *filename, t_all *all)
{
	int i;

	i = ft_strlen(filename);
	if (i < 4)
		error("File should be in format *.cub", all);
	if (filename[i - 1] == 'b' && filename[i - 2] == 'u' &&
	filename[i - 3] == 'c' && filename[i - 4] == '.')
	{
		if ((i = open(filename, O_RDONLY)) < 0)
			error("There is no such .cub file", all);
		return ;
	}
	else
		error("File should be in format *.cub", all);
}
