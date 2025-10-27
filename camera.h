#ifndef CAMERA_H
# define CAMERA_H

#include "vector.h"

#define CAMERA_POS_X 12
#define CAMERA_POS_Y 0
#define CAMERA_POS_Z 0
#define CAMERA_DIR_X -1
#define CAMERA_DIR_Y 0
#define CAMERA_DIR_Z 0
#define ASPECT_RATIO 16.0 / 9.0
#define FOV 70

typedef struct	s_camera {
	t_point3	*location;
	t_vec3		*direction;
	double		aspect_ratio;
	double		fov; //[0-180] degree
}	t_camera;

t_camera	*init_camera();

#endif