#include "rt.h"

t_ray generate_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	t_coor pixel_center;
	t_coor x_offset;
	t_coor y_offset;

	x_offset = multiply(cam->pixel_delta_u, (double) x);
	y_offset = multiply(cam->pixel_delta_v, (double) y);

	pixel_center = addition(cam->pixel_00_loc, x_offset);
	pixel_center = addition(pixel_center, y_offset);

	ray.origin = cam->origin;

	ray.direction = subtract(pixel_center, cam->origin);
	ray.direction = normalization(ray.direction);

	return(ray);
}
