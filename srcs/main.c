#include "rt.h"
#include <stdlib.h>

int main(void)
{
    t_data      data;
    t_camera    cam;
    t_sphere    sphere;

    // 1. HARDCODE THE CAMERA (Looking straight forward)
    cam.origin = create_new_coor(0, 0, 0);
    cam.forward = create_new_coor(0, 0, 1);
    cam.fov = 70.0;
    
    gimbal_lock_check(&cam);
    find_right_axis(&cam);
    find_true_up(&cam);
    calculate_viewport(&cam); 
    // (Assuming calculate_viewport calls find_pixel_00 internally!)

    // 2. HARDCODE THE SPHERE (Placed 10 units away, directly in front of camera)
    sphere.center = create_new_coor(0, 0, 10.0);
    sphere.radius = 2.0; 
    sphere.r = 255; // Red
    sphere.g = 0;
    sphere.b = 0;

    // 3. LINK THEM TO DATA STRUCT
    data.cam = &cam;
    data.sphere = &sphere;

    // 4. MLX INITIALIZATION
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT Test");
    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    // 5. RENDER AND LOOP
    render_scene(&data);
    mlx_loop(data.mlx);
    
    return (0);
}
