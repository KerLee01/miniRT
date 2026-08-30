#ifndef RT_H
#define RT_H

#define WID_WIDTH 800
#define WIN_HEIGHT 600

#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "rt_math.h"
#include "rt_structs.h"

t_ray generate_ray(t_camera *cam, int x, int y);
void render_scene(t_data *data);

#endif
