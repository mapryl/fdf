/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:37:49 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:12:10 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"
#include "keys.h"
#include <math.h>
#include "keyboard_controls.h"
#include "errors.h"
#include "supporting_functions.h"
#include "../includes/map_create_misc.h"

int		key_press(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == NUM_PAD_1 || key == NUM_PAD_2 || key == NUM_PAD_3 ||
		key == NUM_PAD_4 || key == NUM_PAD_6 || key == NUM_PAD_7
		|| key == NUM_PAD_8 || key == NUM_PAD_9)
		rotate(key, fdf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_DOWN
	|| key == ARROW_UP)
		move(key, fdf);
	else if (key == MAIN_PAD_PLUS)
		zoom_in(fdf);
	else if (key == MAIN_PAD_MINUS)
		zoom_out(fdf);
	else if (key == KEYBOARD_I)
		set_iso(fdf);
	return (0);
}

void	init_image(t_fdf *fdf)
{
	if (!(fdf->picture.pic = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH,
		WIN_HEIGHT)))
		throw_error(ERROR_NO_MEMORY);
	fdf->picture.data_address = (int *)mlx_get_data_addr(fdf->picture.pic,
	&fdf->picture.bpp, &fdf->picture.line_size, &fdf->picture.endian);
	fdf->picture.pic_size = WIN_WIDTH * WIN_HEIGHT * sizeof(int);
}

int		close_red_x(void)
{
	exit(0);
}

void	init_window(t_map *map)
{
	int		menu_width;
	int		menu_height;
	int		pepe_width;
	int		pepe_height;
	t_fdf	fdf;

	fdf.map = map;
	camera_create(&fdf.camera);
	fdf.mlx_ptr = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
	"3DViewer 99/100");
	fdf.menu_ptr = mlx_xpm_file_to_image(fdf.mlx_ptr,
	"./menu/menu_backgr.xpm", &menu_width, &menu_height);
	fdf.pepe_ptr = mlx_xpm_file_to_image(fdf.mlx_ptr,
	"./menu/glitched.xpm", &pepe_width, &pepe_height);
	init_image(&fdf);
	print_window(map, &fdf);
	mlx_hook(fdf.mlx_win, 17, 0, close_red_x, &fdf);
	mlx_key_hook(fdf.mlx_win, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
}

int		main(int argc, const char *argv[])
{
	int		fd;
	t_map	map;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			throw_error(FILE_ERROR);
		map_create(&map);
		read_map(fd, &map);
		init_window(&map);
	}
	else
		throw_error(USAGE);
	return (0);
}
