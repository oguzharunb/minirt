/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:26:21 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 16:26:22 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "camera.h"
# include "vector.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

t_vec3		ray_at(t_ray *ray, double t);
void set_ray(t_ray *ray, t_camera *cam, double x, double y, int width, int height);

#endif
