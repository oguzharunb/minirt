#include "vector.h"
#include <stdlib.h>

t_vec3	*create_vector(double x, double y, double z)
{
	t_vec3	*vector;

	vector = malloc(sizeof(vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}