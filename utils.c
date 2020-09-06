#include "cub.h"

void            my_pixel_put(t_all *all, int x, int y, int color)
{
    char    *dest;

    dest = all->win->addr + (y * all->win->line_l + x * (all->win->bpp / 8));
    *(unsigned int*)dest = color;
}