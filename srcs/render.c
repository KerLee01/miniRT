#include "rt.h"
//#include "mlx.h"

/*
void render_scene(t_data *data)
{
   	t_shape *current;
	t_ray current_ray;
	double t;

   	current = data->shape;
	t = 0;
	while(current != NULL)
	{
		if(current->type == SPHERE)
		{
			t = hit_sphere((t_sphere *)current->data, &current_ray);
		}
		else
			(void)t;
		current = current->next;
	}

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
*/
