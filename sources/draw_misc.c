/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:18:39 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:58:46 by mapryl           ###   ########.fr       */
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
