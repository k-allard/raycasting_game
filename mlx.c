#include "cub.h"
//gcc mlx.c libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit
//from https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

void            my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
    char    *dest;

    dest = all->win->addr + (y * all->win->line_l + x * (all->win->bpp / 8));
    *(unsigned int*)dest = color;
}

int main(void)
{
    t_all all; 
    // int x = 100;
    // int y = 100;

    all.win = (t_win *)malloc(sizeof(t_win));
    all.win->mlx = mlx_init();
    all.win->win = mlx_new_window(all.win->mlx, 300, 300, "KALLARD");
    // while (y++ < 200)
    // {
    //     x = 100;
    //     while(x++ < 200)
    //         mlx_pixel_put(all.win->mlx, all.win->win, x, y, 0x66ff00);
    // }
    all.win->img = mlx_new_image(all.win->mlx, 300, 300);
    /*
    ** After creating an image, we can call `mlx_get_data_addr`, we pass
    ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
    ** then be set accordingly for the *current* data address.
    */
    all.win->addr = mlx_get_data_addr(&all.win->img, &all.win->bpp, &all.win->line_l, &all.win->en);
    
    my_mlx_pixel_put(&all, 20, 20, 0x00FF0000);

    mlx_put_image_to_window(all.win->mlx, all.win->win, all.win->img, 0, 0);

    mlx_loop(all.win->mlx);
    return 0;
}