#ifndef FDF_H
#define FDF_H
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#define TEXT_COLOR 0xffffff
#define LINE_COLOR 0xed3000
#define BACKGROUND_COLOR 0x666666

#include <stdio.h>
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft/includes/libft.h"
#include "map.h"

typedef struct t_pos
{
    struct t_pos *pos;

    int pos_x;
    int pos_y;
} s_pos;

typedef struct t_ptr
{
    struct t_pointers *ponters_ptr;

    void *mlx_ptr;
    void *mlx_win;
} s_ptr;

typedef struct t_box
{
    struct t_box *box_ptr;

    s_ptr *pointers;
    s_pos *position;
    char *action_name;
    int button_pressed;
} s_box;

typedef struct t_line
{
    struct t_line *line;

    s_pos *pos_0;
    s_pos *pos_1;
    s_ptr *pointers;
    int color;
    int already_pressed;
} s_line;

int close_key(int key, void *close_param); //Уничтожение окна и выход из программы по нажатию клавиши
int close_mouse(int mousebutton, int x, int y, void *close_param); //Уничтожение окна и выход из программы по нажатию мышью на кнопку
int draw_line(int mousebutton, int x, int y, void *draw_param);
void Draw_Wu(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr, t_color colour);

#endif
