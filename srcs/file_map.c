/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:41:08 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 15:43:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	get_map_size(t_all *all)
{
	int rows;
	int max_columns;
	int row_size;

	rows = 0;
	max_columns = 0;
	while (all->p->map[rows])
	{
		row_size = ft_strlen(all->p->map[rows]);
		if (row_size > max_columns)
			max_columns = row_size;
		rows++;
	}
	all->map_h = rows;
	all->map_w = max_columns;
}

static void	get_player_position(t_all *all)
{
	int		row;
	int		column;
	char	*plr_char;

	row = 0;
	while (all->p->map[row])
	{
		plr_char = ft_strchr(all->p->map[row], all->p->pl_dir);
		if (plr_char)
		{
			column = plr_char - all->p->map[row];
			all->plr->x = 1.0 * column + 0.5;
			all->plr->y = 1.0 * row + 0.5;
			return ;
		}
		row++;
	}
}

static void	sprite_count(t_all *all)
{
	int		row;
	int		count;
	char	*sprite_char;
	char	*start_row;

	row = 0;
	count = 0;
	while (all->p->map[row])
	{
		start_row = all->p->map[row];
		sprite_char = ft_strchr(start_row, '2');
		while (sprite_char)
		{
			count++;
			start_row = sprite_char + 1;
			sprite_char = ft_strchr(start_row, '2');
		}
		row++;
	}
	all->sprite_count = count;
}

static void	get_sprite_position(t_all *all)
{
	int		i;
	int		row;
	int		column;
	char	*sprite_char;
	char	*start_row;

	i = 0;
	row = 0;
	while (all->p->map[row])
	{
		start_row = all->p->map[row];
		sprite_char = ft_strchr(start_row, '2');
		while (sprite_char)
		{
			column = sprite_char - all->p->map[row];
			start_row = sprite_char + 1;
			all->sprites[i]->x = 1.0 * column + 0.5;
			all->sprites[i]->y = 1.0 * row + 0.5;
			i++;
			sprite_char = ft_strchr(start_row, '2');
		}
		row++;
	}
}

void		map_parsing(int fd, char *line, t_all *all)
{
	int		row_is_present;
	char	*line_new;

	row_is_present = 1;
	check_line_map(line, all);
	all->p->line_map = ft_strjoin(line, "|");
	while (row_is_present > 0)
	{
		if ((row_is_present = get_next_line(fd, &line_new)) == (-1))
			error("File reading error!", all);
		check_line_map(line_new, all);
		all->p->line_map = safe_str_join(all->p->line_map, line_new);
		all->p->line_map = safe_str_join(all->p->line_map, "|");
		free(line_new);
	}
	all->p->map = ft_split(all->p->line_map, '|');
	safe_free_str(&all->p->line_map);
	get_map_size(all);
	get_player_position(all);
	sprite_count(all);
	init_sprite_struct(all);
	get_sprite_position(all);
}
