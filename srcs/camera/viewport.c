#include "rt.h"

void	find_pixel_00(t_camera *cam)
{
	t_coor	screen_center;
	t_coor	top_left_corner;
	t_coor	half_u;
	t_coor	half_v;

	screen_center = addition(cam->origin, cam->forward);
	half_u = divide(cam->viewport_u, 2.0);
	half_v = divide(cam->viewport_v, 2.0);
	top_left_corner = subtract(screen_center, half_u);
	top_left_corner = subtract(top_left_corner, half_v);
	half_u = divide(cam->pixel_delta_u, 2.0);
	half_v = divide(cam->pixel_delta_v, 2.0);
	cam->pixel_00_loc = addition(top_left_corner, half_u);
	cam->pixel_00_loc = addition(cam->pixel_00_loc, half_v);
}

void	calculate_viewport(t_camera *cam)
{
	double	radians;
	double	aspect_ratio;

	radians = cam->fov * (M_PI / 180.0);
	cam->viewport_width = 2.0 * tan(radians / 2.0);
	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	cam->viewport_height = cam->viewport_width / aspect_ratio;
	cam->viewport_u = multiply(cam->right, cam->viewport_width);
	cam->viewport_v = multiply(cam->true_up, -cam->viewport_height);
	cam->pixel_delta_u = divide(cam->viewport_u, WIN_WIDTH);
	cam->pixel_delta_v = divide(cam->viewport_v, WIN_HEIGHT);
	find_pixel_00(cam);
}
