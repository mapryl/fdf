/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:14:03 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:59:57 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx_macos/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "map.h"
# include "camera.h"
# include "graphics.h"

typedef struct		s_picture
{
	int				*pic;
	int				*data_address;
	int				bpp;
	int				line_size;
	int				endian;
	size_t			pic_size;
}					t_picture;

typedef struct		s_fdf
{
	t_map			*map;
	t_camera		camera;
	void			*mlx_ptr;
	void			*mlx_win;
	void			*pepe_ptr;
	void			*menu_ptr;
	t_picture		picture;
}					t_fdf;

void				draw_wu(t_point dot1, t_point dot2, t_fdf *fdf);
void				print_window(t_map *map, t_fdf *fdf);

#endif
