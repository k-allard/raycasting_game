/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:17:15 by kallard           #+#    #+#             */
/*   Updated: 2020/09/22 19:42:45 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_all	all;

	if (argc == 2 || argc == 3)
	{
		check_filename(argv[1], &all);	// проверяем, что файл .cub и открывается
		init_check_struct(&all);		// маллок и инициализация значений для структуры checks
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 6))
				error("For a screenshot, the 2nd arg must be ––save", &all);
			all.ch->screenshot = 1;
		}
		all.mlx = mlx_init(); 			// MLX CONNECTION INITIALIZATION
		init_game_structs(&all);		// маллоки для структур player, ray, imgs, textures, params
		file_parsing(open(argv[1], O_RDONLY), &all);	//парсинг параметров и карты
		init_game(&all);
		init_depth_buffer(&all);
		game_start(&all);
	}
	else
		error("Program should have 1 or 2 arguments", &all);
	return (0);
}
