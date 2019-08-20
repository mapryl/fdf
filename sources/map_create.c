/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:48:20 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:13:55 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"
#include "map.h"
#include "../libft/includes/get_next_line.h"
#include <limits.h>
#include "supporting_functions.h"
#include "errors.h"
#include "../includes/map_create_misc.h"

void	map_create(t_map *map)
{
	map->data = NULL;
	map->height_capacity = 0;
	map->height = 0;
	map->width = 0;
	map->max_z = INT_MIN;
	map->min_z = INT_MAX;
}

void	*reallocate(void *data, size_t *capacity, size_t elem_size)
{
	size_t	new_capacity;
	void	*new_data;
	size_t	old_mem_size;

	new_capacity = *capacity;
	new_capacity += (new_capacity + 2) / 2;
	new_data = malloc(new_capacity * elem_size);
	if (!new_data)
		throw_error(ERROR_NO_MEMORY);
	old_mem_size = *capacity * elem_size;
	memcpy(new_data, data, old_mem_size);
	free(data);
	*capacity = new_capacity;
	return (new_data);
}

int		map_add(t_map *map, t_point *data, size_t width)
{
	t_point **new_data;

	if (!map->width)
		map->width = width;
	else if (map->width != width)
		throw_error(INVALID_MAP);
	if (map->height >= map->height_capacity)
	{
		new_data = (t_point**)reallocate(map->data,
				&map->height_capacity, sizeof(t_point*));
		if (!new_data)
			throw_error(ERROR_NO_MEMORY);
		map->data = new_data;
	}
	map->data[map->height++] = data;
	return (0);
}
