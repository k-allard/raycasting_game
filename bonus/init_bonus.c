/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 03:50:53 by kallard           #+#    #+#             */
/*   Updated: 2020/09/26 00:07:03 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void		init_sprite_struct(t_all *all)
{
	int i;

	i = 0;
	if (!(all->sprites = (t_sprite **)malloc(sizeof(t_sprite*)
					* (all->sprite_count))))
		error("Struct Sprite_list MALLOC ERROR", all);
	while (i < all->sprite_count)
	{
		if (!(all->sprites[i] = (t_sprite *)malloc(sizeof(t_sprite))))
			error("Struct Sprite MALLOC ERROR", all);
		all->sprites[i]->is_found = 0;
		i++;
	}
	all->sprites_found = 0;
}

void		init_game_structs(t_all *all)
{
	if (!(all->plr = (t_plr *)malloc(sizeof(t_plr))))
		error("Struct Player MALLOC ERROR", all);
	if (!(all->ray = (t_ray *)malloc(sizeof(t_ray))))
		error("Struct Ray MALLOC ERROR", all);
	if (!(all->rc = (t_rc *)malloc(sizeof(t_rc))))
		error("Struct Ray MALLOC ERROR", all);
	if (!(all->img = (t_img *)malloc(sizeof(t_img))))
		error("Structure of imgs MALLOC ERROR", all);
	if (!(all->text[0] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[0] MALLOC ERROR", all);
	if (!(all->text[1] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[1] MALLOC ERROR", all);
	if (!(all->text[2] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[2] MALLOC ERROR", all);
	if (!(all->text[3] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[3] MALLOC ERROR", all);
	if (!(all->text[4] = (t_img *)malloc(sizeof(t_img))))
		error("Structure of textures[4] MALLOC ERROR", all);
	if (!(all->p = (t_param *)malloc(sizeof(t_param))))
		error("Structure of parametres MALLOC ERROR", all);
}

static void	init_textures(t_all *all)
{
	all->text[NO]->img = mlx_xpm_file_to_image(all->mlx, all->p->no,\
				&(all->text[NO]->w), &(all->text[NO]->h));
	all->text[NO]->addr = mlx_get_data_addr(all->text[NO]->img,\
				&all->text[NO]->bpp, &all->text[NO]->l_sz, &all->text[NO]->en);
	all->text[SO]->img = mlx_xpm_file_to_image(all->mlx, all->p->so,\
				&(all->text[SO]->w), &(all->text[SO]->h));
	all->text[SO]->addr = mlx_get_data_addr(all->text[SO]->img,\
				&all->text[SO]->bpp, &all->text[SO]->l_sz, &all->text[SO]->en);
	all->text[WE]->img = mlx_xpm_file_to_image(all->mlx, all->p->we,\
				&(all->text[WE]->w), &(all->text[WE]->h));
	all->text[WE]->addr = mlx_get_data_addr(all->text[WE]->img,\
				&all->text[WE]->bpp, &all->text[WE]->l_sz, &all->text[WE]->en);
	all->text[EA]->img = mlx_xpm_file_to_image(all->mlx, all->p->ea,\
				&(all->text[EA]->w), &(all->text[EA]->h));
	all->text[EA]->addr = mlx_get_data_addr(all->text[EA]->img,\
				&all->text[EA]->bpp, &all->text[EA]->l_sz, &all->text[EA]->en);
	all->text[S]->img = mlx_xpm_file_to_image(all->mlx, all->p->s,\
				&(all->text[S]->w), &(all->text[S]->h));
	all->text[S]->addr = mlx_get_data_addr(all->text[S]->img,\
				&all->text[S]->bpp, &all->text[S]->l_sz, &all->text[S]->en);
}

void		init_game(t_all *all)
{
	all->win = NULL;
	if (all->ch->screenshot != 1)
		if (!(all->win = mlx_new_window(all->mlx, all->p->w, all->p->h,\
		"Kallard's Cub3D")))
			error("Window opening error", all);
	all->img->img = mlx_new_image(all->mlx, all->p->w, all->p->h);
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bpp,\
				&all->img->l_sz, &all->img->en);
	init_textures(all);
}

void		init_check_struct(t_all *all)
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
