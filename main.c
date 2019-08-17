#include "map.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"
#include "keys.h"
#include <math.h>
#include "keyboard_controls.h"
#include "errors.h"
#include "supporting_functions.h"

int key_press(int key, void* param)
{
    t_fdf *fdf;

    fdf = (t_fdf*)param;
    if (key == MAIN_PAD_ESC)
        exit(0);
    if (key == NUM_PAD_1 || key == NUM_PAD_2 || key == NUM_PAD_3 || key == NUM_PAD_4 || key == NUM_PAD_5 || key == NUM_PAD_6 || key == NUM_PAD_7 || key == NUM_PAD_8 || key == NUM_PAD_9)
        rotate(key, fdf);
    else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_DOWN || key == ARROW_UP)
        move(key, fdf);
    else if(key == MAIN_PAD_PLUS)
        zoom_in(fdf);
    else if(key == MAIN_PAD_MINUS)
        zoom_out(fdf);
    else if(key == KEYBOARD_I)
        set_iso(fdf);
    return (0);
}

void init_window(t_map *map)
{
    void *mlx_ptr = mlx_init();
    void *mlx_win = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "3DViewer 99/100");

    t_fdf fdf;
    fdf.map = map;
    camera_create(&fdf.camera);
    fdf.mlx_ptr = mlx_ptr;
    fdf.mlx_win = mlx_win;

    print_map(map, &fdf);
    mlx_key_hook(mlx_win, key_press, &fdf);

    mlx_loop(mlx_ptr);
}

int main (int argc, const char* argv[])
{
    int fd;
    t_map map;

    if (argc == 2)
    {
        if ((fd = open(argv[1], O_RDONLY)) < 0)
            throw_error(FILE_ERROR);
        map_create(&map);
        read_map(fd, &map);
        init_window(&map);
    }
    return 0;
}