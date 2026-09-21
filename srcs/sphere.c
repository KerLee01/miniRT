 #include "rt.h"

double hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_coor oc;
	double a;
	double b;
	double c;
	double discriminant;
	double t1;
	double t2;

	oc = subtract(ray->origin, sphere->center);
	a = dot_product(ray->direction, ray->direction);
	b = 2.0 * dot_product(oc, ray->direction);
	c = dot_product(oc, oc) - (sphere->radius * sphere->radius);
	discriminant  = (b * b) - (4.0 * a * c);
	if(discriminant < 0.0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if(t1 > 0.001)
		return t1;
	if(t2 > 0.001)
		return t2;
	return (-1.0);
}
