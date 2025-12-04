#ifndef OBJECTS_H
# define OBJECTS_H

# include "ray.h"
# include "vector.h"

typedef struct s_sphere
{
	double		radius;
	t_point3	*center;
}				t_sphere;

t_sphere		*create_sphere(double radius, double x, double y, double z);
int				hit_sphere(t_sphere *sphere, t_ray *ray);
#endif