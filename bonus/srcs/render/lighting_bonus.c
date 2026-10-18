/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/10/18 10:47:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_bonus.h"

t_coor	get_normal(t_shape *shape, t_coor hit_point, t_ray *ray)
{
	if (shape->type == SPHERE)
		return (get_sphere_normal((t_sphere *)shape->data, hit_point, ray));
	if (shape->type == PLANE)
		return (get_plane_normal((t_plane *)shape->data, ray));
	return (get_cylinder_normal((t_cylinder *)shape->data, hit_point, ray));
}

static void	init_ambient(double *rgb, t_rgb base, t_ambient amb)
{
	rgb[0] = base.r * amb.ratio * (amb.rgb.r / 255.0);
	rgb[1] = base.g * amb.ratio * (amb.rgb.g / 255.0);
	rgb[2] = base.b * amb.ratio * (amb.rgb.b / 255.0);
}

static void	add_light_contrib(double *rgb, t_rgb base, t_light *l, double diff)
{
	double	factor;

	factor = diff * l->bright_ratio;
	rgb[0] += base.r * factor * (l->rgb.r / 255.0);
	rgb[1] += base.g * factor * (l->rgb.g / 255.0);
	rgb[2] += base.b * factor * (l->rgb.b / 255.0);
}

static void	add_specular(double *rgb, t_light *l, t_coor refl, t_coor v_vec)
{
	double	s_dot;
	double	factor;

	s_dot = dot_product(v_vec, refl);
	if (s_dot <= 0.0)
		return ;
	factor = pow(s_dot, 32) * l->bright_ratio;
	rgb[0] += l->rgb.r * factor;
	rgb[1] += l->rgb.g * factor;
	rgb[2] += l->rgb.b * factor;
}

int	calculate_lighting(t_data *data, t_shape *shape, t_ray *ray, t_coor hit)
{
	t_coor	v[4];
	t_light	*l;
	double	rgb[3];
	t_rgb	base;

	v[0] = get_normal(shape, hit, ray);
	v[2] = normalization(subtract(data->cam.origin, hit));
	base = get_base_color(shape, hit);
	init_ambient(rgb, base, data->ambient);
	l = data->light;
	while (l != NULL)
	{
		v[1] = normalization(subtract(l->position, hit));
		if (dot_product(v[0], v[1]) > 0.0 && !in_shadow(data, hit, v[0], l))
		{
			add_light_contrib(rgb, base, l, dot_product(v[0], v[1]));
			v[3] = normalization(subtract(multiply(v[0],
							2.0 * dot_product(v[0], v[1])), v[1]));
			add_specular(rgb, l, v[3], v[2]);
		}
		l = l->next;
	}
	return (get_color_int((t_rgb){clamp_channel(rgb[0]),
			clamp_channel(rgb[1]), clamp_channel(rgb[2])}));
}
