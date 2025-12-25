/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:51:45 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 17:23:20 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_UTILS_H
# define SHADING_UTILS_H

# include "objects.h"
# include "ray.h"
# include "vector.h"

t_vec3	sphere_normal(t_sphere *s, t_vec3 p);

t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 p);

#endif
