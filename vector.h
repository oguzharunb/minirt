/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:28:23 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 16:28:58 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef t_vec3	t_point3;

t_vec3			vec(double x, double y, double z);

t_vec3			vec_add(t_vec3 a, t_vec3 b);
t_vec3			vec_sub(t_vec3 a, t_vec3 b);
t_vec3			vec_mul(t_vec3 a, double s);

double			vec_dot(t_vec3 a, t_vec3 b);
t_vec3			vec_cross(t_vec3 a, t_vec3 b);
double			vec_length(t_vec3 a);
t_vec3			vec_normalize(t_vec3 a);

#endif
