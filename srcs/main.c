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

void debug_print_scene(t_data *data)
{
    printf("=== SCENE DATA ===\n");
    printf("Ambient: ratio %f, RGB %d,%d,%d\n", data->ambient.ratio, data->ambient.rgb.r, data->ambient.rgb.g, data->ambient.rgb.b);
    printf("Camera: origin %f,%f,%f, FOV %f\n", data->cam.origin.x, data->cam.origin.y, data->cam.origin.z, data->cam.fov);
    printf("Light: pos %f,%f,%f, ratio %f\n", data->light.position.x, data->light.position.y, data->light.position.z, data->light.bright_ratio);
    
    printf("--- SHAPES ---\n");
    t_shape *current = data->shape;
    int count = 1;
    while (current != NULL)
    {
        if (current->type == SPHERE)
        {
            t_sphere *sp = (t_sphere *)current->data;
            printf("%d: SPHERE - center %f,%f,%f, radius %f\n", count, sp->center.x, sp->center.y, sp->center.z, sp->radius);
        }
        else if (current->type == PLANE)
        {
            t_plane *pl = (t_plane *)current->data;
            printf("%d: PLANE - point %f,%f,%f, norm %f,%f,%f\n", count, pl->point.x, pl->point.y, pl->point.z, pl->forward.x, pl->forward.y, pl->forward.z);
        }
        else if (current->type == CYLINDER)
        {
            t_cylinder *cy = (t_cylinder *)current->data;
            printf("%d: CYLINDER - center %f,%f,%f, radius %f, height %f\n", count, cy->center.x, cy->center.y, cy->center.z, cy->radius, cy->height);
        }
        current = current->next;
        count++;
    }
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
