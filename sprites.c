#include "cub.h"


static int min(int a, int b)
{
    if (a < b) 
    {
        return a;
    }
    else
    {
        return b;
    }
    
}
static void draw_sprite(t_all *all, int index)
{
    t_sprite sprite = *(all->sprite_list[index]);
    t_plr player = *(all->plr);
    int width = all->p->width;
    int hight = all->p->hight;
    int x;
    int y;

    if(sprite.distance < 0.2)
        return;

    // absolute direction from the player to the sprite (in radians) 6.9532541698836285E-310
    double sprite_dir = atan2(sprite.y - player.y, sprite.x - player.x);
    while (sprite_dir - all->ray->dir >  M_PI) sprite_dir -= 2*M_PI; // remove unncesessary periods from the relative direction
    while (sprite_dir - all->ray->dir < -M_PI) sprite_dir += 2*M_PI;

    int sprite_heigth = (int)(hight/sprite.distance); // screen sprite size
    int sprite_width = 1.0 * sprite_heigth * all->textures[texture_S]->width / all->textures[texture_S]->height;

    int h_offset = (sprite_dir - all->ray->dir)*(width/2)/(M_PI / 4) + (width/2) - sprite_width/2; // do not forget the 3D view takes only a half of the framebuffer, thus fb.w/2 for the screen width
    int v_offset = hight/2 - sprite_heigth/2;

    for (int i=0; i<sprite_width; i++) {
        if (h_offset+i<0 || h_offset+i>=width) continue;
        if (all->depth_buffer[h_offset+i]<sprite.distance) continue; // this sprite column is occluded
        for (int j=0; j<sprite_heigth; j++) {
            if (v_offset+j<0 || v_offset+j>=hight) continue;
            x = i*all->textures[texture_S]->width/sprite_width;
            y = j*all->textures[texture_S]->height/sprite_heigth;
            int color = my_pixel_get(all, texture_S, x, y);
            if(color<0xff000000)
                my_pixel_put(all, h_offset+i, v_offset+j, color);
        }
    }
    
}

void draw_sprites(t_all *all)
{
    int i = 0;

    while (i < all->sprite_count)
    {
        draw_sprite(all, i);
        i++;
    }
    
}