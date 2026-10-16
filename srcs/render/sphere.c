/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_coor	oc;
	double	abc[3];
	double	discriminant;
	double	t_vals[2];

	oc = subtract(ray->origin, sphere->center);
	abc[0] = dot_product(ray->direction, ray->direction);
	abc[1] = 2.0 * dot_product(oc, ray->direction);
	abc[2] = dot_product(oc, oc) - (sphere->radius * sphere->radius);
	discriminant = (abc[1] * abc[1]) - (4.0 * abc[0] * abc[2]);
	if (discriminant < 0.0)
		return (-1.0);
	t_vals[0] = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t_vals[1] = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (t_vals[0] > EPSILON)
		return (t_vals[0]);
	if (t_vals[1] > EPSILON)
		return (t_vals[1]);
	return (-1.0);
}

t_coor	get_sphere_normal(t_sphere *sp, t_coor hit_point, t_ray *ray)
{
	t_coor	normal;

	normal = subtract(hit_point, sp->center);
	normal = normalization(normal);
	if (dot_product(ray->direction, normal) > 0.0)
		normal = multiply(normal, -1.0);
	return (normal);
}
