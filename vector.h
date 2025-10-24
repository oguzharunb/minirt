typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3 t_point3;

t_vec3	*scale_vector(t_vec3 *vec, double scale_by);
t_vec3	*create_vector(double x, double y, double z);
t_vec3	*join_vector(t_vec3 *vec1, t_vec3 *vec2);
t_vec3	*append_vector(t_vec3 *vec1, t_vec3 *vec2);