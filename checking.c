#include "cub.h"

void	checkmap(t_all *all, int x, int y)
{
	char	**map;

	// all->plr->pos = 0;
	map = all->p->split_map;
	if (x == all->map_hight)
		error("MAP NOT CLOSED AROUND SPAWN\n");
	if (map[x][y] == '1' || map[x][y] == '3' || map[x][y] == '4')
		return ;
	if (x == 0 || y == 0)
		error("MAP NOT CLOSED AROUND SPAWN\n");
	if (map[x][y] == ' ')
		error("MAP NOT CLOSED AROUND SPAWN\n");
	if (map[x][y] == '0')
		map[x][y] = '3';
	if (map[x][y] == '2')
		map[x][y] = '4';
	checkmap(all, x + 1, y);
	checkmap(all, x, y + 1);
	checkmap(all, x - 1, y);
	checkmap(all, x, y - 1);
}


void check_player(char **map)
{
/*need to check if the player is placed correctly*/
}

void			check_line_map(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !(line[i] >= '0' && line[i] <= '2') &&
		line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
		line[i] != 'W')
			error("Unknown symbol on the map");
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
		line[i] == 'W')
		{
			all->p->pl_dir = line[i];
			all->ch->pos_player++;
		}
		i++;
	}
}

void check_params(t_all *all)
{
    if (all->ch->r == 0)
		error("Resolution is not set");
	if (all->ch->no == 0)
		error("Path to the north texture is not set");
	if (all->ch->so == 0)
		error("Path to the south texture is not set");
	if (all->ch->we == 0)
		error("Path to the west texture is not set");
	if (all->ch->ea == 0)
		error("Path to the east texture is not set");
	if (all->ch->s == 0)
		error("Path to the sprite texture is not set");
	if (all->ch->f == 0)
		error("Floor color is not set");
	if (all->ch->c == 0)
		error("Ceiling color is not set");
	if (all->ch->map != 1)
		error("Is there a map in your file?");
	if (all->ch->pos_player == 0)
		error("Player position is not set");
	if (all->ch->r != 1)
		error("Resolution must be set once");
	if (all->ch->no != 1 || all->ch->so != 1 || all->ch->we != 1 || all->ch->ea != 1 || all->ch->s != 1)
		error("The path to each texture must be set once");
	if (all->ch->f != 1 || all->ch->c != 1)
		error("The floor and ceiling colors must be set once");
	if (all->ch->pos_player != 1)
		error("There must be only one player on the map");

}

int check_filename(char *filename)
{
    int i;

    i = ft_strlen(filename);
    if (filename[i - 1] == 'b' && filename[i - 2] == 'u' &&
	filename[i - 3] == 'c' && filename[i - 4] == '.')
	{
		if ((i = open(filename, O_RDONLY)) < 0)
			error("There is no such .cub file");
		return (1);
	}
	else
		error("File should be in format *.cub");
    return (0);
}