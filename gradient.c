/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:18:12 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

t_color	get_default_color(int z, t_map *map)
{
	double	percentage;
	t_color	color;

	percentage = percent(map->min_z, map->max_z, z);
	color.a = 0;
	color.b = 255;
	color.r = 0;
	if (percentage < 0.2)
		color.g = 0;
	else if (percentage < 0.4)
	{
		color.b = 254;
		color.g = 117;
		color.r = 31;
	}
	else if (percentage < 0.6)
	{
		color.g = 144;
		color.r = 30;
	}
	else if (percentage < 0.8)
		color.g = 191;
	else
		color.g = 255;
	return (color);
}

short	get_light(int start, int end, double percentage)
{
	return ((short)((1 - percentage) * start + percentage * end));
}

t_color	get_color(t_point current, t_point start, t_point end, float alpha)
{
	t_color	new_color;
	double	percentage;

	new_color.a = 0;
	if (current.color.r == end.color.r && current.color.b == end.color.b &&
		current.color.g == end.color.g)
	{
		new_color = current.color;
		new_color.a = (short)((1.0 - alpha) * 255);
		return (new_color);
	}
	percentage = percent(start.x, end.x, current.x);
	new_color.r = get_light(start.color.r, end.color.r, percentage);
	new_color.g = get_light(start.color.g, end.color.g, percentage);
	new_color.b = get_light(start.color.b, end.color.b, percentage);
	new_color.a = (short)((1.0 - alpha) * 255);
	return (new_color);
}
