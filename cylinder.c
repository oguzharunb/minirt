/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:56:36 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 16:59:44 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include <math.h>
#include <stdlib.h>

typedef struct s_cy_vars
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discr;
	double	t1;
	double	t2;
	double	min_t;
}			t_cy_vars;

int	hit_disk(t_ray *ray, t_plane pl, double radius, double *t)
{
	double	denom;
	double	t_temp;
	t_vec3	p;
	t_vec3	v;

	denom = vec_dot(ray->direction, pl.normal);
	if (fabs(denom) < 1e-6)
		return (0);
	t_temp = vec_dot(vec_sub(pl.point, ray->origin), pl.normal) / denom;
	if (t_temp < 1e-4)
		return (0);
	p = vec_add(ray->origin, vec_mul(ray->direction, t_temp));
	v = vec_sub(p, pl.point);
	if (vec_dot(v, v) <= radius * radius)
	{
		*t = t_temp;
		return (1);
	}
	return (0);
}

static void	check_body_hit(t_cylinder *cy, t_ray *ray, t_cy_vars *v)
{
	double	dot_r_ax;
	double	dot_oc_ax;

	dot_r_ax = vec_dot(ray->direction, cy->axis);
	dot_oc_ax = vec_dot(v->oc, cy->axis);
	v->a = vec_dot(ray->direction, ray->direction) - (dot_r_ax * dot_r_ax);
	v->b = 2 * (vec_dot(ray->direction, v->oc) - (dot_r_ax * dot_oc_ax));
	v->c = vec_dot(v->oc, v->oc) - (dot_oc_ax * dot_oc_ax) - (cy->radius
			* cy->radius);
	v->discr = v->b * v->b - 4 * v->a * v->c;
	if (v->discr >= 0)
	{
		v->t1 = (-v->b - sqrt(v->discr)) / (2 * v->a);
		v->t2 = (-v->b + sqrt(v->discr)) / (2 * v->a);
		if (v->t1 > 1e-4 && ((dot_r_ax * v->t1 + dot_oc_ax) >= -cy->height / 2.0
				&& (dot_r_ax * v->t1 + dot_oc_ax) <= cy->height / 2.0))
			if (v->t1 < v->min_t)
				v->min_t = v->t1;
		if (v->t2 > 1e-4 && ((dot_r_ax * v->t2 + dot_oc_ax) >= -cy->height / 2.0
				&& (dot_r_ax * v->t2 + dot_oc_ax) <= cy->height / 2.0))
			if (v->t2 < v->min_t)
				v->min_t = v->t2;
	}
}

static void	check_caps_hit(t_cylinder *cy, t_ray *ray, double *min_t)
{
	t_plane	cap;
	double	t_cap;

	t_cap = 0;
	cap.point = vec_add(cy->center, vec_mul(cy->axis, cy->height / 2.0));
	cap.normal = cy->axis;
	if (hit_disk(ray, cap, cy->radius, &t_cap))
	{
		if (t_cap < *min_t)
			*min_t = t_cap;
	}
	cap.point = vec_sub(cy->center, vec_mul(cy->axis, cy->height / 2.0));
	cap.normal = vec_mul(cy->axis, -1.0);
	if (hit_disk(ray, cap, cy->radius, &t_cap))
	{
		if (t_cap < *min_t)
			*min_t = t_cap;
	}
}

int	hit_cylinder(t_cylinder *cy, t_ray *ray, double *t)
{
	t_cy_vars	v;

	v.min_t = 1e30;
	v.oc = vec_sub(ray->origin, cy->center);
	check_body_hit(cy, ray, &v);
	check_caps_hit(cy, ray, &v.min_t);
	if (v.min_t < 1e30)
	{
		*t = v.min_t;
		return (1);
	}
	return (0);
}
