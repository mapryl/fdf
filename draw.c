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