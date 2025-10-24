#include "vector.h"

typedef struct	s_camera {
	t_point3	location;
	t_vec3		direction;
	double		aspect_ratio;
	double		fov;
}	t_camera;