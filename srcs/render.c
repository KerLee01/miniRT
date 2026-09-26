#include "rt.h"
#include "mlx.h"

int get_color_int(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

void render_scene(t_data *data)
{
	int x;
	int y;
   	t_shape *current;
	t_ray ray;
	double t;
	double closest_t;
	int pixel_color;

	y = 0;
	while(y < WIN_HEIGHT)
	{
		x = 0;
		while(x < WIN_WIDTH)
		{
			ray = generate_ray(&data->cam, x, y);
			closest_t = 1e30;
			pixel_color = 0x000000;
			current = data->shape;
			while(current != NULL)
			{
				if(current->type == SPHERE)
				{
					t = hit_sphere((t_sphere *)current->data, &ray);
					if(t > 0.0 && t < closest_t)
					{
						closest_t = t;
						pixel_color = get_color_int(((t_sphere *)current->data)->rgb);
					}
				}
				else if (current->type == PLANE)
				{
				    t = hit_plane((t_plane *)current->data, &ray);
				    if (t > 0.0 && t < closest_t)
				    {
					closest_t = t;
					pixel_color = get_color_int(((t_plane *)current->data)->rgb);
				    }
				}
				else if (current->type == CYLINDER)
				{
				    t = hit_cylinder((t_cylinder *)current->data, &ray);
				    if (t > 0.0 && t < closest_t)
				    {
					closest_t = t;
					pixel_color = get_color_int(((t_cylinder *)current->data)->rgb);
				    }
				}
				current = current->next;
			}
			my_mlx_pixel_put(data, x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
