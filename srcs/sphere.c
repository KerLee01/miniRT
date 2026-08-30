 #include "rt.h"

int hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_coor oc;
	double a;
	double b;
	double c;
	double discriminant;

	oc = subtract(ray->origin, sphere->center);

	a = dot_product(ray->direction, ray->direction);
	b = 2.0 * dot_product(oc, ray->direction);
	c = dot_product(oc, oc) - (sphere->radius * sphere->radius);

	discriminant  = (b * b) - (4.0 * a * c);
	if(discriminant < 0.0)
		return (0);

	return (1);
}
