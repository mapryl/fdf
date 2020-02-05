/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:23:02 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:20:41 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define TEXT_COLOR 0xffffff

typedef struct	s_color
{
	int			a;
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	t_color		color;
}				t_point;

#endif
