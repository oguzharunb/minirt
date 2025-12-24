/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:20:05 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 16:23:13 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include <math.h>

/**
 * double_t ile bir kesisime rastladiysak nerede rasladigimizin t sini
 * fonksiyon icerisinden disariya gonderiyoruz
 * bunun sebebi;
 * -kesisim var ama hangi (t)
 * -ayni ray baska objeye de carpiyorsa hangisi daha yakin
 * -golge hesaplarken isik ile obje arasinda baska obje varmi
 */

int	hit_plane(t_plane *pl, t_ray *ray, double *t)
{
	double	denom;
	t_vec3	p0_minus_o;
	double	temp_t;

	denom = vec_dot(pl->normal, ray->direction);
	if (fabs(denom) < 1e-6)
		return (0);
	p0_minus_o = vec_sub(pl->point, ray->origin);
	temp_t = vec_dot(p0_minus_o, pl->normal) / denom;
	if (temp_t < 0)
		return (0);
	*t = temp_t;
	return (1);
}
