#ifndef RT_MATH_H
# define RT_MATH_H

# include <math.h>

typedef struct s_coor
{
	double	x;
	double	y;
	double	z;
}	t_coor;

/* basic_arith.c */
t_coor	addition(t_coor a, t_coor b);
t_coor	subtract(t_coor a, t_coor b);
t_coor	multiply(t_coor vector, double scalar);
t_coor	divide(t_coor vector, double scalar);

/* adv_arith.c */
double	magnitude(t_coor vector);
double	dot_product(t_coor a, t_coor b);
t_coor	normalization(t_coor vector);
t_coor	cross_product(t_coor a, t_coor b);

/* helper_func.c */
t_coor	create_new_coor(double x, double y, double z);
double	find_square_total(t_coor coor);

#endif
