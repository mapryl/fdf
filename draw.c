#include "fdf.h"
#include "map.h"
#include "rotate.h"
#include "supporting_functions.h"

void draw_pixel(int steep, int x, int y,  t_fdf* fdf, t_color color)
{
    if (!steep)
    {
        int argb;

        color.a = (1 - color.a) * 255;
        argb = pack_argb(color);
        mlx_pixel_put(fdf->mlx_ptr, fdf->mlx_win, x, y, argb);
    }
    else
    {
        int argb;

        color.a = (1 - color.a) * 255;
        argb = pack_argb(color);
        mlx_pixel_put(fdf->mlx_ptr, fdf->mlx_win, y, x, argb);
    }
}

void draw_between(int steep, const t_point* p1, const t_point* p2, const t_point* delta, t_fdf* fdf)
{
    float gradient;
    float y;
    t_point curr;

    curr = *p1;

    gradient = (float)(p2->y - p1->y) / (float)(p2->x - p1->x);
    y = (float)p1->y + gradient;
    curr.x++;
    while (curr.x <= p2->x - 1)
    {
        draw_pixel(steep, curr.x, (int)y, fdf,  get_color(curr, *p1, *p2, *delta, 1 - (y - (int)y)));
        draw_pixel(steep, curr.x, (int)y + 1, fdf,  get_color(curr, *p1, *p2, *delta, 1 - (y - (int)y)));
        y += gradient;
        curr.x++;
    }
}


void Draw_Wu(t_point dot1, t_point dot2,  t_fdf* fdf)
{
    t_point delta;
    t_point tmp;
    int steep;

    delta.x = abs(dot1.x - dot2.x);
    delta.y = abs(dot1.y - dot2.y);
    steep = delta.y > delta.x;
    if (steep)
    {
        ft_swap(&dot1.x, &dot1.y);
        ft_swap(&dot2.x, &dot2.y);
        ft_swap(&delta.x, &delta.y);
    }
    if (dot1.x > dot2.x)
    {
        tmp = dot1;
        dot1 = dot2;
        dot2 = tmp;
    }
    draw_pixel(steep, dot1.x, dot1.y, fdf, get_color(dot1, dot1, dot2, delta, 0));
    draw_pixel(steep, dot2.x, dot2.y, fdf, get_color(dot2, dot1, dot2, delta, 0));
    draw_between(steep, &dot1, &dot2, &delta, fdf);
}

void draw_thing(int i, int j, t_fdf* fdf)
{
    t_map *map;

    map = fdf->map;

    Draw_Wu(transform(&map->data[i][j], fdf), transform(&map->data[i][j+1], fdf), fdf);
    Draw_Wu(transform(&map->data[i][j], fdf), transform(&map->data[i+1][j+1], fdf), fdf);
    Draw_Wu(transform(&map->data[i][j], fdf), transform(&map->data[i+1][j], fdf), fdf);
}

void print_map(t_map *map, t_fdf *fdf)
{
    size_t i;
    size_t j;

    mlx_clear_window(fdf->mlx_ptr, fdf->mlx_win);
    i = 0;
    while (i < map->height)
    {
        j = 0;
        if (i < map->height - 1)
        {
            while (j < map->width - 1)
            {
                draw_thing(i, j, fdf);
                j++;
            }
            Draw_Wu(transform(&map->data[i][map->width - 1], fdf), transform(&map->data[i+1][map->width - 1], fdf), fdf);
        }
        else
            while (j < map->width - 1)
            {
                Draw_Wu(transform(&map->data[i][j], fdf), transform(&map->data[i][j+1], fdf), fdf);
                j++;
            }
        i++;
    }
}