#include "fdf.h"
#include "map.h"
#include "rotate.h"
#include "supporting_functions.h"

void draw_pixel(int steep, int x, int y, float alpha, void *mlx_ptr, void *win_ptr, t_color color)
{
    if (!steep)
    {
        int argb;

        color.a = (1 - alpha) * 255;
        argb = pack_argb(color);
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, argb);
    }
    else
    {
        int argb;

        color.a = (1 - alpha) * 255;
        argb = pack_argb(color);
        mlx_pixel_put(mlx_ptr, win_ptr, y, x, argb);
    }
}

void Draw_Wu(t_point dot1, t_point dot2, void *mlx_ptr, void *win_ptr)
{
    t_point delta;
    t_point tmp;
    float gradient;
    float y;
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
    t_point curr = dot1;
    draw_pixel(steep, dot1.x, dot1.y, 0, mlx_ptr, win_ptr, get_color(curr, dot1, dot2, delta));
    draw_pixel(steep, dot2.x, dot2.y, 0, mlx_ptr, win_ptr, get_color(dot2, dot1, dot2, delta));
    gradient = (float)(dot2.y - dot1.y) / (float)(dot2.x - dot1.x);
    y = (float)dot1.y + gradient;
    curr.x++;
    while (curr.x <= dot2.x - 1)
    {
        draw_pixel(steep, curr.x, (int)y, 1 - (y - (int)y), mlx_ptr, win_ptr,  get_color(curr, dot1, dot2, delta));
        draw_pixel(steep, curr.x, (int)y + 1, y - (int)y, mlx_ptr, win_ptr,  get_color(curr, dot1, dot2, delta));
        y += gradient;
        curr.x++;
    }
}

void draw_line(t_point p1, t_point p2, t_fdf* fdf)
{
    Draw_Wu(p1, p2, fdf->mlx_ptr, fdf->mlx_win);
}

void print_map(t_map *map, t_fdf *fdf)
{
    mlx_clear_window(fdf->mlx_ptr, fdf->mlx_win);

    for (size_t i = 0; i < map->height; ++i)
    {
        if (i < map->height - 1)
        {
            for (size_t j = 0; j < map->width - 1; ++j)
            {
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i][j+1], fdf), fdf);
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i+1][j+1], fdf), fdf);
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i+1][j], fdf), fdf);
            }
            draw_line(transform(&map->data[i][map->width - 1], fdf), transform(&map->data[i+1][map->width - 1], fdf), fdf);
        }
        else
            for (size_t j = 0; j < map->width - 1; ++j)
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i][j+1], fdf), fdf);
    }

}