#include "rt.h"
#include "mlx.h"

void render_scene(t_data *data)
{
    int     x;
    int     y;
    double t;
    t_ray   current_ray;
    int     color;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            	current_ray = generate_ray(data->cam, x, y);

            	t = hit_sphere(data->sphere, &current_ray);
		if(t > 0.0)
                	color = 0x00FF0000; 
            	else
                	color = 0x00000000;
            	my_mlx_pixel_put(data, x, y, color);
            	x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
