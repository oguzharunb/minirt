/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:26:19 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 18:22:14 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "ray.h"

t_vec3	ray_at(t_ray *ray, double t)
{
	return (vec_add(ray->origin, vec_mul(ray->direction, t)));
}

void	set_ray(t_ray *ray, t_camera *cam, t_ray_h pos)
{
	double	u;
	double	v;

	u = pos.x / (double)pos.width;
	v = 1.0 - (pos.y / (double)pos.height);
	ray->origin = cam->origin;
	ray->direction = vec_sub(vec_add(vec_add(cam->lower_left,
					vec_mul(cam->horizontal, u)), vec_mul(cam->vertical, v)),
			cam->origin);
}
