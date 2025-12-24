/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:31:48 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 12:39:18 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stddef.h>
#define EPS 1e-4

static void	check_spheres(t_scene *scene, t_ray *ray, t_hit *hit)
{
	t_sphere *sp;
	double t;

	sp = scene->spheres;
	while (sp)
	{
		if (hit_sphere(sp, ray, &t) && t > EPS && t < hit->t)
		{
			hit->t = t;
			hit->type = HIT_SPHERE;
			hit->obj = sp;
		}
		sp = sp->next;
	}
}

static void check_planes(t_scene *scene, t_ray *ray, t_hit *hit)
{
    t_plane *pl;
    double  t;
    
    pl = scene->planes;
    while (pl)
    {
        if (hit_plane(pl, ray, &t) && t > EPS && t < hit->t)
        {
            hit->t = t;
            hit->type = HIT_PLANE;
            hit->obj = pl;
        }
        pl = pl->next;
    }
}

static void check_cylinder(t_scene *scene, t_ray *ray, t_hit *hit)
{
    t_cylinder *cy;
    double      t;

    cy = scene->cylinders;
    while (cy)
    {
        if (hit_cylinder(cy, ray, &t) && t > EPS && t < hit->t)
        {
            hit->t = t;
            hit->type = HIT_CYLINDER;
            hit->obj = cy;
        }
        cy = cy->next;
    }
}

int scene_closest_hit(t_scene *scene, t_ray *ray, t_hit *hit)
{
    hit->type = HIT_NONE;
    hit->obj = NULL;
    hit->t = 1e30;
    check_spheres(scene, ray, hit);
    check_planes(scene, ray, hit);
    check_cylinder(scene, ray, hit);
    return (hit->type != HIT_NONE);
}