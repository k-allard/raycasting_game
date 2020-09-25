/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_counter_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:09:30 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 16:53:29 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	coin_counter(t_all *all)
{
	mlx_string_put(all->mlx, all->win, 100, 600, 0xFFFFFF, "FIND 5 COINS!");
}
