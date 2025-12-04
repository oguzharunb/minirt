#ifndef RAY_H

#define RAY_H
#include "vector.h"

typedef struct s_ray {
	t_point3	*point;
	t_vec3		*vec;
}	t_ray;


t_ray *create_ray(t_point3 *point, t_vec3 *vec);
t_ray *init_ray();
t_point3	*ray_at(t_ray *ray, double t);
t_ray *set_ray(t_ray *ray, int i, int j);
void print_ray(t_ray *ray);
#endif