#include "cub.h"


//Пробуем кинуть один луч
void	cast_one_ray(t_all *all)
{
	all->ray->x = all->plr->x + 2; // задаем координаты луча равные координатам середины игрока
	all->ray->y = all->plr->y + 2;

	while (all->p->split_map[(int)(all->ray->y / SCALE)][(int)(all->ray->x / SCALE)] != '1')
	{
		all->ray->x += cos(all->ray->dir);
		all->ray->y += sin(all->ray->dir);
        my_pixel_put(all, all->ray->x, all->ray->y, 0xff4500);
	}
}

// //Пробуем кинуть много лучей
// void	ft_cast_rays(t_all *all)
// {
// 	t_plr	ray = *all->plr; // задаем координаты и направление луча равные координатам игрока
// 	double start = ray.dir - [половина угла обзора]; // начало веера лучей
//   double end = ray.dir + [половина угла обзора]; // край веера лучей

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