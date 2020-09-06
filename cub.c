#include "cub.h"


//предыдущая версия парсера карты! неактульано!

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


int main(int argc, char **argv)
{
	int fd;
	t_all all;

	if(argc == 2)
	{
		check_filename(argv[1]);
		init_check_struct(&all);
		file_parsing(open(argv[1], O_RDONLY), &all);


	}
}