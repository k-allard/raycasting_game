/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 00:09:57 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 02:05:12 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void sort_sprite_array(t_all *all)
{
	t_sprite* tmp;
	int i = 0;
	int j = 0;

	while (i < all->sprite_count - 1)
	{        
		j = 0;
		while (j < all->sprite_count - 1 - i)
		{
			if(all->sprites[j]->dist < all->sprites[j + 1]->dist)
			{
				tmp = all->sprites[j];
				all->sprites[j] = all->sprites[j+1];
				all->sprites[j+1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void calc_sprite_distance(t_all *all)
{
	int i = 0;
	while (i < all->sprite_count)
	{
		all->sprites[i]->dist = sqrt(pow(all->plr->x - all->sprites[i]->x, 2) + pow(all->plr->y - all->sprites[i]->y, 2)); 
		i++;
	}
	sort_sprite_array(all);
}   

int     key_press_hook(int keycode, t_all *all)
{
	if (keycode == 0)       //A -- left 
		all->key_left = 1;
	else if (keycode == 2)       //D -- right 
		all->key_rigth = 1;
	else if (keycode == 1)       //S -- down 
		all->key_down = 1;
	else if (keycode == 13)      //W -- forward 
		all->key_forward = 1;
	else if (keycode == 123)   //Arrow Left
		all->key_rotate_left = 1;
	else if (keycode == 124)   //Arrow Right
		all->key_rotate_rigth = 1;
	else if (keycode == 53)      //ESC
	{
		mlx_destroy_window(all->mlx, all->win);
		exit_game(all, EXIT_SUCCESS);
	}
	all->is_draw = all->key_left || all->key_rigth || all->key_down || all->key_forward || all->key_rotate_left || all->key_rotate_rigth;
	return (0);
}

int     key_release_hook(int keycode, t_all *all)
{
	if (keycode == 0)
		all->key_left = 0;
	else if (keycode == 2)
		all->key_rigth = 0;
	else if (keycode == 1)
		all->key_down = 0;
	else if (keycode == 13)
		all->key_forward = 0;
	else if (keycode == 123)
		all->key_rotate_left = 0;
	else if (keycode == 124)
		all->key_rotate_rigth = 0;
	all->is_draw = all->key_left || all->key_rigth || all->key_down || all->key_forward || all->key_rotate_left || all->key_rotate_rigth;
	return (0);
}

void        calc_new_position(t_all* all)
{
	double y_step;
	double x_step;

	all->ray->dir -= (SPEED * 0.55 * all->key_rotate_left);
	all->ray->dir += (SPEED * 0.55 * all->key_rotate_rigth);

	y_step = SPEED * ( 0.0
		+ sin(all->ray->dir - M_PI / 2) * 0.4 * all->key_left
		+ sin(all->ray->dir + M_PI / 2) * 0.4 * all->key_rigth
		- sin(all->ray->dir) * 0.4 * all->key_down
		+ sin(all->ray->dir) * 0.6 * all->key_forward);

	x_step = SPEED * (0.0
		+ cos(all->ray->dir - M_PI / 2) * 0.4 * all->key_left
		+ cos(all->ray->dir + M_PI / 2) * 0.4 * all->key_rigth
		- cos(all->ray->dir) * 0.4 * all->key_down
		+ cos(all->ray->dir) * 0.6 * all->key_forward);
	if(is_not_wall(all, all->plr->y + y_step * 3, all->plr->x + x_step * 3))
	{
		all->plr->y += y_step;
		all->plr->x += x_step; 
	}
}

void        background(t_all *all)
{
	int x_tmp;
	int y_tmp;
	
	y_tmp = -1;
	while (++y_tmp < all->p->h / 2)
		my_pixel_put_line(all, all->p->w, y_tmp, all->p->c_rgb);
	while (++y_tmp < all->p->h)
		my_pixel_put_line(all, all->p->w, y_tmp, all->p->f_rgb);
}

int     game(t_all *all)
{
	if(all->is_draw != 0)
	{
		if(all->is_draw == -1)
			all->is_draw = 0;
		calc_new_position(all);
		calc_sprite_distance(all);
		int i = 0;
		background(all);
		cast_rays(all);
		draw_sprites(all);
		minimap(all);
		if (all->ch->screenshot == 1)
			make_screenshot(all);
		mlx_sync(MLX_SYNC_IMAGE_WRITABLE, all->img->img);
		mlx_put_image_to_window(all->mlx, all->win, all->img->img, 0, 0);
		mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, all->win);
	}
	return 0;
}

void	hook_n_loop(t_all *all)
{
	mlx_do_key_autorepeatoff(all->mlx);
	mlx_hook(all->win, DestroyNotify, 1L << 0, close_win, all);
	mlx_hook(all->win, KeyPress, 0, key_press_hook, all);
	mlx_hook(all->win, KeyRelease, 0, key_release_hook, all);
	mlx_loop_hook(all->mlx, game, all);
	mlx_loop(all->mlx);
}

void	game_start(t_all *all)
{
	all->is_draw = -1;
	all->key_down = 0;
	all->key_forward = 0;
	all->key_rigth = 0;
	all->key_left = 0;
	all->key_rotate_left = 0;
	all->key_rotate_rigth = 0;
	if (all->p->pl_dir == 'E')
		all->ray->dir = 0;
	else if (all->p->pl_dir == 'S')
		all->ray->dir = M_PI_2;
	else if (all->p->pl_dir == 'W')
		all->ray->dir = M_PI;
	else if (all->p->pl_dir == 'N')
		all->ray->dir = 3 * M_PI_2;
	all->ray->start = -M_PI/4.0;
	all->ray->end = M_PI/4.0;
	if (all->ch->screenshot == 1)
		game(all);
	else
		hook_n_loop(all);
}
