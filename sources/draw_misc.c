/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:18:39 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:11:06 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map.h"
#include "rotate.h"
#include "supporting_functions.h"
#include "errors.h"
#include "../minilibx_macos/mlx.h"
#include "draw_misc.h"

void	clear_picture(t_fdf *fdf)
{
	ft_memset(fdf->picture.data_address, 0, fdf->picture.pic_size);
}

void	draw_on_img(int argb, t_fdf *fdf, int x, int y)
{
	if (y < 0 || y >= WIN_HEIGHT || x < 0 || x > WIN_WIDTH)
		return ;
	fdf->picture.data_address[(y * WIN_WIDTH + x)] = argb;
}

void	draw_pixel(int steep, t_point curr, t_fdf *fdf_image, t_color color)
{
	int argb;

	argb = pack_argb(color);
	if (!steep)
		draw_on_img(argb, fdf_image, curr.x, curr.y);
	else
		draw_on_img(argb, fdf_image, curr.y, curr.x);
}

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
