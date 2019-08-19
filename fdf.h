#ifndef FDF_H
# define FDF_H

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/get_next_line.h"
#include "libft/includes/libft.h"
#include "map.h"
#include "camera.h"
#include "graphics.h"

typedef struct picture
{
    int  *pic;
    int  *data_address;
    int  bpp;
    int  line_size;
    int  endian;
    size_t pic_size;
} t_picture;

typedef struct fdf
{
    t_map *map;
    t_camera camera;
    void *mlx_ptr;
    void *mlx_win;
    void *pepe_ptr;
    void *menu_ptr;
    t_picture picture;
} t_fdf;

void Draw_Wu(t_point dot1, t_point dot2,  t_fdf* fdf);
void print_map(t_map *map, t_fdf *fdf);

#endif
