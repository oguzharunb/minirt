/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:18:41 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 11:38:47 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_UTILS_H
# define LIGHTING_UTILS_H

# include "vector.h"

typedef struct s_shade
{
	t_vec3	p;
	t_vec3	n;
	t_vec3	light_pos;
	double	ambient;
	double	intensity;
}			t_shade;

int			color_scale(int rgb, double k);
// int	lambert_shade(int base_rgb, t_vec3 p, t_vec3 n, t_vec3 light_pos,
// 		double ambient, double intensity);

int			lambert_shade(int base_rgb, t_shade s);

#endif
