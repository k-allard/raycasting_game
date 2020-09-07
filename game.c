#include "cub.h"
//gcc mlx.c libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit
//from https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

// int mlx(void)
// {
//     t_all all; 
//     int x = 20;
//     int y = 20;

//     all.win = (t_win *)malloc(sizeof(t_win));
//     all.win->mlx = mlx_init();
//     all.win->win = mlx_new_window(all.win->mlx, 300, 300, "KALLARD");
//     all.win->img = mlx_new_image(all.win->mlx, 300, 300);
//     all.win->addr = mlx_get_data_addr(all.win->img, &all.win->bpp, &all.win->line_l, &all.win->en);
//     while (y++ < 100)
//     {
//         x = 20;
//         while(x++ < 100)
//             my_pixel_put(&all, x, y, 0x00FF0000);
//     }

//     mlx_put_image_to_window(all.win->mlx, all.win->win, all.win->img, 0, 0);
//     mlx_loop(all.win->mlx);
//     return 0;
// }

void			game_start(t_all *all)
{
	mlx_hook(all->mlx->win, 17, 1L << 0, ?????, (void *)0);			//закрыть игру 
	mlx_hook(all->mlx->win, 2, 5, ?????, all);						//						mlx_loop.1
	mlx_loop_hook(all->mlx->mlx, ?????, all);
	mlx_loop(all->mlx->mlx);
}



