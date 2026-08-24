#include "main.h"

t_coor addition(t_coor a, t_coor b)
{
	t_coor new;

	new = create_new_coor(0, 0, 0);
	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;

	return new;
}

t_coor subtract(t_coor a, t_coor b)
{
	t_coor new;

	new = create_new_coor(0, 0, 0);
	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;

	return new;
}

t_coor multiply(t_coor vector, double scalar)
{
	t_coor new;

	new = create_new_coor(0, 0, 0);
	new.x = vector.x * scalar;
	new.y = vector.y * scalar;
	new.z = vector.z * scalar;

	return new;
}

t_coor divide(t_coor vector, double scalar)
{
	t_coor new;

	new = create_new_coor(0, 0, 0);
	new.x = vector.x / scalar;
	new.y = vector.y /scalar;
	new.z = vector.z /scalar;

	return new;
}
