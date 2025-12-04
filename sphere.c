#include "objects.h"
#include "ray.h"
#include <stdio.h>
#include <stdlib.h>

t_sphere	*create_sphere(double radius, double x, double y, double z)
{
	t_sphere	*sphere;
	t_point3	*center;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	center = create_vector(x, y, z);
	if (!center)
	{
		free(sphere);
		return (NULL);
	}
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}

int	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vec3 *oc;
	double a;
	double b;
	double c;
	double discriminant;
	int result;

	oc = vector_subtract(ray->point, sphere->center);
	if (!oc)
		return (-1);
	a = dot_product2(ray->vec, ray->vec);
	b = -2.0 * dot_product2(ray->vec, oc);
	c = dot_product2(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	result = (discriminant >= 0);
	free(oc);
	return (result);
}