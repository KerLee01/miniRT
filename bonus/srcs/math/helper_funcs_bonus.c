#include "rt_math_bonus.h"

t_coor create_new_coor(double x, double y, double z)
{
	t_coor new;

	new.x = x;
	new.y = y;
	new.z = z;
	return new;
}

double find_square_total(t_coor coor)
{
	double total;

	total = 0;
	total = (coor.x * coor.x) + (coor.y * coor.y) + (coor.z * coor.z);

	return total;
}
