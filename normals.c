/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:41:19 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 12:49:58 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec3  sphere_normal(t_sphere *sp, t_vec3 p)
{
    return (vec_normalize(vec_sub(p, sp->center)));
}

t_vec3 plane_normal(t_plane *pl)
{
    return (vec_normalize(pl->normal));
}

t_vec3 cylinder_normal(t_cylinder *cy, t_vec3 p)
{
    t_vec3 v;
    double proj;
    t_vec3 radial;
    double half;

    v = vec_sub(p, cy->center);
    proj = vec_dot(v, cy->axis);
    radial = vec_sub(v, vec_mul(cy->axis, proj));
    if (cy->height > 0.0)
    {
        half = cy->height * 0.5;
        if (fabs(proj - half) < 1e-3)
            return (cy->axis);
        if (fabs(proj + half) < 1e-3)
            return (vec_mul(cy->axis, -1.0));
    }
    return (vec_normalize(radial));
}

void    orient_normal(t_vec3 *n, t_ray *ray)
{
    if (vec_dot(*n, ray->direction) > 0.0)
        *n = vec_mul(*n, -1.0);
}

t_vec3 get_normal(t_hit *hit, t_vec3 p)
{
    if (hit->type == HIT_SPHERE)
        return (sphere_normal((t_sphere *)hit->obj, p));
    else if (hit->type == HIT_PLANE)
        return (plane_normal((t_plane *)hit->obj));
    else
        return (cylinder_normal((t_cylinder *)hit->obj, p));
    
}