/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:32:04 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 16:43:27 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define CAMERA_POS_X 12.0
# define CAMERA_POS_Y -10.0
# define CAMERA_POS_Z -5.0

# define FOV 90.0

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	double	viewport_w;
	double	viewport_h;

	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	lower_left;
}			t_camera;

#endif
