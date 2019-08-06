#include "fdf.h"
#include "keys.h"

int close_key(int key, void *close_param)
{
    s_box *tmp = (s_box *)close_param;

    if (key == MAIN_PAD_ESC)
    {
        mlx_destroy_window(tmp->pointers->mlx_ptr, tmp->pointers->mlx_win); //нужно ли уничтожать картинку?
        exit(1);
    }
    return (0);
}

int close_mouse(int mousebutton, int x, int y, void *close_param)
{
    s_box *tmp = (s_box *)close_param;
    if (mousebutton == MOUSE_LEFT_BUTTON &&
        tmp->position->pos_x < x &&
        tmp->position->pos_y < y &&
        tmp->position->pos_x + 50 > x &&
        tmp->position->pos_y + 25 > y)
    {
        mlx_destroy_window(tmp->pointers->mlx_ptr, tmp->pointers->mlx_win); //нужно ли уничтожать картинку?
        exit (1);
    }
    return (0);
}

int draw_line(int mousebutton, int x, int y, void *draw_param)
{
    s_line *tmp = (s_line *) draw_param;
    if (mousebutton == MOUSE_LEFT_BUTTON &&
        x < WIN_WIDTH && x > 200 &&
        y < WIN_HEIGHT && y > 0) {
        if (tmp->already_pressed == 0) {
            tmp->pos_0->pos_x = x;
            tmp->pos_0->pos_y = y;
            tmp->already_pressed = 1;
        } else if (tmp->already_pressed == 1) {
            tmp->pos_1->pos_x = x;
            tmp->pos_1->pos_y = y;
            Draw_Wu((tmp->pos_0->pos_x),
                    (tmp->pos_0->pos_y),
                    (tmp->pos_1->pos_x),
                    (tmp->pos_1->pos_y),
                    (tmp->pointers->mlx_ptr),
                    (tmp->pointers->mlx_win), 255);
            tmp->already_pressed = 0;

        }
    }
    return (0);
}
