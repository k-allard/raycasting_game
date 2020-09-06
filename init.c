#include "cub.h"

void		init_dda_struct(t_all *all)
{
	if (!(all->dda = (t_dda *)malloc(sizeof(t_dda))))
		error("Struct Dda malloc error");
}

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
	/*здесь надо определить, куда смотрит камера*/

}

void init_game_struct(t_all *all)
{
	int i;

	i = 0;
	if (!(all->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		error("Struct Mlx malloc error");
	all->mlx->mlx = mlx_init(); // mlx.1 CONNECTION INITIALIZATION
	if (!(all->plr = (t_plr *)malloc(sizeof(t_plr))))
		error("Struct Player malloc error");
	if (!(all->sp = (t_sprite *)malloc(sizeof(t_sprite))))
		error("Struct Sprite malloc error");
	/*
	**далее надо выделить память для структуры Изображений
	*/
}

void init_game(t_all *all)
{
	check_player(all->p->split_map);
	/*
	**здесь надо проверить карту на все возможные ошибки
	*/
	init_game_struct(all);
	/*
	**здесь надо добавить текстуры в массив изображения???
	*/
	init_game_params(all);
	init_dda_struct(all);
	/*
	**здесь надо инициализировать страктуру Спрайт
	*/
	all->mlx->win = mlx_new_window(all->mlx->mlx, all->p->width,
	all->p->hight, "Kallard's Cub3D");													// man /Users/nastya/Desktop/man/man1/mlx_new_window.1
	all->img[0]->img = mlx_new_image(all->mlx->mlx,
	all->p->width, all->p->hight);													// mlx_new_image.1
	all->img[0]->data_addr = mlx_get_data_addr(all->img[0]->img,
	&all->img[0]->bpp, &all->img[0]->size_line, &all->img[0]->endian);		// mlx_new_image.1
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
}

void init_param_struct(t_all *all)
{
	if (!(all->p = (t_param *)malloc(sizeof(t_param))))
		error("Structure of parametres MALLOC ERROR!");
}