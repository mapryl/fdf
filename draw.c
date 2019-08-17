#include "fdf.h"
#include "map.h"
#include "rotate.h"
#include "supporting_functions.h"
#include "errors.h"

void draw_on_img(int argb, t_fdf *image, int x, int y)
{
	image->data_adress[(y * WIN_WIDTH + x)] = argb;
}


void draw_pixel(int steep, int x, int y,  t_fdf* fdf_image, t_color color)
{
    if (!steep)
    {
        int argb;

        color.a = (color.a - 1) * 255;
        argb = pack_argb(color);
        draw_on_img(argb, fdf_image, x, y);
    }
    else
    {
        int argb;

        color.a = (color.a - 1) * 255;
        argb = pack_argb(color);
	    draw_on_img(argb, fdf_image, y, x);
    }
}

void draw_between(int steep, const t_point* p1, const t_point* p2, const t_point* delta, t_fdf* fdf_image)
{
    float gradient;
    float y;
    t_point curr;

    curr = *p1;

    gradient = (float)(p2->y - p1->y) / (float)(p2->x - p1->x);
    y = (float)p1->y + gradient;
    curr.x++;
    while (curr.x <= p2->x - 1)
    {
        draw_pixel(steep, curr.x, (int)y, fdf_image,  get_color(curr, *p1, *p2, *delta, 1 - (y - (int)y)));
        draw_pixel(steep, curr.x, (int)y + 1, fdf_image,  get_color(curr, *p1, *p2, *delta, 1 - (y - (int)y)));
        y += gradient;
        curr.x++;
    }
}


void Draw_Wu(t_point dot1, t_point dot2,  t_fdf* fdf_image)
{
    t_point delta;
    t_point tmp;
    int steep;

    delta.x = abs(dot1.x - dot2.x);
    delta.y = abs(dot1.y - dot2.y);
    steep = delta.y > delta.x;
    if (steep)
    {
        ft_swap(&dot1.x, &dot1.y);
        ft_swap(&dot2.x, &dot2.y);
        ft_swap(&delta.x, &delta.y);
    }
    if (dot1.x > dot2.x)
    {
        tmp = dot1;
        dot1 = dot2;
        dot2 = tmp;
    }
    draw_pixel(steep, dot1.x, dot1.y, fdf_image, get_color(dot1, dot1, dot2, delta, 0));
    draw_pixel(steep, dot2.x, dot2.y, fdf_image, get_color(dot2, dot1, dot2, delta, 0));
    draw_between(steep, &dot1, &dot2, &delta, fdf_image);
}

void draw_thing(int i, int j, t_fdf* fdf_image)
{
    t_map *map;

    map = fdf_image->map;

    Draw_Wu(transform(&map->data[i][j], fdf_image), transform(&map->data[i][j+1], fdf_image), fdf_image);
    Draw_Wu(transform(&map->data[i][j], fdf_image), transform(&map->data[i+1][j+1], fdf_image), fdf_image);
    Draw_Wu(transform(&map->data[i][j], fdf_image), transform(&map->data[i+1][j], fdf_image), fdf_image);
}

void *init_image(t_fdf *fdf)
{
	if (!(fdf->pic = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		return (NULL);
	fdf->data_adress = (int *)mlx_get_data_addr(fdf->pic, &fdf->bpp, &fdf->line_size, &fdf->endian);

	return(fdf);
}

void print_menu(t_fdf *fdf_image)
{
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 23, 25, TEXT_COLOR, "CLOSE   : ESC");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 23, 75, TEXT_COLOR, "ZOOM [+]: NUM +");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 23, 100, TEXT_COLOR, "ZOOM [-]: NUM -");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 23, 150, TEXT_COLOR, "ISOM    : NUM 1");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 23, 175, TEXT_COLOR, "NORM    : NUM 2");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 23, 225, TEXT_COLOR, "MOVEMENT: MOUSE");
}

void print_map(t_map *map, t_fdf *fdf)
{
    size_t i;
    size_t j;

    int menu_width = 200;
    int menu_height = 1080;

    int pepe_width = 473;
    int pepe_height = 500;

    mlx_clear_window(fdf->mlx_ptr, fdf->mlx_win);

    t_fdf *fdf_image = init_image(fdf);

    i = 0;
    while (i < map->height)
    {
        j = 0;
        if (i < map->height - 1)
        {
            while (j < map->width - 1)
            {
                draw_thing(i, j, fdf_image);
                j++;
            }
            Draw_Wu(transform(&map->data[i][map->width - 1], fdf_image), transform(&map->data[i+1][map->width - 1], fdf_image), fdf_image);
        }
        else
            while (j < map->width - 1)
            {
                Draw_Wu(transform(&map->data[i][j], fdf_image), transform(&map->data[i][j+1], fdf_image), fdf_image);
                j++;
            }
        i++;
    }
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_win, fdf_image->pic, 0, 0);
	void *menu_ptr = mlx_xpm_file_to_image(fdf_image->mlx_ptr, "../xpm_menu", &menu_width, &menu_height);
	void *pepe_ptr = mlx_xpm_file_to_image(fdf_image->mlx_ptr, "/Users/mflannel/Desktop/Fdf1608/pepe.xpm", &pepe_width, &pepe_height);
	mlx_put_image_to_window(fdf_image->mlx_ptr, fdf_image->mlx_win, menu_ptr, 0, 0);
	mlx_put_image_to_window(fdf_image->mlx_ptr, fdf_image->mlx_win, pepe_ptr, 0, 580);
	print_menu(fdf_image);
}