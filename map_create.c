#include "line.h"
#include "map.h"
#include "get_next_line.h"
#include <limits.h>
#include "supporting_functions.h"
#include "errors.h"

void map_create(t_map* map)
{
    map->data = NULL;
    map->height_capacity = 0;
    map->height = 0;
    map->width = 0;
    map->max_z = INT_MIN;
    map->min_z = INT_MAX;
}

void* reallocate(void *data, size_t* capacity, size_t elem_size)
{
    size_t new_capacity = *capacity;
    void *new_data;
    size_t old_mem_size;

    new_capacity += (new_capacity + 2) / 2;
    new_data = malloc(new_capacity * elem_size);
    if (!new_data)
        throw_error(ERROR_NO_MEMORY);
    old_mem_size = *capacity * elem_size;
    memcpy(new_data, data, old_mem_size);
    free(data);
    *capacity = new_capacity;
    return new_data;
}

int map_add(t_map* map, t_point* data, size_t width)
{
    t_point **new_data;

    if(!map->width)
        map->width = width;
    else if(map->width != width)
        throw_error(INVALID_MAP);
    if (map->height >= map->height_capacity)
    {
        new_data = (t_point**)reallocate(map->data, &map->height_capacity, sizeof(t_point*));
        if (!new_data)
            throw_error(ERROR_NO_MEMORY);
        map->data = new_data;
    }
    map->data[map->height++] = data;
    return 0;
}

int read_map(const int fd, t_map *map)
{
    char *line;
    char **split_lines;

    while (get_next_line(fd, &line))
    {
        if (!(split_lines = ft_strsplit(line, ' ')))
            throw_error(INVALID_MAP);
        parse_line(split_lines, map);
    }

    int x_offset = (int)(-map->width/2)*X_UNIT;
    int y_offset = (int)(-map->height/2)*Y_UNIT;
    int z_offset = (int)(-(map->max_z - map->min_z)/2);
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            map->data[i][j].color = get_default_color(map->data[i][j].z, map);
            map->data[i][j].x += x_offset;
            map->data[i][j].y += y_offset;
            map->data[i][j].z += z_offset;
        }
    }
    return 0;
}

