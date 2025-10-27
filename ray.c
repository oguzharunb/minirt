#include "ray.h"
#include <stdlib.h>

//P(t) = A + tb
//A: origin of ray
//b: direction of ray
t_point3	*ray_at(t_ray *ray, double t)
{
	t_vec3		*scaled_vec;
	t_point3	*p;

	scaled_vec = scale_vector(ray->vec, t);
	if (!scaled_vec)
		return (NULL);
	p = vector_sum(scaled_vec, ray->point);
	if (!p)
	{
		free(scaled_vec);
		return (NULL);
	}
	free(scaled_vec);
	return (p);
}