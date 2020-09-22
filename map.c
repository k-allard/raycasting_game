#include "cub.h"

static void get_map_size(t_all *all)
{
	int rows = 0;
	int maxColumns = 0;
	int rowSize = 0;

	while (all -> p ->split_map[rows])
	{
		rowSize = ft_strlen(all -> p ->split_map[rows]);
		if(rowSize > maxColumns)
			maxColumns = rowSize;
		rows++;
	}
	all->map_hight = rows;
	all->map_width = maxColumns;
}

static void get_player_position(t_all *all)
{
	int row = 0;
	int column = 0;
	char *playerChar;

	while (all->p->split_map[row])
	{
		playerChar = ft_strchr(all -> p ->split_map[row], all->p->pl_dir);
		if(playerChar)
		{
			column = playerChar - all->p->split_map[row];
			all->plr->x = 1.0 * column + 0.5;
			all->plr->y = 1.0 * row + 0.5;
			return;
		}
		row++;
	}
}

static void sprite_count(t_all *all)
{
	int		row = 0;
	int		column = 0;
	int		count = 0;
	char*	sprite_char;

	row = 0;
	column = 0;
	count = 0;
	while (all->p->split_map[row])
	{
		char* start_row = all->p->split_map[row];
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

static void get_sprite_position(t_all *all)
{
	int 	i;
	int     row;
	int     column;
	char*   sprite_char;
	char*	start_row;
	
	i = 0;
	row = 0;
	column = 0;
	while (all->p->split_map[row])
	{
		start_row = all->p->split_map[row];
		sprite_char = ft_strchr(start_row, '2');
		while(sprite_char)
		{
			column = sprite_char - all->p->split_map[row];
			start_row = sprite_char + 1;
			all->sprites[i]->x = 1.0 * column + 0.5;
			all->sprites[i]->y = 1.0 * row + 0.5;			
			i++;
			sprite_char = ft_strchr(start_row, '2');
		}
		row++;
	}
}

void map_parsing(int fd, char *line, t_all *all)
{
	int row_is_present;

	row_is_present = 1;
	check_line_map(line, all);
	all->p->line_map = ft_strjoin(line, "|");
	while (row_is_present > 0)
	{
		if ((row_is_present = get_next_line(fd, &line)) == (-1))
			error("File reading error!", all);
		check_line_map(line, all);
		all->p->line_map = ft_strjoin(all->p->line_map, line);
		all->p->line_map = ft_strjoin(all->p->line_map, "|");
	}
	all->p->split_map = ft_split(all->p->line_map, '|');
	get_map_size(all);
	get_player_position(all);
	sprite_count(all);
	init_sprite_struct(all);
	get_sprite_position(all);
}