#include "keys.h"
#include "fdf.h"

void rotate(int key, t_fdf *fdf)
{
    if (key == KEYBOARD_W)
        fdf->camera.alpha -= 0.05;
    if (key == KEYBOARD_S)
        fdf->camera.alpha += 0.05;
    if (key == KEYBOARD_D)
        fdf->camera.beta += 0.05;
    if (key == KEYBOARD_A)
        fdf->camera.beta -= 0.05;
    print_map(fdf->map, fdf);
}

void	move(int key, t_fdf *fdf)
{
    if (key == ARROW_LEFT)
        fdf->camera.x_move -= 10;
    else if (key == ARROW_RIGHT)
        fdf->camera.x_move += 10;
    else if (key == ARROW_UP)
        fdf->camera.y_move -= 10;
    else
        fdf->camera.y_move += 10;
    print_map(fdf->map, fdf);
}

void zoom_in(t_fdf *fdf)
{
    camera_zoom_in(&fdf->camera);
    print_map(fdf->map, fdf);
}

void zoom_out(t_fdf *fdf)
{
    camera_zoom_out(&fdf->camera);
    print_map(fdf->map, fdf);
}

void set_iso(t_fdf *fdf)
{
    fdf->camera.is_iso = !fdf->camera.is_iso;
    print_map(fdf->map, fdf);
}