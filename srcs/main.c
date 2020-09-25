/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:17:15 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 15:43:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc == 2 || argc == 3)
	{
		check_filename(argv[1], &all);
		init_check_struct(&all);
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 6))
				error("For a screenshot, the 2nd arg must be ––save", &all);
			all.ch->screenshot = 1;
		}
		if (!(all.mlx = mlx_init()))
			error("Minilibx init error", &all);
		init_game_structs(&all);
		file_parsing(open(argv[1], O_RDONLY), &all);
		init_game(&all);
		if (!(all.depth_buf = (double *)malloc(sizeof(double) * all.p->w)))
			error("Depth_buffer MALLOC ERROR", &all);
		game_start(&all);
	}
	else
		error("Program should have 1 or 2 arguments", &all);
	return (0);
}
