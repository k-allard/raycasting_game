#include "cub.h"

// void		init_dda_struct(t_all *all)
// {
// 	if (!(all->dda = (t_dda *)malloc(sizeof(t_dda))))
// 		error("Struct Dda malloc error");
// }

static int		is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void init_game_params(t_all *all)
{
	int i;
	int j;

	i = -1;
	while (all->p->split_map[++i])
	{
		j = -1;
		while (all->p->split_map[i][++j])
			if (is_player(all->p->split_map[i][j]))
			{
				all->plr->x = (double)i;
				all->plr->y = (double)j;
				break;
			}
	}
	all->plr->x = 0.0;
	all->plr->y = 0.0;
	/*и все остальные значения в структуре Игрока тоже надо будет инициализировать*/
	/*
	** здесь надо определить, куда смотрит камера
	*/

}

void init_game_struct(t_all *all)
{
	int i;

	i = 0;
	all->mlx = mlx_init(); 													// mlx.1 CONNECTION INITIALIZATION
	if (!(all->plr = (t_plr *)malloc(sizeof(t_plr))))
		error("Struct Player malloc error");
	if (!(all->ray = (t_ray *)malloc(sizeof(t_ray))))
		error("Struct Ray malloc error");
	/*
	**далее надо выделить память для структур cпрайтов и изображений?
	*/
}

void init_game(t_all *all)
{
	// check_player(all->p->split_map);
	/*
	**здесь надо проверить карту на все возможные ошибки
	*/
	/*
	**здесь надо добавить текстуры в изображения???
	*/
	//init_game_params(all);
	// init_dda_struct(all);
	/*
	**здесь надо инициализировать структуру спрайтов
	*/
	all->win = mlx_new_window(all->mlx, all->p->width,
	all->p->hight, "Kallard's Cub3D");												// man /Users/nastya/Desktop/man/man1/mlx_new_window.1
	all->img[0]->img = mlx_new_image(all->mlx,
	all->p->width+200, all->p->hight);													// mlx_new_image.1
	all->img[0]->data_addr = mlx_get_data_addr(all->img[0]->img,
	&all->img[0]->bpp, &all->img[0]->size_line, &all->img[0]->endian);				// mlx_new_image.1

	all->textures[0]->img = mlx_xpm_file_to_image(						//загружаем текстуру севера из файла
		all->mlx, all->p->n, &(all->textures[0]->width), &(all->textures[0]->height));
	all->textures[0]->data_addr = mlx_get_data_addr(all->textures[0]->img, &all->textures[0]->bpp,
			&all->textures[0]->size_line, &all->textures[0]->endian);
	
	all->textures[1]->img = mlx_xpm_file_to_image( 						//загружаем текстуру юга из файла
		all->mlx, all->p->s, &(all->textures[1]->width), &(all->textures[1]->height));
	all->textures[1]->data_addr = mlx_get_data_addr(all->textures[1]->img, &all->textures[1]->bpp,
			&all->textures[1]->size_line, &all->textures[1]->endian);

	all->textures[2]->img = mlx_xpm_file_to_image( 						//загружаем текстуру запада из файла
		all->mlx, all->p->w, &(all->textures[2]->width), &(all->textures[2]->height));
	all->textures[2]->data_addr = mlx_get_data_addr(all->textures[2]->img, &all->textures[2]->bpp,
			&all->textures[2]->size_line, &all->textures[2]->endian);

	all->textures[3]->img = mlx_xpm_file_to_image( 						//загружаем текстуру востока из файла
		all->mlx, all->p->e, &(all->textures[3]->width), &(all->textures[3]->height));
	all->textures[3]->data_addr = mlx_get_data_addr(all->textures[3]->img, &all->textures[3]->bpp,
			&all->textures[3]->size_line, &all->textures[3]->endian);
	
}

void init_check_struct(t_all *all)
{
	if (!(all->ch = (t_checks *)malloc(sizeof(t_checks))))
		error("Structure of checks MALLOC ERROR!");
	all->ch->r = 0;
	all->ch->n = 0;
	all->ch->s = 0;
	all->ch->w = 0;
	all->ch->e = 0;
	all->ch->sp = 0;
	all->ch->f = 0;
	all->ch->c = 0;
	all->ch->map = 0;
	all->ch->pos_player = 0;
	all->ch->screen_w = 0;
	all->ch->screen_h = 0;
}

void init_param_struct(t_all *all)
{
	if (!(all->p = (t_param *)malloc(sizeof(t_param))))
		error("Structure of parametres MALLOC ERROR!");
	if (!(all->img = (t_img **)malloc(sizeof(t_img*))))
		error("Structure of imgs MALLOC ERROR!");
	if (!(all->img[0] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of img[0] MALLOC ERROR!");
	if (!(all->textures[0] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[0] MALLOC ERROR!");
	if (!(all->textures[1] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[1] MALLOC ERROR!");
	if (!(all->textures[2] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[2] MALLOC ERROR!");
	if (!(all->textures[3] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[3] MALLOC ERROR!");
}