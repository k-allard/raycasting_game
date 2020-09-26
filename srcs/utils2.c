/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:19:51 by kallard           #+#    #+#             */
/*   Updated: 2020/09/26 13:10:04 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	zeroing(t_all *all)
{
	all->ch = NULL;
	all->p = NULL;
	all->img = NULL;
	all->text[0] = NULL;
	all->text[1] = NULL;
	all->text[2] = NULL;
	all->text[3] = NULL;
	all->text[4] = NULL;
	all->plr = NULL;
	all->ray = NULL;
	all->sprites = NULL;
	all->rc = NULL;
	all->mlx = NULL;
	all->win = NULL;
	all->depth_buf = NULL;
}

char	*safe_str_join(char *str1, const char *str2)
{
	char *str_result;

	str_result = ft_strjoin(str1, str2);
	free(str1);
	return (str_result);
}
