#include "cub.h"

void init_sprite_struct(t_all *all)
{
	int i;

	i = 0;
	if (!(all->sprites = (t_sprite **)malloc(sizeof(t_sprite*)*(all->sprite_count + 1))))
		error("Struct Sprite_list MALLOC ERROR", all);
	while (i < all->sprite_count)
	{
		if (!(all->sprites[i] = (t_sprite *)malloc(sizeof(t_sprite))))
			error("Struct Sprite MALLOC ERROR", all);
		i++;
	}
	all->sprites[all->sprite_count] = NULL;
}

void init_game_structs(t_all *all)
{
	if (!(all->plr = (t_plr *)malloc(sizeof(t_plr))))
		error("Struct Player MALLOC ERROR", all);
	if (!(all->ray = (t_ray *)malloc(sizeof(t_ray))))
		error("Struct Ray MALLOC ERROR", all);
	if (!(all->img = (t_img *)malloc(sizeof(t_img))))
		error("Structure of imgs MALLOC ERROR", all);
	// if (!(all->img = (t_img *)malloc(sizeof(t_img))))
	// 	error("Structure of img[0] MALLOC ERROR", all);
	if (!(all->textures[0] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[0] MALLOC ERROR", all);
	if (!(all->textures[1] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[1] MALLOC ERROR", all);
	if (!(all->textures[2] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[2] MALLOC ERROR", all);
	if (!(all->textures[3] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[3] MALLOC ERROR", all);
	if (!(all->textures[4] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[4] MALLOC ERROR", all);
	if (!(all->p = (t_param *)malloc(sizeof(t_param))))
		error("Structure of parametres MALLOC ERROR", all);
}

void init_depth_buffer(t_all *all)
{
	if (!(all->depth_buffer = (double *)malloc(sizeof(double)*all->p->width)))
		error("Depth_buffer MALLOC ERROR", all);
}

void init_game(t_all *all)
{
	// check_player(all->p->split_map);
	checkmap(all, all->plr->y, all->plr->x);

	if (all->ch->screenshot != 1)
		all->win = mlx_new_window(all->mlx, all->p->width, all->p->hight, "Kallard's Cub3D");
														// man /Users/nastya/Desktop/man/man1/mlx_new_window.1
	all->img->img = mlx_new_image(all->mlx,
		all->p->width, all->p->hight);													// mlx_new_image.1
	all->img->data_addr = mlx_get_data_addr(all->img->img,
		&all->img->bpp, &all->img->size_line, &all->img->endian);				// mlx_new_image.1

	// all->img[1]->img = mlx_new_image(all->mlx,
	// 	all->p->width, all->p->hight);													// mlx_new_image.1
	// all->img[1]->data_addr = mlx_get_data_addr(all->img[1]->img,
	// 	&all->img[1]->bpp, &all->img[1]->size_line, &all->img[1]->endian);				// mlx_new_image.1

	all->textures[texture_NO]->img = mlx_xpm_file_to_image(						//загружаем текстуру севера из файла
		all->mlx, all->p->no, 
		&(all->textures[texture_NO]->width), 
		&(all->textures[texture_NO]->height));
	all->textures[texture_NO]->data_addr = mlx_get_data_addr(
		all->textures[texture_NO]->img, 
		&all->textures[texture_NO]->bpp,
		&all->textures[texture_NO]->size_line, &all->textures[texture_NO]->endian);
	
	all->textures[texture_SO]->img = mlx_xpm_file_to_image( 						//загружаем текстуру юга из файла
		all->mlx, all->p->so, 
		&(all->textures[texture_SO]->width), 
		&(all->textures[texture_SO]->height));
	all->textures[texture_SO]->data_addr = mlx_get_data_addr(
		all->textures[texture_SO]->img, 
		&all->textures[texture_SO]->bpp,
		&all->textures[texture_SO]->size_line, &all->textures[texture_SO]->endian);

	all->textures[texture_WE]->img = mlx_xpm_file_to_image( 						//загружаем текстуру запада из файла
		all->mlx, all->p->we, 
		&(all->textures[texture_WE]->width), 
		&(all->textures[texture_WE]->height));
	all->textures[texture_WE]->data_addr = mlx_get_data_addr(
		all->textures[texture_WE]->img, 
		&all->textures[texture_WE]->bpp,
		&all->textures[texture_WE]->size_line, 
		&all->textures[texture_WE]->endian);

	all->textures[texture_EA]->img = mlx_xpm_file_to_image( 						//загружаем текстуру востока из файла
		all->mlx, all->p->ea, 
		&(all->textures[texture_EA]->width), 
		&(all->textures[texture_EA]->height));
	all->textures[texture_EA]->data_addr = mlx_get_data_addr(
		all->textures[texture_EA]->img, 
		&all->textures[texture_EA]->bpp,
		&all->textures[texture_EA]->size_line, 
		&all->textures[texture_EA]->endian);

	all->textures[texture_S]->img = mlx_xpm_file_to_image( 						//загружаем текстуру востока из файла
		all->mlx, all->p->s, 
		&(all->textures[texture_S]->width), 
		&(all->textures[texture_S]->height));
	all->textures[texture_S]->data_addr = mlx_get_data_addr(
		all->textures[texture_S]->img, 
		&all->textures[texture_S]->bpp,
		&all->textures[texture_S]->size_line, 
		&all->textures[texture_S]->endian);

}

void init_check_struct(t_all *all)
{
	if (!(all->ch = (t_checks *)malloc(sizeof(t_checks))))
		error("Structure of checks MALLOC ERROR", all);
	all->ch->r = 0;
	all->ch->no = 0;
	all->ch->so = 0;
	all->ch->we = 0;
	all->ch->ea = 0;
	all->ch->s = 0;
	all->ch->f = 0;
	all->ch->c = 0;
	all->ch->map = 0;
	all->ch->pos_player = 0;
	all->ch->screen_w = 0;
	all->ch->screen_h = 0;
	all->ch->screenshot = 0;
}

// void init_param_struct(t_all *all)
// {
// 	if (!(all->p = (t_param *)malloc(sizeof(t_param))))
// 		error("Structure of parametres MALLOC ERROR!");
// }