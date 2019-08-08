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

void Draw_Wu(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr, t_color color)
{
    int steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep)
    {
        ft_swap(&x0, &y0);
        ft_swap(&x1, &y1);
    }
    if (x0 > x1)
    {
        ft_swap(&x0, &x1);
        ft_swap(&y0, &y1);
    }
    draw_pixel(steep, x0, y0, 0, mlx_ptr, win_ptr, color);
    draw_pixel(steep, x1, y1, 0, mlx_ptr, win_ptr, color);
    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = dy / dx;
    float y = y0 + gradient;
    for (int x = x0 + 1; x <= x1 - 1; x++)
    {
        draw_pixel(steep, x, (int)y, 1 - (y - (int)y), mlx_ptr, win_ptr, color);
        draw_pixel(steep, x, (int)y + 1, y - (int)y, mlx_ptr, win_ptr, color);
        y += gradient;
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
    Draw_Wu(p1.x, p1.y, p2.x, p2.y,
            fdf->mlx_ptr, fdf->mlx_win, fdf->color);
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
                if (map->data[i][j].z < map->max_z)
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
                }

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