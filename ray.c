#include "ray.h"
#include "camera.h"
#include "minirt.h"
#include <stdlib.h>
#include <stdio.h>

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

t_ray *create_ray(t_point3 *point, t_vec3 *vec)
{
	t_ray *new;

	new = malloc(sizeof(t_ray));
	
	if (!new)
		return (NULL);
	new->point = point;
	new->vec = vec;

	return (new);
}

t_ray *init_ray()
{
	t_point3	*point;
	t_vec3 		*vec;
	t_ray 		*ray;

	point = create_vector(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z);
	if (!point)
		return (NULL);
	vec = create_vector (CAMERA_DIR_X, CAMERA_DIR_Y, CAMERA_DIR_Z);
	if (!vec)
	{
		free(point);
		return (NULL);
	}

	ray = create_ray(point, vec);
	if (!ray)
	{
		free(point);
		free(vec);
		return (NULL);
	}

	return (ray);
}

t_ray *set_ray(t_ray *ray, int i, int j)
{
	ray->vec->x = -12;
	ray->vec->y = (16.0 * j) / SCREEN_WIDTH - 8;
	ray->vec->z = (9.0 * i) / SCREEN_HEIGHT - 4.5;

	return (ray);
}

void print_ray(t_ray *ray)
{
	printf("point: %.2f, %.2f, %.2f, vector: %.2f, %.2f, %.2f\n",
			ray->point->x,
			ray->point->y,
			ray->point->z,

			ray->vec->x,
			ray->vec->y,
			ray->vec->z
			);
}

