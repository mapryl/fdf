/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:29:01 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_CONTROLS_H
# define KEYBOARD_CONTROLS_H

# include "fdf.h"

void	rotate(int key, t_fdf *fdf);
void	move(int key, t_fdf *fdf);
void	zoom_in(t_fdf *fdf);
void	zoom_out(t_fdf *fdf);
void	set_iso(t_fdf *fdf);

#endif
