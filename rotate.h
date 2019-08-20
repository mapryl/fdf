/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:01:43 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATE_H
# define ROTATE_H
# include "fdf.h"
# include "graphics.h"

void		rotate_x(int *y, int *z, double alpha);
static void	rotate_y(int *x, int *z, double beta);
static void	iso(int *x, int *y, int z);
static void	rotate_z(int *x, int *y, double gamma);
t_point		transform(const t_point *p, const t_fdf *fdf);

#endif
