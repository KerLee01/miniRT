#include "rt_bonus.h"
#include "mlx.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int expose_hook(t_data *data)
{
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}
