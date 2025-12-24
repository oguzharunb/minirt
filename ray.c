/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:26:19 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 16:26:20 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "ray.h"
#include <stdio.h>

t_vec3	ray_at(t_ray *ray, double t)
{
	return (vec_add(ray->origin, vec_mul(ray->direction, t)));
}

t_ray	*set_ray(t_ray *ray, t_camera *cam, int i, int j)
{
	double	u;
	double	v;
	t_vec3	p;

	u = (double)i / (SCREEN_WIDTH - 1);
	v = 1.0 - (double)j / (SCREEN_HEIGHT - 1);
	p = vec_add(vec_add(cam->lower_left, vec_mul(cam->horizontal, u)),
			vec_mul(cam->vertical, v));
	ray->origin = cam->origin;
	ray->direction = vec_normalize(vec_sub(p, cam->origin));
	return (ray);
}
