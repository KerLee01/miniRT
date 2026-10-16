/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_arith_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math_bonus.h"

t_coor	addition(t_coor a, t_coor b)
{
	t_coor	new;

	new = create_new_coor(0, 0, 0);
	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_coor	subtract(t_coor a, t_coor b)
{
	t_coor	new;

	new = create_new_coor(0, 0, 0);
	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_coor	multiply(t_coor vector, double scalar)
{
	t_coor	new;

	new = create_new_coor(0, 0, 0);
	new.x = vector.x * scalar;
	new.y = vector.y * scalar;
	new.z = vector.z * scalar;
	return (new);
}

t_coor	divide(t_coor vector, double scalar)
{
	t_coor	new;

	new = create_new_coor(0, 0, 0);
	new.x = vector.x / scalar;
	new.y = vector.y / scalar;
	new.z = vector.z / scalar;
	return (new);
}
