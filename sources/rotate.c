/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:57:34 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rotate.h"

void		rotate_x(int *y, int *z, double alpha)
{
	int	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

static void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

t_point		transform(const t_point *p, const t_fdf *fdf)
{
	t_point tmp;

	tmp = *p;
	tmp.x *= fdf->camera.zoom;
	tmp.y *= fdf->camera.zoom;
	tmp.z *= fdf->camera.zoom;
	rotate_x(&tmp.y, &tmp.z, fdf->camera.alpha);
	rotate_y(&tmp.x, &tmp.z, fdf->camera.beta);
	rotate_z(&tmp.x, &tmp.y, fdf->camera.gamma);
	if (fdf->camera.is_iso)
		iso(&tmp.x, &tmp.y, tmp.z);
	tmp.x += fdf->camera.x_move;
	tmp.y += fdf->camera.y_move;
	return (tmp);
}
