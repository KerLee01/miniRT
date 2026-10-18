/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define EPSILON 1e-3

# include <strings.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "libft.h"
# include "rt_math.h"
# include "rt_structs.h"

# include "parser.h"

/* camera */
void	gimbal_lock_check(t_camera *cam);
void	find_right_axis(t_camera *cam);
void	find_true_up(t_camera *cam);

void	find_pixel_00(t_camera *cam);
void	calculate_viewport(t_camera *cam);

t_ray	generate_ray(t_camera *cam, int x, int y);

/* render.c */
int		get_color_int(t_rgb rgb);
void	render_scene(t_data *data);
t_rgb	get_base_color(t_shape *shape);
t_coor	get_cylinder_normal(t_cylinder *cy, t_coor hit_point, t_ray *ray);

/* mlx.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		expose_hook(t_data *data);
int		mlx_destroy_display(void *mlx_ptr);

/* sphere.c */
double	hit_sphere(t_sphere *sphere, t_ray *ray);
t_coor	get_sphere_normal(t_sphere *sp, t_coor hit_point, t_ray *ray);

/* plane.c */
double	hit_plane(t_plane *plane, t_ray *ray);
t_coor	get_plane_normal(t_plane *pl, t_ray *ray);

/* cylinder.c */
double	hit_cylinder(t_cylinder *cy, t_ray *ray);
t_coor	get_cylinder_normal(t_cylinder *cy, t_coor hit_point, t_ray *ray);

/* lighting.c */
t_coor	get_normal(t_shape *shape, t_coor hit_point, t_ray *ray);
int		calculate_lighting(t_data *data, t_shape *shape, t_ray *ray,
			t_coor hit_point);

/* shadow.c */
int		in_shadow(t_data *data, t_coor hit_point, t_coor norm,
			t_coor light_dir);

#endif
