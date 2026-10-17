/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/10/17 23:05:42 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_bonus.h"

double	check_cylinder_bounds(t_cylinder *cy, t_ray *ray, double t)
{
	t_coor	hit_point;
	t_coor	v;
	double	hit_height;

	hit_point = addition(ray->origin, multiply(ray->direction, t));
	v = subtract(hit_point, cy->center);
	hit_height = dot_product(v, cy->forward);
	if (hit_height >= -(cy->height / 2.0) - EPSILON
		&& hit_height <= (cy->height / 2.0) + EPSILON)
		return (t);
	return (-1.0);
}

double	hit_cap(t_cylinder *cy, t_ray *ray, t_coor center, t_coor normal)
{
	t_plane	plane;
	double	t;
	t_coor	hit_point;
	t_coor	v;

	plane.point = center;
	plane.forward = normal;
	t = hit_plane(&plane, ray);
	if (t < EPSILON)
		return (-1.0);
	hit_point = addition(ray->origin, multiply(ray->direction, t));
	v = subtract(hit_point, center);
	if (dot_product(v, v) <= (cy->radius * cy->radius) + EPSILON)
		return (t);
	return (-1.0);
}

double	hit_cylinder_body(t_cylinder *cy, t_ray *ray, double *closest)
{
	t_coor	p[3];
	double	abc[4];
	double	t;

	p[0] = subtract(ray->origin, cy->center);
	p[1] = subtract(ray->direction, multiply(cy->forward,
				dot_product(ray->direction, cy->forward)));
	p[2] = subtract(p[0], multiply(cy->forward,
				dot_product(p[0], cy->forward)));
	abc[0] = dot_product(p[1], p[1]);
	abc[1] = 2.0 * dot_product(p[1], p[2]);
	abc[2] = dot_product(p[2], p[2]) - (cy->radius * cy->radius);
	abc[3] = (abc[1] * abc[1]) - (4.0 * abc[0] * abc[2]);
	if (abc[3] < 0.0 || fabs(abc[0]) <= 1e-6)
		return (*closest);
	t = check_cylinder_bounds(cy, ray, (-abc[1] - sqrt(abc[3]))
			/ (2.0 * abc[0]));
	if (t > EPSILON && t < *closest)
		*closest = t;
	t = check_cylinder_bounds(cy, ray, (-abc[1] + sqrt(abc[3]))
			/ (2.0 * abc[0]));
	if (t > EPSILON && t < *closest)
		*closest = t;
	return (*closest);
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray)
{
	double	closest_t;
	double	t_cap;
	t_coor	top;
	t_coor	bottom;

	closest_t = 1e30;
	closest_t = hit_cylinder_body(cy, ray, &closest_t);
	bottom = addition(cy->center, multiply(cy->forward, -(cy->height / 2.0)));
	t_cap = hit_cap(cy, ray, bottom, multiply(cy->forward, -1.0));
	if (t_cap > EPSILON && t_cap < closest_t)
		closest_t = t_cap;
	top = addition(cy->center, multiply(cy->forward, cy->height / 2.0));
	t_cap = hit_cap(cy, ray, top, cy->forward);
	if (t_cap > EPSILON && t_cap < closest_t)
		closest_t = t_cap;
	if (closest_t < 1e30)
		return (closest_t);
	return (-1.0);
}

t_coor	get_cylinder_normal(t_cylinder *cy, t_coor hit_point, t_ray *ray)
{
	t_coor	v;
	double	proj;
	t_coor	n;
	t_coor	center_hit;

	v = subtract(hit_point, cy->center);
	proj = dot_product(v, cy->forward);
	if (fabs(proj + (cy->height / 2.0)) < EPSILON)
		n = multiply(cy->forward, -1.0);
	else if (fabs(proj - (cy->height / 2.0)) < EPSILON)
		n = cy->forward;
	else
	{
		center_hit = addition(cy->center, multiply(cy->forward, proj));
		n = normalization(subtract(hit_point, center_hit));
	}
	if (dot_product(ray->direction, n) > 0.0)
		n = multiply(n, -1.0);
	return (n);
}
