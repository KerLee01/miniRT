#include "rt.h"

int	in_shadow(t_data *data, t_coor hit_point, t_coor light_dir)
{
	t_shape	*current;
	t_ray	shadow_ray;
	double	t;
	double	dist_to_light;
	t_coor	v_light;

	v_light = subtract(data->light.position, hit_point);
	dist_to_light = sqrt(dot_product(v_light, v_light));
	shadow_ray.origin = addition(hit_point, multiply(light_dir, 0.001));
	shadow_ray.direction = light_dir;
	current = data->shape;
	while (current != NULL)
	{
		t = -1.0;
		if (current->type == SPHERE)
			t = hit_sphere((t_sphere *)current->data, &shadow_ray);
		else if (current->type == PLANE)
			t = hit_plane((t_plane *)current->data, &shadow_ray);
		else if (current->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)current->data, &shadow_ray);
		if (t > 0.001 && t < dist_to_light)
			return (1);
		current = current->next;
	}
	return (0);
}
