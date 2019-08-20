/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:26:50 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:59:38 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "fdf.h"

void	rotate(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_8)
		fdf->camera.alpha -= 0.05;
	else if (key == NUM_PAD_2)
		fdf->camera.alpha += 0.05;
	else if (key == NUM_PAD_6)
		fdf->camera.beta += 0.05;
	else if (key == NUM_PAD_4)
		fdf->camera.beta -= 0.05;
	else if (key == NUM_PAD_3 || key == NUM_PAD_9)
		fdf->camera.gamma += 0.05;
	else if (key == NUM_PAD_1 || key == NUM_PAD_7)
		fdf->camera.gamma -= 0.05;
	print_window(fdf->map, fdf);
}

void	move(int key, t_fdf *fdf)
{
	if (key == ARROW_LEFT)
		fdf->camera.x_move -= 10;
	else if (key == ARROW_RIGHT)
		fdf->camera.x_move += 10;
	else if (key == ARROW_UP)
		fdf->camera.y_move -= 10;
	else
		fdf->camera.y_move += 10;
	print_window(fdf->map, fdf);
}

void	zoom_in(t_fdf *fdf)
{
	camera_zoom_in(&fdf->camera);
	print_window(fdf->map, fdf);
}

void	zoom_out(t_fdf *fdf)
{
	camera_zoom_out(&fdf->camera);
	print_window(fdf->map, fdf);
}

void	set_iso(t_fdf *fdf)
{
	fdf->camera.is_iso = !fdf->camera.is_iso;
	print_window(fdf->map, fdf);
}
