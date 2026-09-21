#include "rt.h"
#include "mlx.h"
#include <stdlib.h>

int close_window(t_data *data)
{
    clear_malloc(data);
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == 53) // 53 is ESC on macOS (use 65307 if testing on Linux/Nix)
        close_window(data);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    ft_bzero(&data, sizeof(t_data));
    if (argc != 2)
    {
        write(2, "Error\nUsage: ./miniRT <scene.rt>\n", 33);
        return (1);
    }
    
    parse_scene(argv[1], &data);

    // Initialize Camera Orientation Vectors & Viewport
    gimbal_lock_check(&data.cam);
    find_right_axis(&data.cam);
    find_true_up(&data.cam);
    calculate_viewport(&data.cam);

    // Initialize MiniLibX
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    // Render the scene into the image buffer
    render_scene(&data);

    // MLX Hooks for exiting cleanly
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 2, 1L << 0, key_hook, &data);

    mlx_loop(data.mlx);
    return (0);
}
