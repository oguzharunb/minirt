#include "objects.h"
#include "ray.h"
#include <stdlib.h>

t_sphere	*create_sphere(double radius, double x, double y, double z)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->radius = radius;
	s->center = vec(x, y, z);
	return (s);
}

int	hit_sphere(t_sphere *s, t_ray *ray)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	oc = vec_sub(ray->origin, s->center);
	a = vec_dot(ray->direction, ray->direction);
	half_b = vec_dot(oc, ray->direction);
	c = vec_dot(oc, oc) - s->radius * s->radius;
	discriminant = half_b * half_b - a * c;
	return (discriminant >= 0);
}
