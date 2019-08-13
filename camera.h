#ifndef CAMERA_H
#define CAMERA_H

typedef struct  camera
{
    double      alpha;
    double      beta;
    double      gamma;
    int         x_move;
    int         y_move;
    double      zoom;
    int         is_iso;
}               t_camera;

void    camera_create(t_camera* camera);
void    camera_zoom_in(t_camera* camera);
void    camera_zoom_out(t_camera* camera);

#endif