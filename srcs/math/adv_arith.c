#include "main.h"

double magnitude(t_coor vector)
{
	double result;
	double square_total;

	result = 0;
	square_total = 0;
	square_total = find_square_total(vector);
	result = sqrt(square_total);
	return result;
}

double dot_product(t_coor a, t_coor b)
{
	double result;

	result = 0;
	result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return result;
}

t_coor normalization(t_coor vector)
{
	t_coor new;
	double mag;

	new = create_new_coor(0, 0, 0);
	mag = magnitude(vector);
	if(mag != 0)
	{
		new.x = vector.x / mag;
		new.y = vector.y / mag;
		new.z = vector.z /mag;
	}

	return new;
}

t_coor cross_product(t_coor a, t_coor b)
{
	t_coor new;

	new = create_new_coor(0, 0, 0);
	new.x = (a.y * b.z) - (a.z * b.y);
	new.y = (a.z * b.x) - (a.x * b.z);
	new.z = (a.x * b.y) - (a.y * b.x);

	return new;
}
