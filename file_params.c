/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:41:01 by kallard           #+#    #+#             */
/*   Updated: 2020/09/23 13:34:34 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		floor_n_c(char *line, int *rgb, char flag, t_all *all)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	r = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	g = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	b = ft_atoi(&line[i]);
	if (!((r >= 0 && r <= 255) && ((g >= 0 && g <= 255)) &&
	((b >= 0 && b <= 255))))
		error("Floor and ceilling RGB should be in range [0; 255]", all);
	*rgb = r;
	*rgb = (*rgb << 8) + g;
	*rgb = (*rgb << 8) + b;
	if (flag == 'F')
		all->ch->f++;
	else if (flag == 'C')
		all->ch->c++;
}

void		resolution_pars(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	all->p->w = ft_atoi(&line[i]);
	if (all->p->w <= 0)
		error("Width is less than or equals zero", all);
	mlx_get_screen_size(all->mlx, &(all->ch->screen_w), &(all->ch->screen_h));
	if (all->p->w > all->ch->screen_w)
		all->p->w = all->ch->screen_w;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	all->p->h = ft_atoi(&line[i]);
	if (all->p->h <= 0)
		error("Hight is less than or equals zero", all);
	if (all->p->h > all->ch->screen_h)
		all->p->h = all->ch->screen_h;
	all->ch->r++;
}

static void	texture_path_pars(char **param, char *line, t_all *all)
{
	int fd;

	while (*line == ' ')
		line++;
	if (*line == '.' && *(line + 1) == '/')
	{
		if ((fd = open(line, O_RDONLY)) < 0)
			error("Incorrect path to the texture", all);
		*param = line;
	}
	else
		error("Incorrect path to the texture", all);
}

void		texture_pars(char *line, t_all *all, char *id, int i)
{
	if (id[i] == 'N' && id[i + 1] == 'O')
	{
		texture_path_pars(&(all->p->no), line, all);
		all->ch->no++;
	}
	else if (id[i] == 'S' && id[i + 1] == 'O')
	{
		texture_path_pars(&(all->p->so), line, all);
		all->ch->so++;
	}
	else if (id[i] == 'W' && id[i + 1] == 'E')
	{
		texture_path_pars(&(all->p->we), line, all);
		all->ch->we++;
	}
	else if (id[i] == 'E' && id[i + 1] == 'A')
	{
		texture_path_pars(&(all->p->ea), line, all);
		all->ch->ea++;
	}
	else if (id[i] == 'S' && id[i + 1] == '\0')
	{
		texture_path_pars(&(all->p->s), line, all);
		all->ch->s++;
	}
}

void		sort_param(char *line, t_all *all)
{
	int i;

	i = 0;
	if (line[i] == '\0' || line[i] == 13)
		return ;
	if (line[i] == 'R' && (line[i + 1] == ' '))
		resolution_pars(&line[i + 1], all);
	else if (((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' &&
	line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E') ||
	(line[i] == 'E' && line[i + 1] == 'A')) && (line[i + 2] == ' '))
		texture_pars(&line[i + 2], all, &line[i], 0);
	else if (line[i] == 'S' && (line[i + 1] == ' '))
		texture_pars(&line[i + 1], all, "S", 0);
	else if (line[i] == 'F' && (line[i + 1] == ' '))
		floor_n_c(&line[i + 1], &(all->p->f_rgb), line[i], all);
	else if (line[i] == 'C' && (line[i + 1] == ' '))
		floor_n_c(&line[i + 1], &(all->p->c_rgb), line[i], all);
	else
		error("Incorrect identifier", all);
}
