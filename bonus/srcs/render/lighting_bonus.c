#include "rt_bonus.h"

static int	clamp_channel(double val)
{
	if (val > 255.0)
		return (255);
	if (val < 0.0)
		return (0);
	return ((int)val);
}

t_coor	get_normal(t_shape *shape, t_coor hit_point, t_ray *ray)
{
	if (shape->type == SPHERE)
		return (get_sphere_normal((t_sphere *)shape->data, hit_point, ray));
	if (shape->type == PLANE)
		return (get_plane_normal((t_plane *)shape->data, ray));
	return (get_cylinder_normal((t_cylinder *)shape->data, hit_point, ray));
}

static void	init_ambient(double *rgb, t_rgb base, t_ambient amb)
{
	rgb[0] = base.r * amb.ratio * (amb.rgb.r / 255.0);
	rgb[1] = base.g * amb.ratio * (amb.rgb.g / 255.0);
	rgb[2] = base.b * amb.ratio * (amb.rgb.b / 255.0);
}

static void	add_light_contrib(double *rgb, t_rgb base,
		t_light *l, double diff)
{
	double	factor;

	factor = diff * l->bright_ratio;
	rgb[0] += base.r * factor * (l->rgb.r / 255.0);
	rgb[1] += base.g * factor * (l->rgb.g / 255.0);
	rgb[2] += base.b * factor * (l->rgb.b / 255.0);
}

int	calculate_lighting(t_data *data, t_shape *shape, t_ray *ray, t_coor hit)
{
	t_coor	norm;
	t_coor	l_dir;
	double	rgb[3];
	t_light	*l;

	norm = get_normal(shape, hit, ray);
	init_ambient(rgb, get_base_color(shape), data->ambient);
	l = data->light;
	while (l != NULL)
	{
		l_dir = normalization(subtract(l->position, hit));
		if (dot_product(norm, l_dir) > 0.0 && !in_shadow(data, hit, l, l_dir))
			add_light_contrib(rgb, get_base_color(shape), l,
				dot_product(norm, l_dir));
		l = l->next;
	}
	return (get_color_int((t_rgb){clamp_channel(rgb[0]),
			clamp_channel(rgb[1]), clamp_channel(rgb[2])}));
}
