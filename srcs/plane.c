#include "rt.h"

double hit_plane(t_plane *plane, t_ray *ray)
{
    t_coor  p0_minus_origin;
    double  denominator;
    double  numerator;
    double  t;

    denominator = dot_product(ray->direction, plane->forward);

    if (fabs(denominator) < 1e-6)
        return (-1.0);

    p0_minus_origin = subtract(plane->point, ray->origin);
    numerator = dot_product(p0_minus_origin, plane->forward);

    t = numerator / denominator;

    if (t > 0.001)
        return (t);

    return (-1.0);
}
