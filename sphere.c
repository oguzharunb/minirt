#include "objects.h"
#include <stdlib.h>

t_sphere	*create_sphere(double radius, double x, double y, double z)
{
	t_sphere	*sphere;
	t_point3	*center;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	center = create_point(x, y, z);
	if (!center)
	{
		free(sphere);
		return (NULL);
	}
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}