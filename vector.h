#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3 t_point3;

t_vec3	*scale_vector(t_vec3 *vec, double scale_by);
t_vec3	*create_vector(double x, double y, double z);
double	dot_product3(t_vec3 *vec1, t_vec3 *vec2, t_vec3 *vec3);
double	dot_product2(t_vec3 *vec1, t_vec3 *vec2);
t_vec3	*vector_sum(t_vec3 *vec1, t_vec3 *vec2);
t_vec3	*vector_subtract(t_vec3 *vec1, t_vec3 *vec2);

#endif