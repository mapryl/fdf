/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:18:39 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:01:48 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map.h"
#include "rotate.h"
#include "supporting_functions.h"
#include "errors.h"
#include "../minilibx_macos/mlx.h"
#include "draw_misc.h"

void	draw_between(int steep, const t_point *p1, const t_point *p2,
		t_fdf *fdf_image)
{
	float	gradient;
	float	y;
	t_point	curr;

	curr = *p1;
	gradient = (float)(p2->y - p1->y) / (float)(p2->x - p1->x);
	y = (float)p1->y + gradient;
	curr.x++;
	while (curr.x <= p2->x - 1)
	{
		curr.y = (int)y;
		draw_pixel(steep, curr, fdf_image, get_color(curr, *p1,
					*p2, 1 - (y - (int)y)));
		curr.y += 1;
		draw_pixel(steep, curr, fdf_image, get_color(curr, *p1,
					*p2, y - (int)y));
		y += gradient;
		curr.x++;
	}
}

void	draw_wu(t_point dot1, t_point dot2, t_fdf *fdf_image)
{
	t_point	delta;
	t_point	tmp;
	int		steep;

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
	draw_pixel(steep, dot1, fdf_image,
			get_color(dot1, dot1, dot2, 1));
	draw_pixel(steep, dot2, fdf_image,
			get_color(dot2, dot1, dot2, 1));
	draw_between(steep, &dot1, &dot2, fdf_image);
}

void	draw_thing(int i, int j, t_fdf *fdf_image)
{
	t_map	*map;
	t_point	p;

	map = fdf_image->map;
	p = transform(&map->data[i][j], fdf_image);
	draw_wu(p, transform(&map->data[i][j + 1], fdf_image), fdf_image);
	draw_wu(p, transform(&map->data[i + 1][j + 1], fdf_image), fdf_image);
	draw_wu(p, transform(&map->data[i + 1][j], fdf_image), fdf_image);
}

void	print_menu(t_fdf *fdf_image)
{
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 73, 25,
			TEXT_COLOR, "PRESS ESC TO EXIT PROGRAM");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 73, 100,
			TEXT_COLOR, "ZOOM IN:                +");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 73, 120,
			TEXT_COLOR, "ZOOM OUT:               -");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 73, 175,
			TEXT_COLOR, "ISOMETRIC/NORMAL:       I");
	mlx_string_put(fdf_image->mlx_ptr, fdf_image->mlx_win, 73, 225,
			TEXT_COLOR, "ROTATE:           NUM 0-9");
}

void print_map(t_map *map, t_fdf *fdf)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		if (i < map->height - 1)
		{
			while (j < map->width - 1)
			{
				draw_thing(i, j, fdf);
				j++;
			}
			draw_wu(transform(&map->data[i][map->width - 1], fdf),
					transform(&map->data[i+1][map->width - 1], fdf), fdf);
		}
		else
			while (j < map->width - 1)
			{
				draw_wu(transform(&map->data[i][j], fdf),
						transform(&map->data[i][j+1], fdf), fdf);
				j++;
			}
		i++;
	}
}

void print_window(t_map *map, t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->mlx_win);
	clear_picture(fdf);
	print_map(map, fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_win, fdf->picture.pic, 250, 0);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_win, fdf->menu_ptr, 0, 0);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_win, fdf->pepe_ptr, 109, WIN_HEIGHT - 109);
	print_menu(fdf);
}