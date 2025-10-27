#include "vector.h"
#include <stdlib.h>

//creates a new vector
t_vec3	*scale_vector(t_vec3 *vec, double scale_by)
{
	t_vec3	*new_vec;

	new_vec = create_vector(vec->x, vec->y, vec->z);
	if (!new_vec)
		return (NULL);
	new_vec->x = vec->x * scale_by;
	new_vec->y = vec->y * scale_by;
	new_vec->z = vec->z * scale_by;
	return (new_vec);
}

t_vec3	*vector_sum(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3	*new_vec;

	new_vec = create_vector(vec1->x + vec2->x,
		vec1->y + vec2->y, vec1->z + vec2->z);
	if (!new_vec)
		return (NULL);
	return (new_vec);
}

t_vec3	*vector_subtract(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3	*new_vec;

	new_vec = create_vector(vec1->x - vec2->x,
		vec1->y - vec2->y, vec1->z - vec2->z);
	if (!new_vec)
		return (NULL);
	return (new_vec);
}

double	dot_product3(t_vec3 *vec1, t_vec3 *vec2, t_vec3 *vec3)
{
	return (
			vec1->x * vec2->x * vec3->x
		+	vec1->y * vec2->y * vec3->y
		+	vec1->z * vec2->z * vec3->z
	);
}

double	dot_product2(t_vec3 *vec1, t_vec3 *vec2)
{
	return (
			vec1->x * vec2->x
		+	vec1->y * vec2->y
		+	vec1->z * vec2->z
	);
}