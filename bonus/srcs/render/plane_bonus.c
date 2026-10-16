/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_bonus.h"

double	hit_plane(t_plane *plane, t_ray *ray)
{
	t_coor	p0_minus_origin;
	double	denominator;
	double	numerator;
	double	t;

	denominator = dot_product(ray->direction, plane->forward);
	if (fabs(denominator) < EPSILON)
		return (-1.0);
	p0_minus_origin = subtract(plane->point, ray->origin);
	numerator = dot_product(p0_minus_origin, plane->forward);
	t = numerator / denominator;
	if (t > EPSILON)
		return (t);
	return (-1.0);
}

t_coor	get_plane_normal(t_plane *pl, t_ray *ray)
{
	if (dot_product(ray->direction, pl->forward) > 0.0)
		return (multiply(pl->forward, -1.0));
	return (pl->forward);
}
