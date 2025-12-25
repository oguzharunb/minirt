/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:29:16 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 17:06:24 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include <math.h>

#define EPS 1e-4

static int	pick_root(double half_b, double a, double sqrt_d, double *t)
{
	double	root;

	root = (-half_b - sqrt_d) / a;
	if (root > EPS)
	{
		*t = root;
		return (1);
	}
	root = (-half_b + sqrt_d) / a;
	if (root > EPS)
	{
		*t = root;
		return (1);
	}
	return (0);
}

int	hit_sphere(t_sphere *s, t_ray *ray, double *t)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	d;

	oc = vec_sub(ray->origin, s->center);
	a = vec_dot(ray->direction, ray->direction);
	if (fabs(a) < 1e-12)
		return (0);
	half_b = vec_dot(oc, ray->direction);
	c = vec_dot(oc, oc) - (s->radius * s->radius);
	d = (half_b * half_b) - (a * c);
	if (d < 0.0)
		return (0);
	return (pick_root(half_b, a, sqrt(d), t));
}
