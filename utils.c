#include "cub.h"

void            my_pixel_put(t_all *all, int x, int y, int color)
{
    char    *dest;

    dest = all->img[0]->data_addr + (y * all->img[0]->size_line + x * (all->img[0]->bpp / 8));
    *(unsigned int*)dest = color;
}