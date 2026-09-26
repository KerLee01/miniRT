#include "rt.h"

double	check_cylinder_bounds(t_cylinder *cy, t_ray *ray, double t)
{
	t_coor	hit_point;
	t_coor	v;
	double	hit_height;

	hit_point = addition(ray->origin, multiply(ray->direction, t));
	v = subtract(hit_point, cy->center);
	hit_height = dot_product(v, cy->forward);
	if (hit_height >= -EPSILON && hit_height <= cy->height + EPSILON)
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
	t_coor	oc;
	t_coor	d_p;
	t_coor	oc_p;
	double	abc[3];
	double	disc;
	double	t_vals[2];

	oc = subtract(ray->origin, cy->center);
	abc[0] = dot_product(ray->direction, cy->forward);
	abc[1] = dot_product(oc, cy->forward);
	d_p = subtract(ray->direction, multiply(cy->forward, abc[0]));
	oc_p = subtract(oc, multiply(cy->forward, abc[1]));
	abc[0] = dot_product(d_p, d_p);
	abc[1] = 2.0 * dot_product(d_p, oc_p);
	abc[2] = dot_product(oc_p, oc_p) - (cy->radius * cy->radius);
	disc = (abc[1] * abc[1]) - (4.0 * abc[0] * abc[2]);
	if (disc < 0.0 || fabs(abc[0]) <= 1e-6)
		return (*closest);
	t_vals[0] = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	t_vals[1] = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	disc = check_cylinder_bounds(cy, ray, t_vals[0]);
	if (disc > EPSILON && disc < *closest)
		*closest = disc;
	disc = check_cylinder_bounds(cy, ray, t_vals[1]);
	if (disc > EPSILON && disc < *closest)
		*closest = disc;
	return (*closest);
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray)
{
	double	closest_t;
	double	t_cap;
	t_coor	top;

	closest_t = 1e30;
	hit_cylinder_body(cy, ray, &closest_t);
	t_cap = hit_cap(cy, ray, cy->center, multiply(cy->forward, -1.0));
	if (t_cap > 0.001 && t_cap < closest_t)
		closest_t = t_cap;
	top = addition(cy->center, multiply(cy->forward, cy->height));
	t_cap = hit_cap(cy, ray, top, cy->forward);
	if (t_cap > 0.001 && t_cap < closest_t)
		closest_t = t_cap;
	if (closest_t < 1e30)
		return (closest_t);
	return (-1.0);
}
