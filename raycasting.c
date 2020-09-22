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

void	draw_wall_line_from_texture(t_all *all, int text_id, double column_heigth, int x, double hit)
{
	int text_x_int = ((int)(all->textures[text_id]->width * hit)) % all->textures[text_id]->width;
	double text_y = 0.0;

	double text_y_step = all->textures[text_id]->height / column_heigth;
	int y = all->p->hight/2.0 - column_heigth/2.0;
	int y_max = all->p->hight/2.0 + column_heigth/2.0;
	if (y_max > all->p->hight)
		y_max = all->p->hight;
	int color = my_pixel_get(all, text_id, text_x_int, (int)text_y);
	while (y <= y_max)
	{
		if(y >= 0)
		{
			my_pixel_put(all, x, y, color);
			if (((int)text_y) != (int)(text_y + text_y_step))
				color = my_pixel_get(all, text_id, text_x_int, (int)text_y);
		}
		y += 1;
		text_y += text_y_step;
	}
}

int is_not_wall(t_all* all, double y, double x)
{
	return ((all->p->split_map[(int)y][(int)x] != '1') &&
	 (all->p->split_map[(int)y][(int)x] != '\0') && 
	 (all->p->split_map[(int)y][(int)x] != ' '));

	return ((all->map_protect[(int)y+1][(int)x+1] != '1') &&
	 (all->map_protect[(int)y+1][(int)x+1] != 'X') && 
	 (all->map_protect[(int)y+1][(int)x+1] != ' '));
}

int is_wall(t_all* all, double y, double x)
{
	return ((all->p->split_map[(int)y][(int)x] == '1') || 
		(all->p->split_map[(int)y][(int)x] == '\0') ||
		(all->p->split_map[(int)y][(int)x] == ' '));

	return ((all->map_protect[(int)y+1][(int)x+1] == '1') || 
		(all->map_protect[(int)y+1][(int)x+1] == 'X') ||
		(all->map_protect[(int)y+1][(int)x+1] == ' '));
}

void	cast_rays(t_all *all)
{
	int x_scale_int;
	int y_scale_int;
	int x_int;
	int y_int;
	double x = all->plr->x; // задаем координаты луча равные координатам середины игрока
	double y = all->plr->y;
	
	double angle = all->ray->dir - M_PI/4; // начало веера лучей
    double angle_max  = all->ray->dir + M_PI/4; // край веера лучей

	int pixel_index = 0;
	int step = 0;
	while(angle < angle_max && pixel_index < all->p->width)
	{
		x = all->plr->x;	// каждый раз возвращаемся в точку начала
		y = all->plr->y;
		double x_step = cos(angle) / 20.0;
		double y_step = sin(angle) / 20.0;

		while (is_not_wall(all, y, x))
		{
			x_int = (int)x;
			y_int = (int)y;
			x_scale_int = (int)(x*SCALE);
			y_scale_int = (int)(y*SCALE);
			while (x_scale_int == (int)(x*SCALE) && y_scale_int == (int)(y*SCALE) && x_int == (int)x && y_int == (int)y)
			{
				x += x_step; 
				y += y_step;
			}
			my_pixel_put(all, \
				x * SCALE, \
				all->p->hight - SCALE * all->map_hight + y * SCALE, \
				0x666699);
		}
		if(is_wall(all, y, x))
		{
			double round_y = 1.0 * round(y);
			double round_y_d = (round_y - all->plr->y) / sinl(angle);
			double round_y_x = cos(angle) * round_y_d + (all->plr->x);
			double round_x = 1.0 * round(x);
			double round_x_d = (round_x - all->plr->x) / cos(angle);
			double round_x_y = sin(angle) * round_x_d + (all->plr->y);	
			double distance = (round_x_d < round_y_d) ? round_x_d : round_y_d;
			double hit;
			int text_id;
			int color;
			int round_x_step = (round_x > x) ? -1 : 0;
			int round_y_step = (round_y > y) ? -1 : 0;
		
			//расстояние при округлении по y отрицательное ИЛИ 
			//расстояние при округлении по y не отрицательное И по x тоже не отрицательное И
			//		расстояние при округлении по x меньше чем при округлении по y И точка при округлении по x является стеной
			// 		ИЛИ
			//		расстояние при округлении по y меньше чем при округлении по x, НО точка при округлении по y не является стеной
			if (round_y_d < 0 || (round_x_d >= 0 && ( \
				(round_x_d < round_y_d && is_wall(all, round_x_y, (int)round_x + round_x_step)) || \
				(round_y_d < round_x_d && is_not_wall(all, (int)(round_y) + round_y_step, round_y_x)))))
			{	
				distance = round_x_d;
				hit = round_x_y - (int)round_x_y;
				if (cos(angle) > 0)
					text_id = texture_EA;  		//east
				else
					text_id = texture_WE; 		//west
			}
			else
			{
				distance = round_y_d;
				hit = round_y_x - (int)round_y_x;
				if (sin(angle) > 0)
					text_id = texture_SO;		//south
				else 
					text_id = texture_NO;		//north
			}
			
			all->depth_buffer[pixel_index] = distance;
			double column_heigth =  all->p->hight / distance / cos(angle - all->ray->dir);			
			draw_wall_line_from_texture(all, text_id, column_heigth, pixel_index, hit);
		}
		angle += M_PI/2.0/all->p->width; 	//[угол обзора] / [количество лучей]
		pixel_index ++; //
	}
}
