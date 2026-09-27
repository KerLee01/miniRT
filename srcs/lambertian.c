#include "rt.h"

double calculate_diffuse(t_data *data, t_coor hit_point, t_coor normal)
{
    t_coor  light_dir;
    double  diffuse_factor;

    light_dir = subtract(data->light.position, hit_point);
    light_dir = normalization(light_dir);
    diffuse_factor = dot_product(normal, light_dir);
    if (diffuse_factor < 0.0)
        diffuse_factor = 0.0;
    return (diffuse_factor * data->light.bright_ratio);
}

t_coor get_normal(t_shape *shape, t_coor hit_point, t_ray *ray)
{
	if (shape->type == SPHERE)
		return (get_sphere_normal((t_sphere *)shape->data, hit_point));
	if (shape->type == PLANE)
		return (get_plane_normal((t_plane *)shape->data, ray));
	return (get_cylinder_normal((t_cylinder *)shape->data, hit_point, ray));
}

int calculate_lighting(t_data *data, t_shape *shape, t_ray *ray, t_coor hit_point)
{
	t_coor	normal;
	t_coor	light_dir;
	double	diffuse_factor;
	double	intensity;
	t_rgb	color;

	normal = get_normal(shape, hit_point, ray);
	color = get_base_color(shape);
	
	light_dir = normalization(subtract(data->light.position, hit_point));
	
	diffuse_factor = dot_product(normal, light_dir);
	if (diffuse_factor < 0.0)
		diffuse_factor = 0.0;
		
	intensity = data->ambient.ratio + (diffuse_factor * data->light.bright_ratio);
	if (intensity > 1.0)
		intensity = 1.0;

	return (get_color_int((t_rgb){
		(int)(color.r * intensity),
		(int)(color.g * intensity),
		(int)(color.b * intensity)
	}));
}
