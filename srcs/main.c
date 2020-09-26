/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:17:15 by kallard           #+#    #+#             */
/*   Updated: 2020/09/26 13:09:53 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc == 2 || argc == 3)
	{
		zeroing(&all);
		check_filename(argv[1], &all);
		init_check_struct(&all);
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7))
				error("For a screenshot, the 2nd arg must be ––save", &all);
			all.ch->screenshot = 1;
		}
		init_game_structs(&all);
		file_parsing(open(argv[1], O_RDONLY), &all);
		init_game(&all);
		game_start(&all);
	}
	else
		error("Program should have 1 or 2 arguments", &all);
	return (0);
}
