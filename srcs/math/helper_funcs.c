/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

t_coor	create_new_coor(double x, double y, double z)
{
	t_coor	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double	find_square_total(t_coor coor)
{
	double	total;

	total = (coor.x * coor.x) + (coor.y * coor.y) + (coor.z * coor.z);
	return (total);
}

int	clamp_channel(double val)
{
	if (val > 255.0)
		return (255);
	if (val < 0.0)
		return (0);
	return ((int)val);
}
