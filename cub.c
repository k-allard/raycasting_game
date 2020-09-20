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

	if(argc == 2)
	{
		check_filename(argv[1]);		//проверяем, что карта .cub
		init_check_struct(&all);		//выделяем память под структуру проверок и инициализируем ее значения нулями
		init_game_struct(&all);
		file_parsing(open(argv[1], O_RDONLY), &all);
		init_game(&all);
		init_depth_param_struct(&all);
		game_start(&all);
	}
	else if(argc == 3)
	{
		//your program must save the first rendered image in bmp format when its second argument is "––save":
		if (ft_strncmp(argv[2], "--save", 6))
			error("For a screenshot, the 2nd argument should be ––save");
		if (check_filename(argv[1]))
			all.ch->screenshot = 1;
	}
	else
		error("Program should have 1 or 2 arguments");
	return (0);
}