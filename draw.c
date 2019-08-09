#include "fdf.h"
#include <math.h>
#include "map.h"


void	ft_swap(int *a, int *b)
{
    int tmp_a;

    tmp_a = *a;
    *a = *b;
    *b = tmp_a;
}

int pack_argb(const t_color col)
{
    int argb = 0;

    argb |= (col.a << 24);
    argb |= (col.r << 16);
    argb |= (col.g << 8);
    argb |= (col.b);

    return argb;
}

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
    delta.x = abs(dot1.x - dot2.x);
    delta.y = abs(dot1.y - dot2.y);
    int steep = delta.y > delta.x;
    if (steep)
    {
        ft_swap(&dot1.x, &dot1.y);
        ft_swap(&dot2.x, &dot2.y);
        ft_swap(&delta.x, &delta.y);
    }
    if (dot1.x > dot2.x)
    {
        //ft_swap(&dot1.x, &dot2.x);
        //ft_swap(&dot1.y, &dot2.y);
        //ft_swap(&dot1.z, &dot2.z);
        tmp = dot1;
        dot1 = dot2;
        dot2 = tmp;
    }
    t_point curr = dot1;
    draw_pixel(steep, dot1.x, dot1.y, 0, mlx_ptr, win_ptr, get_color(curr, dot1, dot2, delta));
    draw_pixel(steep, dot2.x, dot2.y, 0, mlx_ptr, win_ptr, get_color(curr, dot1, dot2, delta));
    float dx = dot2.x - dot1.x;
    float dy = dot2.y - dot1.y;
    float gradient = dy / dx;
    float y = (float)dot1.y + gradient;
    curr.x++;
    while (curr.x <= dot2.x - 1)
    {
        draw_pixel(steep, curr.x, (int)y, 1 - (y - (int)y), mlx_ptr, win_ptr,  get_color(curr, dot1, dot2, delta));
        draw_pixel(steep, curr.x, (int)y + 1, y - (int)y, mlx_ptr, win_ptr,  get_color(curr, dot1, dot2, delta));
        y += gradient;
        curr.x++;
    }
}

void	rotate_x(int *y, int *z, double alpha)
{
    int previous_y;

    previous_y = *y;
    *y = previous_y * cos(alpha) + *z * sin(alpha);
    *z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
    int previous_x;

    previous_x = *x;
    *x = previous_x * cos(beta) + *z * sin(beta);
    *z = -previous_x * sin(beta) + *z * cos(beta);
}


void project_rot_x(t_map *map, t_camera camera)
{
    for (size_t i = 0; i < map->height; ++i)
        for (size_t j = 0; j < map->width; ++j)
            rotate_x(&map->data[i][j].y,&map->data[i][j].z, camera.alpha);
}


void project_rot_y(t_map *map, t_camera camera) {
    for (size_t i = 0; i < map->height; ++i)
        for (size_t j = 0; j < map->width; ++j)
            rotate_y(&map->data[i][j].x, &map->data[i][j].z, camera.beta);
}
/*
static void	rotate_z(int *x, int *y, double gamma)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = previous_x * cos(gamma) - previous_y * sin(gamma);
    *y = previous_x * sin(gamma) + previous_y * cos(gamma);
}*/

t_point transform(const t_point* p, const t_fdf* fdf)
{
    t_point tmp = *p;
    rotate_x(&tmp.y, &tmp.z, fdf->camera.alpha);
    rotate_y(&tmp.x, &tmp.z, fdf->camera.beta);

    tmp.x += fdf->camera.x_move;
    tmp.y += fdf->camera.y_move;

    return tmp;
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
               /* if (map->data[i][j].z < map->max_z)
                {
                    fdf->color.r = 31;
                    fdf->color.b = 254;
                    fdf->color.g = 117;
                }
                else
                {
                    fdf->color.r = 0;
                    fdf->color.b = 255;
                    fdf->color.g = 191;
                } */

                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i][j+1], fdf), fdf);
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i+1][j+1], fdf), fdf);
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i+1][j], fdf), fdf);
            }
            draw_line(transform(&map->data[i][map->width - 1], fdf), transform(&map->data[i+1][map->width - 1], fdf), fdf);
        }
        else
        {
            for (size_t j = 0; j < map->width - 1; ++j)
            {
                draw_line(transform(&map->data[i][j], fdf), transform(&map->data[i][j+1], fdf), fdf);
            }
        }
    }

}