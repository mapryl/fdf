/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:18:39 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:25:35 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_ALINA_DRAW_MISC_H
# define FDF_ALINA_DRAW_MISC_H

# include "fdf.h"
# include "map.h"
# include "rotate.h"
# include "supporting_functions.h"
# include "errors.h"
# include "../minilibx_macos/mlx.h"
# include "draw_misc.h"

void	clear_picture(t_fdf *fdf);
void	draw_on_img(int argb, t_fdf *fdf, int x, int y);
void	draw_pixel(int steep, t_point curr, t_fdf *fdf_image, t_color color);
void	draw_between(int steep, const t_point *p1, const t_point *p2,
					t_fdf *fdf_image);
#endif
