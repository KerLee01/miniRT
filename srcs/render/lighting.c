/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_coor	get_normal(t_shape *shape, t_coor hit_point, t_ray *ray)
{
	if (shape->type == SPHERE)
		return (get_sphere_normal((t_sphere *)shape->data, hit_point, ray));
	if (shape->type == PLANE)
		return (get_plane_normal((t_plane *)shape->data, ray));
	return (get_cylinder_normal((t_cylinder *)shape->data, hit_point, ray));
}

int	calculate_lighting(t_data *data, t_shape *shape, t_ray *ray, t_coor hit)
{
	t_coor	v[2];
	double	diff;
	double	intensity;
	t_rgb	c;

	v[0] = get_normal(shape, hit, ray);
	c = get_base_color(shape);
	v[1] = normalization(subtract(data->light.position, hit));
	diff = 0.0;
	if (dot_product(v[0], v[1]) > 0.0 && !in_shadow(data, hit, v[0], v[1]))
		diff = dot_product(v[0], v[1]);
	intensity = data->ambient.ratio + (diff * data->light.bright_ratio);
	if (intensity > 1.0)
		intensity = 1.0;
	return (get_color_int((t_rgb){(int)(c.r * intensity),
		(int)(c.g * intensity), (int)(c.b * intensity)}));
}
