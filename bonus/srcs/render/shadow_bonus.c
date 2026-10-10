#include "rt_bonus.h"

int	in_shadow(t_data *data, t_coor hit, t_light *light, t_coor light_dir)
{
	t_shape	*curr;
	t_ray	shadow_ray;
	double	t;
	double	dist;

	dist = sqrt(dot_product(subtract(light->position, hit), 
			subtract(light->position, hit)));
	shadow_ray.origin = addition(hit, multiply(light_dir, 0.001));
	shadow_ray.direction = light_dir;
	curr = data->shape;
	while (curr != NULL)
	{
		t = -1.0;
		if (curr->type == SPHERE)
			t = hit_sphere((t_sphere *)curr->data, &shadow_ray);
		else if (curr->type == PLANE)
			t = hit_plane((t_plane *)curr->data, &shadow_ray);
		else if (curr->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)curr->data, &shadow_ray);
		if (t > 0.001 && t < dist)
			return (1);
		curr = curr->next;
	}
	return (0);
}
