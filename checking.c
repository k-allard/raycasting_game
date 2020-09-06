#include "cub.h"

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
    if (all->ch->r != 1)
		error("Have you set resolution?");
	if (all->ch->n != 1)
		error("Have you set north texture?");
	if (all->ch->s != 1)
		error("Have you set south texture?");
	if (all->ch->w != 1)
		error("Have you set west texture?");
	if (all->ch->e != 1)
		error("Have you set east texture?");
	if (all->ch->sp != 1)
		error("Have you set sprite?");
	if (all->ch->f != 1)
		error("Have you set floor color?");
	if (all->ch->c != 1)
		error("Have you set ceilling color?");
	if (all->ch->map != 1)
		error("Is there a map in your file?");
	if (all->ch->pos_player != 1)
		error("Have you set player position?");
}

int check_filename(char *filename)
{
    int len;

    len = ft_strlen(filename);
    if (filename[len - 1] == 'b' && filename[len - 2] == 'u' &&
	filename[len - 3] == 'c' && filename[len - 4] == '.')
		return (1);
	error("Map should be in format *.cub");
    return (0);
}