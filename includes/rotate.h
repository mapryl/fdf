/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:01:43 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:47:56 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATE_H
# define ROTATE_H
# include "fdf.h"
# include "graphics.h"

void		rotate_x(int *y, int *z, double alpha);
t_point		transform(const t_point *p, const t_fdf *fdf);

#endif
