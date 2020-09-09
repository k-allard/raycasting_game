#include "cub.h"
//gcc mlx.c libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit
//from https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

void			game_start(t_all *all)
{
    int x = 20;
    int y = 20;

    while (y++ < 100)
    {
        x = 20;
        while(x++ < 100)
            my_pixel_put(all, x, y, 0x00FF7F);
			// mlx_pixel_put(all->mlx, all->win, x, y, 0x00FF0000);
    }
    mlx_put_image_to_window(all->mlx, all->win, all->img[0]->img, 0, 0);
    mlx_loop(all->mlx);
}

// void			game_start(t_all *all)
// {
// 	mlx_hook(all->win, 17, 1L << 0, ?????, (void *)0);			//закрыть игру 
// 	mlx_hook(all->win, 2, 5, ?????, all);						//						mlx_loop.1
// 	mlx_loop_hook(all->mlx, ?????, all);
// 	mlx_loop(all->mlx);
// }



