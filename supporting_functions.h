/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting_functions.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:06:14 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPPORTING_FUNCTIONS_H
# define SUPPORTING_FUNCTIONS_H

# include "graphics.h"

void	ft_swap(int *a, int *b);
int		pack_argb(const t_color col);
int		ft_isnumber(const char *str);
void	throw_error(char *str);

#endif
