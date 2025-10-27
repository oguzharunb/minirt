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

//allocation
t_vec3	*join_vector(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3	*new_vec;

	new_vec = malloc(sizeof(t_vec3));
	if (!new_vec)
		return (NULL);
	new_vec->x = vec1->x + vec2->x;
	new_vec->y = vec1->y + vec2->y;
	new_vec->z = vec1->z + vec2->z;
	return (new_vec);
}

//adds vec2 to vec1 returns vec1
t_vec3	*append_vector(t_vec3 *vec1, t_vec3 *vec2)
{
	vec1->x += vec2->x;
	vec1->y += vec2->y;
	vec1->z += vec2->z;
	return (vec1);
} 