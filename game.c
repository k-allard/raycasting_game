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

void sort_sprite_array(t_all *all)
{
    t_sprite* tmp;
    int i = 0;
    int j = 0;

    while (i < all->sprite_count - 1)
    {        
        j = 0;
        while (j < all->sprite_count - 1 - i)
        {
            if(all->sprite_list[j]->distance < all->sprite_list[j+1]->distance)
            {
                tmp = all->sprite_list[j];
                all->sprite_list[j] = all->sprite_list[j+1];
                all->sprite_list[j+1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void calc_sprite_distance(t_all *all)
{
    int i = 0;
    while (i < all->sprite_count)
    {
        all->sprite_list[i]->distance = sqrt(pow(all->plr->x - all->sprite_list[i]->x, 2) + pow(all->plr->y - all->sprite_list[i]->y, 2)); 
        i++;
    }
    sort_sprite_array(all);
}   



int             keyhook(int keycode, t_all *all)
{
    double x = all->plr->x;
    double y = all->plr->y;

    double x_next[3];
    double y_next[3];

    x_next[0] = x;
    x_next[1] = x;
    x_next[2] = x;
    y_next[0] = y;
    y_next[1] = y;
    y_next[2] = y;
    
    // printf("%d\n", keycode);
    // fflush(stdout);
    if (keycode == 53)      //ESC
    {
        mlx_destroy_window(all->mlx, all->win);
        exit(EXIT_SUCCESS);
    }
    if (keycode == 0)       //A -- left 
    {
        y_next[0] = y + sin(all->ray->dir - M_PI/2 - M_PI/6) *0.1;
        x_next[0] = x + cos(all->ray->dir - M_PI/2 - M_PI/6) *0.1;

        y_next[1] = y + sin(all->ray->dir - M_PI / 2) *0.1;
        x_next[1] = x + cos(all->ray->dir - M_PI / 2) *0.1;

        y_next[2] = y + sin(all->ray->dir - M_PI/2 + M_PI/6) *0.1;
        x_next[2] = x + cos(all->ray->dir - M_PI/2 + M_PI/6) *0.1;

        y += sin(all->ray->dir - M_PI / 2) *0.15;
        x += cos(all->ray->dir - M_PI / 2) *0.15;
    }
    if (keycode == 2)       //D -- right 
    {
        y_next[0] = y + sin(all->ray->dir + M_PI/2 - M_PI/6) *0.1;
        x_next[0] = x + cos(all->ray->dir + M_PI/2 - M_PI/6) *0.1;

        y_next[1] = y + sin(all->ray->dir + M_PI / 2) *0.1;
        x_next[1] = x + cos(all->ray->dir + M_PI / 2) *0.1;

        y_next[2] = y + sin(all->ray->dir + M_PI/2 + M_PI/6) *0.1;
        x_next[2] = x + cos(all->ray->dir + M_PI/2 + M_PI/6) *0.1;

        y += sin(all->ray->dir + M_PI / 2) *0.15;
        x += cos(all->ray->dir + M_PI / 2) *0.15;
    }
    if (keycode == 1)       //S -- down 
    {
        y_next[0] = y - sin(all->ray->dir - M_PI/6) *0.2;
        x_next[0] = x - cos(all->ray->dir - M_PI/6) *0.2;

        y_next[1] = y - sin(all->ray->dir) *0.2;
        x_next[1] = x - cos(all->ray->dir) *0.2;

        y_next[2] = y - sin(all->ray->dir + M_PI/6) *0.2;
        x_next[2] = x - cos(all->ray->dir + M_PI/6) *0.2;

        y -= sin(all->ray->dir) *0.15;
        x -= cos(all->ray->dir) *0.15;
    }
    if (keycode == 13)      //W -- forward 
    {
        y_next[0] = y + sin(all->ray->dir - M_PI/6) *0.4;
        x_next[0] = x + cos(all->ray->dir - M_PI/6) *0.4;

        y_next[1] = y + sin(all->ray->dir) *0.4;
        x_next[1] = x + cos(all->ray->dir) *0.4;

        y_next[2] = y + sin(all->ray->dir + M_PI/6) *0.4;
        x_next[2] = x + cos(all->ray->dir + M_PI/6) *0.4;

        y += sin(all->ray->dir)*0.25;
        x += cos(all->ray->dir)*0.25;
    }
    if (keycode == 123)   //Arrow Left
    {
        all->ray->dir -= 0.1;
        all->is_draw = 1;
    }
    if (keycode == 124)   //Arrow Right
    {
        all->ray->dir += 0.1;
        all->is_draw = 1;
    }
    if ((all->p->split_map[(int)y_next[0]][(int)x_next[0]] != '1')&&
        (all->p->split_map[(int)y_next[1]][(int)x_next[1]] != '1')&&
        (all->p->split_map[(int)y_next[2]][(int)x_next[2]] != '1'))
    {
        all->plr->x = x;
        all->plr->y = y;
        
        all->is_draw = 1;
        calc_sprite_distance(all);
    }
    return (0);
}



// void player(t_all *all, double x, double y)           //для ИГРОКА (квадратик 4*4 пикселя)
// {
//     double size = 7.0;
//     double x_tmp = x - size;
//     double y_tmp = y - size;

//     while (y_tmp < y + size)
//     {
//         y_tmp += 0.1;
//         x_tmp = x - size;
//         while(x_tmp < x + size) {
//             x_tmp += 0.1;
//             my_pixel_put(all, x_tmp, y_tmp, 0xff4500);
//         }
//     }
// }

void player2(t_all *all, double x, double y)           //для ИГРОКА (квадратик 4*4 пикселя)
{
    double size = 1.0 * SCALE / 2.0;
    if (size < 1.0) 
        size = 1.0;
    double x_tmp;
    double y_tmp = all->p->hight - SCALE * all->map_hight + y * SCALE - size/2;
    double y_max = y_tmp + size;

    while (y_tmp < y_max)
    {
        x_tmp = x * SCALE - size/2;
        while (x_tmp < x * SCALE + size/2) 
        {
            my_pixel_put(all, x_tmp, y_tmp, 0xff4500);
            x_tmp += 1.0;
        }
        y_tmp += 1.0;
    }
}

void draw_sprites_on_minimap(t_all *all)
{
    double size = 1.0 * SCALE / 3.0;
    double x_tmp;
    double y_tmp;
    double y_max;
    int i = -1;

    if (size < 1.0) 
        size = 1.0;
    while (++i < all->sprite_count)
    {
        y_tmp = all->p->hight - SCALE * all->map_hight + all->sprite_list[i]->y * SCALE - size/2;
        y_max = y_tmp + size;

        while (y_tmp < y_max)
        {
            x_tmp = all->sprite_list[i]->x * SCALE - size/2;
            while (x_tmp < all->sprite_list[i]->x * SCALE + size/2) 
            {
                my_pixel_put(all, x_tmp, y_tmp, 0xff4500);
                x_tmp += 1.0;
            }
            y_tmp += 1.0;
        }
    }
}

void big_square2(t_all *all)                         //для ФОНА (квадрат 200*200 пикселей)
{
    int x_tmp;
    int y_tmp = -1;

    while (++y_tmp <= all->p->hight / 2)
    {
        x_tmp = -1;
        while(++x_tmp < all->p->width)
            my_pixel_put(all, x_tmp, y_tmp, all->p->c_rgb);//0x99CCFF);
    }
    while (++y_tmp <= all->p->hight)
    {
        x_tmp = -1;
        while(++x_tmp < all->p->width)
            my_pixel_put(all, x_tmp, y_tmp, all->p->f_rgb);//0x006600);
    }

}

void minimap_background(t_all *all)
{
    int x;
    int y = -1;

    y = all->p->hight - SCALE * all->map_hight;
    while (++y < all->p->hight)
    {
        x = -1;
        while(++x < SCALE * all->map_width)
            my_pixel_put(all, x, y, 0xc1ffb6);
        
    }
}

// void            little_square(t_all *all, int x, int y) //для ЛАБИРИНТА (рисует 1 квадратик 20*20, принимает координару верхнего левого угла)
// {
//     x *= SCALE;
//     y *= SCALE;
//     int x_tmp = x;
//     int y_tmp = y;

//     while (y_tmp++ < y + SCALE)
//     {
//         x_tmp = x;
//         while(x_tmp++ < x + SCALE)
//             my_pixel_put(all, x_tmp, y_tmp, 0xffb6c1);
//     }
// }

void            little_square2(t_all *all, int i, int j) //для ЛАБИРИНТА (рисует 1 квадратик 20*20, принимает координару верхнего левого угла)
{
    int x = i * SCALE;
    int y = all->p->hight - SCALE * all->map_hight + SCALE * j;
    int x_tmp;
    int y_tmp = y-1;

    while (++y_tmp < y + SCALE)
    {
        x_tmp = x-1;
        while(++x_tmp < x + SCALE)
            my_pixel_put(all, x_tmp, y_tmp, 0xffb6c1);
    }
}

int game(t_all *all)
{
    if(all->is_draw == 1)
    {
        int i = 0;
        big_square2(all);
        minimap_background(all);
        cast_rays3(all);
        draw_sprites(all);
        while (all->p->split_map[i])
        {
            int j = 0;
            while(all->p->split_map[i][j])
            {
                if (all->p->split_map[i][j] == '1')
                    little_square2(all, j, i);
                j++;
            }
            i++;
        }
        // draw_viewcone(all);
        player2(all, all->plr->x, all->plr->y);
        draw_sprites_on_minimap(all);
        // three_dimensions();

        mlx_sync(MLX_SYNC_IMAGE_WRITABLE, all->img[0]->img);
        mlx_put_image_to_window(all->mlx, all->win, all->img[0]->img, 0, 0);
        mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, all->win);
        //mlx_put_image_to_window(all->mlx, all->win, all->img[0]->img, 0, 0);
        all->is_draw = 0;
    }
    return 0;
}

void			game_start(t_all *all)
{
    all->is_draw = 1;
    //all->plr->x = 30;
    //all->plr->y = 30;
    if (all->p->pl_dir == 'E')
        all->ray->dir = 0;
    else if (all->p->pl_dir == 'S')
        all->ray->dir = M_PI_2;
    else if (all->p->pl_dir == 'W')
        all->ray->dir = M_PI;
    else if (all->p->pl_dir == 'N')
        all->ray->dir = 3 * M_PI_2;

    all->ray->start = -M_PI/4.0; // начало веера лучей
    all->ray->end = M_PI/4.0; // край веера лучей

    calc_sprite_distance(all);

    mlx_hook(all->win, X11_Event_DestroyNotify, 1L << 0, close_win, (void *)0);
    mlx_hook(all->win, X11_Event_KeyPress, 5, keyhook, all);
    mlx_loop_hook(all->mlx, game, all);
    mlx_loop(all->mlx);
}
