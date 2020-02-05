/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:48:20 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:16:22 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_create_misc.h"
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
#include "line.h"

void	map_center(t_map *map)
{
	t_point	offset;
	size_t	i;
	size_t	j;

	offset.x = (int)(-map->width / 2) * X_UNIT;
	offset.y = (int)(-map->height / 2) * Y_UNIT;
	offset.z = (int)(-(map->max_z - map->min_z) / 2);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->data[i][j].color = get_default_color(map->data[i][j].z, map);
			map->data[i][j].x += offset.x;
			map->data[i][j].y += offset.y;
			map->data[i][j].z += offset.z;
			j++;
		}
		i++;
	}
}

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int		read_map(const int fd, t_map *map)
{
	char *line;
	char **split_lines;

	while (get_next_line(fd, &line))
	{
		if (!(split_lines = ft_strsplit(line, ' ')))
			throw_error(INVALID_MAP);
		parse_line(split_lines, map);
		free(line);
		free_split(split_lines);
	}
	if (map->width < 2 || map->height < 2)
		throw_error(INVALID_MAP);
	map_center(map);
	return (0);
}
