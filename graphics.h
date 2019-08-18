#ifndef GRAPHICS_H
#define GRAPHICS_H

//#define WIN_WIDTH 1920
//#define WIN_HEIGHT 1080

#define WIN_WIDTH 1600
#define WIN_HEIGHT 900

#define TEXT_COLOR 0xffffff

typedef struct
{
    int a;
    int r;
    int g;
    int b;
} t_color;

typedef struct point
{
    int x;
    int y;
    int z;
    t_color color;
} t_point;

#endif
