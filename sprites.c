#include "cub.h"


static int min(int a, int b)
{
	if (a < b) 
	{
		return a;
	}
	else
	{
		return b;
	}
	
}
static void draw_sprite(t_all *all, int index)
{
	t_sprite sp;
	int x;
	int y;
	int i;
	int j;

	sp = *(all->sprites[index]);
	if (sp.dist < 0.2)
		return;
	sp.dir = atan2(sp.y - all->plr->y, sp.x - all->plr->x);
	while (sp.dir - all->ray->dir >  M_PI) 
		sp.dir -= 2 * M_PI;
	while (sp.dir - all->ray->dir < -M_PI) 
		sp.dir += 2 * M_PI;
	sp.h = (int)(all->p->h / sp.dist);
	sp.w = 1.0 * sp.h * all->text[S]->w / all->text[S]->h;
	sp.x_start = (sp.dir - all->ray->dir) * (all->p->w / 2) / (M_PI / 4) + (all->p->w / 2) - sp.w / 2;
	sp.y_start = all->p->h / 2 - sp.h / 2;

	i = 0;
	while (i < sp.w)
	{
		if ((sp.x_start + i >= 0 && sp.x_start + i < all->p->w) &&
			(all->depth_buf[sp.x_start + i] >= sp.dist))
		{
			j = 0; 
			while (j < sp.h)
			{
				if (sp.y_start + j >= 0 && sp.y_start + j < all->p->h)
				{
					x = i * all->text[S]->w / sp.w;
					y = j * all->text[S]->h / sp.h;
					int color = my_pixel_get(all, S, x, y);
					if (color < 0xff000000)
						my_pixel_put(all, sp.x_start + i, sp.y_start + j, color);
				}
				j++;
			}
		}
		i++;
	}
}

void draw_sprites(t_all *all)
{
	int i = 0;

	while (i < all->sprite_count)
	{
		draw_sprite(all, i);
		i++;
	}
}