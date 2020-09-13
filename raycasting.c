#include "cub.h"

void three_dimensions(t_all *all)
{
	for(size_t i = 0; i < 200; i++)
	{
		double angle = all->ray->dir - M_PI/4 + (M_PI/2)*i/200.0;
		double max_scale_factor = 11.0;

		double test_x = all->plr->x;
		double test_y = all->plr->y;
		double test = 0;
		while (test_x >= 0.0 && test_x <= 200.0 && test_y >= 0.0 && test_y <= 200.0 && test < 200.0)
		{
			test_x = all->plr->x + test*cos(angle);
			test_y = all->plr->y + test*sin(angle);


			test += 0.1;
		}
		
		for (double test = 0; test < max_scale_factor; test += 0.001)
		{
			double test_x = all->plr->x + test*cos(angle);
			double test_y = all->plr->y + test*sin(angle);
		}
	}

}


//Пробуем кинуть один луч
void	cast_rays2(t_all *all)
{
	double x = all->plr->x; // задаем координаты луча равные координатам середины игрока
	double y = all->plr->y;
	
	double angle = all->ray->dir - M_PI/4; // начало веера лучей
    double angle_max  = all->ray->dir + M_PI/4; // край веера лучей

	int pixel_index = 0;
	while(angle <= angle_max)
	{
		x = all->plr->x;	// каждый раз возвращаемся в точку начала
		y = all->plr->y;
		double x_step = cos(angle)/10.0;
		double y_step = sin(angle)/10.0;
		while (all->p->split_map[(int)(y / SCALE)][(int)(x / SCALE)] != '1')
		{
			x += x_step;
			y += y_step;
			my_pixel_put(all, x, y, 0x21de00);
		}
		if(all->p->split_map[(int)(y / SCALE)][(int)(x / SCALE)] == '1')
		{
			int color = \
				(all->p->split_map[(int)(y / SCALE)][(int)((x + 0.1) / SCALE)] == '1') &&
				(all->p->split_map[(int)(y / SCALE)][(int)((x - 0.1)/ SCALE)] == '1') ?
				0xFF9999 : 0xFFCCCC;
			double destination = (all->plr->y - y) == 0.0 ? (all->plr->x - x) : (all->plr->y - y)/(y_step*10.0);
			if (destination < 0.0)
				destination = - destination;
			destination = destination * 20.0 / 200.0;
			
			double column_heigth = destination == 0 ? 200 : 200 / destination / cos(angle - all->ray->dir);
			column_heigth = column_heigth > 200 ? 200 : column_heigth;
			int windows_x = 200 + pixel_index;
			double windows_y = 200.0/2.0 - column_heigth/2.0;
			while (windows_y <= 200.0/2 + column_heigth/2.0)
			{
				my_pixel_put(all, windows_x, windows_y, color);
				windows_y += 0.2;
			}
		}
		angle += M_PI/2.0/200.0; 	//[угол обзора] / [количество лучей]
		pixel_index ++; //
	}
}

//Пробуем кинуть один луч
void	cast_rays(t_all *all)
{
	all->ray->x = all->plr->x; // задаем координаты луча равные координатам середины игрока
	all->ray->y = all->plr->y;
	all->ray->start = all->ray->dir - M_PI/4; // начало веера лучей
    all->ray->end = all->ray->dir + M_PI/4; // край веера лучей

	while(all->ray->start <= all->ray->end)
	{
		all->ray->x = all->plr->x;	// каждый раз возвращаемся в точку начала
		all->ray->y = all->plr->y;
		while (all->p->split_map[(int)(all->ray->y / SCALE)][(int)(all->ray->x / SCALE)] != '1')
		{
			all->ray->x += cos(all->ray->start);
			all->ray->y += sin(all->ray->start);
			my_pixel_put(all, all->ray->x, all->ray->y, 0x21de00);
		}

		all->ray->start += M_PI/2/200; 	//[угол обзора] / [количество лучей]
	}
}
