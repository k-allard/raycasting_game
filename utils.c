#include "cub.h"

void            my_pixel_put(t_all *all, int x, int y, int color)
{
    char    *dest;

    dest = all->img[0]->data_addr + (y * all->img[0]->size_line + x * (all->img[0]->bpp / 8));
    *(unsigned int*)dest = color;
}


int            my_pixel_get(t_all *all, int text_id, int x, int y)
{
    char    *dest;

    dest = all->textures[text_id]->data_addr + (y * all->textures[text_id]->size_line + x * (all->textures[text_id]->bpp / 8));
    return *(unsigned int*)dest;
}