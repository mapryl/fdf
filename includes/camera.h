/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapryl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:51:58 by mapryl            #+#    #+#             */
/*   Updated: 2019/08/17 17:12:49 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct	s_camera
{
	double		alpha;
	double		beta;
	double		gamma;
	int			x_move;
	int			y_move;
	double		zoom;
	int			is_iso;
}				t_camera;

void			camera_create(t_camera *camera);
void			camera_zoom_in(t_camera *camera);
void			camera_zoom_out(t_camera *camera);

#endif
