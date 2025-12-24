/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:29:16 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 00:53:12 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include <math.h>

int	hit_sphere(t_sphere *s, t_ray *ray, double *t)
{
	const double	EPSILON = 1e-4;
	t_vec3			oc;
	double			a;
	double			half_b;
	double			c;
	double			discriminant;
	double			sqrt_d;
	double			root;

	oc = vec_sub(ray->origin, s->center);
	a = vec_dot(ray->direction, ray->direction);
	if (fabs(a) < 1e-12)
		return (0);
	half_b = vec_dot(oc, ray->direction);
	c = vec_dot(oc, oc) - s->radius * s->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	sqrt_d = sqrt(discriminant);
	root = (-half_b - sqrt_d) / a;
	if (root <= EPSILON)
	{
		root = (-half_b + sqrt_d) / a;
		if (root <= EPSILON)
			return (0);
	}
	*t = root;
	return (1);
}
