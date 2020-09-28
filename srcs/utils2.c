/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:19:51 by kallard           #+#    #+#             */
/*   Updated: 2020/09/28 19:16:39 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** Itoa() substitution, returning -1 if no number found
*/

int		num_pars(char *str)
{
	unsigned long long	result;
	int					length_max;
	int					sign;
	int					i;

	result = 0;
	length_max = 19;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + str[i++] - '0';
			if (result > 10000)
				return (10000 * sign);
		}
	}
	else
		return (-1);
	return (sign * result);
}

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
