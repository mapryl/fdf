#ifndef LINE_H
#define LINE_H

#include "map.h"
void line_create(t_line* vec);
int line_add(t_line* line, int x, int y, int z);
void parse_line(char **split_line, t_map *map);

#endif
