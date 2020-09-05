#include "cub.h"

// //Пробуем кинуть один луч
// void	ft_cast_ray(t_all *all)
// {
// 	t_plr	ray = *all->plr; // задаем координаты луча равные координатам игрока

// 	while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
// 	{
// 		ray.x += cos(ray.dir);
// 		ray.y += sin(ray.dir);
// 		mlx_pixel_put(all->mlx, all->win, ray.x, ray.y, 0x990099);
// 	}
// }

// //Пробуем кинуть много лучей
// void	ft_cast_rays(t_all *all)
// {
// 	t_plr	ray = *all->plr; // задаем координаты и направление луча равные координатам игрока
// 	float start = ray.dir - [половина угла обзора]; // начало веера лучей
//   float end = ray.dir + [половина угла обзора]; // край веера лучей

//   while (ray.start <= ray.end)
// 	{
// 		ray.x = all->plr->x; // каждый раз возвращаемся в точку начала
// 		ray.y = all->plr->y;
// 		while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
// 		{
// 			ray.x += cos(ray.start);
// 			ray.y += sin(ray.start);
// 			mlx_pixel_put(all->mlx, all->win, ray.x, ray.y, 0x990099);
// 		}
// 		ray.start += [угол обзора] / [количество лучей];
// 	}
// }

char	**make_map(t_list **head, int size)
{
	char	  **map = ft_calloc(size + 1, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;

	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	i = -1;
	while (map[++i])
		ft_putendl_fd(map[i], 0);
	return (map);
}

int		main(int argc, char **argv)
{
	int      fd = open(argv[1], O_RDONLY);
	char	  *line = NULL;
	t_list	*head = NULL;

	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));			//later we will count size of the list and turn it into 2d char array
	make_map(&head, ft_lstsize(head));
}


