#include "cub.h"
#include <stdio.h>

void my_pixel_put(t_all *all, int x, int y, int color)
{
	char    *dest;

	dest = all->img->data_addr + (y * all->img->size_line + x * (all->img->bpp / 8));
	*(unsigned int*)dest = color;
}


void my_pixel_put_line(t_all *all, int width, int y, int color)
{
	char    *dest;
	int x;
	int pixel_size;

	pixel_size = all->img->bpp / 8;
	dest = all->img->data_addr + (y * all->img->size_line);

	while (--width)
		*(unsigned int*)(dest + width * pixel_size) = color;
}


int inline           my_pixel_get(t_all *all, int text_id, int x, int y)
{
	char    *dest;

	dest = all->textures[text_id]->data_addr + (y * all->textures[text_id]->size_line + x * (all->textures[text_id]->bpp / 8));
	return *(unsigned int*)dest;
}