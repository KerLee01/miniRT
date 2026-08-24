#ifndef STRUCTS_H
#define STRUCTS_H

#include "math.h"

typedef struct s_ray {
    t_coor origin;
    t_coor direction;
} t_ray;

typedef struct s_camera
{
   t_coor origin;
   t_coor forward;
   double fov;
   t_coor right;
   t_coor left;
} t_camera;

#endif
