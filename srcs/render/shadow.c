/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	in_shadow(t_data *data, t_coor hit_point, t_coor norm, t_coor light_dir)
{
	t_shape	*current;
	t_ray	shadow_ray;
	double	t;
	double	dist_to_light;

	dist_to_light = magnitude(subtract(data->light.position, hit_point));
	shadow_ray.origin = addition(hit_point, multiply(norm, EPSILON));
	shadow_ray.direction = light_dir;
	current = data->shape;
	while (current != NULL)
	{
		t = -1.0;
		if (current->type == SPHERE)
			t = hit_sphere((t_sphere *)current->data, &shadow_ray);
		else if (current->type == PLANE)
			t = hit_plane((t_plane *)current->data, &shadow_ray);
		else if (current->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)current->data, &shadow_ray);
		if (t > EPSILON && t < dist_to_light - EPSILON)
			return (1);
		current = current->next;
	}
	return (0);
}
