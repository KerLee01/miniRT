#ifndef RT_H
#define RT_H

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define EPSILON 1e-4

#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "libft.h"
#include "rt_math.h"
#include "rt_structs.h"

#include "parser.h"

// camera
void gimbal_lock_check(t_camera *cam);
void find_right_axis(t_camera *cam);
void find_true_up(t_camera *cam);

void find_pixel_00(t_camera *cam);
void calculate_viewport(t_camera *cam);

t_ray generate_ray(t_camera *cam, int x, int y);
void render_scene(t_data *data);

// mlx.c
void my_mlx_pixel_put(t_data *data, int x, int y, int color);

// sphere.c
double hit_sphere(t_sphere *sphere, t_ray *ray);

// plane.c
double hit_plane(t_plane *plane, t_ray *ray);

// cylinder.c
double hit_cylinder(t_cylinder *cy, t_ray *ray);

#endif
