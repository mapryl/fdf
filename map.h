#ifndef MAP_H
#define MAP_H
#include <stdlib.h>

typedef struct line
{
    int* data;
    size_t width;
    size_t width_capacity;
} t_line;

typedef struct map
{
    int** data;
    size_t hight;
    size_t width;
    size_t hight_capacity;
} t_map;

void map_create(t_map* map);
int read_map(const int fd, t_map *map);

#endif
