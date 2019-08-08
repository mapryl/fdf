#ifndef MAP_H
#define MAP_H
#include <stdlib.h>

# define X_UNIT 50
# define Y_UNIT 50

typedef struct point
{
    int x;
    int y;
    int z;
} t_point;

typedef struct line
{
    t_point* data;
    size_t width;
    size_t width_capacity;
} t_line;

typedef struct map
{
    t_point** data;
    size_t height;
    size_t width;
    size_t height_capacity;
    size_t max_z;
    size_t min_z;
} t_map;

typedef struct
{
    short a;
    short r;
    short g;
    short b;
} t_color;

typedef struct camera
{
    double alpha;
    double beta;
    double gamma;
    int x_move;
    int y_move;
} t_camera;

typedef struct fdf
{
    t_map *map;
    t_camera camera;
    void *mlx_ptr;
    void *mlx_win;
    t_color color;
} t_fdf;

void map_create(t_map* map);
int read_map(const int fd, t_map *map);

#endif
