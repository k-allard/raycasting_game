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
	int step = 0;
	while(angle <= angle_max)
	{
		x = all->plr->x;	// каждый раз возвращаемся в точку начала
		y = all->plr->y;
		double x_step = cos(angle)/14.0;
		double y_step = sin(angle)/14.0;
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
			double destination = (all->plr->y - y) == 0.0 ? (all->plr->x - x) : (all->plr->y - y)/(y_step*14.0);
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
void	cast_rays3(t_all *all)
{
	double x = all->plr->x; // задаем координаты луча равные координатам середины игрока
	double y = all->plr->y;
	
	double angle = all->ray->dir - M_PI/4; // начало веера лучей
    double angle_max  = all->ray->dir + M_PI/4; // край веера лучей

	int resolution = 1000;

	int pixel_index = 0;
	int step = 0;
	while(angle <= angle_max)
	{
		x = all->plr->x * resolution;	// каждый раз возвращаемся в точку начала
		y = all->plr->y * resolution;
		double x_step = cos(angle) * resolution / 10.0;
		double y_step = sin(angle) * resolution / 10.0;

		while (all->p->split_map[(int)(y / resolution)][(int)(x / resolution)] != '1')
		{
			x += x_step; 
			y += y_step;
			my_pixel_put(all, \
				x * SCALE / resolution, \
				all->p->hight - SCALE * all->map_hight + y * SCALE / resolution, \
				0x21de00);
		}
		if(all->p->split_map[(int)(y / resolution)][(int)(x / resolution)] == '1')
		{
			if(x >= 980 && x <= 981 && y >= 1997 && y <= 1998)
				x = x;
			double round_y = 1.0 * resolution * round(y / resolution);
			double round_y_d = (round_y - all->plr->y * resolution) / sinl(angle);
			double round_y_x = cos(angle) * round_y_d + (all->plr->x * resolution);
			double round_y_x2 = all->plr->x * resolution - (all->plr->y * resolution - round_y) / tan(angle);
			//round_y_d = fabs(round_y_d);

			double test_angle = cos(angle);
			double test_angle2 = cos(angle) * round_y_d;
			//if( round_y_x >= 0 && \
			//	round_y_x - resolution * ((int)(x / resolution) - 1) <= resolution * 3 && \
			//	resolution * ((int)(x / resolution) + 1) - round_y_x <= resolution * 3)
			//{
			//	if(all->p->split_map[(int)(round_y / resolution)][(int)(round_y_x / resolution)] != '1')
			//		round_y_d = 100000000000.0;
			//} else
			//{
			//	round_y_d = 100000000000.0;
			//}				

			//round_y_d = 			round_y_d = round_y_d > 0.0 ? round_y_d : -round_y_d;
			//if(all->p->split_map[(int)(round_y / resolution)][(int)(round_y_x / resolution)] != '1')
			//	round_y_d = round_y_d * 1234;

			double round_x = 1.0 * resolution * round(x / resolution);
			double round_x_d = (round_x - all->plr->x * resolution) / cos(angle);
			double round_x_y = sin(angle) * round_x_d + (all->plr->y * resolution);
			//round_x_d = fabs(round_x_d);

			//if(round_y_x <= resolution * (int)(x / resolution) || round_y_x - resolution * (int)(x / resolution) >= resolution )
			//	round_y_d = 100000000000.0;
			//else
			//if(round_x_y <= resolution * (int)(y / resolution) || round_x_y - resolution * (int)(y / resolution) >= resolution )
			//	round_x_d = 100000000000.0;
			//if(round_x_y >= 0 && \
			//	round_x_y - resolution * ((int)(y / resolution) - 1) <= resolution * 3 && \
			//	resolution * ((int)(y / resolution) + 1) - round_x_y <= resolution * 3)
			//{
			//	if(all->p->split_map[(int)(round_x_y / resolution)][(int)(round_x / resolution)] != '1')
			//		round_x_d = 100000000000.0;
			//} else
			//{
			//	round_x_d = 100000000000.0;
			//}				

			double destination = (round_x_d < round_y_d) ? round_x_d : round_y_d;
			int color;
			int round_x_step = (round_x > x) ? -1 : 0;
			int round_y_step = (round_y > y) ? -1 : 0;
			if(round_y_d < 0)
			{
				destination = round_x_d;
				color = 0xFF9999;
			} else if(round_x_d < 0)
			{
				destination = round_y_d;
				color = 0xFFCCCC;
			} else if(round_x_d < round_y_d)
			{
				if(all->p->split_map[(int)(round_x_y / resolution)][(int)(round_x / resolution) + round_x_step] == '1')
				{
					destination = round_x_d;
					color = 0xFF9999;
				}
				else
				{
					destination = round_y_d;
					color = 0xFFCCCC;
				}
			} else
			{
				if(all->p->split_map[(int)(round_y / resolution) + round_y_step][(int)(round_y_x / resolution)] == '1')
				{
					destination = round_y_d;
					color = 0xFFCCCC;
				}
				else
				{
					destination = round_x_d;
					color = 0xFF9999;
				}
			}
			
			
			// = (round_x_d < round_y_d) ? round_x_d : round_y_d;

			//double column_heigth =  all->p->hight / 200.0 / (destination / resolution) / cos(angle - all->ray->dir);
			double column_heigth =  all->p->hight / (destination / resolution) / cos(angle - all->ray->dir);
			column_heigth = column_heigth > all->p->hight ? all->p->hight : column_heigth;

					
			int windows_x = pixel_index;
			double windows_y = all->p->hight/2.0 - column_heigth/2.0;
			while (windows_y <= all->p->hight/2 + column_heigth/2.0)
			{
				if(!(windows_x <= SCALE * all->map_width && \
				 	windows_y >= all->p->hight - SCALE * all->map_hight))
					my_pixel_put(all, windows_x, windows_y, color);
				windows_y += 0.5;
			}
		}
		angle += M_PI/2.0/all->p->width; 	//[угол обзора] / [количество лучей]
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
