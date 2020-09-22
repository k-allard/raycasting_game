/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 23:31:41 by kallard           #+#    #+#             */
/*   Updated: 2020/09/22 23:33:57 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void error(char *message, t_all *all)
{
    ft_putendl_fd("Error", 1);
    ft_putendl_fd(message, 1);
    exit_game(all, EXIT_FAILURE);
}

int		close_win(t_all *all)
{
	write(1, "Player closed the window.\nGame exited\n", 38);
    exit_game(all, EXIT_SUCCESS);
	return (0);
}

int		exit_game(t_all *all, int exit_code)
{
	int i;

	// i = 0;
	// if (all->p->split_map)
	// {
	// 	while (all->p->split_map[i])
	// 	{
	// 		free(all->p->split_map[i]);
	// 		i++;
	// 	}
	// 	free(all->p->split_map);
	// }
	exit(exit_code);
}
