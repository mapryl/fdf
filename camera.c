//
// Created by alina on 12.08.2019.
//

#include "camera.h"
#include "graphics.h"

void camera_create(t_camera* camera)
{
    camera->alpha = 0;
    camera->beta = 0;
    camera->gamma = 0;
    camera->x_move = WIN_WIDTH/2;
    camera->y_move = WIN_HEIGHT/2;
    camera->zoom = 1;
    camera->is_iso = 0;
}

void camera_zoom_in(t_camera* camera)
{
    if(camera->zoom >= 1.0)
        camera->zoom += 0.5;
    else
        camera->zoom += 0.1;
}

void camera_zoom_out(t_camera* camera)
{
    if(camera->zoom >= 1)
        camera->zoom -= 0.5;
    else if( (camera->zoom -= 0.1) < 0.1 )
        camera->zoom = 0.1;
}
