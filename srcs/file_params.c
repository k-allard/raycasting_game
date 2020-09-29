/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:41:01 by kallard           #+#    #+#             */
/*   Updated: 2020/09/29 13:44:47 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void		resolution_pars(char *line, t_all *all)
{
	int i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	all->p->w = num_pars(&line[i]);
	if (all->p->w <= 0)
		error("Width is less than or equals zero", all);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	all->p->h = num_pars(&line[i]);
	if (all->p->h <= 0)
		error("Hight is less than or equals zero", all);
	max_screen_size(all);
	while (ft_isspace(line[i]))
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0')
		error("Resolution must contain only width and height", all);
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
		*param = ft_strdup(line);
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
