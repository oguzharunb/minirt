/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:53:10 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 12:59:09 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
