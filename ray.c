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

/* ray.c dosyası */

void set_ray(t_ray *ray, t_camera *cam, double x, double y, int width, int height)
{
    double u;
    double v;

    u = x / (double)width;
    
    // ESKİ HALİ (Ters Çeviren):
    // v = y / (double)height;

    // YENİ HALİ (DÜZELTME):
    // Y değerini 1'den çıkartarak ters çeviriyoruz (Flip Vertical)
    v = 1.0 - (y / (double)height);

    ray->origin = cam->origin;
    ray->direction = vec_sub(
        vec_add(vec_add(cam->lower_left, vec_mul(cam->horizontal, u)),
        vec_mul(cam->vertical, v)),
        cam->origin);
}