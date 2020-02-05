/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create_misc.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:48:20 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 15:13:37 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAFICS_PART1_MAP_CREATE_MISC_H
# define GRAFICS_PART1_MAP_CREATE_MISC_H

# include "map.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "fdf.h"
# include "keys.h"
# include <math.h>
# include "keyboard_controls.h"
# include "errors.h"
# include "supporting_functions.h"

void	map_center(t_map *map);
void	free_split(char **split);
int		read_map(const int fd, t_map *map);

#endif
