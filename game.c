#include "cub.h"
#include <stdio.h>

//gcc mlx.c libft/libft.a libmlx.dylib -framework OpenGL -framework AppKit
//from https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

int		close_win(void)
{
	printf("Player closed the window.\nGame exited\n");
    exit(EXIT_SUCCESS);
	return (0);
}

int             keyhook(int keycode, t_all *all)
{
    printf("%d\n", keycode);
    fflush(stdout);
    if (keycode == 53)      //ESC
    {
        mlx_destroy_window(all->mlx, all->win);
        exit(EXIT_SUCCESS);
    }
    if (keycode == 0)       //A -- left 
    {
        all->plr->x -= 4;
    }
    if (keycode == 2)       //D -- right 
    {
        all->plr->x += 4;
    }
    if (keycode == 1)       //S -- down 
    {
        all->plr->y += 4;
    }
    if (keycode == 13)      //W -- up 
    {
        all->plr->y -= 4;
    }
    if (keycode == 123)   //Arrow Left
    {
        all->ray->dir -= 0.02;
    }
    if (keycode == 124)   //Arrow Right
    {
        all->ray->dir += 0.02;
    }
    return (0);
}

void player(t_all *all, int x, int y)           //для ИГРОКА (квадратик 5*5 пикселя)
{
    int x_tmp = x;
    int y_tmp = y;

    while (y_tmp++ < y + 4)
    {
        x_tmp = x;
        while(x_tmp++ < x + 4)
            my_pixel_put(all, x_tmp, y_tmp, 0xff4500);
    }
}

void big_square(t_all *all)                         //для ФОНА (квадрат 200*200 пикселей)
{
    int x = 0;
    int y = 0;
    int x_tmp = x;
    int y_tmp = y;

    while (y_tmp++ < y + 200)
    {
        x_tmp = x;
        while(x_tmp++ < x + 200)
            my_pixel_put(all, x_tmp, y_tmp, 0xc1ffb6);
    }
}

void            little_square(t_all *all, int x, int y) //для ЛАБИРИНТА (рисует 1 квадратик 20*20, принимает координару верхнего левого угла)
{
    x *= SCALE;
    y *= SCALE;
    int x_tmp = x;
    int y_tmp = y;

    while (y_tmp++ < y + SCALE)
    {
        x_tmp = x;
        while(x_tmp++ < x + SCALE)
            my_pixel_put(all, x_tmp, y_tmp, 0xffb6c1);
    }
}

int game(t_all *all)
{
    int i = 0;
    big_square(all);
    while (all->p->split_map[i])
    {
        int j = 0;
        while(all->p->split_map[i][j])
        {
            if (all->p->split_map[i][j] == '1')
                little_square(all, j, i);
            j++;
        }
        i++;
    }
    player(all, all->plr->x, all->plr->y);
    cast_one_ray(all);
    mlx_put_image_to_window(all->mlx, all->win, all->img[0]->img, 0, 0);
    return 0;
}

void			game_start(t_all *all)
{
    all->plr->x = 20;
    all->plr->y = 30;
    all->ray->dir = 0;

    mlx_hook(all->win, 17, 1L << 0, close_win, (void *)0);
    mlx_hook(all->win, 2, 5, keyhook, all);
    mlx_loop_hook(all->mlx, game, all);
    mlx_loop(all->mlx);
}
