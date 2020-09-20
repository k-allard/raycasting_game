#include "cub.h"

static void		screenshot(t_all *all, char *filename)
{
	int fd;
	unsigned char			*file_header;
	unsigned char			*bitmap_header;

	fd = open(filename, O_RDONLY);
	/*
	** open map and render
	*/
	close(fd);
	fd = open("cub3D.bmp", O_CREAT | O_RDWR, 416);					// fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	/*
	** drawing screenshot
	*/
	close(fd);

}

int main(int argc, char **argv)
{
	int fd;
	t_all all;

	if (argc == 2 || argc == 3)
	{
		check_filename(argv[1]);		// проверяем, что файл .cub и открывается
		init_check_struct(&all);		// маллок и инициализация значений для структуры checks
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 6))
				error("For a screenshot, the 2nd argument should be ––save");
			all.ch->screenshot = 1;
		}
		all.mlx = mlx_init(); 			// MLX CONNECTION INITIALIZATION
		init_game_structs(&all);		// маллоки для структур player, ray, imgs, textures, params
		file_parsing(open(argv[1], O_RDONLY), &all);
		init_game(&all);
		init_depth_buffer(&all);
		game_start(&all);
	}
	else
		error("Program should have 1 or 2 arguments");
	return (0);
}