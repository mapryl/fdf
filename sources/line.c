/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:32:44 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:48:46 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"
#include "supporting_functions.h"
#include "../libft/includes/libft.h"
#include "errors.h"

void	line_create(t_line *vec)
{
	vec->data = NULL;
	vec->width_capacity = 0;
	vec->width = 0;
}

int		line_add(t_line *line, int x, int y, int z)
{
	t_point *new_data;
	t_point point;

	if (line->width >= line->width_capacity)
	{
		new_data = (t_point*)reallocate(line->data, &line->width_capacity,
					sizeof(t_point));
		if (!new_data)
			throw_error(ERROR_NO_MEMORY);
		line->data = new_data;
	}
	point.x = x;
	point.y = y;
	point.z = z;
	line->data[line->width++] = point;
	return (0);
}

void	parse_line(char **split_line, t_map *map)
{
	t_line	line;
	int		i;
	int		map_num;

	line_create(&line);
	i = 0;
	while (*split_line)
	{
		if (ft_isnumber(*split_line) == -1)
			throw_error(INVALID_SYMB_IN_MAP);
		map_num = ft_atoi(*split_line) * Z_UNIT;
		line_add(&line, i * X_UNIT, map->height * Y_UNIT, map_num);
		if (map_num > map->max_z)
			map->max_z = map_num;
		if (map_num < map->min_z)
			map->min_z = map_num;
		split_line++;
		i++;
	}
	map_add(map, line.data, line.width);
}
