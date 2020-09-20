#include "cub.h"
#include <stdlib.h>
#include <stdio.h>

static void floor_n_c(char *line, int *rgb, char flag, t_all *all)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	r = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	g = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	b = ft_atoi(&line[i]);
	if (!((r >= 0 && r <= 255) && ((g >= 0 && g <= 255)) &&
	((b >= 0 && b <= 255))))
		error("Floor and ceilling RGB should be in range [0; 255]");
	//в структуру param цвета пола и потолка сохраняются в hex виде:
	*rgb = r;					
	*rgb = (*rgb << 8) + g;
	*rgb = (*rgb << 8) + b;

	if (flag == 'F')
		all->ch->f++;
	else if (flag == 'C')
		all->ch->c++;
}

static void resolution_pars(char *line, t_all *all)
{

	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	all->p->width = ft_atoi(&line[i]);
	if (all->p->width <= 0)
		error("Width is less than or equals zero");
	mlx_get_screen_size(all->mlx, &(all->ch->screen_w), &(all->ch->screen_h));
	if (all->p->width > all->ch->screen_w)
		all->p->width = all->ch->screen_w; 		//the window width will be set depending to the current display resolution
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	all->p->hight = ft_atoi(&line[i]);
	if (all->p->hight <= 0)
		error("Hight is less than or equals zero");
	if (all->p->hight > all->ch->screen_h)
		all->p->hight = all->ch->screen_h;		//the window width will be set depending to the current display resolution
	all->ch->r++;
}

static void			texture_path_pars(char **param, char *line)
{
	int fd;

	while (*line == ' ')
		line++;
	if (*line == '.' && *(line + 1) == '/')
	{	
		if ((fd = open(line, O_RDONLY)) < 0)
			error("Incorrect path to the texture");
		*param = line;
	}
	else
		error("Incorrect path to the texture");
}

static void texture_pars(char *line, t_all *all, char *id, int i)
{
	if (id[i] == 'N' && id[i + 1] == 'O')
	{
		texture_path_pars(&(all->p->no), line);
		all->ch->no++;
	}
	else if (id[i] == 'S' && id[i + 1] == 'O')
	{
		texture_path_pars(&(all->p->so), line);
		all->ch->so++;
	}
	else if (id[i] == 'W' && id[i + 1] == 'E')
	{
		texture_path_pars(&(all->p->we), line);
		all->ch->we++;
	}
	else if (id[i] == 'E' && id[i + 1] == 'A')
	{
		texture_path_pars(&(all->p->ea), line);
		all->ch->ea++;
	}
	else if (id[i] == 'S' && id[i + 1] == '\0')
	{
		texture_path_pars(&(all->p->s), line);
		all->ch->s++;
	}
}

static void sort_param(char *line, t_all *all)
{
	int i;

	i = 0;
	if (line[i] == '\0' || line[i] == 13)		//код 13 - возврат каретки
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


static void get_sprite_position(t_all *all)
{
	int row = 0;
	int column = 0;
	char *spriteChar;
	int sprite_count = 0;
	int i=0;

	while (all->p->split_map[row])
	{
		char* startRowStr = all -> p ->split_map[row];
		spriteChar = ft_strchr(startRowStr, '2');
		while(spriteChar)
		{
			sprite_count++;
			startRowStr = spriteChar + 1;
			spriteChar = ft_strchr(startRowStr, '2');
		}
		row++;
	}
	all->sprite_count = sprite_count;

	if (!(all->sprite_list = (t_sprite **)malloc(sizeof(t_sprite*)*(sprite_count+1))))
		error("Structure of sprite_list MALLOC ERROR!");
	while (i < sprite_count)
	{
		if (!(all->sprite_list[i] = (t_sprite *)malloc(sizeof(t_sprite))))
			error("Structure of sprite_list MALLOC ERROR!");
		i++;
	}
	all->sprite_list[sprite_count] = NULL;
	
	row = 0;
	sprite_count = 0;
	while (all->p->split_map[row])
	{
		char* startRowStr = all->p->split_map[row];
		spriteChar = ft_strchr(startRowStr, '2');
		while(spriteChar)
		{
			column = spriteChar - all->p->split_map[row];
			startRowStr = spriteChar + 1;
			all->sprite_list[sprite_count]->x = 1.0 * column + 0.5;
			all->sprite_list[sprite_count]->y = 1.0 * row + 0.5;			
			sprite_count++;
			spriteChar = ft_strchr(startRowStr, '2');
		}
		row++;
	}	
}


static void protect_map(t_all* all)
{
	char ** map;
	int i;

	if (!(map = (char **)malloc(sizeof(char*)*(all->map_hight+3))))
		error("Structure of protect_map MALLOC ERROR!");
	if (!(map[0] = (char *)malloc(sizeof(char)*(all->map_width+3))))
		error("Structure of protect_map MALLOC ERROR!");
	i = -1;
	while (++i<all->map_width+2)
		map[0][i]='X';
	map[0][all->map_width+2]='\0';
	i = 0;
	while (++i<all->map_hight+2)
		if (!(map[i]=ft_strdup((const char*)(map[0]))))
			error("Structure of protect_map MALLOC ERROR!");
	i = 0;
	while (++i<all->map_hight+1)
		ft_memmove((void*)(map[i]+1), (const void*)(all->p->split_map[i-1]), ft_strlen(all->p->split_map[i-1]));
	map[all->map_hight+2] = NULL;
	all->map_protect = map;

	i = 0;
	printf("Protected Map:\n");
	while (i < all->map_hight+3)
	{
		printf("[%s]\n", all->map_protect[i]);
		i++;
	}
	fflush(stdout);
	
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
	get_map_size(all);
	protect_map(all);
	get_player_position(all);
	get_sprite_position(all);
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
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')     //значит, началась карта
		{
			all->ch->map++;
			map_parsing(fd, line, all);
			break;													//карта - всегда последний "параметр" в файле, выходим из цикла while
		}
		sort_param(&line[i], all);
	}
	check_params(all);
}