#ifndef GRAPHICS_H
#define GRAPHICS_H

#define WIN_WIDTH 1500
#define WIN_HEIGHT 800

#define TEXT_COLOR 0xffffff

typedef struct
{
    short a;
    short r;
    short g;
    short b;
} t_color;

typedef struct point
{
    int x;
    int y;
    int z;
    t_color color;
} t_point;

#endif
