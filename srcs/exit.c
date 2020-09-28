/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:31:41 by kallard           #+#    #+#             */
/*   Updated: 2020/09/28 15:12:35 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
#include <stdio.h>

void		error(char *message, t_all *all)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(message, 1);
	exit_game(all, EXIT_FAILURE);
}

int			close_win(t_all *all)
{
	write(1, "Player closed the window.\nGame exited\n", 38);
	exit_game(all, EXIT_SUCCESS);
	return (0);
}

static void	free_params(t_all *all)
{
	int i;

	safe_free_str(&all->p->ea);
	if (all->p->line_map)
		safe_free_str(&all->p->line_map);
	safe_free_str(&all->p->no);
	safe_free_str(&all->p->s);
	safe_free_str(&all->p->so);
	safe_free_str(&all->p->we);
	i = -1;
	if (all->p->map)
	{
		while (++i < all->map_h)
			safe_free_str(&all->p->map[i]);
		safe_free(all->p->map);
	}
	safe_free(all->p);
}

static void	destroy_mlx(t_all *all)
{
	int	i;

	i = -1;
	if (!all->mlx)
		return ;
	while (++i <= S)
	{
		if (all->text[i])
		{
			if (all->text[i]->img)
				mlx_destroy_image(all->mlx, all->text[i]->img);
			free(all->text[i]);
		}
	}
	if (all->img)
	{
		if (all->img->img)
			mlx_destroy_image(all->mlx, all->img->img);
		free(all->img);
	}
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
}

int			exit_game(t_all *all, int exit_code)
{
	int i;

	if (all)
	{
		destroy_mlx(all);
		safe_free(all->depth_buf);
		if (all->p)
			free_params(all);
		if (all->sprites)
		{
			i = -1;
			while (++i < all->sprite_count)
				safe_free(all->sprites[i]);
			safe_free(all->sprites);
		}
		safe_free(all->plr);
		safe_free(all->ray);
		safe_free(all->rc);
	}
	exit(exit_code);
}
