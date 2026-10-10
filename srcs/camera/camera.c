#include "rt.h"

void	gimbal_lock_check(t_camera *cam)
{
	if (cam->forward.y > 0.99 || cam->forward.y < -0.99)
		cam->world_up = create_new_coor(0, 0, 1);
	else
		cam->world_up = create_new_coor(0, 1, 0);
}

void	find_right_axis(t_camera *cam)
{
	cam->right = cross_product(cam->world_up, cam->forward);
	cam->right = normalization(cam->right);
}

void	find_true_up(t_camera *cam)
{
	cam->true_up = cross_product(cam->forward, cam->right);
	cam->true_up = normalization(cam->true_up);
}
