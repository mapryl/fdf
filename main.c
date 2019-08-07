#include "map.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"

void throw_error();

s_box *crt_box(int x, int y, char *name, void *mlx_ptr, void *mlx_win) //создание бокса
{
    s_box *button_pointer;
    if (!(button_pointer = (s_box *)malloc(sizeof(s_box))))
        return (NULL);
    if (!(button_pointer->position = (s_pos *)malloc(sizeof(s_pos))))
        return (NULL);
    if (!(button_pointer->pointers = (s_ptr *)malloc(sizeof(s_box))))
        return (NULL);
    button_pointer->position->pos_x = x;
    button_pointer->position->pos_y = y;
    button_pointer->button_pressed = 0;
    button_pointer->action_name = ft_strdup(name);
    button_pointer->pointers->mlx_ptr = mlx_ptr;
    button_pointer->pointers->mlx_win = mlx_win;

    return(button_pointer);
}

s_line  *crt_line(void *mlx_ptr, void *mlx_win)
{
    s_line *line;

    if (!(line = (s_line *)malloc(sizeof(s_line))))
        return (NULL);
    if (!(line->pos_0 = (s_pos *)malloc(sizeof(s_pos))))
        return (NULL);
    if (!(line->pos_1 = (s_pos *)malloc(sizeof(s_pos))))
        return (NULL);
    if (!(line->pointers = (s_ptr *)malloc(sizeof(s_pos))))
        return (NULL);
    line->pointers->mlx_win = mlx_win;
    line->pointers->mlx_ptr = mlx_ptr;
    line->color = 255;
    line->already_pressed = 0;

    return (line);
}

static void	iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void project_iso(t_map *map)
{
    for (size_t i = 0; i < map->hight; ++i)
        for (size_t j = 0; j < map->width; ++j)
            iso(&map->data[i][j].x,&map->data[i][j].y, map->data[i][j].z);
}

#define X_ORIGIN 500
#define Y_ORIGIN 200

void init_window(t_map *map)
{
    void *mlx_ptr = mlx_init();
    void *mlx_win = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "TEST WNDW"); //Создаем новое окно

    int menu_width = WIN_WIDTH;
    int menu_height = WIN_HEIGHT;

    //void *mlx_file_img_ptr = mlx_xpm_file_to_image(mlx_ptr, "../xpm_test", &menu_width, &menu_height); //создаем плашку для меню
    //mlx_put_image_to_window(mlx_ptr, mlx_win, mlx_file_img_ptr, 0, 0); //Пихаем плашку в окно

    s_box *close_button = crt_box(23, 25, "CLOSE   : ESC", mlx_ptr, mlx_win); //создаем бокс для кнопки закрытия
    mlx_string_put(mlx_ptr, mlx_win,
                   close_button->position->pos_x,
                   close_button->position->pos_y,
                   TEXT_COLOR,
                   close_button->action_name);

    mlx_string_put(mlx_ptr, mlx_win, 23, 75, TEXT_COLOR, "ZOOM [+]: NUM +");
    mlx_string_put(mlx_ptr, mlx_win, 23, 100, TEXT_COLOR, "ZOOM [-]: NUM -");
    mlx_string_put(mlx_ptr, mlx_win, 23, 150, TEXT_COLOR, "ISOM    : NUM 1");
    mlx_string_put(mlx_ptr, mlx_win, 23, 175, TEXT_COLOR, "NORM    : NUM 2");
    mlx_string_put(mlx_ptr, mlx_win, 23, 225, TEXT_COLOR, "MOVEMENT: MOUSE");

    s_line *test_line = crt_line(mlx_ptr, mlx_win);

    t_color color;
    color.a = 0;
    color.g = 0;
    color.r = 0;
    color.b = 255;

    project_iso(map);

    for (size_t i = 0; i < map->hight; ++i)
    {
        if (i < map->hight - 1)
		{
        	for (size_t j = 0; j < map->width - 1; ++j)
        	{
				Draw_Wu(map->data[i][j].x + X_ORIGIN, map->data[i][j].y + Y_ORIGIN, map->data[i][j + 1].x + X_ORIGIN,
                        map->data[i][j + 1].y + Y_ORIGIN, mlx_ptr, mlx_win, color);
				Draw_Wu(map->data[i][j].x + X_ORIGIN, map->data[i][j].y + Y_ORIGIN, map->data[i + 1][j + 1].x + X_ORIGIN,
                        map->data[i + 1][j + 1].y + Y_ORIGIN, mlx_ptr, mlx_win, color);
                Draw_Wu(map->data[i][j].x + X_ORIGIN, map->data[i][j].y + Y_ORIGIN, map->data[i + 1][j].x + X_ORIGIN,
                        map->data[i + 1][j].y + Y_ORIGIN, mlx_ptr, mlx_win, color);
			}
            Draw_Wu(map->data[i][map->width - 1].x + X_ORIGIN, map->data[i][map->width - 1].y + Y_ORIGIN, map->data[i + 1][map->width - 1].x + X_ORIGIN,
                    map->data[i + 1][map->width - 1].y + Y_ORIGIN, mlx_ptr, mlx_win, color);
		}
        else
		{
			for (size_t j = 0; j < map->width - 1; ++j)
			{
                Draw_Wu(map->data[i][j].x + X_ORIGIN, map->data[i][j].y + Y_ORIGIN, map->data[i][j + 1].x + X_ORIGIN,
                        map->data[i][j + 1].y + Y_ORIGIN, mlx_ptr, mlx_win, color);
			}
		}
	}

    //Draw_Wu(WIN_HEIGHT / 4 , WIN_WIDTH / 4, WIN_HEIGHT / 4 + 10, WIN_WIDTH / 4 + 10, mlx_ptr, mlx_win, 255);
    mlx_key_hook(mlx_win, close_key, NULL);
    mlx_mouse_hook(mlx_win, close_mouse, (void *)close_button);
    mlx_mouse_hook(mlx_win, draw_line, (void *)test_line);

    mlx_loop(mlx_ptr);
}

int main (int argc, const char* argv[])
{
    int fd;
    t_map map;

    if (argc == 2)
    {
        if ((fd = open(argv[1], O_RDONLY)) >= 0)
            throw_error();
        map_create(&map);
        read_map(fd, &map);
        init_window(&map);
    }
    return 0;
}