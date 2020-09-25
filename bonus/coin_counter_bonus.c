/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_counter_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:09:30 by kallard           #+#    #+#             */
/*   Updated: 2020/09/26 00:47:51 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int		sprites_found(t_all *all)
{
	int i;
	int found;

	found = 0;
	i = 0;
	while (i < all->sprite_count)
	{
		if (all->sprites[i]->is_found == 1)
			found++;
		i++;
	}
	return (found);
}

void	coin_counter(t_all *all)
{
	char *found;
	char *found_with_slash;
	char *total;
	char *counter;

	mlx_string_put(all->mlx, all->win, 15, 20, 0xFFFFFF, "FIND COINS!");
	found = ft_itoa(sprites_found(all));
	found_with_slash = ft_strjoin(found, "/");
	total = ft_itoa(all->sprite_count);
	counter = ft_strjoin(found_with_slash, total);
	mlx_string_put(all->mlx, all->win, 15, 35, 0xFFFFFF, counter);
	free(found);
	free(found_with_slash);
	free(total);
	free(counter);
}
