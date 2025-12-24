/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:53:10 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 13:07:28 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-4

static int	clamp255(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

int	rgb_to_int(t_rgb c)
{
	int	r;
	int	g;
	int	b;

	r = clamp255(c.r);
	g = clamp255(c.g);
	b = clamp255(c.b);
	return ((r << 16) | (g << 8) | b);
}

int	get_obj_color(t_hit *hit)
{
	if (hit->type == HIT_SPHERE)
		return (rgb_to_int(((t_sphere *)hit->obj)->color));
	else if (hit->type == HIT_PLANE)
		return (rgb_to_int(((t_plane *)hit->obj)->color));
	else
		return (rgb_to_int(((t_cylinder *)hit->obj)->color));
}

int	is_in_shadow_scene(t_scene *scene, t_vec3 p, t_vec3 n, t_vec3 light_pos)
{
	t_ray	shadow_ray;
	t_hit	hit;
	t_vec3	to_light;
	double	dist;

	to_light = vec_sub(light_pos, p);
	dist = vec_length(to_light);
	if (dist <= EPS)
		return (0);
	shadow_ray.origin = vec_add(p, vec_mul(n, EPS));
	shadow_ray.direction = vec_mul(to_light, 1.0 / dist);
	if (!scene_closest_hit(scene, &shadow_ray, &hit))
		return (0);
	if (hit.t > EPS && hit.t < dist - EPS)
		return (1);
	return (0);
}
