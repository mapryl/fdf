#ifndef KEYBOARD_CONTROLS_H
#define KEYBOARD_CONTROLS_H

#include "fdf.h"

void rotate(int key, t_fdf *fdf);
void	move(int key, t_fdf *fdf);
void zoom_in(t_fdf *fdf);
void zoom_out(t_fdf *fdf);
void set_iso(t_fdf *fdf);

#endif
