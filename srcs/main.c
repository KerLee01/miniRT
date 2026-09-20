#include "rt.h"
//#include "mlx.h"
#include <stdlib.h>

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
    int i;

    // 1. Check for exactly one argument (the .rt file)
    if (argc != 2)
    {
        i = write(2, "Error\nUsage: ./miniRT <scene.rt>\n", 33);
	(void)i;
        return (1);
    }
    ft_bzero(&data, sizeof(t_data));
    // 2. Parse the scene. 
    // (If anything goes wrong, this function will automatically free memory and exit)
    parse_scene(argv[1], &data);

    // 3. Print the data to the terminal to verify your math/parsing
    debug_print_scene(&data);

    // 4. Clean up your shape linked list before a clean exit
    clear_malloc(&data);

    return (0);
}
