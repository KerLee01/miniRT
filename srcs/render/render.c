#include "rt.h"
#include "mlx.h"

t_rgb	get_base_color(t_shape *shape)
{
	if (shape->type == SPHERE)
		return (((t_sphere *)shape->data)->rgb);
	if (shape->type == PLANE)
		return (((t_plane *)shape->data)->rgb);
	return (((t_cylinder *)shape->data)->rgb);
}

int	get_color_int(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

t_shape	*get_closest_shape(t_shape *shapes, t_ray *ray, double *closest_t)
{
	t_shape	*current;
	t_shape	*closest_shape;
	double	t;

	current = shapes;
	closest_shape = NULL;
	while (current != NULL)
	{
		t = -1.0;
		if (current->type == SPHERE)
			t = hit_sphere((t_sphere *)current->data, ray);
		else if (current->type == PLANE)
			t = hit_plane((t_plane *)current->data, ray);
		else if (current->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)current->data, ray);
		if (t > 0.001 && t < *closest_t)
		{
			*closest_t = t;
			closest_shape = current;
		}
		current = current->next;
	}
	return (closest_shape);
}

static void	render_pixel(t_data *data, int x, int y)
{
	t_ray	ray;
	double	closest_t;
	t_shape	*closest_shape;
	t_coor	hit_point;
	int		color;

	ray = generate_ray(&data->cam, x, y);
	closest_t = 1e30;
	closest_shape = get_closest_shape(data->shape, &ray, &closest_t);
	if (closest_shape != NULL)
	{
		hit_point = addition(ray.origin, multiply(ray.direction, closest_t));
		color = calculate_lighting(data, closest_shape, &ray, hit_point);
		my_mlx_pixel_put(data, x, y, color);
	}
	else
		my_mlx_pixel_put(data, x, y, 0x000000);
}

void	render_scene(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			render_pixel(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
