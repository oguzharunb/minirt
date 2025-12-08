#include "vector.h"
#include <math.h>
#include <stdlib.h>

t_vec3	vec(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_mul(t_vec3 a, double s)
{
	return (vec(a.x * s, a.y * s, a.z * s));
}

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	));
}
double	vec_length(t_vec3 a)
{
	return (sqrt(vec_dot(a, a)));
}
t_vec3	vec_normalize(t_vec3 a)
{
	double len;

	len = vec_length(a);
	return (vec(a.x / len, a.y / len, a.z / len));
}

