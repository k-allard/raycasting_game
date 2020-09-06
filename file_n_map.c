#include "cub.h"

static void floor_n_c(char *line, int *rgb, char flag, t_all *all)
{
/*
** Функция для парсинга цвета пола и потолка
** Your program must be able to set the floor and ceilling colors to two different ones.
Floor/Ceilling color:
F 220,100,0
· R,G,B colors in range [0,255]: 0, 255, 255
*/
}

static void resolution_pars(char *line, t_all *all)
{

	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	all->p->width = ft_atoi(&line[i]);
	if (all->p->width <= 0)
		error("Width is less than or equals zero");
	/*
	** If the declared screen size in the map is greater than the display resolution, 
	** the window size will be set depending to the current display resolution.
	*/
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	all->p->hight = ft_atoi(&line[i]);
	if (all->p->hight <= 0)
		error("Hight is less than or equals zero");
	/*
	** If the declared screen size in the map is greater than the display resolution, 
	** the window size will be set depending to the current display resolution.
	*/
	all->ch->r++;
}

static void			texture_path_pars(char **param, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '.' && line[i + 1] == '/')
		*param = line;
	else
		error("Incorrect path to the texture");
}

static void texture_pars(char *line, t_all *all, char *id, int i)
{
	if (id[i] == 'N' && id[i + 1] == 'O')
	{
		texture_path_pars(&(all->p->n), line);
		all->ch->n++;
	}
	else if (id[i] == 'S' && id[i + 1] == 'O')
	{
		texture_path_pars(&(all->p->s), line);
		all->ch->s++;
	}
	else if (id[i] == 'W' && id[i + 1] == 'E')
	{
		texture_path_pars(&(all->p->w), line);
		all->ch->w++;
	}
	else if (id[i] == 'E' && id[i + 1] == 'A')
	{
		texture_path_pars(&(all->p->e), line);
		all->ch->e++;
	}
	else if (id[i] == 'S' && id[i + 1] == '\0')
	{
		texture_path_pars(&(all->p->sp), line);
		all->ch->sp++;
	}
}

static void sort_param(char *line, t_all *all)
{
	int i;

	i = 0;
	if (line[i] == '\0' || line[i] == 13)		//13 - возврат каретки
		return ;
	if (line[i] == 'R' && (line[i + 1] == ' '))
		resolution_pars(&line[i + 1], all);
	else if (((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' &&
	line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E') ||
	(line[i] == 'E' && line[i + 1] == 'A')) && (line[i + 2] == ' '))			//N/S/W/E texture
		texture_pars(&line[i + 2], all, &line[i], 0);
	else if (line[i] == 'S' && (line[i + 1] == ' '))							//Sprite texture
		texture_pars(&line[i + 1], all, "S", 0);
	else if (line[i] == 'F' && (line[i + 1] == ' '))							//Floor color
		floor_n_c(&line[i + 1], &(all->p->f_rgb), line[i], all);
	else if (line[i] == 'C' && (line[i + 1] == ' '))							//Ceilling color
		floor_n_c(&line[i + 1], &(all->p->c_rgb), line[i], all);
	else
		error("Incorrect identifier");
}

static void map_parsing(int fd, char *line, t_all *all)
{
	int row_is_present;

	row_is_present = 1;
	check_line_map(line, all);
	all->p->line_map = ft_strjoin(line, "|");
	while (row_is_present > 0)
	{
		if ((row_is_present = get_next_line(fd, &line)) == (-1))
			error("File reading error!");
		check_line_map(line, all);
		all->p->line_map = ft_strjoin(all->p->line_map, line);
		all->p->line_map = ft_strjoin(all->p->line_map, "|");
	}
	all->p->split_map = ft_split(all->p->line_map, '|');

}

void file_parsing(int fd, t_all *all)
{
	int row_is_present;
	char *line;
	int i;

	init_param_struct(all);
	row_is_present = 1;
	i = 0;
	while (row_is_present > 0)
	{
		if ((row_is_present = get_next_line(fd, &line)) == (-1))
			error("File reading error!");
		while(line[i] == ' ')               						//только ли пробелы возможны??
			i++;
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')     //значит, читаем ряд с картой
		{
			all->ch->map++;
			map_parsing(fd, line, all);
			break;
		}
		sort_param(&line[i], all);
	}
	check_params(all);
}