#ifndef RT_STRUCTS_H
#define RT_STRUCTS_H

#include "rt_math.h"

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
   t_coor true_up;
   t_coor world_up;

   double viewport_width;
   double viewport_height;
   t_coor viewport_u;
   t_coor viewport_v;
   t_coor pixel_delta_u;
   t_coor pixel_delta_v;
   t_coor pixel_00_loc;
} t_camera;

typedef struct s_sphere
{
    t_coor  center;
    double  radius;
    int     r;
    int     g;
    int     b;
} t_sphere;

typedef enum e_shape_type
{
   SPHERE,
   PLANE, 
   CYLINDER
} t_shape_type;

typedef struct s_shape
{
   t_shape_type type;
   void *data;
   struct s_shape *next;
} t_shape;

typedef struct s_data 
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    
    t_camera *cam;
    t_shape *shape;
} t_data;

#endif
