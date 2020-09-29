/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:44:17 by kallard           #+#    #+#             */
/*   Updated: 2020/09/29 13:44:34 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	color_pars(int arr[], char *line, t_all *all)
{
	int	n;

	n = 0;
	while (n < 3)
	{
		arr[n] = num_pars(line);
		skip_spaces(&line);
		while (*line >= '0' && *line <= '9')
			line++;
		skip_spaces(&line);
		if (n < 2)
		{
			if (*line == ',')
				line++;
			else
				error("Floor and ceilling colors must be in format r,g,b", all);
		}
		skip_spaces(&line);
		n++;
	}
	if (*line != '\0')
		error("Floor and ceilling colors must be in format r,g,b", all);
}

void		floor_n_c(char *line, int *rgb, char flag, t_all *all)
{
	int	arr[3];
	int n;

	color_pars(arr, line, all);
	n = 0;
	while (n < 3)
	{
		if (arr[n] < 0 || arr[n] > 255)
			error("Floor and ceilling RGB must be in range [0; 255]", all);
		n++;
	}
	*rgb = arr[0];
	*rgb = (*rgb << 8) + arr[1];
	*rgb = (*rgb << 8) + arr[2];
	if (flag == 'F')
		all->ch->f++;
	else if (flag == 'C')
		all->ch->c++;
}
