#include "cub.h"
//gcc mlx.c libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit
//from https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

void            little_square(t_all *all, int x, int y) // рисует квадратик 10*10 пикселей, принимает координару верхнего левого угла квадрата
{
    int x_tmp = x;
    int y_tmp = y;

    while (y_tmp++ < y + 10)
    {
        x_tmp = x;
        while(x_tmp++ < x + 10)
            my_pixel_put(all, x_tmp, y_tmp, 0x00FF7F);
			// mlx_pixel_put(all->mlx, all->win, x, y, 0x00FF0000);
    }
}

void			game_start(t_all *all)
{
    little_square(all, 0, 0);
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



