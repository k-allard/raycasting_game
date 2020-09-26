/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 00:09:57 by kallard           #+#    #+#             */
/*   Updated: 2020/09/26 13:48:00 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static int	key_press_hook(int keycode, t_all *all)
{
	if (keycode == 0)
		all->key_left = 1;
	else if (keycode == 2)
		all->key_rigth = 1;
	else if (keycode == 1)
		all->key_down = 1;
	else if (keycode == 13)
		all->key_forward = 1;
	else if (keycode == 123)
		all->key_rotate_left = 1;
	else if (keycode == 124)
		all->key_rotate_rigth = 1;
	else if (keycode == 53)
		exit_game(all, EXIT_SUCCESS);
	all->is_draw = all->key_left || all->key_rigth || all->key_down ||\
		all->key_forward || all->key_rotate_left || all->key_rotate_rigth;
	return (0);
}

static int	key_release_hook(int keycode, t_all *all)
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
	all->is_draw = all->key_left || all->key_rigth || all->key_down ||\
		all->key_forward || all->key_rotate_left || all->key_rotate_rigth;
	return (0);
}

static int	game(t_all *all)
{
	if (all->is_draw != 0)
	{
		if (all->is_draw == -1)
			all->is_draw = 0;
		calc_new_position(all);
		calc_sprite_distance(all);
		background(all);
		cast_rays(all);
		draw_sprites(all);
		minimap(all);
		if (all->ch->screenshot == 1)
			make_screenshot(all);
		mlx_sync(MLX_SYNC_IMAGE_WRITABLE, all->img->img);
		mlx_put_image_to_window(all->mlx, all->win, all->img->img, 0, 0);
		coin_counter(all);
		mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, all->win);
	}
	return (0);
}

static void	hook_n_loop(t_all *all)
{
	mlx_do_key_autorepeatoff(all->mlx);
	mlx_hook(all->win, DestroyNotify, 1L << 0, close_win, all);
	mlx_hook(all->win, KeyPress, 0, key_press_hook, all);
	mlx_hook(all->win, KeyRelease, 0, key_release_hook, all);
	mlx_loop_hook(all->mlx, game, all);
	mlx_loop(all->mlx);
}

void		game_start(t_all *all)
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
	all->ray->start = -M_PI / 4.0;
	all->ray->end = M_PI / 4.0;
	if (all->ch->screenshot == 1)
		game(all);
	else
		hook_n_loop(all);
}
