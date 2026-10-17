/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_bonus.h"

int	in_shadow(t_data *data, t_coor hit, t_coor norm, t_light *light)
{
	t_shape	*curr;
	t_ray	shadow_ray;
	double	t;
	double	dist;

	dist = magnitude(subtract(light->position, hit));
	shadow_ray.origin = addition(hit, multiply(norm, EPSILON));
	shadow_ray.direction = normalization(subtract(light->position, hit));
	curr = data->shape;
	while (curr != NULL)
	{
		t = -1.0;
		if (curr->type == SPHERE)
			t = hit_sphere((t_sphere *)curr->data, &shadow_ray);
		else if (curr->type == PLANE)
			t = hit_plane((t_plane *)curr->data, &shadow_ray);
		else if (curr->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)curr->data, &shadow_ray);
		if (t > EPSILON && t < dist - EPSILON)
			return (1);
		curr = curr->next;
	}
	return (0);
}
