/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:53:56 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 17:23:33 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y
			* b.x));
}

double	vec_length(t_vec3 a)
{
	return (sqrt(vec_dot(a, a)));
}

t_vec3	vec_normalize(t_vec3 a)
{
	double	len;

	len = vec_length(a);
	return (vec(a.x / len, a.y / len, a.z / len));
}
