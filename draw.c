#include "fdf.h"
#include <math.h>


void	ft_swap(int *a, int *b)
{
    int tmp_a;

    tmp_a = *a;
    *a = *b;
    *b = tmp_a;
}


void draw_pixel(int steep, int x, int y, float c, void *mlx_ptr, void *win_ptr, int colour)
{
    if (!steep)
    {
       // int r = 1 - c;
       // int g = 1 - c;
       // int b = 1 - c;
      //  int color_test = r + g + b;
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour);
    }
    else
    {
        //int r = 1 - c;
        //int g = 1 - c;
       // int b = 1 - c;
        //int color_test = r + g + b;
        mlx_pixel_put(mlx_ptr, win_ptr, y, x, colour);
    }
}

void Draw_Wu(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr, int colour)
{
    int steep = abs(y1 - y0) > abs(x1 - x0) ? 1 : -1;

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

    draw_pixel(steep, x0, y0, 255, mlx_ptr, win_ptr, colour);
    draw_pixel(steep, x1, y1, 255, mlx_ptr, win_ptr, colour);
    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = dy / dx;
    float y = y0 + gradient;
    for (int x = x0 + 1; x <= x1 - 1; x++)
    {
        draw_pixel(steep, x, (int)y, 1 - (y - (int)y), mlx_ptr, win_ptr, colour);
        draw_pixel(steep, x, (int)y + 1, y - (int)y, mlx_ptr, win_ptr, colour);
        y += gradient;
    }
}