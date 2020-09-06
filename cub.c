#include "cub.h"


//далее идет предыдущая версия парсера карты! неактульано!

// char	**make_map(t_list **head, int size)
// {
// 	char	  **map = ft_calloc(size + 1, sizeof(char *));
// 	int		  i = -1;
// 	t_list	*tmp = *head;
// 	while (tmp)
// 	{
// 		map[++i] = tmp->content;
// 		tmp = tmp->next;
// 	}
// 	i = -1;
// 	while (map[++i])
// 		ft_putendl_fd(map[i], 0);
// 	return (map);
// }
// int		map_parser(int argc, char **argv)
// {
// 	int      fd = open(argv[1], O_RDONLY);
// 	char	  *line = NULL;
// 	t_list	*head = NULL;

// 	while (get_next_line(fd, &line))
// 		ft_lstadd_back(&head, ft_lstnew(line));
// 	ft_lstadd_back(&head, ft_lstnew(line));			//later we will count size of the list and turn it into 2d char array
// 	make_map(&head, ft_lstsize(head));
// 	return 0;
// }

static void		screenshot(t_all *all, char *filename)
{
	int fd;
	unsigned char			*file_header;
	unsigned char			*bitmap_header;

	fd = open(filename, O_RDONLY);
	/*open map and render*/
	close(fd);
	fd = open("cub3D.bmp", O_CREAT | O_RDWR, 416);					// fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	/*drawing screenshot*/
	close(fd);

}

int main(int argc, char **argv)
{
	int fd;
	t_all all;

	if(argc == 2)
	{
		check_filename(argv[1]);
		init_check_struct(&all);
		file_parsing(open(argv[1], O_RDONLY), &all);
		init_game(&all);
		game_start(&all);
	}
	else if(argc == 3)
	{
		/*your program must save the first rendered image in bmp format when its second argument is "––save"*/
		if (ft_strncmp(argv[2], "--save", 6))
			error("For a screenshot, the 2nd argument should be ––save");
		if (check_filename(argv[1]))
			screenshot(&all, argv[1]);
	}
	else
		error("Program should have 1 or 2 arguments");
	return (0);
}