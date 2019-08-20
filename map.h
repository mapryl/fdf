/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:45:18 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdlib.h>
# include "graphics.h"

# define X_UNIT 50
# define Y_UNIT 50
# define Z_UNIT 10

typedef struct	s_line
{
	t_point		*data;
	size_t		width;
	size_t		width_capacity;
}				t_line;

typedef struct	s_map
{
	t_point		**data;
	size_t		height;
	size_t		width;
	size_t		height_capacity;
	int			max_z;
	int			min_z;
}				t_map;

void			map_create(t_map *map);
int				read_map(const int fd, t_map *map);
t_color			get_color(t_point current, t_point start,
		t_point end, float alpha);
t_color			get_default_color(int z, t_map *map);
void			*reallocate(void *data, size_t *capacity, size_t elem_size);
int				map_add(t_map *map, t_point *data, size_t width);

#endif
